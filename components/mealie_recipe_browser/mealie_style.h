#pragma once
// Look of the Mealie recipe browser. Change fonts, colors, spacing and text decoration here only.
//
// Fonts, from large to small: VALUE (38) > HEADLINE (27) > BODY_LARGE (21) > TITLE (18, bold) > BODY (16).
//   The numbers are base sizes of Tessera's standard look; the screen scales them.
// Colors are theme roles (light and dark value each), for example INK (text), MUTED (second line),
//   CARD (card background), LINE (border). The full list is in tessera-plugins/docs, "theme::Role".
// Sizes ending in _PX are design pixels. The code passes them through ui::px(), so they scale with the screen.
#include "esphome/components/smart_display/plugin_api.h"

namespace esphome::mealie_recipe_browser::style {

// ---------------------------------------------------------------------------------------------------------------
// Recipe list (the tile)
// ---------------------------------------------------------------------------------------------------------------
constexpr tessera::Font LIST_TITLE_FONT = tessera::Font::TITLE;      // "Mealie" heading above the cards
constexpr theme::Role LIST_TITLE_COLOR = theme::INK;
constexpr tessera::Font LIST_STATUS_FONT = tessera::Font::BODY;     // "Lade Rezepte ..." / "5 Rezepte"
constexpr theme::Role LIST_STATUS_COLOR = theme::MUTED;
constexpr int LIST_STATUS_GAP_PX = 6;    // heading -> status line
constexpr int LIST_TOP_GAP_PX = 24;      // status line -> first card row

// Recipe cards
constexpr int CARD_COLUMNS = 3;          // cards per row (5 cards: row 1 has 3, row 2 has 2)
constexpr int CARD_GAP_PX = 8;           // between cards, horizontally and vertically
constexpr int CARD_HEIGHT_PX = 86;
constexpr int CARD_RADIUS_PX = 12;
constexpr int CARD_PADDING_PX = 10;      // inside the card
constexpr int CARD_BORDER_WIDTH = 1;     // real pixels, not scaled
constexpr theme::Role CARD_BG_COLOR = theme::CARD;
constexpr theme::Role CARD_BORDER_COLOR = theme::LINE;
constexpr tessera::Font CARD_NAME_FONT = tessera::Font::BODY_LARGE;  // recipe name
constexpr theme::Role CARD_NAME_COLOR = theme::INK;
constexpr int CARD_NAME_HEIGHT_PX = 46;  // room for the name (it wraps)
constexpr tessera::Font CARD_META_FONT = tessera::Font::BODY;        // time and servings
constexpr theme::Role CARD_META_COLOR = theme::MUTED;
constexpr int CARD_META_Y_PX = 54;       // top of the meta line inside the card
constexpr int CARD_META_HEIGHT_PX = 22;

// ---------------------------------------------------------------------------------------------------------------
// Recipe card (the detail view; its title bar is set by Tessera and cannot be changed here)
// ---------------------------------------------------------------------------------------------------------------
constexpr tessera::Font DETAIL_META_FONT = tessera::Font::BODY;      // time and servings, also the loading text
constexpr theme::Role DETAIL_META_COLOR = theme::MUTED;
constexpr tessera::Font DETAIL_HEADING_FONT = tessera::Font::HEADLINE;  // "Zutaten" / "Zubereitung"
constexpr theme::Role DETAIL_HEADING_COLOR = theme::INK;
constexpr tessera::Font DETAIL_TEXT_FONT = tessera::Font::BODY;      // ingredient lines and steps
constexpr theme::Role DETAIL_TEXT_COLOR = theme::INK;
constexpr int DETAIL_META_GAP_PX = 20;     // meta line -> headings
constexpr int DETAIL_COLUMN_GAP_PX = 24;   // between the two columns
constexpr int DETAIL_HEADING_GAP_PX = 8;   // heading -> text

// Text decoration
constexpr const char *INGREDIENT_BULLET = "• ";   // before each ingredient (a glyph Tessera's fonts contain)
constexpr const char *INGREDIENT_SEPARATOR = "\n";
constexpr const char *STEP_SEPARATOR = "\n\n";     // between steps

// How many lines the card shows. These MUST match the fields in tessera-plugin.yaml ("answers" of
// call_service:mealie.get_recipe: i0..i5 are ingredients, s0..s2 are steps). Tessera allows 12 fields in total.
constexpr int DETAIL_INGREDIENT_LINES = 6;
constexpr int DETAIL_STEPS = 3;

}  // namespace esphome::mealie_recipe_browser::style
