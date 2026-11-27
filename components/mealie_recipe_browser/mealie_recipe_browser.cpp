#include "mealie_recipe_browser.h"
#include "mealie_style.h"
#include <cstdio>
#include <string>
#include <utility>

namespace esphome::mealie_recipe_browser {
namespace ui = tessera::ui;
namespace st = style;

// Tessera's fonts hold a fixed set of glyphs (packages/core.yaml); anything else is drawn as a box.
// Write vulgar fractions out, turn no-break spaces into spaces and drop characters the font lacks.
static std::string printable(const std::string &in) {
  static const struct { const char *from, *to; } words[] = {
      {"\xC2\xBD", "1/2"}, {"\xC2\xBC", "1/4"}, {"\xC2\xBE", "3/4"},
      {"\xE2\x85\x93", "1/3"}, {"\xE2\x85\x94", "2/3"}, {"\xE2\x85\x95", "1/5"}, {"\xE2\x85\x96", "2/5"},
      {"\xE2\x85\x97", "3/5"}, {"\xE2\x85\x98", "4/5"}, {"\xE2\x85\x99", "1/6"}, {"\xE2\x85\x9A", "5/6"},
      {"\xE2\x85\x9B", "1/8"}, {"\xE2\x85\x9C", "3/8"}, {"\xE2\x85\x9D", "5/8"}, {"\xE2\x85\x9E", "7/8"},
      {"\xC2\xA0", " "}, {"\xE2\x80\xAF", " "}, {"\xE2\x80\x89", " "}};
  std::string out;
  for (size_t i = 0; i < in.size();) {
    const unsigned char lead = static_cast<unsigned char>(in[i]);
    const size_t len = lead < 0x80 ? 1 : lead >= 0xF0 ? 4 : lead >= 0xE0 ? 3 : lead >= 0xC0 ? 2 : 1;
    const std::string ch = in.substr(i, len);
    i += len;
    bool replaced = false;
    for (const auto &w : words)
      if (ch == w.from) { out += w.to; replaced = true; break; }
    if (replaced) continue;
    if (ch == "\n" || ui::covers(ch, tessera::Font::BODY)) out += ch;
  }
  return out;
}

class RecipeBrowserTile : public tessera::Tile {
 public:
  explicit RecipeBrowserTile(MealieRecipeBrowser *plugin) : plugin_(plugin) {}
  void create(const tessera::TileContext &c) override {
    width_ = c.width;
    height_ = c.height;
    tile_ = c.tile;
    parent_ = c.parent;

    title_ = ui::label(c.parent, st::LIST_TITLE_FONT, st::LIST_TITLE_COLOR);
    ui::set_text(title_, plugin_->text("screen_title"));
    lv_obj_set_pos(title_, 0, 0);
    lv_obj_set_size(title_, width_, ui::line_height(st::LIST_TITLE_FONT));

    status_label_ = ui::label(c.parent, st::LIST_STATUS_FONT, st::LIST_STATUS_COLOR);
    lv_obj_set_pos(status_label_, 0, ui::line_height(st::LIST_TITLE_FONT) + ui::px(st::LIST_STATUS_GAP_PX));
    lv_obj_set_size(status_label_, width_, ui::line_height(st::LIST_STATUS_FONT));

    list_top_ = ui::line_height(st::LIST_TITLE_FONT) + ui::line_height(st::LIST_STATUS_FONT) +
                ui::px(st::LIST_STATUS_GAP_PX + st::LIST_TOP_GAP_PX);
    list_ = lv_obj_create(c.parent);
    lv_obj_set_pos(list_, 0, list_top_);
    lv_obj_set_size(list_, width_, height_ - list_top_);
    lv_obj_set_style_bg_opa(list_, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(list_, 0, 0);
    lv_obj_set_style_pad_all(list_, 0, 0);
    lv_obj_set_style_pad_row(list_, ui::px(st::CARD_GAP_PX), 0);
    lv_obj_set_style_pad_column(list_, ui::px(st::CARD_GAP_PX), 0);
    lv_obj_set_scrollbar_mode(list_, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(list_, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_remove_flag(list_, LV_OBJ_FLAG_CLICKABLE);

    content_ = lv_obj_create(list_);
    lv_obj_set_pos(content_, 0, 0);
    lv_obj_set_size(content_, width_, height_ - list_top_);
    lv_obj_set_style_bg_opa(content_, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(content_, 0, 0);
    lv_obj_set_style_pad_all(content_, 0, 0);
    lv_obj_clear_flag(content_, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_remove_flag(content_, LV_OBJ_FLAG_CLICKABLE);

    const int gap = ui::px(st::CARD_GAP_PX);
    const int cols = st::CARD_COLUMNS;
    card_width_ = (width_ - (cols - 1) * gap) / cols;
    card_height_ = ui::px(st::CARD_HEIGHT_PX);
    for (size_t i = 0; i < MAX_VISIBLE_RECIPES; ++i) {
      cards_[i].panel = lv_obj_create(content_);
      lv_obj_set_size(cards_[i].panel, card_width_, card_height_);
      lv_obj_set_pos(cards_[i].panel, (static_cast<int>(i) % cols) * (card_width_ + gap),
                     (static_cast<int>(i) / cols) * (card_height_ + gap));
      lv_obj_set_style_radius(cards_[i].panel, ui::px(st::CARD_RADIUS_PX), 0);
      lv_obj_set_style_bg_color(cards_[i].panel, ui::color(st::CARD_BG_COLOR), 0);
      lv_obj_set_style_bg_opa(cards_[i].panel, LV_OPA_COVER, 0);
      lv_obj_set_style_border_width(cards_[i].panel, st::CARD_BORDER_WIDTH, 0);
      lv_obj_set_style_border_color(cards_[i].panel, ui::color(st::CARD_BORDER_COLOR), 0);
      lv_obj_set_style_pad_all(cards_[i].panel, ui::px(st::CARD_PADDING_PX), 0);
      lv_obj_clear_flag(cards_[i].panel, LV_OBJ_FLAG_SCROLLABLE);
      lv_obj_remove_flag(cards_[i].panel, LV_OBJ_FLAG_CLICKABLE);

      cards_[i].name = ui::label(cards_[i].panel, st::CARD_NAME_FONT, st::CARD_NAME_COLOR);
      lv_obj_set_pos(cards_[i].name, 0, 0);
      lv_obj_set_size(cards_[i].name, card_width_ - 2 * ui::px(st::CARD_PADDING_PX),
                      ui::px(st::CARD_NAME_HEIGHT_PX));
      lv_label_set_long_mode(cards_[i].name, LV_LABEL_LONG_WRAP);

      cards_[i].meta = ui::label(cards_[i].panel, st::CARD_META_FONT, st::CARD_META_COLOR);
      lv_obj_set_pos(cards_[i].meta, 0, ui::px(st::CARD_META_Y_PX));
      lv_obj_set_size(cards_[i].meta, card_width_ - 2 * ui::px(st::CARD_PADDING_PX),
                      ui::px(st::CARD_META_HEIGHT_PX));
    }

    update_cards();
    plugin_->load_recipes();
  }

  void on_tick(uint32_t) override { update_cards(); }

  void on_theme() override {
    ui::set_color(title_, st::LIST_TITLE_COLOR);
    ui::set_color(status_label_, st::LIST_STATUS_COLOR);
    for (auto &card : cards_) {
      ui::set_color(card.name, st::CARD_NAME_COLOR);
      ui::set_color(card.meta, st::CARD_META_COLOR);
    }
  }

  void on_tap() override {
    const tessera::Point p = tessera::tap_point();
    lv_area_t pa;
    lv_obj_get_coords(parent_, &pa);
    const int ax = pa.x1 + p.x;
    const int ay = pa.y1 + p.y;
    const auto &recipes = plugin_->recipes();

    for (size_t i = 0; i < recipes.size() && i < MAX_VISIBLE_RECIPES; ++i) {
      lv_area_t a;
      lv_obj_get_coords(cards_[i].panel, &a);
      if (ax < a.x1 || ax > a.x2 || ay < a.y1 || ay > a.y2) continue;
      if (recipes[i].id.empty()) return;
      plugin_->selected_recipe_id_ = recipes[i].id;
      tessera::open_card(plugin_->plugin_id(), "recipe", "", tile_, recipes[i].name);
      return;
    }
  }

 private:
  struct RecipeCard {
    lv_obj_t *panel = nullptr;
    lv_obj_t *name = nullptr;
    lv_obj_t *meta = nullptr;
  };

  void update_cards() {
    const auto &recipes = plugin_->recipes();
    for (size_t i = 0; i < MAX_VISIBLE_RECIPES; ++i) {
      if (i >= recipes.size()) {
        lv_obj_add_flag(cards_[i].panel, LV_OBJ_FLAG_HIDDEN);
        continue;
      }
      lv_obj_clear_flag(cards_[i].panel, LV_OBJ_FLAG_HIDDEN);
      ui::set_text(cards_[i].name, recipes[i].name);
      char meta[80];
      const uint32_t minutes = (recipes[i].total_seconds + 59) / 60;
      if (minutes > 0 && recipes[i].servings > 0)
        snprintf(meta, sizeof(meta), "%lu min  ·  %.1f %s",
                 static_cast<unsigned long>(minutes), recipes[i].servings, plugin_->text("servings"));
      else if (minutes > 0)
        snprintf(meta, sizeof(meta), "%lu min", static_cast<unsigned long>(minutes));
      else if (recipes[i].servings > 0)
        snprintf(meta, sizeof(meta), "%.1f %s", recipes[i].servings, plugin_->text("servings"));
      else
        meta[0] = 0;
      ui::set_text(cards_[i].meta, meta);
    }

    char count_text[80];
    if (plugin_->status() == "loaded") {
      snprintf(count_text, sizeof(count_text), plugin_->text("recipe_count"),
               static_cast<unsigned>(recipes.size()));
    } else if (plugin_->status() == "partial_results") {
      snprintf(count_text, sizeof(count_text), plugin_->text("partial_count"),
               static_cast<unsigned>(recipes.size()));
    } else if (plugin_->status() == "loading" && !recipes.empty()) {
      snprintf(count_text, sizeof(count_text), plugin_->text("loading_count"),
               static_cast<unsigned>(recipes.size()));
    } else {
      snprintf(count_text, sizeof(count_text), "%s", plugin_->text(plugin_->status().c_str()));
    }
    ui::set_text(status_label_, count_text);

    const size_t rows = (recipes.size() + st::CARD_COLUMNS - 1) / st::CARD_COLUMNS;
    const int gap = ui::px(st::CARD_GAP_PX);
    const int content_height = rows == 0 ? 0 :
        static_cast<int>(rows) * card_height_ + static_cast<int>(rows - 1) * gap;
    lv_obj_set_height(content_, content_height);
    lv_obj_update_layout(content_);
  }

  static constexpr size_t MAX_VISIBLE_RECIPES = 24;
  MealieRecipeBrowser *plugin_;
  int width_ = 0;
  int height_ = 0;
  int tile_ = -1;
  int list_top_ = 0;
  int card_width_ = 0;
  int card_height_ = 0;
  lv_obj_t *title_ = nullptr;
  lv_obj_t *status_label_ = nullptr;
  lv_obj_t *list_ = nullptr;
  lv_obj_t *content_ = nullptr;
  lv_obj_t *parent_ = nullptr;
  RecipeCard cards_[MAX_VISIBLE_RECIPES];
};

class RecipeDetailCard : public tessera::Card {
 public:
  explicit RecipeDetailCard(MealieRecipeBrowser *plugin) : plugin_(plugin) {}
  ~RecipeDetailCard() override {
    if (plugin_->open_card_ == this) plugin_->open_card_ = nullptr;
  }

  void open(const tessera::CardContext &c) override {
    parent_ = c.parent;
    width_ = c.width;
    height_ = c.height;
    plugin_->open_card_ = this;

    meta_ = ui::label(parent_, st::DETAIL_META_FONT, st::DETAIL_META_COLOR);
    lv_obj_set_pos(meta_, 0, 0);
    lv_obj_set_size(meta_, width_, ui::line_height(st::DETAIL_META_FONT));
    ui::set_text(meta_, plugin_->text("detail_loading"));

    const int top = ui::line_height(st::DETAIL_META_FONT) + ui::px(st::DETAIL_META_GAP_PX);
    const int gap = ui::px(st::DETAIL_COLUMN_GAP_PX);
    const int col = (width_ - gap) / 2;

    ingredients_title_ = ui::label(parent_, st::DETAIL_HEADING_FONT, st::DETAIL_HEADING_COLOR);
    lv_obj_set_pos(ingredients_title_, 0, top);
    lv_obj_set_size(ingredients_title_, col, ui::line_height(st::DETAIL_HEADING_FONT));
    ui::set_text(ingredients_title_, plugin_->text("ingredients"));

    instructions_title_ = ui::label(parent_, st::DETAIL_HEADING_FONT, st::DETAIL_HEADING_COLOR);
    lv_obj_set_pos(instructions_title_, col + gap, top);
    lv_obj_set_size(instructions_title_, col, ui::line_height(st::DETAIL_HEADING_FONT));
    ui::set_text(instructions_title_, plugin_->text("instructions"));

    const int body_y = top + ui::line_height(st::DETAIL_HEADING_FONT) +
                       ui::px(st::DETAIL_HEADING_GAP_PX);
    const int body_h = height_ - body_y;
    ingredients_ = ui::label(parent_, st::DETAIL_TEXT_FONT, st::DETAIL_TEXT_COLOR);
    lv_obj_set_pos(ingredients_, 0, body_y);
    lv_obj_set_size(ingredients_, col, body_h);
    lv_label_set_long_mode(ingredients_, LV_LABEL_LONG_WRAP);

    instructions_ = ui::label(parent_, st::DETAIL_TEXT_FONT, st::DETAIL_TEXT_COLOR);
    lv_obj_set_pos(instructions_, col + gap, body_y);
    lv_obj_set_size(instructions_, col, body_h);
    lv_label_set_long_mode(instructions_, LV_LABEL_LONG_WRAP);

    if (!plugin_->load_recipe(plugin_->selected_recipe_id_))
      ui::set_text(meta_, plugin_->text("detail_failed"));
  }

  void answer(JsonObjectConst m) {
    if ((m["re"] | 0u) != plugin_->detail_request_id_) return;
    if (!(m["ok"] | false)) {
      ui::set_text(meta_, plugin_->text("detail_failed"));
      return;
    }

    JsonObjectConst r = m["result"].as<JsonObjectConst>();
    if (r.isNull()) {
      ui::set_text(meta_, plugin_->text("detail_failed"));
      return;
    }

    const uint32_t seconds = r["time"] | 0u;
    const uint32_t minutes = (seconds + 59) / 60;
    const float servings = r["serv"] | 0.0f;
    char meta[96];
    meta[0] = 0;
    if (minutes > 0 && servings > 0)
      snprintf(meta, sizeof(meta), "%lu min  ·  %.1f %s",
               static_cast<unsigned long>(minutes), servings, plugin_->text("servings"));
    else if (minutes > 0)
      snprintf(meta, sizeof(meta), "%lu min", static_cast<unsigned long>(minutes));
    else if (servings > 0)
      snprintf(meta, sizeof(meta), "%.1f %s", servings, plugin_->text("servings"));
    ui::set_text(meta_, meta);

    std::string ing;
    for (int i = 0; i < st::DETAIL_INGREDIENT_LINES; ++i) {
      char key[8];
      snprintf(key, sizeof(key), "i%d", i);
      const char *line = r[key] | "";
      if (!*line) continue;
      if (!ing.empty()) ing += st::INGREDIENT_SEPARATOR;
      ing += st::INGREDIENT_BULLET;
      ing += printable(line);
    }

    std::string steps;
    int n = 0;
    for (int i = 0; i < st::DETAIL_STEPS; ++i) {
      char key[8];
      snprintf(key, sizeof(key), "s%d", i);
      const char *txt = r[key] | "";
      if (!*txt) continue;
      if (!steps.empty()) steps += st::STEP_SEPARATOR;
      char number[12];
      snprintf(number, sizeof(number), "%d. ", ++n);
      steps += number;
      steps += printable(txt);
    }

    ui::set_text(ingredients_, ing.empty() ? plugin_->text("no_ingredients") : ing);
    ui::set_text(instructions_, steps.empty() ? plugin_->text("no_instructions") : steps);
  }

  void on_theme() override {
    ui::set_color(meta_, st::DETAIL_META_COLOR);
    ui::set_color(ingredients_title_, st::DETAIL_HEADING_COLOR);
    ui::set_color(instructions_title_, st::DETAIL_HEADING_COLOR);
    ui::set_color(ingredients_, st::DETAIL_TEXT_COLOR);
    ui::set_color(instructions_, st::DETAIL_TEXT_COLOR);
  }

 private:
  MealieRecipeBrowser *plugin_;
  lv_obj_t *parent_ = nullptr;
  lv_obj_t *meta_ = nullptr;
  lv_obj_t *ingredients_title_ = nullptr;
  lv_obj_t *instructions_title_ = nullptr;
  lv_obj_t *ingredients_ = nullptr;
  lv_obj_t *instructions_ = nullptr;
  int width_ = 0;
  int height_ = 0;
};

void MealieRecipeBrowser::setup() {
  add_tile("browser", [this]() { return new RecipeBrowserTile(this); });
  add_card("recipe", [this]() { return new RecipeDetailCard(this); });
}

bool MealieRecipeBrowser::load_recipes() {
  recipes_.clear();
  recipe_pages_received_ = 0;
  recipe_page_failures_ = 0;
  for (size_t i = 0; i < RECIPE_PAGE_COUNT; ++i) {
    recipe_request_ids_[i] = 0;
    recipe_page_received_[i] = false;
  }

  status_ = "loading";
  bool sent_any = false;
  for (size_t i = 0; i < RECIPE_PAGE_COUNT; ++i) {
    JsonDocument request;
    request["ask"] = "fetch:recipes";
    request["data"]["page"] = static_cast<unsigned>(i + 1);
    recipe_request_ids_[i] = tessera::send(this, request.as<JsonObjectConst>());
    if (recipe_request_ids_[i]) {
      sent_any = true;
    } else {
      recipe_page_received_[i] = true;
      ++recipe_pages_received_;
      ++recipe_page_failures_;
    }
  }

  if (recipe_pages_received_ == RECIPE_PAGE_COUNT) {
    status_ = sent_any ? "service_error" : "request_failed";
  }
  return sent_any;
}

bool MealieRecipeBrowser::load_recipe(const std::string &slug) {
  if (slug.empty()) return false;
  JsonDocument request;
  request["ask"] = "fetch:recipe";
  request["data"]["slug"] = slug;
  detail_request_id_ = tessera::send(this, request.as<JsonObjectConst>());
  return detail_request_id_ != 0;
}

void MealieRecipeBrowser::on_message(JsonObjectConst message) {
  const uint32_t received_id = message["re"] | 0u;
  if (open_card_) open_card_->answer(message);

  for (size_t page = 0; page < RECIPE_PAGE_COUNT; ++page) {
    if (recipe_request_ids_[page] != received_id || recipe_page_received_[page]) continue;

    recipe_page_received_[page] = true;
    ++recipe_pages_received_;
    if (!(message["ok"] | false)) {
      ++recipe_page_failures_;
    } else {
      JsonObjectConst result = message["result"].as<JsonObjectConst>();
      JsonArrayConst items = result["items"].as<JsonArrayConst>();
      if (items.isNull()) {
        ++recipe_page_failures_;
      } else {
        for (JsonObjectConst item : items) {
          if (recipes_.size() >= MAX_RECIPES) break;
          RecipeSummary recipe;
          recipe.id = item["id"] | "";
          recipe.name = printable(std::string(item["name"] | ""));
          if (recipe.name.empty() || recipe.id.empty()) continue;
          recipe.total_seconds = item["seconds"] | 0u;
          recipe.servings = item["servings"] | 0.0f;
          recipes_.push_back(std::move(recipe));
        }
      }
    }

    if (recipe_pages_received_ == RECIPE_PAGE_COUNT) {
      if (recipes_.empty())
        status_ = recipe_page_failures_ ? "service_error" : "no_results";
      else
        status_ = recipe_page_failures_ ? "partial_results" : "loaded";
    }
    return;
  }
}
}  // namespace esphome::mealie_recipe_browser
