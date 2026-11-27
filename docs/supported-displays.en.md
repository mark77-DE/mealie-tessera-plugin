# Supported displays

The recipe browser's 24-card layout is designed for displays with a resolution of 1280 × 800. The board IDs below are listed in the current official Tessera board catalog and enabled in the plugin manifest.

| Display | Size | Resolution | Board ID | Platform | Tessera catalog |
|---|---:|---:|---|---|---|
| Guition JC8012P4A1 (V1) | 10.1″ | 1280 × 800 | jc8012p4a1 | ESP32-P4 | new |
| Guition JC8012P4A1 V2 | 10.1″ | 1280 × 800 | jc8012p4a1v2 | ESP32-P4 | experimental |
| Guition JC8012P4A1 V3 | 10.1″ | 1280 × 800 | jc8012p4a1v3 | ESP32-P4 | experimental |
| reTerminal D1001 | 8″ | 1280 × 800 | reterminald1001 | ESP32-P4 | experimental |
| Waveshare ESP32-P4 Touch LCD 10.1 | 10.1″ | 1280 × 800 | waveshare101 | ESP32-P4 | experimental |
| Waveshare ESP32-P4 Touch LCD 10.1 V3 | 10.1″ | 1280 × 800 | waveshare101v3 | ESP32-P4 | new |

**Important notes**

- Hardware revisions are separate boards and must be listed individually. This applies in particular to Guition JC8012P4A1 V1, V2 and V3.
- “New” and “Experimental” are status labels from Tessera's board catalog; they do not describe this plugin's maturity.
- Enabling a board in the manifest allows Tessera to offer the plugin for it. It does not replace a successful firmware build or a hardware test.
- The official preview bench should build every listed board variant. Touch operation, readability and performance still need to be checked on real hardware.
- 7-inch and smaller-resolution displays are deliberately excluded because the 24-card grid is too tall for them.
