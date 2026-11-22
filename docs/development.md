# Entwicklungsplan

Ziel ist ein installierbares Tessera-Plugin als Rezeptbrowser für das große 10,1-Zoll-Küchendisplay. Eine eigene Lovelace-Karte ist nicht Bestandteil des Projekts.

## Phase 0 – Grundlagen
- [x] GitHub-Repository angelegt
- [x] Mealie-Rezeptsuche in Home Assistant getestet
- [x] Vollständigen Rezeptabruf in Home Assistant getestet
- [x] Beobachtetes Mealie-Datenmodell dokumentiert
- [x] Tessera als einziges Frontend festgelegt
- [x] Zielgerät auf das große 10,1-Zoll-Display begrenzt
- [x] Tessera Screen Manager 0.4.98 / Firmware 0.61.0 festgestellt
- [x] Ziel-Board-ID `jc8012p4a1v3` anhand des aktuellen Tessera-Boardkatalogs verifiziert
- [x] Plugin API 0.28 und offizielles Plugin-Schema geprüft
- [x] Plugin-Grundgerüst und erste Full-Screen-Ansicht angelegt

## Phase 1 – Datenfluss
- [x] Mealie-Suchaktion als deklarierten Tessera-HA-Befehl eintragen
- [x] Config-Entry-ID als lokale Plugin-Eingabe vorsehen
- [x] Ersten Suchaufruf und Antwortverarbeitung implementieren
- [x] Aufruf von `mealie.get_recipe` für die Detailansicht implementieren
- [x] Repräsentative Such- und Rezeptdetailantworten für die Preview-Bench hinterlegen
- [ ] Tatsächliche Antwortstruktur und Größenlimits mit dem Screen prüfen
- [ ] Lange Zutaten- und Anweisungstexte abschnittsweise übertragen
- [ ] Kategorienquelle und Kategorie-Filterstrategie festlegen
- [ ] Automatische Erkennung der installierten Mealie-Integrationen ermöglichen (benötigt Tessera-API-Erweiterung)

## Phase 2 – Rezeptbrowser
- [x] ESPHome-Komponente und Full-Screen-Tile angelegt
- [x] Erste Trefferliste mit Name, Zeit und Portionen
- [x] Treffer per Touch öffnen
- [x] Erste Rezeptdetailansicht mit Zutaten und Zubereitung
- [ ] Touch-Suchfeld und Bildschirmtastatur
- [ ] Kategorienauswahl und „Alle Rezepte“
- [ ] Treffer mit Bild und Pagination
- [x] Deutsch und Englisch als Übersetzungen pflegen

## Phase 3 – Kochfunktionen
- [ ] Portionenzahl anpassen
- [ ] Zutaten abhaken
- [ ] Schrittweise Kochansicht
- [ ] Vorheriger/Nächster Schritt
- [ ] Optional Timer-Funktion prüfen

## Phase 4 – Vorschau, Test und Veröffentlichung
- [x] Offiziellen Tessera-Plugin-Checker in GitHub Actions einrichten
- [ ] Offizielle Preview-Bench erfolgreich durchlaufen lassen
- [ ] Layout und Lesbarkeit bei 1280 × 800 prüfen
- [ ] `store.png` aus dem geprüften Preview-Bench erzeugen
- [ ] Plugin über „Add with a link“ auf einem Testscreen installieren
- [ ] Touch-Bedienung, Speicherbedarf und Antwortgrößen prüfen
- [ ] Auf dem Guition JC8012P4A1C-I-W-Y / Hardware V3 testen, sobald vorhanden

## Entwicklungsregeln
- Kleine, nachvollziehbare Commits.
- Keine Annahmen über nicht getestete Mealie-Felder.
- Offizielle Tessera-Plugin-Struktur und Prüfwerkzeuge verwenden.
- Keine Secrets oder installationsspezifischen IDs einchecken.
- Bestehende Home-Assistant- und Tessera-Konfiguration nicht ungefragt überschreiben.
