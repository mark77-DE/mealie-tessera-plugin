# Architecture

## Goal

A Tessera recipe browser for the large kitchen display. It adds a dedicated recipe view without replacing the existing Tessera dashboard. The target layout is a header, dynamic category/search navigation and a three-column by eight-row recipe grid (up to 24 recipes).

## Data path

```text
Mealie
  ↕ authenticated connection
Official Home Assistant Mealie integration
  ↕ existing HA client
Mealie Tessera Bridge (custom integration)
  - get_recipes response service
  - get_categories response service
  - get_recipe response service
  ↕ native Tessera Home Assistant command channel
Tessera app / plugin
  ↕
GUITION display
```

Tessera does not connect to Mealie directly. It has no Mealie URL, IP address, API token, bridge URL, bridge key or network permission. All credentials and server configuration remain in Home Assistant.

## Responsibilities

### Mealie and Home Assistant
- The official Mealie integration owns the server connection, authentication and API client.
- The Mealie Tessera Bridge registers read-only response services and converts Mealie responses into compact display data.

### Tessera app
- Mediates commands between the plugin and Home Assistant.
- Enforces the plugin's `permissions.ha_commands` allow-list.
- Bounds command responses; service payloads therefore stay compact.

### Tessera plugin
- Requests recipe pages, categories and recipe details through `tessera::send()`.
- Buffers recipe summaries for the 3 × 8 grid.
- Keeps search and category state across page requests.
- Loads detail data only after a recipe is selected.

## Home Assistant command contract

| Command | Input | Response |
|---|---|---|
| `call_service:mealie_tessera_bridge.get_recipes` | `page`, optional `search`, optional `category` | `items[]`, `page`, `per_page`, `total`, `total_pages` |
| `call_service:mealie_tessera_bridge.get_categories` | none | `items[]` with `id` and `name` |
| `call_service:mealie_tessera_bridge.get_recipe` | `slug` | `time`, `serv`, `i0..i5`, `s0..s2` |

The recipe list contains at most five summaries per service call. The current detail response is deliberately compact for Tessera's response-size limit; expanded, chunked detail loading is a later task.

## Filter and pagination model

- Search and category can be combined.
- Filter changes reset the displayed result page to page 1 and discard the old buffer.
- Every page request repeats the active filters.
- A display page contains up to 24 recipes, collected from multiple five-item Home Assistant responses.
- Old asynchronous responses must not be appended after the filter state changes.

## Technical constraints

- Plugin API 0.28.
- Home Assistant commands are declared under `permissions.ha_commands`.
- No `permissions.network`, `fetch` entries or secret inputs.
- Tessera command answers are bounded to about 3 KB; mapped text is limited to 48 bytes.
- Keep service responses small and preserve structured source data in Home Assistant for later enhancements.

## Later work

- Category picker and search UI wired to the native services.
- True 24-result pagination and stale-response protection.
- More than six ingredients and three instructions through segmented detail requests.
- Preview Bench and physical-display verification.
