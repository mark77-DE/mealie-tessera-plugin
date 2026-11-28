# Layout and spacing of the Mealie recipe browser

This document explains the layout constants in `components/mealie_recipe_browser/mealie_style.h`.
The plugin targets the 1280 × 800 GUITION JC8012P4A1. Tessera scales design pixels through
`ui::px()` for supported display variants.

## Coordinate system and outer spacing

- The tile's content origin is the upper-left corner of the plugin tile.
- The title starts at the left edge. The search placeholder shares its row and starts at 58% of
  the tile width.
- `LIST_STATUS_GAP_PX` is the vertical gap between the title row and the recipe count/status.
- `LIST_TOP_GAP_PX` is the extra space between the status line and the first recipe row.
- The recipe grid uses the available tile width; it has no extra outer left/right margin.

## Recipe grid

The list displays up to **20 recipes** in three columns. Three columns preserve useful width for
long German recipe names. The seventh row contains the remaining two cards.

- `CARD_COLUMNS`: number of columns.
- `CARD_GAP_PX`: horizontal and vertical gap between neighboring cards.
- `CARD_HEIGHT_PX`: fixed card height.
- `CARD_PADDING_PX`: inset from the card border to the text. Name and metadata start at this inset.
- `CARD_RADIUS_PX`, `CARD_BORDER_WIDTH`, `CARD_BG_COLOR`, `CARD_BORDER_COLOR`: card appearance.
- `CARD_NAME_HEIGHT_PX`: reserved height for the recipe name, which can wrap to two lines.
- `CARD_META_Y_PX`: vertical position of the time/servings line, measured from the card's top edge.
  This is closer to the name than in the previous layout.
- `CARD_META_HEIGHT_PX`: height reserved for the time/servings line.

The name and metadata coordinates are relative to the card's inner content area, after the border
and padding. Increasing `CARD_PADDING_PX` moves both text lines farther from the left and right
card edges; it does not change the width of the grid columns.

## Footer navigation

The footer is reserved at the bottom of the tile.

- `FOOTER_HEIGHT_PX` in the C++ tile controls the footer's total height.
- `NAV_BUTTON_SIZE_PX` sets the square buttons' width and height.
- `NAV_BUTTON_INSET_PX` sets their distance from the left and right edge.
- `NAV_BUTTON_RADIUS_PX` controls the corner radius; the border and background reuse the recipe-card theme.
- The chevrons are drawn from LVGL line segments, not font characters, so they do not depend on glyph coverage.
- Only taps inside the visible square button bounds change pages; the middle footer area is not a navigation target.
- The page indicator occupies the remaining center area.
- On page 1, the previous arrow is disabled and muted. On the last page, the next arrow is disabled
  and muted. Disabled arrows do not trigger page changes.

## Detail view

The recipe detail card uses two columns. `DETAIL_COLUMN_GAP_PX` is the horizontal space between
ingredients and instructions. `DETAIL_META_GAP_PX` separates preparation metadata from the
column headings, and `DETAIL_HEADING_GAP_PX` separates headings from their text.

## Changing the layout safely

1. Change the relevant constant in `mealie_style.h`.
2. Keep measurements in design pixels (the `_PX` suffix) and apply them with `ui::px()`.
3. Check both one-line and two-line recipe names. Keep the metadata below the wrapped name.
4. Check the first and last pages for disabled-arrow styling and touch areas.
5. Run the official Tessera preview for the JC8012P4A1 target and inspect the rendered screen.
