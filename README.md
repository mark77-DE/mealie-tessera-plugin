# Mealie Recipe Browser for Tessera

Browse your Mealie recipe collection on a large Tessera touch display. The plugin adds a dedicated recipe view and leaves the existing Tessera dashboard and its pages untouched.

> **Status: beta / bridge migration in progress.** The current plugin contains the original direct-Mealie implementation. The target architecture is to access Mealie through the Home Assistant Mealie Tessera Bridge before adding dynamic categories and search.

## Target experience

- Full-screen recipe browser for 1280 × 800 displays, including supported Guition devices.
- Header: **Mealie Rezepte**.
- Left navigation: search field and dynamically loaded Mealie categories.
- Right area: up to 24 recipes in a three-column, eight-row grid.
- Recipe tiles show name, total time and servings.
- Search and category filters can be combined.
- Filters remain active when moving between result pages.
- Full recipe details are loaded only after a recipe is selected.

See [the implementation plan](docs/implementation-plan.md) for the agreed behavior and work sequence.

## Target architecture

Tessera communicates with the Home Assistant integration [Mealie Tessera Bridge](https://github.com/mark77-DE/mealie-tessera-bridge). The bridge reuses the already configured Home Assistant Mealie integration. The long Mealie API token stays in Home Assistant; Tessera uses a separate bridge key.

Target endpoints:

- `GET /api/mealie-tessera/categories`
- `GET /api/mealie-tessera/recipes?page=1&search=...&category=...`
- `GET /api/mealie-tessera/recipe/{slug}`

The bridge returns five recipes per list request. Tessera combines responses to fill up to 24 tiles. The search and category parameters must be repeated on every request, including requests for subsequent pages.

## Current implementation state

The original plugin was built against the Mealie API directly. Its direct-token setup and fetch definitions are being migrated to the bridge. Do not treat the legacy setup instructions or direct Mealie endpoints in old examples as the target architecture.

| Feature | Status |
|---|---|
| Home Assistant bridge with separate bearer key | Implemented; live endpoint verification pending |
| Bridge recipe list and on-demand detail endpoint | Implemented and previously tested |
| Bridge search and category parameters | Added; verify against installed Mealie version |
| Dynamic category endpoint | Added; verify against installed Mealie version |
| Bridge pagination metadata passthrough | Added; verify raw response |
| Tessera bridge configuration and authentication | Planned |
| Header, sidebar and 3×8 recipe grid | Existing grid foundation; target layout work pending |
| Dynamic categories and search UI | Planned |
| Persistent filters across pagination | Planned |
| Full detail view and structured ingredients | Existing foundation; verify during migration |
| Serving adjustment and cooking mode | Later phase |

## Documentation

- [Implementation plan and AI handoff](docs/implementation-plan.md)
- [Architecture](docs/architecture.md)
- [Mealie API data model](docs/mealie-data-model.md)
- [Tessera data contract](docs/shared-data-contract.md)
- [Development plan](docs/development.md)
- [Live Mealie preview](docs/live-preview.md)

## Development rules

- Read the implementation plan before changing the plugin.
- Do not add a direct Mealie token input to the target architecture.
- Do not invent Mealie routes or fields; verify them against the installed instance at `/docs`.
- Never commit Mealie tokens, bridge keys or private credentials.
- Keep the recipe browser isolated from the existing Tessera dashboard.
