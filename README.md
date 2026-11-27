# Mealie Recipe Browser for Tessera

Browse your Mealie recipe collection on a large Tessera touch display. The plugin adds a dedicated recipe view and leaves the existing Tessera dashboard and its pages untouched.

> **Status: beta / early development.** The plugin loads recipe summaries in five-item pages and can display up to 24 recipes in a three-column, eight-row grid. Live API and hardware verification are still pending.

## What it does

- Reads recipes directly from the Mealie REST API over HTTPS.
- Loads five recipes per API request and combines up to five pages.
- Shows up to 24 recipes on the full-screen tile.
- Displays each recipe's name, total time and servings.
- Opens a recipe detail card when a result is tapped.
- Loads ingredients and preparation steps only when a recipe is opened.
- Keeps the Mealie API token in Tessera's secret storage; the token is not sent to the ESP32 firmware.

The manifest currently contains the placeholder host `mealie.example.com`. Before installing, replace it with your Mealie server's public HTTPS hostname in `permissions.network` and both fetch URLs. Tessera requires the fetch host to be fixed and explicitly allowlisted.

## Target screen

The 24-card layout is designed for 1280 × 800 displays, including Guition JC8012P4A1 V1/V2/V3, reTerminal D1001 and Waveshare 10.1-inch models. The recipe browser uses the whole page so all 24 entries can fit. Smaller 7-inch displays are not enabled because their lower resolution cannot fit this grid. See [supported displays](docs/supported-displays.en.md).

## Set up

1. In Mealie, open **User Profile → API Tokens** (usually `/user/profile/api-tokens`) and create a long-lived API token.
2. In Tessera, open **Plugins** and choose **Add with a link**.
3. Add this repository: [mark77-DE/mealie-tessera-plugin](https://github.com/mark77-DE/mealie-tessera-plugin).
4. Select your large display and install the plugin.
5. When Tessera asks for **Mealie API token**, paste the token you created in Mealie. Tessera stores it as a secret.
6. In Layout, add **Recipe browser** from the Plugins group as a full-page tile.

No Home Assistant Mealie integration or config-entry ID is required for the recipe list or recipe details. Mealie must be reachable at the configured public HTTPS hostname from the Tessera app's fetch service.

## Pagination

The browser makes five requests to `GET /api/recipes?page=<page>&perPage=5`. It combines their results and displays the first 24 recipes. The fifth page may return fewer than five items. Mealie's API provides the pagination; the Home Assistant Mealie actions do not expose a page parameter.

## Privacy

The Tessera app sends the API token in the HTTPS `Authorization: Bearer` header to `luigi.mahlen.biz` only. It requests recipe summaries from `/api/recipes` and a single recipe's details from `/api/recipes/{slug}`. The token is stored by Tessera as a secret and is not included in the plugin manifest, source code, preview fixtures or screen firmware. Mealie receives the API requests and may record them in its normal server logs.

The plugin does not send recipe data or the API token to any other host.

## Known limitations

- The Mealie hostname is fixed in the manifest because Tessera's network permission model does not allow a user-supplied hostname in a fetch URL.
- The initial list is unfiltered and alphabetically ordered. Search, category filters and cooking mode are planned for later work.
- The detail card currently shows up to six ingredients and three preparation steps. Longer recipes need segmented detail loading.
- The virtual preview does not install plugins or replace a test on the physical display.

## Live development preview

The official Tessera Preview Bench can use the real Mealie API. See [Live Mealie preview](docs/live-preview.md) for setup and security notes.

## Development status

| Feature | Status |
|---|---|
| Direct Mealie API connection using a Tessera secret input | Implemented; live verification pending |
| Five-item pagination and collection of up to 24 recipes | Implemented; live verification pending |
| Three-column, eight-row full-screen recipe grid | Implemented; layout verification pending |
| Recipe details loaded on demand | Implemented; live verification pending |
| Search and category filters | Planned |
| Cooking mode and ingredient checklist | Planned |
| Preview Bench and supported-board builds | Pending |
| Physical display test | Pending |

## Documentation

- [Architecture](docs/architecture.md)
- [Mealie API data model](docs/mealie-data-model.md)
- [Tessera data contract](docs/shared-data-contract.md)
- [Development plan](docs/development.md)
- [Live Mealie preview](docs/live-preview.md)

## Safety

Never commit Mealie API tokens, private URLs or other credentials. Use the Tessera secret input for the token. The manifest declares the one public Mealie hostname this plugin is allowed to contact.
