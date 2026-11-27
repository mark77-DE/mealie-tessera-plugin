# Mealie recipe data contract

## Purpose

This document describes the compact data that the Tessera plugin receives from the Mealie REST API. The manifest maps Mealie's camelCase API fields to short names before they reach the ESP32.

## Principles

- Recipe summaries contain only the fields needed by the list.
- Recipe details are fetched only after a recipe is opened.
- The Mealie API token is a Tessera secret and never reaches the firmware.
- Each mapped text field is limited to 48 bytes.
- The list uses five requests with five results per page and keeps at most 24 recipes.

## Recipe summary

| Mapped field | Mealie API field | Meaning |
|---|---|---|
| `id` | `slug` | Recipe slug used by the detail endpoint |
| `name` | `name` | Display name |
| `seconds` | `totalTimeSeconds` | Total preparation time in seconds |
| `servings` | `recipeServings` | Number of servings |

The API response is paginated under `items[]`.

## Recipe details

| Mapped field | Mealie API field | Meaning |
|---|---|---|
| `name` | `name` | Recipe name |
| `time` | `totalTime` | Human-readable/ISO duration from Mealie |
| `serv` | `recipeServings` | Number of servings |
| `i0` … `i5` | `recipeIngredient[0..5].display` | Formatted ingredient lines |
| `s0` … `s2` | `recipeInstructions[0..2].text` | Preparation steps |

The detail map uses all 12 available fields. More ingredients or steps require a second, segmented request.

## API requests

- List: `GET /api/recipes?page={page}&perPage=5&orderBy=name&orderDirection=asc`
- Detail: `GET /api/recipes/{slug}`
- Authentication: `Authorization: Bearer <api_token>`

The list fetch asks for pages 1 to 5. The plugin retains the first 24 results from the 25 possible slots.

## Categories and search

The current list is unfiltered and alphabetically ordered. Search and category filtering are planned separately.
