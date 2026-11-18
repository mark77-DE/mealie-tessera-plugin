# Mealie Recipe Browser

Ein gemeinsamer Rezeptbrowser für Home Assistant und das große Tessera-Küchendisplay. Beide Oberflächen greifen auf dieselbe Mealie-Datenbasis und dieselben fachlichen Datenmodelle zurück.

> Entwicklungsstand: Grundlagen und Bedienkonzepte dokumentiert; es gibt noch keine installierbare Lovelace-Karte oder Tessera-Plugin-Version.

## Ziel

Rezepte aus einer Mealie-Instanz sollen sowohl im Home-Assistant-Dashboard als auch auf einem großen Tessera-Touchdisplay gesucht, angezeigt und beim Kochen genutzt werden können.

Die beiden Oberflächen werden eigenständig entwickelt:

- **Home Assistant:** Lovelace-Custom-Card für bestehende HA-Dashboards.
- **Tessera:** zusätzliche Rezeptoberfläche für ein großes Touchdisplay, insbesondere das Guition JC8012P4A1C-I-W-Y (1280 × 800). Kleine Tessera-Displays sind vorerst kein Ziel.

## Gemeinsame Grundlage

- Mealie als Quelle für Rezepte, Kategorien und Rezeptdetails
- Home Assistant als zentrale Integrations- und Vermittlungsschicht
- ein gemeinsames, frontend-neutrales Rezeptdatenmodell
- gemeinsame fachliche Logik, z. B. Zeitformatierung und spätere Portionsberechnung

Die Oberflächen, Navigation und Darstellung bleiben frontend-spezifisch. Tessera wird nicht zur Voraussetzung für die Home-Assistant-Karte und umgekehrt.

## Geplante Funktionen

- Rezeptsuche nach Namen und Zutaten
- Kategorien und ungefilterte Rezeptübersicht
- Trefferliste mit Bild, Zeit und Portionen
- Rezeptdetails mit Zutaten und Zubereitung
- Portionenzahl anpassen
- Kochmodus mit Zutaten-Checkliste und Schritt-Navigation

## Projektstruktur (Zielbild)

- `backend/homeassistant/`: Mealie-Anbindung und Bereitstellung der Daten
- `shared/`: gemeinsames Datenmodell und fachliche Logik
- `frontend/home-assistant-card/`: Lovelace-Custom-Card
- `tessera/plugin/`: Plugin für das große Tessera-Display
- `docs/`: Architektur, Datenmodell und Entwicklungsentscheidungen

Die Struktur wird schrittweise aufgebaut. Es wird noch kein nicht getesteter Code als funktionsfähig vorausgesetzt.

## Projektstatus

In Home Assistant wurden `mealie.get_recipes` (Rezeptsuche) und `mealie.get_recipe` (vollständiger Rezeptabruf) praktisch getestet. Die beobachteten Felder sind in [docs/mealie-data-model.md](docs/mealie-data-model.md) dokumentiert.

## Dokumentation

- [Architektur](docs/architecture.md)
- [Gemeinsamer Datenvertrag](docs/shared-data-contract.md)
- [Bedienkonzept](docs/ui-concept.md)
- [Beobachtetes Mealie-Datenmodell](docs/mealie-data-model.md)
- [Home-Assistant-Aktionen](docs/home-assistant.md)
- [Konzept der Home-Assistant-Karte](docs/home-assistant-card.md)
- [Entwicklungsplan](docs/development.md)

## Sicherheit

Keine Home-Assistant-Tokens, Mealie-Zugangsdaten, privaten URLs, Config-Entry-IDs oder sonstigen Secrets in dieses Repository einchecken.
