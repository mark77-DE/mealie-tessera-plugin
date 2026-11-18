# Architektur

## Zielbild

Das Projekt ist ein Tessera-Plugin als Rezeptbrowser für das große 10,1-Zoll-Küchendisplay. Es ergänzt das bestehende Tessera-Dashboard, ersetzt es aber nicht.

## Architekturprinzip

```text
       Mealie
          |
  Home-Assistant-Mealie-Integration
          |
  deklarierte HA-Kommandos / Antworttransport
          |
    Tessera-App und Firmware
          |
      Tessera-Plugin
          |
 Suche · Kategorien · Treffer · Details · Kochmodus
```

Home Assistant ist die Vermittlungsschicht zwischen Plugin und Mealie. Das Plugin soll keine ungeschützte direkte Verbindung zu Mealie benötigen.

## Zuständigkeiten

### Mealie
- Quelle der Rezeptdaten, Kategorien, Zutaten und Zubereitungsschritte
- liefert Suchergebnisse und vollständige Rezeptdetails

### Home Assistant
- Verbindung zur Mealie-Instanz über die installierte Integration
- Aufruf von `mealie.get_recipes` und `mealie.get_recipe`
- Bereitstellung der Kategorien über einen noch festzulegenden sicheren Weg
- Verwaltung installationsspezifischer Zugangsdaten und IDs

### Tessera-App
- liest das Plugin-Manifest
- führt deklarierte Home-Assistant-Befehle aus
- übergibt Antworten an die Plugin-Firmware

### Tessera-Plugin
- Touch-Eingabe und Navigation
- Rezeptsuche und Kategorienauswahl
- Trefferliste und Rezeptdetails
- Portionenfaktor und Zutaten-Checkliste
- Kochmodus und Schritt-Navigation

## Datenfluss

1. Der Nutzer öffnet den Rezeptbereich über das bestehende Tessera-Dashboard.
2. Das Plugin fordert Kategorien oder Suchtreffer an.
3. Die Tessera-App führt den im Manifest deklarierten Home-Assistant-Befehl aus.
4. Home Assistant ruft die Mealie-Integration bzw. den festgelegten Kategorien-Endpunkt auf.
5. Die Tessera-App übergibt die Antwort an das Plugin.
6. Das Plugin stellt die Daten dar.
7. Beim Öffnen eines Rezepts werden die vollständigen Details separat geladen.

Suchergebnisse bleiben kompakt. Zutaten und Anweisungen werden erst beim Öffnen eines Rezepts angefordert.

## Technische Leitplanken

- Vorhandenes Tessera-Dashboard bleibt unangetastet.
- Zielauflösung: 1280 × 800 Pixel.
- Kleine Tessera-Displays sind kein Ziel.
- Keine Zugangsdaten, Tokens, privaten URLs oder Config-Entry-IDs im Repository.
- Keine Annahmen über nicht getestete Mealie-Felder.
- Lange Texte und große Listen werden in transportgerechte Pakete aufgeteilt.
- Tessera-API-Version so niedrig wie möglich wählen, aber benötigte Funktionen vorher prüfen.
- Die tatsächliche Manifest-Syntax, dynamische Eingabewerte und Antwortzuordnung werden anhand der installierten Tessera-Version verifiziert.

## Offene technische Kernfrage: Kategorien

Die Mealie-API stellt eine Kategorienliste über `GET /api/organizers/categories` bereit. Die Home-Assistant-Mealie-Integration bietet nach bisherigem Test keine eigene Aktion zum Auflisten der Kategorien; ihr Kategorien-Sensor liefert nur die Anzahl. `mealie.get_recipes` nimmt einen Freitext-Suchbegriff, aber keine Kategorie-ID entgegen.

Vor der UI-Implementierung muss geklärt werden, wie Home Assistant die Kategorien sicher an Tessera liefern kann und wie die Auswahl einer Kategorie in eine Mealie-Abfrage übersetzt wird.
