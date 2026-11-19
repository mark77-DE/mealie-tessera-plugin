# Development notes

This repository is a Tessera plugin. Follow the upstream plugin rules and tools:

- Rules and required reading: https://github.com/MaxGramser/tessera-plugins/blob/main/AGENTS.md
- Plugin guide: https://github.com/MaxGramser/tessera-plugins/blob/main/docs/MAKING_A_PLUGIN.md
- Manifest reference: https://github.com/MaxGramser/tessera-plugins/blob/main/docs/MANIFEST.md
- Firmware API: https://github.com/MaxGramser/tessera-plugins/blob/main/docs/FIRMWARE_API.md
- Preview bench: https://github.com/MaxGramser/tessera-plugins/blob/main/docs/PREVIEW.md
- Publishing and store image: https://github.com/MaxGramser/tessera-plugins/blob/main/docs/PUBLISHING.md

Before calling a change complete, run the upstream checker and preview bench against this repository. Generate `store.png` with the upstream `tools/store_image.py` after the preview bench has produced clean, representative screenshots. Never claim that the plugin compiled or was hardware-tested unless that actually happened.
