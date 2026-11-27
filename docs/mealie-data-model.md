# Mealie API data model

This document records the Mealie v3 REST API fields used by the plugin. The installed Mealie instance was previously identified as v3.31.0; the live response still needs to be verified against the current server.

## Recipe list

Endpoint: `GET /api/recipes?page=<page>&perPage=5&orderBy=name&orderDirection=asc`

Mealie returns a paginated object with an `items[]` array. The plugin maps each item to:

| Mealie field | Plugin field | Use |
|---|---|---|
| `slug` | `id` | Detail endpoint identifier |
| `name` | `name` | Display name |
| `totalTimeSeconds` | `seconds` | Total time in seconds |
| `recipeServings` | `servings` | Number of servings |

The plugin requests five pages with five results per page and keeps at most 24 recipes.

## Recipe detail

Endpoint: `GET /api/recipes/{slug}`

The detail response is mapped to the 12 fields supported by Tessera:

| Mealie field | Plugin field | Use |
|---|---|---|
| `name` | `name` | Recipe name |
| `totalTime` | `time` | Total time display |
| `recipeServings` | `serv` | Number of servings |
| `recipeIngredient[0..5].display` | `i0..i5` | Formatted ingredient lines |
| `recipeInstructions[0..2].text` | `s0..s2` | Preparation steps |

Mealie formats ingredient quantities and units in `display`, so the plugin does not need to reconstruct ingredient lines.

## Authentication

The plugin uses a long-lived Mealie API token in the HTTP header:

```http
Authorization: Bearer <api-token>
```

The token is a Tessera input of kind `secret`. It is stored by the Tessera app and is not passed to the ESP32 firmware.

## Limitations

- The list is currently unfiltered and alphabetically ordered.
- Only six ingredients and three instructions are included in the detail map.
- Tessera mapped text fields are limited to 48 bytes, so long text can be shortened.
- Live API response validation remains pending.
