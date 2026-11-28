# Changelog

## 0.5.3 - 2026-11-28
- Replace unsupported arrow characters with clearly outlined square navigation buttons and vector-drawn chevrons.
- Restrict page changes to the visible square touch targets.
- Keep the total recipe count stable while another page loads; remove transient partial-load counters.

## 0.5.2 - 2026-11-28
- Display up to 20 recipes per Tessera page and fetch five Mealie pages per view.
- Tighten recipe card metadata spacing and improve footer pagination arrows.
- Document layout measurements and spacing in `docs/ui-layout.md` and `mealie_style.h`.

## 0.5.1 - 2026-11-28
- Add diagnostics for Home Assistant recipe-service requests and responses.
- Keep partial recipe results visible while additional pages load.
- Include hidden preview diagnostics in CI artifacts.


## 0.5.0 - 2026-11-28
- Replace direct Mealie HTTP access with native Home Assistant response services.
- Remove the Mealie API token input, server URL and Tessera network permission.
- Use the Home Assistant Mealie integration through the Mealie Tessera Bridge.
- Add native command fixtures for the 24-recipe preview.

## 0.4.7 - 2026-11-27
- Prepare the direct-fetch implementation that is superseded by the native Home Assistant transport in 0.5.0.

## 0.4.6 - 2026-11-27
- Fetch recipe summaries in five-item pages, combining up to 24 results.
- Add recipe detail loading by slug and a three-column, eight-row full-screen grid.

## 0.4.5 - 2026-11-27
- Read the recipe list from Mealie's raw response instead of unsupported array mappings.

## 0.4.4 - 2026-11-26
- Map Mealie recipe responses to compact fields to stay within the Tessera plugin response limit.

## 0.4.3 - 2026-11-22
- Enable large Tessera touch displays and add automated preview builds.

## 0.4.2 - 2026-11-22
- Correct the supported 10.1-inch Guition JC8012P4A1 V3 board.
- Add representative recipe search and detail responses for the preview bench.

## 0.4.1 - 2026-11-19
- Open a recipe from the results and view its ingredients and preparation steps.
- Show total time and servings in the recipe detail view.

## 0.4.0 - 2026-11-18
- First installable plugin skeleton and recipe search.
- Show recipe names, total time and servings.
