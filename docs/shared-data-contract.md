# Mealie recipe data contract

## Purpose

This document describes the data that the Tessera plugin receives through the Home Assistant Mealie Tessera Bridge. Mealie's API model is the source of truth; Tessera should map only the fields needed for the current view and preserve structured detail fields for future cooking features.

## Principles

- Tessera talks to the Home Assistant bridge, not directly to Mealie.
- The Mealie API token stays in Home Assistant.
- Tessera uses a separate bridge bearer key.
- Recipe summaries contain only the fields needed by the list.
- Recipe details are fetched only after a recipe is opened.
- The list uses five results per bridge request and can collect up to 24 results for one display page.
- Preserve Mealie pagination metadata.
- Preserve structured ingredient values such as quantity, unit and food in recipe details.

## Bridge endpoints

| Request | Endpoint | Purpose |
|---|---|---|
| Categories | `GET /api/mealie-tessera/categories` | Dynamic category list |
| Recipe list | `GET /api/mealie-tessera/recipes?page=N&search=TEXT&category=ID` | Filtered, paginated recipe summaries |
| Recipe detail | `GET /api/mealie-tessera/recipe/{slug}` | Full recipe detail |

All requests use `Authorization: Bearer <bridge-key>`.

## Recipe summary

The bridge passes through Mealie's paginated recipe response. The expected top-level fields are:

| Field | Meaning |
|---|---|
| `items[]` | Recipe summaries |
| `page` | Current Mealie API page |
| `per_page` | Number of results per Mealie page |
| `total` | Total matching recipes |
| `total_pages` | Number of Mealie pages |

The exact payload must be confirmed against the installed Mealie version before relying on optional fields.

Useful recipe summary fields:

| Mealie field | Tessera use |
|---|---|
| `slug` | Detail endpoint identifier |
| `name` | Display name |
| `totalTimeSeconds` | Total time in seconds |
| `recipeServings` | Number of servings |
| `recipeCategory` | Category data, if included in summary |

## Filter semantics

- `search` is optional.
- `category` is an optional Mealie category ID.
- Both may be supplied together.
- Tessera repeats the active filters on every list request.
- Filter changes reset the displayed page to 1.
- Moving between pages does not clear filters.

## Recipe details

The detail endpoint returns the full Mealie recipe object inside `recipe`.

The UI may use `display` for formatted ingredient text, but must also preserve the structured ingredient fields, including (where present):

- `quantity`
- `unit`
- `food`
- `note`
- `originalText`

Structured data is required for future serving-size scaling. Do not replace it with a formatted string.

Recipe instructions retain their `text`, title/summary and any timing or references supplied by Mealie.

## Display mapping

The existing compact list mapping uses:

| Mealie field | Plugin field | Meaning |
|---|---|---|
| `slug` | `id` | Recipe slug |
| `name` | `name` | Display name |
| `totalTimeSeconds` | `seconds` | Total time |
| `recipeServings` | `servings` | Servings |

Tessera mapped text fields may be limited to 48 bytes. Keep list summaries short; do not truncate the source detail object before the detail UI has processed it.
