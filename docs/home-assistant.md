# Home-Assistant-Aktionen

Das Plugin verwendet die Home-Assistant-Mealie-Integration. Die Verbindung zu Mealie und die Zugangsdaten bleiben in Home Assistant.

## Config-Entry-ID der Mealie-Integration ermitteln

Die Config-Entry-ID ist eine interne, installationsspezifische Kennung. Sie ist nicht mit dem Integrationsnamen `mealie` oder einer Entity-ID wie `sensor.mealie_recipes` identisch.

Am einfachsten lässt sie sich über eine vorhandene Entität der gewünschten Mealie-Integration ermitteln:

1. Öffne in Home Assistant **Einstellungen → Geräte & Dienste → Entitäten**.
2. Filtere die Liste nach der Integration **Mealie**.
3. Suche eine Entität, die von der gewünschten Mealie-Instanz bereitgestellt wird, und notiere ihre Entity-ID, zum Beispiel `sensor.mealie_recipes`. Der konkrete Entity-Name kann bei dir abweichen.
4. Öffne **Entwicklerwerkzeuge → Template**.
5. Füge diese Vorlage ein und ersetze die Beispiel-Entity-ID durch deine tatsächliche Entity-ID:

```jinja
{{ config_entry_id('sensor.mealie_recipes') }}
```

6. Home Assistant zeigt darunter die Config-Entry-ID an. Kopiere diesen Wert in die lokale Plugin-Eingabe **config_entry_id** in Tessera.

Die Template-Funktion `config_entry_id(entity_id)` ist in Home Assistant Core ab Version 2023.3 verfügbar. Sie liefert die Config-Entry-ID der Integration, zu der die angegebene Entität gehört. Bei YAML-definierten Entitäten oder Helfern kann das Ergebnis `None` sein. Verwende deshalb eine echte Entität der Mealie-Integration.

**Bei mehreren Mealie-Instanzen:** Verwende eine Entität derjenigen Instanz, die der Rezeptbrowser verwenden soll. Jede Integrationseinrichtung hat ihre eigene Config-Entry-ID.

### Alternative, falls keine passende Entität vorhanden ist

Die ID steht auch in der Home-Assistant-Konfigurationsdatei `.storage/core.config_entries` im Verzeichnis `/config`. Suche dort den Eintrag mit `"domain":"mealie"` und prüfe den zugehörigen Titel, bevor du den Wert aus `"entry_id"` verwendest.

Die Datei ist eine interne JSON-Datei. Öffne sie nur lesend und ändere ihren Inhalt nicht. Home Assistant sollte währenddessen nicht manuell in dieser Datei bearbeitet werden.

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

Die Config-Entry-ID wird aktuell als lokale Plugin-Eingabe erfasst. Tessera stellt Plugins derzeit keine freigegebene Schnittstelle bereit, um installierte Config-Entries aufzulisten und daraus eine Mealie-Instanz auswählen zu lassen. Die ID wird nicht im Repository gespeichert.

## Transportgrenzen

Tessera übermittelt die Antwort einer Home-Assistant-Aktion an das Plugin. Die Antwort ist auf ungefähr 3 KB begrenzt; längere Texte und Listen können gekürzt werden. Die Detailansicht begrenzt deshalb Zutaten und Anweisungen jeweils auf etwa 1.050 Zeichen. Für sehr lange Rezepte ist eine spätere abschnittsweise Abfrage erforderlich.
