# Entwicklungsplan

Das Projekt wird als gemeinsamer Rezeptbrowser mit zwei Oberflächen entwickelt. Die Home-Assistant-Karte ist die erste vollständige Referenzoberfläche. Tessera folgt als optimierte Oberfläche für das große Küchendisplay.

## Phase 0 – Grundlagen
- [x] GitHub-Repository angelegt
- [x] Mealie-Rezeptsuche in Home Assistant getestet
- [x] Vollständigen Rezeptabruf in Home Assistant getestet
- [x] Beobachtetes Mealie-Datenmodell dokumentiert
- [x] Zielbild mit zwei Frontends festgelegt
- [ ] Gemeinsamen Rezept-Datenvertrag finalisieren
- [ ] Mealie-Kategorien zuverlässig abrufen
- [ ] HA-Service-Rückgaben und Frontend-Zugriff verbindlich prüfen

## Phase 1 – Gemeinsame Datenbasis
- [ ] Rezept-, Zutaten-, Schritt- und Kategorienmodell festlegen
- [ ] Mealie-Suche und Rezeptdetails über Home Assistant abrufen
- [ ] Mealie-Antworten normalisieren
- [ ] Fehler-, Leer- und Ladezustände definieren
- [ ] Kategorienquelle und Filterstrategie festlegen
- [ ] Portionsberechnung fachlich spezifizieren und mit Beispielen testen

## Phase 2 – Home-Assistant-Custom-Card
- [ ] Minimal lauffähiges Custom-Card-Grundgerüst erstellen
- [ ] Konfiguration und Auswahl der Mealie-Integration klären
- [ ] Rezeptsuche und Kategorien integrieren
- [ ] Trefferliste mit Zeiten, Portionen und optionalen Bildern
- [ ] Rezeptdetailansicht mit Zutaten und Anleitung
- [ ] Responsive Layout für Tablet und Desktop
- [ ] In ein bestehendes HA-Dashboard integrieren und testen

## Phase 3 – Kochfunktionen
- [ ] Portionenzahl anpassen
- [ ] Zutaten abhaken
- [ ] Schrittweise Kochansicht
- [ ] Vorheriger/Nächster Schritt
- [ ] Optional Timer-Funktion prüfen

## Phase 4 – Tessera-Plugin für das große Display
- [ ] Tatsächliche Tessera-App-/Plugin-API-Version feststellen
- [ ] Offizielles Plugin-Template und Preview einrichten
- [ ] HA-Kommandos und Antworttransport verifizieren
- [ ] Große Touch-Suchoberfläche umsetzen
- [ ] Kategorien und Trefferliste darstellen
- [ ] Rezeptdetails und Kochmodus umsetzen
- [ ] Nachrichtengrößen und Aufteilung langer Inhalte testen

## Phase 5 – Zielgerät und Stabilisierung
- [ ] Preview mit 1280 × 800 prüfen
- [ ] Touch-Bedienung und Lesbarkeit aus typischem Betrachtungsabstand testen
- [ ] Speicherbedarf und Antwortgrößen prüfen
- [ ] Auf dem Guition JC8012P4A1C-I-W-Y / Hardware V3 testen, sobald vorhanden
- [ ] Installations- und Update-Anleitung dokumentieren

## Entwicklungsregeln
- Kleine, nachvollziehbare Commits.
- Keine Annahmen über nicht getestete Mealie-Felder.
- Gemeinsame Datenmodelle vor UI-spezifischer Implementierung festlegen.
- Keine Secrets oder installationsspezifischen IDs einchecken.
- Bestehende Home-Assistant- und Tessera-Konfiguration nicht ungefragt überschreiben.
