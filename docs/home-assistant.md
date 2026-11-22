# Home-Assistant-Aktionen

Das Plugin verwendet die Home-Assistant-Mealie-Integration. Die Verbindung zu Mealie und die Zugangsdaten bleiben in Home Assistant.

## Config-Entry-ID der Mealie-Integration ermitteln

Die Config-Entry-ID ist eine interne, installationsspezifische Kennung. Sie ist weder der Integrationsname `mealie` noch eine Entity-ID wie `sensor.mealie_recipes`. Du musst sie auch nicht über Entwicklerwerkzeuge oder Sensorattribute suchen.

Home Assistant bietet dafür direkt eine Funktion zum Kopieren der Eintrag-ID:

1. Öffne **Einstellungen → Geräte & Dienste**.
2. Suche den Integrationseintrag **Mealie** und öffne dessen Menü über die drei Punkte.
3. Wähle **Eintrag-ID kopieren**.
4. Füge den kopierten Wert in Tessera in die lokale Plugin-Eingabe **config_entry_id** ein.

<text>Hinweis:</text> Die Schaltfläche **Eintrag-ID kopieren** befindet sich im Drei-Punkte-Menü des Integrationseintrags. Sie ist nicht das Menü einer einzelnen Entität oder eines Geräts.

**Bei mehreren Mealie-Instanzen:** Kopiere die Eintrag-ID genau des Mealie-Integrationseintrags, den der Rezeptbrowser verwenden soll. Jede konfigurierte Instanz hat eine eigene ID.

Die Config-Entry-ID wird nur lokal in Tessera eingetragen und darf nicht in dieses Repository oder in öffentliche Screenshots übernommen werden.

## Rezeptübersicht ohne Suchfilter

Bestätigter Aktionsname: `mealie.get_recipes`

Für die Übersicht wird `search_terms` bewusst weggelassen. Home Assistant dokumentiert dieses Feld als optional. `result_limit` begrenzt die Anzahl der zurückgegebenen Rezepte.

```yaml
action: mealie.get_recipes
data:
  config_entry_id: "<MEALIE_CONFIG_ENTRY_ID>"
  result_limit: 12
```

Das Plugin zeigt derzeit maximal 12 Einträge an. Eine vollständige Auflistung größerer Mealie-Bibliotheken benötigt eine spätere Pagination; der Suchfilter ist davon unabhängig und bleibt deaktiviert.

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

Die Config-Entry-ID wird aktuell als lokale Plugin-Eingabe erfasst. Tessera stellt Plugins derzeit keine freigegebene Schnittstelle bereit, um installierte Config-Entries aufzulisten und daraus eine Mealie-Instanz auswählen zu lassen.

## Transportgrenzen

Tessera übermittelt die Antwort einer Home-Assistant-Aktion an das Plugin. Die Antwort ist auf ungefähr 3 KB begrenzt; längere Texte und Listen können gekürzt werden. Die Detailansicht begrenzt deshalb Zutaten und Anweisungen jeweils auf etwa 1.050 Zeichen. Für sehr lange Rezepte ist eine spätere abschnittsweise Abfrage erforderlich.
