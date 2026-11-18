# Entwicklungsplan

Ziel ist ein installierbares Tessera-Plugin als Rezeptbrowser für das große Küchendisplay. Eine eigene Lovelace-Karte ist nicht Bestandteil des Projekts.

## Phase 0 – Grundlagen
- [x] GitHub-Repository angelegt
- [x] Mealie-Rezeptsuche in Home Assistant getestet
- [x] Vollständigen Rezeptabruf in Home Assistant getestet
- [x] Beobachtetes Mealie-Datenmodell dokumentiert
- [x] Tessera als einziges Frontend festgelegt
- [x] Zielgerät auf das große 10,1-Zoll-Display begrenzt
- [x] Tessera Screen Manager 0.4.98 / Firmware 0.61.0 festgestellt
- [x] Plugin API 0.28 und offizielles Plugin-Schema geprüft
- [x] Plugin-Grundgerüst und erste Full-Screen-Ansicht angelegt

## Phase 1 – Datenfluss
- [x] Mealie-Suchaktion als deklarierten Tessera-HA-Befehl eintragen
- [x] Config-Entry-ID als lokale Plugin-Eingabe vorsehen
- [x] Ersten Suchaufruf und Antwortverarbeitung implementieren
- [ ] Tatsächliche Antwortstruktur und Größenlimits mit dem Screen testen
- [ ] Vollständigen Rezeptabruf über `mealie.get_recipe` implementieren
- [ ] Lange Zutaten- und Anweisungstexte in transportgerechte Pakete aufteilen
- [ ] Kategorienquelle und Kategorie-Filterstrategie festlegen

## Phase 2 – Rezeptbrowser
- [x] ESPHome-Komponente aus dem offiziellen Tessera-Plugin-Muster angelegt
- [x] Full-Screen-Tile für das große Display angelegt
- [x] Erste Trefferliste mit Name, Zeit und Portionen
- [ ] Touch-Suchfeld und Bildschirmtastatur
- [ ] Kategorienauswahl und „Alle Rezepte“
- [ ] Treffer mit Bild und Pagination
- [ ] Rezeptdetailansicht mit Zutaten und Anleitung
- [ ] Deutsch und Englisch als Übersetzungen pflegen

## Phase 3 – Kochfunktionen
- [ ] Portionenzahl anpassen
- [ ] Zutaten abhaken
- [ ] Schrittweise Kochansicht
- [ ] Vorheriger/Nächster Schritt
- [ ] Optional Timer-Funktion prüfen

## Phase 4 – Test und Veröffentlichung
- [ ] Plugin-Manifest mit Tessera-Prüfwerkzeug validieren
- [ ] Preview mit 1280 × 800 prüfen
- [ ] Plugin über „Add with a link“ auf einem Testscreen installieren
- [ ] Touch-Bedienung, Lesbarkeit, Speicherbedarf und Antwortgrößen prüfen
- [ ] Auf dem Guition JC8012P4A1C-I-W-Y / Hardware V3 testen, sobald vorhanden

## Entwicklungsregeln
- Kleine, nachvollziehbare Commits.
- Keine Annahmen über nicht getestete Mealie-Felder.
- Tessera-Dateistruktur aus dem offiziellen Template übernehmen.
- Keine Secrets oder installationsspezifischen IDs einchecken.
- Bestehende Home-Assistant- und Tessera-Konfiguration nicht ungefragt überschreiben.
