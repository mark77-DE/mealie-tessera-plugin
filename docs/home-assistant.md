# Home Assistant integration

The Tessera plugin uses the native Home Assistant command channel. It does not call the Mealie API or any HTTP endpoint directly.

Install the **Mealie Tessera Bridge** custom integration and link it to the existing official Mealie integration. The bridge registers three read-only response services:

- `mealie_tessera_bridge.get_recipes`
- `mealie_tessera_bridge.get_categories`
- `mealie_tessera_bridge.get_recipe`

The Tessera manifest allows these commands through `permissions.ha_commands`. The Mealie URL, IP address, API token and authentication session remain inside Home Assistant. The Tessera plugin has no network permission or credential input.

See the [Bridge repository](https://github.com/mark77-DE/mealie-tessera-bridge) for installation and service response details.
