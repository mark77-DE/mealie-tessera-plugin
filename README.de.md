# Mealie-Rezeptbrowser für Tessera

Rezepte aus einer Mealie-Instanz auf einem Tessera-Touchdisplay suchen und anzeigen. Das Plugin ergänzt das vorhandene Tessera-Dashboard um eine eigene Rezeptansicht. Das bestehende Dashboard und seine Seiten bleiben unverändert.

> **Status: Beta / frühe Entwicklung.** Rezeptsuche und eine erste Rezeptdetailansicht sind implementiert. Bildschirmtastatur, Kategorienfilter, Seitennavigation und Kochmodus sind noch geplant. Das Plugin wurde bisher nicht auf echter Hardware gebaut oder getestet.

## Funktionen

- Rezepte über die Mealie-Integration von Home Assistant suchen.
- Rezeptnamen, Gesamtzeit und Portionen anzeigen.
- Einen Treffer per Touch öffnen.
- Zutaten und Zubereitung nebeneinander darstellen.
- Die Mealie-Verbindung und Zugangsdaten in Home Assistant belassen.

Aktuell verwendet das Plugin die Home-Assistant-Aktionen `mealie.get_recipes` und `mealie.get_recipe`.

## Zielgerät

Das erste Ziel ist das 10,1-Zoll-Display Guition JC8012P4A1C-I-W-Y / JC8012P4A1 (Hardware V3, 1280 × 800, ESP32-P4 + ESP32-C6). Das Manifest beschränkt das Plugin derzeit auf Guition-Boards. Kleinere Displays sind kein Projektziel.

## Einrichtung

1. In Tessera **Plugins** öffnen und **Add with a link** wählen.
2. Dieses Repository hinzufügen: [mark77-DE/mealie-tessera-plugin](https://github.com/mark77-DE/mealie-tessera-plugin).
3. Das gewünschte Display auswählen und das Plugin installieren.
4. In den Plugin-Einstellungen des Displays die Config-Entry-ID der Mealie-Integration eintragen.
5. Im Layout unter der Gruppe **Plugins** die Kachel **Rezeptbrowser** hinzufügen. Den anfänglichen Suchbegriff kannst du im Kachel-Inspektor ändern.

Die Config-Entry-ID ist installationsspezifisch und gehört nicht in dieses Repository.

## Bekannte Einschränkungen

- Tessera gibt Plugins derzeit keinen Zugriff auf den geschützten Endpunkt `config_entries/get`. Daher kann das Plugin installierte Mealie-Integrationen noch nicht automatisch erkennen und zur Auswahl anbieten.
- Kategorienliste und Kategorienfilter sind noch nicht angebunden.
- Die Detailantwort wird bewusst klein gehalten. Sehr lange Rezepte können gekürzt werden, bis die abschnittsweise Übertragung umgesetzt ist.
- Die virtuelle Vorschau in der Tessera-App kann keine Plugins installieren. Für die Darstellung gibt es eine separate Entwickler-Vorschau (Bench), die keinen physischen Bildschirm benötigt.

## Entwicklungsstand

| Funktion | Stand |
|---|---|
| Plugin-Manifest und Guition-Ziel | Implementiert |
| Rezeptsuche über Home Assistant | Implementiert; Hardwaretest offen |
| Rezepttrefferliste | Erste Implementierung |
| Rezeptdetailansicht | Erste Implementierung |
| Bildschirmtastatur | Geplant |
| Kategorien und Filter | Geeigneter Datenweg in Home Assistant noch offen |
| Seitennavigation | Geplant |
| Kochmodus und Zutaten-Checkliste | Geplant |
| Automatische Auswahl der Mealie-Integration | Benötigt eine Erweiterung der Tessera-API |

## Dokumentation

- [Architektur](https://github.com/mark77-DE/mealie-tessera-plugin/blob/main/docs/architecture.md)
- [Bedienkonzept](https://github.com/mark77-DE/mealie-tessera-plugin/blob/main/docs/ui-concept.md)
- [Home-Assistant-Aktionen](https://github.com/mark77-DE/mealie-tessera-plugin/blob/main/docs/home-assistant.md)
- [Beobachtetes Mealie-Datenmodell](https://github.com/mark77-DE/mealie-tessera-plugin/blob/main/docs/mealie-data-model.md)
- [Tessera-Datenvertrag](https://github.com/mark77-DE/mealie-tessera-plugin/blob/main/docs/shared-data-contract.md)
- [Entwicklungsplan](https://github.com/mark77-DE/mealie-tessera-plugin/blob/main/docs/development.md)

## Sicherheit

Keine Home-Assistant-Tokens, Mealie-Zugangsdaten, privaten URLs, Config-Entry-IDs oder sonstigen Geheimnisse einchecken. Das Plugin ruft Mealie über Home Assistant auf und speichert keine Mealie-Zugangsdaten selbst.
