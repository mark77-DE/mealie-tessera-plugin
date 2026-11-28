# Architecture

## Goal

A Tessera recipe browser for the large 10.1-inch kitchen display. It adds a dedicated recipe view without replacing the existing Tessera dashboard.

The target display is 1280 × 800 pixels. The browser has a full-width header, a left navigation sidebar and a three-column by eight-row recipe grid.

## Target data path

```text
             Mealie v3 REST API
                    ▲
                    │ existing authenticated client
        Home Assistant Mealie integration
                    ▲
                    │
          Mealie Tessera Bridge
          - bridge bearer key
          - categories
          - filtered recipe pages
          - recipe details
                    ▲
                    │ HTTPS / trusted LAN
              Tessera app
          - requests and mapping
          - buffers five-item pages
                    ▲
                    │ compact data
            Tessera plugin UI
          - header and category sidebar
          - search and filter state
          - 3 × 8 recipe grid
                    ▲
                    │
             GUITION display
```

The long Mealie API token remains in Home Assistant. Tessera uses a separate bridge key. The screen firmware receives only mapped display data and never receives either server's credentials.

## Responsibilities

### Mealie
- Source of recipes, categories, ingredients and preparation steps.
- Provides native search, category filtering and pagination.
- Provides complete recipe details.

### Home Assistant Mealie integration
- Owns the Mealie server configuration and API token.
- Provides the authenticated client reused by the bridge.

### Mealie Tessera Bridge
- Authenticates Tessera with a dedicated bearer key.
- Exposes a read-only API under `/api/mealie-tessera`.
- Provides category data.
- Provides recipe pages of five items with optional search and category filters.
- Preserves Mealie pagination metadata.
- Fetches one full recipe by slug on demand.

### Tessera app
- Stores the bridge base URL and bridge key as plugin configuration, subject to Tessera's supported configuration model.
- Calls the bridge, maps response fields and buffers list results.
- Requests categories and recipe details only when needed.

### Tessera plugin
- Renders the header, search/category sidebar and recipe grid.
- Combines up to five bridge responses to fill 24 recipe tiles.
- Keeps filters stable across pages.
- Opens a recipe detail view only after a tile is selected.

## API contract

- Categories: `GET /api/mealie-tessera/categories`
- Recipe page: `GET /api/mealie-tessera/recipes?page=N&search=TEXT&category=CATEGORY_ID`
- Recipe detail: `GET /api/mealie-tessera/recipe/{slug}`
- Authentication: `Authorization: Bearer <bridge-key>`

The list response is Mealie's paginated response, including `items`, `page`, `per_page`, `total` and `total_pages` (exact field casing must be verified against the installed version). The bridge uses a page size of five.

## Filter and pagination model

- Category and search are independent filter values and can be active together.
- Changing either filter resets the displayed result page to page 1.
- Moving to the next or previous displayed page retains both filters.
- The display page contains up to 24 results; the bridge page contains up to five.
- Tessera must calculate which bridge pages are needed for the requested 24-result window.
- A response belonging to an older filter state must not be appended to the current buffer.

## Migration status

The repository originally implemented direct Mealie API access from Tessera. That is a legacy implementation and is being replaced by the Home Assistant bridge. Until the plugin fetch definitions and configuration have been migrated, do not assume the target bridge flow is already active on the display.

## Technical constraints

- Target resolution: 1280 × 800 pixels.
- The browser tile takes the whole page.
- Plugin API 0.28.
- Mapped text fields are limited to 48 bytes; keep list fields compact.
- Do not reduce structured ingredient data to display strings: later serving adjustment needs quantities, units and food references.
- Never put credentials in fixtures, source code or firmware.

## Later work

- More than six ingredients and three instructions through segmented detail rendering.
- Serving adjustment, ingredient checklist and cooking mode.
- Live Preview Bench and physical-screen verification.
