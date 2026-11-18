#include "mealie_recipe_browser.h"

#include <cstdio>
#include <string>
#include <utility>

namespace esphome::mealie_recipe_browser {

using tessera::Font;
namespace ui = tessera::ui;

class RecipeBrowserTile : public tessera::Tile {
 public:
  explicit RecipeBrowserTile(MealieRecipeBrowser *plugin) : plugin_(plugin) {}

  void create(const tessera::TileContext &context) override {
    width_ = context.width;
    height_ = context.height;

    title_ = ui::label(context.parent, Font::TITLE, theme::INK);
    ui::set_text(title_, plugin_->text("screen_title"));
    lv_obj_set_pos(title_, 0, 0);
    lv_obj_set_size(title_, width_, ui::line_height(Font::TITLE));

    query_ = context.options["query"] | "sauce";
    query_label_ = ui::label(context.parent, Font::BODY, theme::MUTED);
    ui::set_text(query_label_, tessera::fill(plugin_->text("searching_for"), "n", query_));
    lv_obj_set_pos(query_label_, 0, ui::line_height(Font::TITLE) + ui::px(8));
    lv_obj_set_size(query_label_, width_, ui::line_height(Font::BODY));

    status_label_ = ui::label(context.parent, Font::BODY, theme::MUTED);
    lv_obj_set_pos(status_label_, 0, ui::line_height(Font::TITLE) + ui::line_height(Font::BODY) + ui::px(18));
    lv_obj_set_size(status_label_, width_, ui::line_height(Font::BODY));

    const int top = ui::line_height(Font::TITLE) + ui::line_height(Font::BODY) + ui::px(52);
    const int row_height = (height_ - top) / 6;
    for (size_t i = 0; i < rows_.size(); ++i) {
      rows_[i].name = ui::label(context.parent, Font::BODY_LARGE, theme::INK);
      rows_[i].meta = ui::label(context.parent, Font::BODY, theme::MUTED);
      lv_obj_set_pos(rows_[i].name, 0, top + static_cast<int>(i) * row_height);
      lv_obj_set_size(rows_[i].name, width_, ui::line_height(Font::BODY_LARGE));
      lv_obj_set_pos(rows_[i].meta, 0, top + static_cast<int>(i) * row_height + ui::line_height(Font::BODY_LARGE));
      lv_obj_set_size(rows_[i].meta, width_, ui::line_height(Font::BODY));
    }

    plugin_->search(query_);
  }

  void on_tick(uint32_t) override {
    ui::set_text(status_label_, plugin_->text(plugin_->status().c_str()));
    const auto &recipes = plugin_->recipes();
    for (size_t i = 0; i < rows_.size(); ++i) {
      if (i >= recipes.size()) {
        ui::set_text(rows_[i].name, "");
        ui::set_text(rows_[i].meta, "");
        continue;
      }
      ui::set_text(rows_[i].name, recipes[i].name);
      char meta[64];
      const uint32_t minutes = (recipes[i].total_seconds + 59) / 60;
      if (recipes[i].servings > 0) {
        snprintf(meta, sizeof(meta), "%lu min  ·  %.1f", static_cast<unsigned long>(minutes), recipes[i].servings);
        ui::set_text(rows_[i].meta, meta);
      } else {
        snprintf(meta, sizeof(meta), "%lu min", static_cast<unsigned long>(minutes));
        ui::set_text(rows_[i].meta, meta);
      }
    }
  }

  void on_theme() override {
    ui::set_color(title_, theme::INK);
    ui::set_color(query_label_, theme::MUTED);
    ui::set_color(status_label_, theme::MUTED);
    for (auto &row : rows_) {
      ui::set_color(row.name, theme::INK);
      ui::set_color(row.meta, theme::MUTED);
    }
  }

 private:
  struct Row {
    lv_obj_t *name = nullptr;
    lv_obj_t *meta = nullptr;
  };

  MealieRecipeBrowser *plugin_;
  int width_ = 0;
  int height_ = 0;
  std::string query_;
  lv_obj_t *title_ = nullptr;
  lv_obj_t *query_label_ = nullptr;
  lv_obj_t *status_label_ = nullptr;
  Row rows_[6];
};

void MealieRecipeBrowser::setup() {
  add_tile("browser", [this]() { return new RecipeBrowserTile(this); });
}

bool MealieRecipeBrowser::search(const std::string &terms) {
  if (config_entry_id_.empty()) {
    status_ = "missing_config";
    return false;
  }

  JsonDocument request;
  request["ask"] = "call_service:mealie.get_recipes";
  request["data"]["config_entry_id"] = config_entry_id_;
  request["data"]["search_terms"] = terms;
  request["data"]["result_limit"] = 3;

  request_id_ = tessera::send(this, request.as<JsonObjectConst>());
  status_ = request_id_ ? "loading" : "request_failed";
  return request_id_ != 0;
}

void MealieRecipeBrowser::on_message(JsonObjectConst message) {
  if ((message["re"] | 0u) != request_id_) return;

  if (!(message["ok"] | false)) {
    recipes_.clear();
    status_ = "service_error";
    return;
  }

  JsonObjectConst result = message["result"].as<JsonObjectConst>();
  JsonArrayConst items = result["recipes"]["items"].as<JsonArrayConst>();
  if (items.isNull()) items = result["items"].as<JsonArrayConst>();

  recipes_.clear();
  for (JsonObjectConst item : items) {
    RecipeSummary recipe;
    recipe.id = item["recipe_id"] | "";
    recipe.name = item["name"] | "";
    recipe.total_seconds = item["total_time_seconds"] | 0u;
    recipe.servings = item["recipe_servings"] | 0.0f;
    if (!recipe.name.empty()) recipes_.push_back(std::move(recipe));
  }

  status_ = recipes_.empty() ? "no_results" : "loaded";
}

}  // namespace esphome::mealie_recipe_browser
