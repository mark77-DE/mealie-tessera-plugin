# Home Assistant – Mealie-Aktionen

Diese Datei dokumentiert die auf der Zielinstallation bestätigten Aktionsaufrufe. Die Konfigurations-ID ist installationsspezifisch und wird bewusst nicht im Repository gespeichert.

## Rezeptsuche

Bestätigter Aktionsname:

`mealie.get_recipes`

Benötigte Daten:
- `search_terms`: Suchtext, z. B. `sauce`
- `result_limit`: maximale Anzahl Treffer, im Test `3`
- `config_entry_id`: Config-Entry der Mealie-Integration in Home Assistant

Beispiel mit Platzhalter:

```yaml
action: mealie.get_recipes
data:
  config_entry_id: "<MEALIE_CONFIG_ENTRY_ID>"
  search_terms: "sauce"
  result_limit: 3
```

## Einzelnes Rezept abrufen

Bestätigter Aktionsname:

`mealie.get_recipe`

Benötigte Daten:
- `recipe_id`: Mealie-Rezept-ID (UUID)
- `config_entry_id`: Config-Entry der Mealie-Integration in Home Assistant

Beispiel mit Platzhaltern:

```yaml
action: mealie.get_recipe
data:
  config_entry_id: "<MEALIE_CONFIG_ENTRY_ID>"
  recipe_id: "<MEALIE_RECIPE_ID>"
```

## Umsetzung im Tessera-Plugin

Das Plugin soll diese Aktionen nicht direkt als YAML ausführen. Stattdessen werden die unterstützten Home-Assistant-Befehle im Tessera-Manifest deklariert. Die Tessera-App führt sie aus und übermittelt die Antwort an die Firmware.

Vor der Implementierung müssen wir anhand der installierten Tessera-Plugin-Version verifizieren:
- die genaue Manifest-Syntax für die HA-Kommandos und Antwortzuordnung,
- wie dynamische Eingabewerte (Suchtext und Rezept-ID) übergeben werden,
- wie die Config-Entry-ID konfigurierbar gemacht werden kann,
- ob und wie Antworten bei großen Rezepten in mehrere Nachrichten aufgeteilt werden.

## Umgang mit der Config-Entry-ID

Die Config-Entry-ID ist keine Zugangsinformation wie ein Passwort oder Token, aber sie ist an eine konkrete Home-Assistant-Installation gebunden. Daher:
- nicht als festen Wert in den Plugin-Quellcode schreiben,
- nicht in Beispielen mit einem echten Wert veröffentlichen,
- als Plugin-Konfiguration bzw. Home-Assistant-seitigen Parameter vorsehen.

## Noch nicht festgelegt

Die konkreten Rückgabe-Payloads werden nicht aus den Aktionsnamen abgeleitet. Für die Implementierung verwenden wir die bereits getesteten Antwortbeispiele und prüfen weitere Varianten mit realen Rezepten.
