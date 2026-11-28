# Mealie Recipe Browser for Tessera

Browse recipes from a Mealie instance on a Tessera touch display. The plugin uses Tessera's native Home Assistant command channel and the **Mealie Tessera Bridge** custom integration. It never connects to Mealie directly.

## Architecture

- Mealie connection and credentials remain in Home Assistant's official Mealie integration.
- The Mealie Tessera Bridge exposes read-only Home Assistant response services.
- Tessera calls those services through its native Home Assistant connection.
- No Mealie URL, IP address, API token, bridge key, or network permission is configured in the plugin.

## Setup

1. Set up the official Mealie integration in Home Assistant.
2. Install and configure [Mealie Tessera Bridge](https://github.com/mark77-DE/mealie-tessera-bridge), linking it to the existing Mealie config entry.
3. Install this plugin in Tessera.
4. Add the Recipe Browser tile to the Tessera layout.

## Data

- Recipe summaries are retrieved in pages of four.
- Up to 24 recipes can be shown on the overview.
- Search and category filters are passed to Home Assistant.
- Categories are loaded dynamically from Mealie.
- Recipe details are requested only after selecting a recipe.

## Development status

The native HA command transport is being introduced on the `native-ha-services` branch. The preview uses fixture responses for the Home Assistant commands; real service responses still need to be verified against the installed HA/Mealie versions and the Tessera app.
