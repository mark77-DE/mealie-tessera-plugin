#pragma once
#include <string>
#include <vector>
#include "esphome/core/component.h"
#include "esphome/components/smart_display/plugin_api.h"

namespace esphome::mealie_recipe_browser {
class RecipeDetailCard;
struct RecipeSummary {
  std::string id;  // Mealie recipe slug, used by the detail fetch.
  std::string name;
  uint32_t total_seconds = 0;
  float servings = 0;
};
class MealieRecipeBrowser : public Component, public tessera::Plugin {
 public:
  void setup() override;
  float get_setup_priority() const override { return setup_priority::DATA; }
  bool load_recipes();
  bool load_recipe(const std::string &slug);
  const std::vector<RecipeSummary> &recipes() const { return recipes_; }
  const std::string &status() const { return status_; }
  void on_message(JsonObjectConst message) override;
 private:
  friend class RecipeDetailCard;
  friend class RecipeBrowserTile;
  static constexpr size_t RECIPE_PAGE_SIZE = 5;
  static constexpr size_t RECIPE_PAGE_COUNT = 5;
  static constexpr size_t MAX_RECIPES = 24;
  std::string status_ = "not_loaded";
  std::string selected_recipe_id_;
  std::vector<RecipeSummary> recipes_;
  uint32_t recipe_request_ids_[RECIPE_PAGE_COUNT]{};
  bool recipe_page_received_[RECIPE_PAGE_COUNT]{};
  size_t recipe_pages_received_ = 0;
  size_t recipe_page_failures_ = 0;
  uint32_t detail_request_id_ = 0;
  RecipeDetailCard *open_card_ = nullptr;
};
}  // namespace esphome::mealie_recipe_browser
