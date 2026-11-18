# Mealie for Tessera

Ein Tessera-Plugin zum Suchen, Anzeigen und Kochen von Rezepten aus einer Mealie-Instanz.

> Entwicklungsstand: technische Grundlagen dokumentiert; das Plugin ist noch nicht installierbar.

## Ziel

Das Plugin ergänzt ein bestehendes Tessera-Dashboard um einen Rezeptbrowser. Die normale Tessera-Oberfläche bleibt erhalten.

Geplante Funktionen:
- Rezepte direkt auf dem Touchdisplay suchen
- Suchtreffer als Liste anzeigen
- Rezeptdetails mit Zutaten und Zubereitung darstellen
- Portionenzahl anpassen
- Kochmodus mit Zutaten-Checkliste und Schritt-Navigation

## Architektur

- **Mealie:** Rezeptdaten und Suche
- **Home Assistant:** Backend und Aufruf der Mealie-Integration
- **Tessera-App:** führt deklarierte Home-Assistant-Befehle aus und übermittelt Antworten
- **Tessera-Firmware:** rendert die Plugin-Oberfläche auf dem Display

Das Plugin baut keine eigene Netzwerkverbindung vom Display zu Mealie auf. Die konkrete Tessera-Struktur wird aus dem offiziellen Template übernommen.

## Projektstatus

Die Mealie-Aktionen wurden in Home Assistant getestet: Rezeptsuche (Suchbegriff `sauce`) und vollständiger Abruf des Rezepts `Pizzasauce`. Die beobachteten Felder stehen in [docs/mealie-data-model.md](docs/mealie-data-model.md).

## Dokumentation

- [Architektur](docs/architecture.md)
- [Beobachtetes Mealie-Datenmodell](docs/mealie-data-model.md)
- [Entwicklungsplan](docs/development.md)

Technische Grundlage: [Tessera Plugin-Dokumentation](https://github.com/MaxGramser/tessera-plugins).

## Sicherheit

Keine Home-Assistant-Tokens, Mealie-Zugangsdaten, privaten URLs oder sonstigen Secrets in dieses Repository einchecken.
