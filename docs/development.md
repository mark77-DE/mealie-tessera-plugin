# Entwicklungsplan

Ziel ist ein installierbares Tessera-Plugin als Rezeptbrowser für das große Küchendisplay. Die Home-Assistant-Seite wird durch vorhandene Mealie-Karten aus dem Marketplace abgedeckt; eine eigene Lovelace-Karte ist nicht geplant.

## Phase 0 – Grundlagen
- [x] GitHub-Repository angelegt
- [x] Mealie-Rezeptsuche in Home Assistant getestet
- [x] Vollständigen Rezeptabruf in Home Assistant getestet
- [x] Beobachtetes Mealie-Datenmodell dokumentiert
- [x] Tessera als einziges Frontend festgelegt
- [x] Zielgerät auf das große 10,1-Zoll-Display begrenzt
- [ ] Tatsächliche Tessera-App-/Plugin-API-Version feststellen
- [ ] Offizielles Plugin-Template und Preview einrichten

## Phase 1 – Datenfluss
- [ ] Exakte Home-Assistant-Service-Namen und Eingabefelder dokumentieren
- [ ] Tessera-Manifest mit `permissions.ha_commands` und passenden Antworten erstellen
- [ ] Dynamische Eingabewerte (Suchtext, Rezept-ID) übergeben
- [ ] Kategorienquelle und Kategorie-Filterstrategie festlegen
- [ ] Suchantwort auf wenige Felder begrenzen
- [ ] Rezeptdetails getrennt abrufen
- [ ] Größenlimits mit realen Rezepten testen

## Phase 2 – Erste Oberfläche
- [ ] Plugin-Komponente aus dem offiziellen Tessera-Template erzeugen
- [ ] Rezeptbrowser als Touch-Oberfläche umsetzen
- [ ] Suche und Kategorienauswahl
- [ ] Suchtreffer darstellen
- [ ] Rezeptdetailansicht mit Zutaten und Anleitung
- [ ] Deutsch und Englisch als Übersetzungen pflegen

## Phase 3 – Kochfunktionen
- [ ] Portionenzahl anpassen
- [ ] Zutaten abhaken
- [ ] Schrittweise Kochansicht
- [ ] Vorheriger/Nächster Schritt
- [ ] Optional Timer-Funktion prüfen

## Phase 4 – Displaytest
- [ ] Preview mit 1280 × 800 prüfen
- [ ] Touch-Bedienung und Lesbarkeit aus typischem Betrachtungsabstand testen
- [ ] Speicherbedarf und Antwortgrößen prüfen
- [ ] Auf dem Guition JC8012P4A1C-I-W-Y / Hardware V3 testen, sobald vorhanden

## Entwicklungsregeln
- Kleine, nachvollziehbare Commits.
- Keine Annahmen über nicht getestete Mealie-Felder.
- Tessera-Dateistruktur aus dem offiziellen Template übernehmen.
- Keine Secrets oder installationsspezifischen IDs einchecken.
- Bestehende Home-Assistant- und Tessera-Konfiguration nicht ungefragt überschreiben.
