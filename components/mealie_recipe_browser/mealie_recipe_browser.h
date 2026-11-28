#pragma once
#include <string>
#include <vector>
#include "esphome/core/component.h"
#include "esphome/components/smart_display/plugin_api.h"

namespace esphome::mealie_recipe_browser {
class RecipeDetailCard;
struct RecipeSummary {
  std::string id;  // Mealie recipe slug, used by the HA detail service.
  std::string name;
  uint32_t total_seconds = 0;
  float servings = 0;
};
class MealieRecipeBrowser : public Component, public tessera::Plugin {
 public:
  void setup() override;
  float get_setup_priority() const override { return setup_priority::DATA; }
  bool load_recipes();
  bool load_page(size_t page);
  bool load_recipe(const std::string &slug);
  const std::vector<RecipeSummary> &recipes() const { return recipes_; }
  const std::string &status() const { return status_; }
  void on_message(JsonObjectConst message) override;
  void on_interval(uint32_t now_ms) override;
 private:
  friend class RecipeDetailCard;
  friend class RecipeBrowserTile;
  static constexpr size_t MEALIE_PAGES_PER_VIEW = 5;
  static constexpr size_t MAX_RECIPES = 20;
  std::string status_ = "not_loaded";
  std::string selected_recipe_id_;
  std::vector<RecipeSummary> recipes_;
  std::vector<RecipeSummary> recipe_page_items_[MEALIE_PAGES_PER_VIEW];
  uint32_t recipe_request_ids_[MEALIE_PAGES_PER_VIEW]{};
  bool recipe_page_received_[MEALIE_PAGES_PER_VIEW]{};
  size_t recipe_pages_received_ = 0;
  size_t recipe_page_failures_ = 0;
  size_t next_mealie_page_index_ = 0;
  uint32_t request_started_ms_ = 0;
  void send_next_recipe_page();
  void publish_recipe_pages();
  size_t current_page_ = 1;
  size_t total_pages_ = 1;
  size_t total_recipes_ = 0;
  uint32_t detail_request_id_ = 0;
  RecipeDetailCard *open_card_ = nullptr;
};
}  // namespace esphome::mealie_recipe_browser
