# Supported displays

The plugin is intended for large Tessera touch displays of 7 inches and larger. The board IDs below are listed in the current official Tessera board catalog and are enabled in the plugin manifest.

| Display | Size | Resolution | Board ID | Platform | Tessera catalog |
|---|---:|---:|---|---|---|
| Guition JC1060P470 | 7″ | 1024 × 600 | jc1060p470 | ESP32-P4 | experimentell |
| Guition JC1060P470 V2 | 7″ | 1024 × 600 | jc1060p470v2 | ESP32-P4 | experimentell |
| Guition JC8012P4A1 (V1) | 10,1″ | 1280 × 800 | jc8012p4a1 | ESP32-P4 | neu |
| Guition JC8012P4A1 V2 | 10,1″ | 1280 × 800 | jc8012p4a1v2 | ESP32-P4 | experimentell |
| Guition JC8012P4A1 V3 | 10,1″ | 1280 × 800 | jc8012p4a1v3 | ESP32-P4 | experimentell |
| reTerminal D1001 | 8″ | 1280 × 800 | reterminald1001 | ESP32-P4 | experimentell |
| CrowPanel Advanced 10.1 | 10,1″ | 1024 × 600 | crowpanel101 | ESP32-P4 | experimentell |
| Sunton ESP32-8048S070 | 7″ | 800 × 480 | sunton8048s070 | ESP32-S3 | experimentell |
| Waveshare ESP32-S3 Touch LCD 7 | 7″ | 800 × 480 | waveshare7 | ESP32-S3 | experimentell |
| Waveshare ESP32-S3 Touch LCD 7B | 7″ | 1024 × 600 | waveshare7b | ESP32-S3 | experimentell |
| Waveshare ESP32-P4 Touch LCD 7 | 7″ | 1280 × 720 | wavesharep47 | ESP32-P4 | experimentell |
| Waveshare ESP32-P4 Touch LCD 7B | 7″ | 1024 × 600 | wavesharep47b | ESP32-P4 | experimentell |
| Waveshare ESP32-P4 Touch LCD 10.1 | 10,1″ | 1280 × 800 | waveshare101 | ESP32-P4 | experimentell |
| Waveshare ESP32-P4 Touch LCD 10.1 V3 | 10,1″ | 1280 × 800 | waveshare101v3 | ESP32-P4 | neu |

**Important notes**

- Hardware revisions are separate boards and must be listed individually in the manifest. This applies in particular to JC8012P4A1 V1, V2 and V3.
- “New” and “Experimental” are status labels from Tessera's board catalog; they do not describe this plugin's maturity.
- Enabling a board in the manifest allows Tessera to offer the plugin for it. It does not replace a successful firmware build or a hardware test.
- GitHub's preview bench builds the listed board variants automatically. Touch operation, readability and performance still need to be checked on real hardware.
- Displays smaller than 7 inches are deliberately not enabled.
