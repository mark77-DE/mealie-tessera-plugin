# Mealie Recipe Browser for Tessera

Browse recipes from a Mealie instance on a Tessera touch screen. The plugin adds a dedicated recipe view and leaves the existing Tessera dashboard and its pages untouched.

> **Status: beta / early development.** Recipe search and an initial recipe detail card are implemented. The search keyboard, category filters, paging and cooking mode are still planned. The plugin has not yet been built or tested on physical hardware.

## What it does

- Searches recipes through Home Assistant's Mealie integration.
- Shows recipe names, total time and servings.
- Opens a recipe detail card when a result is tapped.
- Shows ingredients and preparation instructions side by side.
- Keeps the Mealie connection and its credentials in Home Assistant.

The current implementation uses the Home Assistant actions `mealie.get_recipes` and `mealie.get_recipe`.

## Target screen

The first and currently only supported target is the 10.1-inch Guition JC8012P4A1 V3 (`jc8012p4a1v3`, 1280 × 800, ESP32-P4). Smaller screens are deliberately not listed as compatible because the recipe browser is designed as a full-screen kitchen interface.

## Set up

1. In Tessera, open **Plugins** and choose **Add with a link**.
2. Add this repository: [mark77-DE/mealie-tessera-plugin](https://github.com/mark77-DE/mealie-tessera-plugin).
3. Select the Guition JC8012P4A1 V3 screen and install the plugin.
4. In Home Assistant, open **Settings → Devices & services**.
5. Find the **Mealie** integration entry, open its three-dot menu and choose **Copy entry ID**.
6. Paste the copied ID into the `config_entry_id` field in the screen's plugin settings.
7. In Layout, add **Recipe browser** from the Plugins group. The initial search term can be changed in the tile inspector.

If you have multiple Mealie instances, copy the entry ID from the integration entry you want the recipe browser to use. The ID is specific to your Home Assistant installation and is stored only in Tessera's local plugin configuration. Do not commit it to this repository.

## Known limitations

- The installed Mealie integration cannot currently be selected automatically in the plugin. Its config entry ID must be copied manually once using **Copy entry ID**.
- Category listing and category filtering are not yet connected to the plugin.
- The current detail response is deliberately kept small; very long recipes may be shortened until segmented loading is implemented.
- A virtual preview in the Tessera app cannot install plugins. The separate developer preview/bench is intended for inspecting plugin rendering without a physical screen.

## Development status

| Feature | Status |
|---|---|
| Plugin manifest and Guition JC8012P4A1 V3 target | Implemented |
| Recipe search via Home Assistant | Implemented; hardware verification pending |
| Recipe result list | Initial implementation |
| Recipe detail card | Initial implementation |
| Search keyboard | Planned |
| Categories and filters | Blocked on a suitable Home Assistant data path |
| Pagination | Planned |
| Cooking mode and ingredient checklist | Planned |
| Automatic Mealie integration selection | Not currently exposed by the Tessera plugin API |

## Documentation

- [Architecture](https://github.com/mark77-DE/mealie-tessera-plugin/blob/main/docs/architecture.md)
- [UI concept](https://github.com/mark77-DE/mealie-tessera-plugin/blob/main/docs/ui-concept.md)
- [Home Assistant actions and entry ID](https://github.com/mark77-DE/mealie-tessera-plugin/blob/main/docs/home-assistant.md)
- [Observed Mealie data model](https://github.com/mark77-DE/mealie-tessera-plugin/blob/main/docs/mealie-data-model.md)
- [Tessera data contract](https://github.com/mark77-DE/mealie-tessera-plugin/blob/main/docs/shared-data-contract.md)
- [Development plan](https://github.com/mark77-DE/mealie-tessera-plugin/blob/main/docs/development.md)

## Safety

Never commit Home Assistant tokens, Mealie credentials, private URLs, config entry IDs or other secrets. The plugin calls Mealie through Home Assistant; it does not store Mealie credentials itself.
