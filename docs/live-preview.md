# Live Home Assistant preview

The official Tessera Preview Bench normally answers Home Assistant plugin commands from `preview.yaml`. This helper adds a local-only bridge for the Mealie Recipe Browser: the preview process calls the real Home Assistant service and passes its response back through the same Tessera preview pipeline.

## Requirements

- The official `tessera-plugins` repository checked out next to this repository, unless `TESSERA_PLUGINS_DIR` is set.
- The Preview Bench already set up once (`python3 tools/preview.py --setup`).
- A Home Assistant long-lived access token.
- The Mealie integration's `config_entry_id`.
- Network access from WSL/Linux to Home Assistant.

## Run from WSL

From the `tessera-plugins` checkout, set the three local values:

```bash
export TESSERA_HA_URL="http://homeassistant.local:8123"
export TESSERA_HA_TOKEN="YOUR_LONG_LIVED_ACCESS_TOKEN"
export TESSERA_MEALIE_CONFIG_ENTRY_ID="YOUR_MEALIE_CONFIG_ENTRY_ID"
```

Use the URL that is reachable from the WSL environment. HTTPS is also supported.

Then run the bridge instead of `tools/preview.py`:

```bash
python3 ../mealie-tessera-plugin/tools/preview-ha.py --board jc8012p4a1v3 --window
```

Change the board as needed. The helper uses the sibling `tessera-plugins` checkout by default. If it is elsewhere:

```bash
export TESSERA_PLUGINS_DIR="/path/to/tessera-plugins"
```

## What it does

- Clones the official Tessera firmware/render repository into `~/.cache/tessera-ha-preview` the first time and applies a small local patch to the Preview Bench's service-answer handler.
- Uses Home Assistant's authenticated REST service endpoint with `?return_response` for plugin commands such as `mealie.get_recipes` and `mealie.get_recipe`.
- Supplies the Mealie `config_entry_id` to the component for the duration of the preview run. The helper restores `plugin.yaml` afterwards, including if the preview exits with an error.
- Leaves `preview.yaml` unchanged. It remains the fallback fixture source when using the official preview command without this helper.
- Does not modify the official `tessera-plugins` checkout or commit credentials/entry IDs.

The local firmware checkout is deliberately separate from the official previewer's normal cache. It is not updated automatically, because that would overwrite the local patch. To refresh it manually, remove `~/.cache/tessera-ha-preview`; the next run clones it again and reapplies the patch.

## Security

Treat the Home Assistant token as a password. Do not put it in shell history, source files, screenshots, logs or Git. Environment variables are inherited by the preview process but the helper does not print their values. Revoke the token in Home Assistant when it is no longer needed.

The bridge only forwards the two Mealie service calls that the plugin already declares in its manifest. It does not expose Home Assistant as a general-purpose proxy.

## Limitations

- This is a local developer convenience, not a Tessera feature and not a replacement for testing on the actual display.
- It depends on the current structure of Tessera's `tools/bench.py`. If upstream changes that code, the helper stops rather than silently applying an uncertain patch.
- The Mealie actions must return response data through Home Assistant's service API. If Home Assistant returns an error, the preview reports it as a live service-call finding.
- This first version handles service responses; it does not make the Preview Bench's screen state, touch input or hardware simulation live.
