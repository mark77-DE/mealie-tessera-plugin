# Home-Assistant-Aktionen

## Rezeptsuche

Bestätigter Aktionsname: `mealie.get_recipes`

Benötigte Daten:
- `search_terms`: Suchtext, z. B. `sauce`
- `result_limit`: maximale Anzahl Treffer
- `config_entry_id`: Config-Entry der Mealie-Integration in Home Assistant

```yaml
action: mealie.get_recipes
data:
  config_entry_id: "<MEALIE_CONFIG_ENTRY_ID>"
  search_terms: "sauce"
  result_limit: 3
```

## Rezeptdetails

Bestätigter Aktionsname: `mealie.get_recipe`

```yaml
action: mealie.get_recipe
data:
  config_entry_id: "<MEALIE_CONFIG_ENTRY_ID>"
  recipe_id: "<MEALIE_RECIPE_ID>"
```

Das Plugin öffnet die Detailkarte nach einem Tipp auf einen Treffer und ruft Zutaten und Zubereitung ab.

## Berechtigungen

```yaml
permissions:
  ha_commands:
    - "call_service:mealie.get_recipes"
    - "call_service:mealie.get_recipe"
```

Die Config-Entry-ID wird weiterhin als lokale Plugin-Eingabe erfasst. Tessera blockiert ausdrücklich den Zugriff auf `config_entries/get`; eine automatische Auflistung installierter Integrationen ist mit der derzeitigen Plugin-Schnittstelle daher nicht möglich. Die ID gehört nicht in dieses Repository.

## Transportgrenzen

Tessera übermittelt die Antwort einer Home-Assistant-Aktion an das Plugin. Die Antwort ist auf ungefähr 3 KB begrenzt; längere Texte und Listen können gekürzt werden. Die Detailansicht begrenzt deshalb Zutaten und Anweisungen jeweils auf etwa 1.050 Zeichen. Für sehr lange Rezepte ist eine spätere abschnittsweise Abfrage erforderlich.
