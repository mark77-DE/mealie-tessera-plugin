# Architektur

## Zielbild

Das Projekt ist ein Tessera-Plugin als Rezeptbrowser für das große 10,1-Zoll-Küchendisplay. Es ergänzt das bestehende Tessera-Dashboard, ersetzt es aber nicht.

## Architekturprinzip

```text
       Mealie
          |
  Home-Assistant-Mealie-Integration
          |
  deklarierter HA-Befehl: mealie.get_recipes / mealie.get_recipe
          |
    Tessera-App (führt HA-Aktion aus)
          |
    Tessera-Plugin (ESPHome-Komponente)
          |
 Suche · Kategorien · Treffer · Details · Kochmodus
```

Das Plugin greift nicht direkt auf Mealie zu. Home Assistant bleibt Vermittlungsschicht und verwaltet die Verbindung zur Mealie-Instanz.

## Zuständigkeiten

### Mealie
- Quelle für Rezepte, Kategorien, Zutaten und Zubereitungsschritte
- liefert Suchergebnisse und vollständige Rezeptdetails

### Home Assistant
- Verbindung zur Mealie-Instanz über die installierte Integration
- Aktionen `mealie.get_recipes` und `mealie.get_recipe`
- Kategorienbereitstellung über einen noch zu klärenden Weg
- Verwaltung installationsspezifischer Zugangsdaten und IDs

### Tessera-App
- liest das Plugin-Manifest
- führt nur die im Manifest deklarierten Home-Assistant-Befehle aus
- übermittelt die Antworten an die Plugin-Firmware

### Tessera-Plugin
- Touch-Eingabe und Navigation
- Rezeptsuche und Kategorienauswahl
- Trefferliste und Rezeptdetails
- Portionenfaktor und Zutaten-Checkliste
- Kochmodus und Schritt-Navigation

## Aktueller Datenfluss

1. Das Full-Screen-Tile wird im Tessera-Layout geöffnet.
2. Der im Tile-Inspector hinterlegte Suchbegriff wird gelesen.
3. Das Plugin sendet `call_service:mealie.get_recipes` mit Config-Entry-ID, Suchbegriff und Ergebnislimit an die Tessera-App.
4. Die App führt die Aktion in Home Assistant aus.
5. Die Antwort wird an `on_message()` des Plugins übergeben.
6. Das Plugin liest die Rezeptliste und zeigt Name, Gesamtzeit und Portionen an.

Der aktuelle Stand ist ein erster vertikaler Datenfluss. Die Antwortstruktur muss noch auf dem realen Screen verifiziert werden. Danach folgen Rezeptdetails und die Touch-Suche.

## Technische Leitplanken

- Bestehendes Tessera-Dashboard bleibt unangetastet.
- Zielauflösung: 1280 × 800 Pixel.
- Kleine Tessera-Displays sind kein Ziel.
- Plugin API 0.28 für Tessera 0.4.98 / Firmware 0.61.0.
- Config-Entry-ID wird als lokale Plugin-Eingabe konfiguriert, nicht eingecheckt.
- Keine Zugangsdaten, Tokens oder privaten URLs im Repository.
- Lange Texte und große Listen werden in transportgerechte Pakete aufgeteilt.

## Offene technische Kernfrage: Kategorien

Die Mealie-API stellt eine Kategorienliste über `GET /api/organizers/categories` bereit. Die Home-Assistant-Mealie-Integration bietet nach bisherigem Test keine eigene Aktion zum Auflisten der Kategorien; ihr Kategorien-Sensor liefert nur die Anzahl. `mealie.get_recipes` nimmt einen Freitext-Suchbegriff, aber keine Kategorie-ID entgegen.

Vor der Kategorien-UI muss geklärt werden, wie Home Assistant die Kategorien sicher an Tessera liefern kann und wie die Auswahl einer Kategorie in eine Mealie-Abfrage übersetzt wird.
