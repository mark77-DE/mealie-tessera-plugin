# Architektur

## Zielbild

Ein gemeinsamer Mealie-Rezeptbrowser erhält zwei eigenständige Oberflächen:

1. eine Lovelace-Custom-Card für Home Assistant,
2. ein Tessera-Plugin für das große 10,1-Zoll-Küchendisplay.

Beide Oberflächen nutzen dieselbe fachliche Datenbasis und sollen dieselben Rezeptfunktionen anbieten. Die Darstellung und Bedienung werden nicht geteilt, sondern jeweils passend zur Plattform umgesetzt.

## Architekturprinzip

```text
                         Mealie
                           |
                  Home-Assistant-Integration
                           |
              zentrale Daten-/Vermittlungsschicht
                           |
              gemeinsamer Rezept-Datenvertrag
                     /             \
                    /               \
        Home-Assistant-Karte     Tessera-Plugin
        Lovelace / JavaScript    ESPHome / C++
```

Home Assistant ist die zentrale Integrationsschicht. Die konkrete technische Form der Vermittlung (HA-Service-Aufrufe, Template-/REST-Helfer oder eine eigene Integration) wird anhand der benötigten Rückgabedaten und der Tessera-Nachrichtengrenzen festgelegt.

## Gemeinsame Zuständigkeiten

### Mealie und Home Assistant
- Verbindung zur Mealie-Instanz
- Rezeptsuche und Abruf vollständiger Rezeptdaten
- Bereitstellung der Kategorien
- sichere Verwaltung installationsspezifischer Zugangsdaten und IDs
- Normalisierung der Mealie-Antworten in einen stabilen, frontend-neutralen Datenvertrag

### Gemeinsamer Datenvertrag und Fachlogik
- einheitliche Felder für Rezepte, Zutaten, Schritte und Kategorien
- Zeitformatierung und Behandlung optionaler Daten
- Portionsfaktor und – sobald fachlich sauber möglich – Mengenberechnung
- definierte Lade-, Leer- und Fehlerzustände

Der gemeinsame Vertrag beschreibt Daten und Verhalten, nicht die konkrete UI-Implementierung. Die Datenmodelle können in beiden Frontends sprachspezifisch abgebildet werden.

## Frontend-Zuständigkeiten

### Home-Assistant-Custom-Card
- Einbettung in bestehende Lovelace-Dashboards
- Suche, Kategorien, Trefferliste und Rezeptdetails
- responsive Darstellung für Tablet, Desktop und HA-Touchscreens
- Kochmodus innerhalb der Karte

Die Karte soll sich in bestehende Dashboards integrieren lassen und keine separate HA-Installation oder ein eigenes Dashboard voraussetzen.

### Tessera-Plugin
- zusätzlicher Einstieg aus dem bestehenden Tessera-Dashboard
- Touch-Oberfläche optimiert für 1280 × 800 Pixel
- große Trefferkarten und gut lesbare Rezeptdetails
- Kochmodus mit großen Schritt-Schaltflächen
- Rückkehr zum bestehenden Dashboard ohne dessen Layout zu verändern

Kleine Tessera-Displays sind vorerst ausdrücklich nicht Ziel der Umsetzung.

### Tessera-App und Firmware
Die Tessera-App führt deklarierte Home-Assistant-Befehle aus und reicht Antworten an das Plugin weiter. Das Plugin soll keine ungeschützte direkte Verbindung zu Mealie benötigen. Die konkrete Manifest-Syntax und die Nachrichtengrenzen werden vor der Implementierung anhand der tatsächlich eingesetzten Tessera-Version geprüft.

## Datenfluss

1. Ein Frontend fordert Kategorien, Suchtreffer oder ein Rezept an.
2. Die Anfrage wird über die für das jeweilige Frontend vorgesehene HA-Schnittstelle ausgeführt.
3. Home Assistant ruft die Mealie-Integration bzw. den festgelegten Kategorien-Endpunkt auf.
4. Die Rückgabe wird in das gemeinsame Datenmodell überführt.
5. Das jeweilige Frontend rendert die Daten plattformspezifisch.

Suchtreffer und Rezeptdetails werden getrennt geladen. Für Tessera werden große Listen und lange Texte zusätzlich in transportgerechte Pakete aufgeteilt.

## Technische Leitplanken

- Bestehende Home-Assistant- und Tessera-Dashboards bleiben unangetastet.
- Keine Zugangsdaten, Tokens, privaten URLs oder Config-Entry-IDs im Repository.
- Keine Mealie-API-Annahmen ohne Test gegen die verwendete Version.
- Gemeinsame Fachlogik, aber getrennte UI-Implementierungen.
- Suchergebnisse kompakt halten; vollständige Details erst bei Auswahl laden.
- Tessera-API-Version so niedrig wie möglich wählen, aber nur nach Prüfung der benötigten Funktionen.
- Keine vorzeitige Festlegung auf eine eigene HA-Integration, solange ein schlankerer und stabiler Weg genügt.
