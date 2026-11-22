# Unterstützte Displays

Das Plugin ist für große Tessera-Touchdisplays ab 7 Zoll vorgesehen. Die folgenden Board-IDs sind im aktuellen offiziellen Tessera-Boardkatalog enthalten und im Plugin-Manifest freigeschaltet.

| Display | Größe | Auflösung | Board-ID | Plattform | Tessera-Katalog |
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

**Wichtige Hinweise**

- Die Versionsvarianten sind getrennte Boards und müssen deshalb einzeln im Manifest aufgeführt werden. Das gilt insbesondere für JC8012P4A1 V1, V2 und V3.
- „Neu“ und „Experimentell“ sind die Statusangaben des Tessera-Boardkatalogs, keine Aussage über den Reifegrad dieses Plugins.
- Die Freigabe im Manifest bedeutet, dass Tessera das Plugin für diese Boards anbieten darf. Sie ersetzt keinen erfolgreichen Firmware-Build und keinen Hardwaretest.
- Die GitHub-Preview-Bench baut die oben aufgeführten Board-Varianten automatisiert. Die tatsächliche Touchbedienung, Lesbarkeit und Performance müssen anschließend auf realer Hardware geprüft werden.
- Kleinere Displays unter 7 Zoll sind bewusst nicht freigeschaltet.
