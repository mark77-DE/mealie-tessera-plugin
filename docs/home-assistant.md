# Home-Assistant-Aktionen

## Rezeptsuche

Bestätigter Aktionsname:

`mealie.get_recipes`

Benötigte Daten:
- `search_terms`: Suchtext, z. B. `sauce`
- `result_limit`: maximale Anzahl Treffer
- `config_entry_id`: Config-Entry der Mealie-Integration in Home Assistant

Beispiel zur manuellen Prüfung in Home Assistant:

```yaml
action: mealie.get_recipes
data:
  config_entry_id: "<MEALIE_CONFIG_ENTRY_ID>"
  search_terms: "sauce"
  result_limit: 3
```

Das Tessera-Plugin ruft dieselbe Aktion als deklarierte Antwortaktion auf:

```yaml
permissions:
  ha_commands:
    - "call_service:mealie.get_recipes"
```

Die Config-Entry-ID wird beim Hinzufügen des Plugins lokal als Eingabe erfasst. Sie gehört nicht in dieses Repository.

## Einzelnes Rezept abrufen

Bestätigter Aktionsname:

`mealie.get_recipe`

Benötigte Daten:
- `recipe_id`: Mealie-Rezept-ID (UUID)
- `config_entry_id`: Config-Entry der Mealie-Integration

Beispiel zur manuellen Prüfung:

```yaml
action: mealie.get_recipe
data:
  config_entry_id: "<MEALIE_CONFIG_ENTRY_ID>"
  recipe_id: "<MEALIE_RECIPE_ID>"
```

Diese Aktion wird in einer folgenden Plugin-Ausbaustufe ergänzt, wenn ein Treffer geöffnet wird.

## Transportgrenzen

Tessera übermittelt die Antwort einer Home-Assistant-Aktion an das Plugin. Die Antwort ist auf ungefähr 3 KB begrenzt; längere Texte werden gekürzt und Listen bei Bedarf verkürzt. Deshalb begrenzt die erste Implementierung die Suche auf drei Treffer. Zutaten und Anweisungen werden später getrennt geladen und müssen bei langen Rezepten in kleinere Abschnitte aufgeteilt werden.
