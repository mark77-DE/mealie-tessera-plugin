# Mealie recipe data contract

## Purpose

This document describes the compact data returned to Tessera by the Home Assistant Mealie Tessera Bridge. Mealie's data remains the source of truth; Tessera receives only the fields needed by its current view.

## Principles

- Tessera talks to Home Assistant through native `call_service` commands, never directly to Mealie.
- Mealie URL, IP address, token and authenticated client remain in Home Assistant.
- The Bridge exposes read-only response services.
- Recipe summaries are requested in pages of four.
- The browser can collect up to 24 summaries for one display page.
- Recipe details are requested only after a recipe is opened.
- Search and category filters are repeated on every page request.

## Home Assistant service contract

| Service | Input | Response |
|---|---|---|
| `mealie_tessera_bridge.get_recipes` | `page`, optional `search`, optional `category` | `items[]`, `page`, `per_page`, `total`, `total_pages` |
| `mealie_tessera_bridge.get_categories` | none | `items[]`: `id`, `name` |
| `mealie_tessera_bridge.get_recipe` | `slug` | `time`, `serv`, `i0..i5`, `s0..s2` |

## Recipe summary

Each summary item contains:

| Field | Meaning |
|---|---|
| `id` | Mealie recipe slug |
| `name` | Recipe name |
| `seconds` | Total time in seconds |
| `servings` | Number of servings |

The service returns no more than four summaries per page. Pagination metadata describes the current filtered result set.

## Filter semantics

- `search` is optional.
- `category` is an optional Mealie category ID.
- Both may be supplied together.
- Tessera repeats active filters on every page request.
- A filter change resets the display page to 1 and clears the old result buffer.

## Recipe details

The first native service implementation returns compact fields for the current card:

- `time`: total time in seconds
- `serv`: servings
- `i0` through `i5`: first six formatted ingredients
- `s0` through `s2`: first three instruction texts

This is a transport-sized initial contract, not the final recipe model. A later iteration should retrieve ingredients and instructions in chunks and preserve structured Mealie ingredient fields such as quantity, unit and food so serving-size scaling remains possible.

## Tessera transport limits

Tessera's Home Assistant command response is bounded to about 3 KB and text values are limited to 48 bytes. Keep each response compact. Recipe summaries are intentionally split into four-item pages.
