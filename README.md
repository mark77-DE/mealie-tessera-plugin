# Mealie Recipe Browser für Tessera

Ein Tessera-Plugin zum Suchen, Anzeigen und Kochen von Rezepten aus einer Mealie-Instanz.

> Entwicklungsstand: Plugin-Grundgerüst und erster Home-Assistant-Aufruf für die Rezeptsuche sind implementiert. Die Touch-Suche und Rezeptdetailansicht folgen.

## Ziel

Der Rezeptbrowser ergänzt ein bestehendes Tessera-Dashboard um eine eigenständige Rezeptoberfläche. Die normale Tessera-Oberfläche bleibt erhalten.

Zielgerät ist das große 10,1-Zoll-Touchdisplay Guition JC8012P4A1C-I-W-Y / JC8012P4A1, Hardware V3, mit 1280 × 800 Pixeln. Kleine Tessera-Displays sind ausdrücklich nicht Teil des aktuellen Projektziels.

## Architektur

- **Mealie:** Quelle für Rezepte, Kategorien und Rezeptdetails
- **Home Assistant:** stellt über die installierte Mealie-Integration Rezeptdaten bereit
- **Tessera-App:** führt deklarierte Home-Assistant-Befehle aus und übermittelt Antworten
- **Tessera-Plugin:** rendert Suche, Treffer, Details und Kochmodus auf dem großen Display

Eine eigene Lovelace-Karte ist nicht Bestandteil dieses Projekts.

## Aktueller Stand

- Plugin-Manifest für Tessera Plugin API 0.28 angelegt.
- ESPHome-Komponente und Full-Screen-Tile angelegt.
- Erster Datenaufruf über `mealie.get_recipes` implementiert.
- Der erste Suchbegriff wird aktuell als Tile-Option gesetzt.
- Die Suchergebnisliste zeigt Rezeptname, Gesamtzeit und Portionen.
- Touch-Tastatur, Kategorien, Rezeptdetails und Kochmodus sind noch nicht implementiert.

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
