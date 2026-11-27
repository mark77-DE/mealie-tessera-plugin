# Home Assistant integration

The recipe browser no longer uses Home Assistant's Mealie integration actions. Recipe summaries and recipe details are read directly from the Mealie REST API by Tessera's app-side fetch service.

No Mealie config-entry ID, Home Assistant long-lived token or Home Assistant service permission is required by the installed plugin.

See:

- [README setup and privacy](../README.md#setup)
- [Mealie API data model](mealie-data-model.md)
- [Live Mealie preview](live-preview.md)

Home Assistant may still host the Mealie container or provide network access to it, but it is not part of the plugin's recipe data path.
