#pragma once
#include <string>
#include <vector>
#include "esphome/core/component.h"
#include "esphome/components/smart_display/plugin_api.h"

namespace esphome::mealie_recipe_browser {
class RecipeDetailCard;
struct RecipeSummary {
  std::string id;
  std::string name;
  uint32_t total_seconds = 0;
  float servings = 0;
};
class MealieRecipeBrowser : public Component, public tessera::Plugin {
 public:
  void setup() override;
  float get_setup_priority() const override { return setup_priority::DATA; }
  void set_config_entry_id(const std::string &value) { config_entry_id_ = value; }
  bool load_recipes();
  bool load_recipe(const std::string &recipe_id);
  const std::vector<RecipeSummary> &recipes() const { return recipes_; }
  const std::string &status() const { return status_; }
  void on_message(JsonObjectConst message) override;
 private:
  friend class RecipeDetailCard;
  friend class RecipeBrowserTile;
  std::string config_entry_id_;
  std::string status_ = "not_loaded";
  std::string selected_recipe_id_;
  std::vector<RecipeSummary> recipes_;
  uint32_t request_id_ = 0;
  uint32_t detail_request_id_ = 0;
  RecipeDetailCard *open_card_ = nullptr;
};
}  // namespace esphome::mealie_recipe_browser
