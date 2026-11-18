# Mealie Recipe Browser für Tessera

Ein Tessera-Plugin zum Suchen, Anzeigen und Kochen von Rezepten aus einer Mealie-Instanz.

> Entwicklungsstand: technische Grundlagen und Bedienkonzept dokumentiert; das Plugin ist noch nicht installierbar.

## Ziel

Der Rezeptbrowser ergänzt ein bestehendes Tessera-Dashboard um eine eigenständige Rezeptoberfläche. Die normale Tessera-Oberfläche bleibt erhalten.

Zielgerät ist das große 10,1-Zoll-Touchdisplay Guition JC8012P4A1C-I-W-Y / JC8012P4A1, Hardware V3, mit 1280 × 800 Pixeln. Kleine Tessera-Displays sind ausdrücklich nicht Teil des aktuellen Projektziels.

## Geplante Funktionen

- Rezepte direkt auf dem Touchdisplay suchen
- Kategorien dynamisch aus Mealie laden
- Suchtreffer mit Bild, Zeit und Portionen anzeigen
- Rezeptdetails mit Zutaten und Zubereitung darstellen
- Portionenzahl anpassen
- Kochmodus mit Zutaten-Checkliste und Schritt-Navigation

## Architektur

- **Mealie:** Quelle für Rezepte, Kategorien und Rezeptdetails
- **Home Assistant:** stellt über die installierte Mealie-Integration die Rezeptdaten bereit und vermittelt die Aufrufe
- **Tessera-App:** führt deklarierte Home-Assistant-Befehle aus und übermittelt Antworten
- **Tessera-Plugin:** rendert Suche, Treffer, Details und Kochmodus auf dem großen Display

Eine eigene Lovelace-Karte ist nicht Bestandteil dieses Projekts. Für Home Assistant können bereits vorhandene Mealie-Karten aus dem Marketplace genutzt werden.

## Projektstatus

In Home Assistant wurden `mealie.get_recipes` (Rezeptsuche) und `mealie.get_recipe` (vollständiger Rezeptabruf) praktisch getestet. Die beobachteten Felder stehen in [docs/mealie-data-model.md](docs/mealie-data-model.md).

## Dokumentation

- [Architektur](docs/architecture.md)
- [Tessera-Datenvertrag](docs/shared-data-contract.md)
- [Bedienkonzept](docs/ui-concept.md)
- [Beobachtetes Mealie-Datenmodell](docs/mealie-data-model.md)
- [Home-Assistant-Aktionen](docs/home-assistant.md)
- [Entwicklungsplan](docs/development.md)

## Sicherheit

Keine Home-Assistant-Tokens, Mealie-Zugangsdaten, privaten URLs, Config-Entry-IDs oder sonstigen Secrets in dieses Repository einchecken.
