# Changelog

## 0.4.6 - 2026-11-27
- Fetch recipe summaries directly from the Mealie API in five-item pages, combining up to 24 results.
- Store the Mealie API token as a Tessera secret instead of using the Home Assistant Mealie integration.
- Load recipe details directly by slug and display the list in a three-column, eight-row full-screen grid.

## 0.4.5 - 2026-11-27
- Read the recipe list from Mealie's raw `get_recipes` response instead of unsupported array mappings.
- Keep the mapped `get_recipe` response for recipe details.

## 0.4.4 - 2026-11-26
- Map Mealie recipe responses to compact fields to stay within the Tessera plugin response limit.
- Limit the recipe browser to five results and read recipe IDs, names, total time and servings from the mapped response.
- Keep the live Home Assistant preview response envelope intact and apply the manifest answer mapping.

## 0.4.3 - 2026-11-22
- Enable all currently cataloged Tessera touch displays of 7 inches and larger, including hardware revisions and Waveshare, Guition, reTerminal, CrowPanel and Sunton models.
- Add an automated preview build for every enabled large display.
- Document board IDs, resolutions and catalog status.

## 0.4.2 - 2026-11-22
- Correct the supported board to the 10.1-inch Guition JC8012P4A1 V3.
- Add representative recipe search and detail responses for the official preview bench.

## 0.4.1 - 2026-11-19
- Open a recipe from the results and view its ingredients and preparation steps.
- The recipe detail view shows the total time and servings.

## 0.4.0 - 2026-11-18
- First installable plugin skeleton and recipe search.
- Show recipe names, total time and servings.
