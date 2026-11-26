#include "mealie_recipe_browser.h"
#include <cstdio>
#include <string>
#include <utility>
namespace esphome::mealie_recipe_browser {
using tessera::Font;
namespace ui = tessera::ui;

// Tessera's fonts hold a fixed set of glyphs (packages/core.yaml); anything else is drawn as a box.
// Write vulgar fractions out ("½" -> "1/2"), turn no-break spaces into spaces and drop what the font lacks.
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
    if (ch == "\n" || ui::covers(ch, tessera::Font::BODY)) out += ch;  // a character the font lacks is left out
  }
  return out;
}

class RecipeBrowserTile : public tessera::Tile {
 public:
  explicit RecipeBrowserTile(MealieRecipeBrowser *plugin) : plugin_(plugin) {}
  void create(const tessera::TileContext &c) override {
    width_ = c.width; height_ = c.height; tile_ = c.tile; parent_ = c.parent;
    title_ = ui::label(c.parent, Font::TITLE, theme::INK);
    ui::set_text(title_, plugin_->text("screen_title"));
    lv_obj_set_pos(title_, 0, 0); lv_obj_set_size(title_, width_, ui::line_height(Font::TITLE));

    status_label_ = ui::label(c.parent, Font::BODY, theme::MUTED);
    lv_obj_set_pos(status_label_, 0, ui::line_height(Font::TITLE) + ui::px(6));
    lv_obj_set_size(status_label_, width_, ui::line_height(Font::BODY));

    list_top_ = ui::line_height(Font::TITLE) + ui::line_height(Font::BODY) + ui::px(24);
    list_ = lv_obj_create(c.parent);
    lv_obj_set_pos(list_, 0, list_top_);
    lv_obj_set_size(list_, width_, height_ - list_top_);
    lv_obj_set_style_bg_opa(list_, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(list_, 0, 0);
    lv_obj_set_style_pad_all(list_, 0, 0);
    lv_obj_set_style_pad_row(list_, ui::px(14), 0);
    lv_obj_set_style_pad_column(list_, ui::px(14), 0);
    // Five recipe cards fit in two rows. Keep this container non-scrollable so
    // taps reach the tile's touch guard and RecipeBrowserTile::on_tap().
    lv_obj_set_scrollbar_mode(list_, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(list_, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_remove_flag(list_, LV_OBJ_FLAG_CLICKABLE);  // let taps reach on_tap()

    content_ = lv_obj_create(list_);
    lv_obj_set_pos(content_, 0, 0);
    lv_obj_set_size(content_, width_, height_ - list_top_);
    lv_obj_set_style_bg_opa(content_, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(content_, 0, 0);
    lv_obj_set_style_pad_all(content_, 0, 0);
    lv_obj_clear_flag(content_, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_remove_flag(content_, LV_OBJ_FLAG_CLICKABLE);
    const int gap = ui::px(8);
    card_width_ = (width_ - 2 * gap) / 3;
    card_height_ = ui::px(86);
    for (size_t i = 0; i < MAX_VISIBLE_RECIPES; ++i) {
      cards_[i].panel = lv_obj_create(content_);
      lv_obj_set_size(cards_[i].panel, card_width_, card_height_);
      lv_obj_set_pos(cards_[i].panel, static_cast<int>(i % 3) * (card_width_ + gap),
                     static_cast<int>(i / 3) * (card_height_ + gap));
      lv_obj_set_style_radius(cards_[i].panel, ui::px(12), 0);
      lv_obj_set_style_bg_color(cards_[i].panel, ui::color(theme::CARD), 0);
      lv_obj_set_style_bg_opa(cards_[i].panel, LV_OPA_COVER, 0);
      lv_obj_set_style_border_width(cards_[i].panel, 1, 0);
      lv_obj_set_style_border_color(cards_[i].panel, ui::color(theme::LINE), 0);
      lv_obj_set_style_pad_all(cards_[i].panel, ui::px(10), 0);
      lv_obj_clear_flag(cards_[i].panel, LV_OBJ_FLAG_SCROLLABLE);
      lv_obj_remove_flag(cards_[i].panel, LV_OBJ_FLAG_CLICKABLE);

      cards_[i].name = ui::label(cards_[i].panel, Font::BODY_LARGE, theme::INK);
      lv_obj_set_pos(cards_[i].name, 0, 0);
      lv_obj_set_size(cards_[i].name, card_width_ - ui::px(20), ui::px(46));
      lv_label_set_long_mode(cards_[i].name, LV_LABEL_LONG_WRAP);

      cards_[i].meta = ui::label(cards_[i].panel, Font::BODY, theme::MUTED);
      lv_obj_set_pos(cards_[i].meta, 0, ui::px(54));
      lv_obj_set_size(cards_[i].meta, card_width_ - ui::px(20), ui::px(22));
    }
    update_cards();
    plugin_->load_recipes();
  }
  void on_tick(uint32_t) override {
    ui::set_text(status_label_, plugin_->text(plugin_->status().c_str()));
    update_cards();
  }
  void on_theme() override {
    ui::set_color(title_, theme::INK);
    ui::set_color(status_label_, theme::MUTED);
    for (auto &card : cards_) {
      ui::set_color(card.name, theme::INK);
      ui::set_color(card.meta, theme::MUTED);
    }
  }
  void on_tap() override {
  const tessera::Point p = tessera::tap_point();
  // tap_point() is relative to the tile's parent; convert to absolute glass pixels
  lv_area_t pa;
  lv_obj_get_coords(parent_, &pa);
  const int ax = pa.x1 + p.x, ay = pa.y1 + p.y;
  printf("[Mealie tap] tile=(%d,%d) abs=(%d,%d) parent=(%d,%d)-(%d,%d)\n",
         p.x, p.y, ax, ay, pa.x1, pa.y1, pa.x2, pa.y2);
  const auto &recipes = plugin_->recipes();
  for (size_t i = 0; i < recipes.size() && i < MAX_VISIBLE_RECIPES; ++i) {
    lv_area_t a;
    lv_obj_get_coords(cards_[i].panel, &a);
    printf("[Mealie tap]   card %u: (%d,%d)-(%d,%d)\n", static_cast<unsigned>(i), a.x1, a.y1, a.x2, a.y2);
    if (ax < a.x1 || ax > a.x2 || ay < a.y1 || ay > a.y2) continue;
    if (recipes[i].id.empty()) break;
    plugin_->selected_recipe_id_ = recipes[i].id;
    printf("[Mealie tap] opening recipe index=%u id=%s\n", static_cast<unsigned>(i), recipes[i].id.c_str());
    fflush(stdout);

    tessera::open_card(plugin_->plugin_id(), "recipe", "", tile_, recipes[i].name);
    return;
  }
  printf("[Mealie tap] no card under the finger\n");
  fflush(stdout);
}
 private:
  struct RecipeCard { lv_obj_t *panel = nullptr; lv_obj_t *name = nullptr; lv_obj_t *meta = nullptr; };
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
      snprintf(count_text, sizeof(count_text), "%u / 5 Rezepte",
               static_cast<unsigned>(recipes.size()));
    } else if (plugin_->status() == "loading") {
      snprintf(count_text, sizeof(count_text), "Lade Rezepte …");
    } else {
      snprintf(count_text, sizeof(count_text), "%s (%u / 5)",
               plugin_->status().c_str(), static_cast<unsigned>(recipes.size()));
    }
    ui::set_text(status_label_, count_text);
    const size_t rows = (recipes.size() + 2) / 3;
    const int gap = ui::px(8);
    const int content_height = rows == 0 ? 0 :
        static_cast<int>(rows) * card_height_ + static_cast<int>(rows - 1) * gap;
    lv_obj_set_height(content_, content_height);
    lv_obj_update_layout(content_);
  }
  static constexpr size_t MAX_VISIBLE_RECIPES = 5;
  MealieRecipeBrowser *plugin_;
  int width_ = 0, height_ = 0, tile_ = -1, list_top_ = 0, card_width_ = 0, card_height_ = 0;
  lv_obj_t *title_ = nullptr, *status_label_ = nullptr, *list_ = nullptr, *content_ = nullptr; lv_obj_t *parent_ = nullptr;
  RecipeCard cards_[MAX_VISIBLE_RECIPES];
};
class RecipeDetailCard : public tessera::Card {
 public:
  explicit RecipeDetailCard(MealieRecipeBrowser *plugin):plugin_(plugin){}
  ~RecipeDetailCard() override { if(plugin_->open_card_==this) plugin_->open_card_=nullptr; }
  void open(const tessera::CardContext &c) override {
    parent_=c.parent; width_=c.width; height_=c.height; plugin_->open_card_=this;
    meta_=ui::label(parent_,Font::BODY,theme::MUTED);
    lv_obj_set_pos(meta_,0,0);
    lv_obj_set_size(meta_,width_,ui::line_height(Font::BODY));
    ui::set_text(meta_,plugin_->text("detail_loading"));  // status text until the data arrives
    const int top=ui::line_height(Font::BODY)+ui::px(20);
    const int gap=ui::px(24), col=(width_-gap)/2;
    ingredients_title_=ui::label(parent_,Font::HEADLINE,theme::INK);
    lv_obj_set_pos(ingredients_title_,0,top); lv_obj_set_size(ingredients_title_,col,ui::line_height(Font::HEADLINE));
    ui::set_text(ingredients_title_,plugin_->text("ingredients"));
    instructions_title_=ui::label(parent_,Font::HEADLINE,theme::INK);
    lv_obj_set_pos(instructions_title_,col+gap,top); lv_obj_set_size(instructions_title_,col,ui::line_height(Font::HEADLINE));
    ui::set_text(instructions_title_,plugin_->text("instructions"));
    const int body_y=top+ui::line_height(Font::HEADLINE)+ui::px(8), body_h=height_-body_y;
    ingredients_=ui::label(parent_,Font::BODY,theme::INK);
    lv_obj_set_pos(ingredients_,0,body_y); lv_obj_set_size(ingredients_,col,body_h);
    lv_label_set_long_mode(ingredients_,LV_LABEL_LONG_WRAP);
    instructions_=ui::label(parent_,Font::BODY,theme::INK);
    lv_obj_set_pos(instructions_,col+gap,body_y); lv_obj_set_size(instructions_,col,body_h);
    lv_label_set_long_mode(instructions_,LV_LABEL_LONG_WRAP);
    if(!plugin_->load_recipe(plugin_->selected_recipe_id_)) ui::set_text(meta_,plugin_->text("detail_failed"));
  }
  void answer(JsonObjectConst m) {
    if((m["re"]|0u)!=plugin_->detail_request_id_) return;
    if(!(m["ok"]|false)){ui::set_text(meta_,plugin_->text("detail_failed"));return;}
    // Result of the manifest "answers" mapping: name, time, serv, i0..i5, s0..s2 (texts are cut at 48 bytes)
    JsonObjectConst r=m["result"].as<JsonObjectConst>();
    if(r.isNull()){ui::set_text(meta_,plugin_->text("detail_failed"));return;}
    const std::string time=printable(std::string(r["time"]|""));
    const float servings=r["serv"]|0.0f;
    char meta[96]; meta[0]=0;
    if(!time.empty() && servings>0) snprintf(meta,sizeof(meta),"%s  ·  %.1f %s",time.c_str(),servings,plugin_->text("servings"));
    else if(!time.empty()) snprintf(meta,sizeof(meta),"%s",time.c_str());
    else if(servings>0) snprintf(meta,sizeof(meta),"%.1f %s",servings,plugin_->text("servings"));
    ui::set_text(meta_,meta);
    std::string ing;
    for(int i=0;i<6;++i){
      char key[8]; snprintf(key,sizeof(key),"i%d",i);
      const char *line=r[key]|""; if(!*line) continue;
      if(!ing.empty()) ing+="\n"; ing+="• "; ing+=printable(line);
    }
    std::string steps; int n=0;
    for(int i=0;i<3;++i){
      char key[8]; snprintf(key,sizeof(key),"s%d",i);
      const char *txt=r[key]|""; if(!*txt) continue;
      if(!steps.empty()) steps+="\n\n";
      char number[12]; snprintf(number,sizeof(number),"%d. ",++n); steps+=number; steps+=printable(txt);
    }
    ui::set_text(ingredients_,ing.empty()?plugin_->text("no_ingredients"):ing);
    ui::set_text(instructions_,steps.empty()?plugin_->text("no_instructions"):steps);
  }
  void on_theme() override {
    ui::set_color(meta_,theme::MUTED);
    ui::set_color(ingredients_title_,theme::INK); ui::set_color(instructions_title_,theme::INK);
    ui::set_color(ingredients_,theme::INK); ui::set_color(instructions_,theme::INK);
  }
 private:
  MealieRecipeBrowser *plugin_;
  lv_obj_t *parent_=nullptr,*meta_=nullptr,*ingredients_title_=nullptr,*instructions_title_=nullptr,*ingredients_=nullptr,*instructions_=nullptr;
  int width_=0,height_=0;
};

void MealieRecipeBrowser::setup(){
  add_tile("browser",[this](){return new RecipeBrowserTile(this);});
  add_card("recipe",[this](){return new RecipeDetailCard(this);});
}
bool MealieRecipeBrowser::load_recipes(){
  if(config_entry_id_.empty()){status_="missing_config";return false;}
  JsonDocument request; request["ask"]="call_service:mealie.get_recipes";
  request["data"]["config_entry_id"]=config_entry_id_; request["data"]["result_limit"]=5;
  request_id_=tessera::send(this,request.as<JsonObjectConst>());
  status_=request_id_?"loading":"request_failed"; return request_id_!=0;
}
bool MealieRecipeBrowser::load_recipe(const std::string &id){
  if(config_entry_id_.empty()||id.empty()) return false;
  JsonDocument request; request["ask"]="call_service:mealie.get_recipe";
  request["data"]["config_entry_id"]=config_entry_id_; request["data"]["recipe_id"]=id;
  detail_request_id_=tessera::send(this,request.as<JsonObjectConst>()); return detail_request_id_!=0;
}
void MealieRecipeBrowser::on_message(JsonObjectConst message){
  const uint32_t received_id = message["re"] | 0u;
  printf("[Mealie plugin] on_message re=%lu expected_list=%lu expected_detail=%lu ok=%s\n",
         static_cast<unsigned long>(received_id),
         static_cast<unsigned long>(request_id_),
         static_cast<unsigned long>(detail_request_id_),
         (message["ok"] | false) ? "true" : "false");
  fflush(stdout);
  if(open_card_) open_card_->answer(message);
  if(received_id != request_id_) {
    if(received_id != detail_request_id_) {
      char diagnostic[80];
      snprintf(diagnostic, sizeof(diagnostic), "reply_id_mismatch (%lu/%lu)",
               static_cast<unsigned long>(received_id), static_cast<unsigned long>(request_id_));
      status_ = diagnostic;
    }
    return;
  }
  if(!(message["ok"]|false)){recipes_.clear();status_="service_error";return;}
  // The manifest maps the large Mealie response to five compact recipe entries.
  JsonObjectConst result=message["result"].as<JsonObjectConst>();
  JsonArrayConst secs=result["secs"].as<JsonArrayConst>();
  JsonArrayConst serv=result["serv"].as<JsonArrayConst>();
  recipes_.clear();
  for(size_t i=0;i<5;++i){
    char key_id[8], key_name[8];
    snprintf(key_id,sizeof(key_id),"id%u",static_cast<unsigned>(i));
    snprintf(key_name,sizeof(key_name),"n%u",static_cast<unsigned>(i));
    RecipeSummary recipe;
    recipe.id=result[key_id]|"";
    recipe.name=printable(std::string(result[key_name]|""));
    if(recipe.name.empty()) continue;
    if(!secs.isNull() && i<secs.size()) recipe.total_seconds=secs[i]|0u;
    if(!serv.isNull() && i<serv.size()) recipe.servings=serv[i]|0.0f;
    recipes_.push_back(std::move(recipe));
  }
  status_=recipes_.empty()?"no_results":"loaded";
}
}  // namespace esphome::mealie_recipe_browser
