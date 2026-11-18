# Entwicklungsplan

## Phase 0 – Grundlagen
- [x] GitHub-Repository angelegt
- [x] Mealie-Rezeptsuche in Home Assistant getestet
- [x] Vollständigen Rezeptabruf in Home Assistant getestet
- [x] Beobachtetes Datenmodell dokumentiert
- [ ] Tessera-Template und Plugin-API-Version festlegen
- [ ] Plugin-Prüfwerkzeuge und Preview-Umgebung einrichten

## Phase 1 – Datenfluss
- [ ] Exakte Home-Assistant-Service-Namen und Eingabefelder der Mealie-Aktionen festhalten
- [ ] Tessera-Manifest mit `permissions.ha_commands` und passenden `answers` erstellen
- [ ] Suchantwort auf wenige Felder begrenzen
- [ ] Rezeptdetails getrennt abrufen
- [ ] Größenlimits mit realen Rezepten testen

## Phase 2 – Erste Oberfläche
- [ ] Plugin-Komponente aus dem offiziellen Tessera-Template erzeugen
- [ ] Rezeptsuche als Touch-Oberfläche umsetzen
- [ ] Suchtreffer darstellen
- [ ] Rezeptdetailansicht mit Zutaten und Anleitung darstellen
- [ ] Deutsch und Englisch als Übersetzungen pflegen

## Phase 3 – Kochfunktionen
- [ ] Portionenzahl anpassen
- [ ] Zutaten abhaken
- [ ] Schrittweise Kochansicht
- [ ] Vorheriger/Nächster Schritt
- [ ] Optional Timer-Funktion prüfen

## Phase 4 – Displaytest
- [ ] Preview mit 1280 × 800 prüfen
- [ ] Touch-Bedienung testen
- [ ] Speicherbedarf und Antwortgrößen prüfen
- [ ] Auf dem Guition JC8012P4A1C-I-W-Y / Hardware V3 testen, sobald vorhanden

## Entwicklungsregeln
- Kleine, nachvollziehbare Commits.
- Keine Annahmen über nicht getestete Mealie-Felder.
- Tessera-Dateistruktur aus dem offiziellen Template übernehmen.
- Vor einer Plugin-Version `tools/check.py` und Tessera-Preview ausführen.
- Bestehende Home-Assistant- und Tessera-Konfiguration nicht ungefragt überschreiben.
