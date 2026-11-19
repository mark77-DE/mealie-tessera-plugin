# Mealie Recipe Browser für Tessera

Ein Tessera-Plugin zum Suchen, Anzeigen und Kochen von Rezepten aus einer Mealie-Instanz.

> Entwicklungsstand: Rezeptsuche und erste Rezeptdetailansicht sind implementiert. Touch-Suche, Kategorien und Kochmodus folgen.

## Ziel

Der Rezeptbrowser ergänzt ein bestehendes Tessera-Dashboard um eine eigenständige Rezeptoberfläche. Die normale Tessera-Oberfläche bleibt erhalten.

Zielgerät ist das große 10,1-Zoll-Touchdisplay Guition JC8012P4A1C-I-W-Y / JC8012P4A1, Hardware V3, mit 1280 × 800 Pixeln. Kleine Tessera-Displays sind ausdrücklich nicht Teil des aktuellen Projektziels.

## Aktueller Stand

- Tessera-Plugin API 0.28, nur für Guition-Displays.
- Rezeptsuche über `mealie.get_recipes`.
- Trefferliste mit Name, Gesamtzeit und Portionen.
- Touch auf einen Treffer öffnet die Detailkarte.
- Detailkarte zeigt Zutaten und Zubereitung nebeneinander.
- Die Config-Entry-ID wird noch manuell in den Plugin-Einstellungen eingetragen.
- Touch-Tastatur, Kategorien, Pagination und Kochmodus sind noch offen.

## Architektur

- **Mealie:** Quelle für Rezepte, Kategorien und Rezeptdetails.
- **Home Assistant:** stellt über die installierte Mealie-Integration Rezeptdaten bereit.
- **Tessera-App:** führt deklarierte Home-Assistant-Befehle aus und übermittelt Antworten.
- **Tessera-Plugin:** rendert Suche, Treffer und Rezeptdetails auf dem großen Display.

Eine eigene Lovelace-Karte ist nicht Bestandteil dieses Projekts.

## Einrichtung und Sicherheit

Beim Hinzufügen des Plugins wird die installationsspezifische Config-Entry-ID der Mealie-Integration als lokale Plugin-Eingabe abgefragt. Sie wird nicht im Repository gespeichert. Im Tile-Inspector kann ein erster Suchbegriff gesetzt werden.

Keine Home-Assistant-Tokens, Mealie-Zugangsdaten, privaten URLs, Config-Entry-IDs oder sonstigen Secrets in dieses Repository einchecken.

## Dokumentation

- [Architektur](docs/architecture.md)
- [Tessera-Datenvertrag](docs/shared-data-contract.md)
- [Bedienkonzept](docs/ui-concept.md)
- [Beobachtetes Mealie-Datenmodell](docs/mealie-data-model.md)
- [Home-Assistant-Aktionen](docs/home-assistant.md)
- [Entwicklungsplan](docs/development.md)
