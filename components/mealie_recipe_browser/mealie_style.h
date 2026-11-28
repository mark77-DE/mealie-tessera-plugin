#pragma once
// Look of the Mealie recipe browser. Change fonts, colors, spacing and text decoration here only.
// Layout measurements and spacing are documented in docs/ui-layout.md.
// All *_PX values are design pixels and must be applied through ui::px().
//
// Fonts, from large to small: VALUE (38) > HEADLINE (27) > BODY_LARGE (21) > TITLE (18, bold) > BODY (16).
//   The numbers are base sizes of Tessera's standard look; the screen scales them.
// Colors are theme roles (light and dark value each), for example INK (text), MUTED (second line),
//   CARD (card background), LINE (border). The full list is in tessera-plugins/docs, "theme::Role".
// Sizes ending in _PX are design pixels. The code passes them through ui::px(), so they scale with the screen.
#include "esphome/components/smart_display/plugin_api.h"

namespace esphome::mealie_recipe_browser::style {

// ---------------------------------------------------------------------------------------------------------------
// Recipe list (the full-page tile)
// ---------------------------------------------------------------------------------------------------------------
constexpr tessera::Font LIST_TITLE_FONT = tessera::Font::TITLE;
constexpr theme::Role LIST_TITLE_COLOR = theme::INK;
constexpr tessera::Font LIST_STATUS_FONT = tessera::Font::BODY;
constexpr theme::Role LIST_STATUS_COLOR = theme::MUTED;
constexpr int LIST_STATUS_GAP_PX = 6;  // gap from title baseline to the result/status line
constexpr int LIST_TOP_GAP_PX = 18;  // breathing room between status line and first recipe row

// 20 recipes: three columns, seven rows (the last row contains two cards).
// Keep three columns so long German recipe names retain useful width.
constexpr int CARD_COLUMNS = 3;
constexpr int CARD_GAP_PX = 8;  // horizontal and vertical gap between neighboring cards
constexpr int CARD_HEIGHT_PX = 76;
constexpr int CARD_RADIUS_PX = 12;
constexpr int CARD_PADDING_PX = 10;  // inset from card border to name and metadata
constexpr int CARD_BORDER_WIDTH = 1;
constexpr theme::Role CARD_BG_COLOR = theme::CARD;
constexpr theme::Role CARD_BORDER_COLOR = theme::LINE;
constexpr tessera::Font CARD_NAME_FONT = tessera::Font::BODY_LARGE;
constexpr theme::Role CARD_NAME_COLOR = theme::INK;
constexpr int CARD_NAME_HEIGHT_PX = 42;
constexpr tessera::Font CARD_META_FONT = tessera::Font::BODY;
constexpr theme::Role CARD_META_COLOR = theme::MUTED;
constexpr int CARD_META_Y_PX = 46;  // metadata baseline relative to the card top; reduced from 50 px
constexpr int CARD_META_HEIGHT_PX = 20;

// Footer navigation: large arrows with a generous 20% touch target at each edge.
constexpr tessera::Font NAV_ARROW_FONT = tessera::Font::HEADLINE;

// ---------------------------------------------------------------------------------------------------------------
// Recipe card (the detail view; its title bar is set by Tessera and cannot be changed here)
// ---------------------------------------------------------------------------------------------------------------
constexpr tessera::Font DETAIL_META_FONT = tessera::Font::BODY;
constexpr theme::Role DETAIL_META_COLOR = theme::MUTED;
constexpr tessera::Font DETAIL_HEADING_FONT = tessera::Font::HEADLINE;
constexpr theme::Role DETAIL_HEADING_COLOR = theme::INK;
constexpr tessera::Font DETAIL_TEXT_FONT = tessera::Font::BODY;
constexpr theme::Role DETAIL_TEXT_COLOR = theme::INK;
constexpr int DETAIL_META_GAP_PX = 20;
constexpr int DETAIL_COLUMN_GAP_PX = 24;
constexpr int DETAIL_HEADING_GAP_PX = 8;

constexpr const char *INGREDIENT_BULLET = "• ";
constexpr const char *INGREDIENT_SEPARATOR = "\n";
constexpr const char *STEP_SEPARATOR = "\n\n";

// These counts match the 12 fields in the direct Mealie detail fetch.
constexpr int DETAIL_INGREDIENT_LINES = 6;
constexpr int DETAIL_STEPS = 3;

}  // namespace esphome::mealie_recipe_browser::style
