# Mealie Recipe Browser – Implementierungsplan

Dieses Dokument beschreibt den verbindlichen Zielzustand und den aktuellen Umbau auf native Home-Assistant-Funktionen.

## 1. Projektziel

Ein eigenständiger Mealie-Rezeptbrowser als Vollbild-Ansicht in Tessera für das GUITION-Display. Die bestehende Tessera-Startseite und andere Dashboard-Seiten bleiben unverändert.

Ziel-Layout: Kopfbereich, linke Navigation mit Suche und Kategorien sowie eine rechte Rezeptfläche mit 3 Spalten × 8 Reihen. Bis zu 24 Rezepte werden gleichzeitig angezeigt.

## 2. Verbindliche Architektur

Tessera spricht ausschließlich über den nativen Home-Assistant-Command-Kanal mit der **Mealie Tessera Bridge**.

```text
Mealie
  ↕
Offizielle Mealie-Integration in Home Assistant
  ↕ vorhandener authentifizierter Client
Mealie Tessera Bridge (HA Custom Integration)
  ↕ native HA Response Services
Tessera-App / Mealie Recipe Browser
  ↕
GUITION Display
```

Tessera enthält keine Mealie-URL, IP-Adresse, API-Zugangsdaten oder Bridge-Token. Im Tessera-Manifest gibt es keine `permissions.network`, keine Fetch-URLs und keine Secret-Inputs.

## 3. Native Home-Assistant-Services

| Service | Eingaben | Aufgabe |
|---|---|---|
| `mealie_tessera_bridge.get_recipes` | `page`, optional `search`, optional `category` | Eine Seite mit fünf Rezeptzusammenfassungen |
| `mealie_tessera_bridge.get_categories` | keine | Dynamische Kategorienliste |
| `mealie_tessera_bridge.get_recipe` | `slug` | Kompakte Rezeptdetails |

Das Plugin deklariert die drei Aufrufe in `permissions.ha_commands` und fragt sie mit `tessera::send()` ab.

Tessera begrenzt Antworten auf etwa 3 KB und Textfelder auf 48 Bytes. Deshalb bleiben Listenaufrufe bei fünf Rezepten pro Antwort. Die UI sammelt mehrere Antworten für bis zu 24 Kacheln.

## 4. Filter und Pagination

- Suche und Kategorie sind kombinierbar.
- Jede Seitenanfrage übergibt die aktiven Filter erneut.
- Ein Filterwechsel setzt die Displayseite auf 1 und leert den bisherigen Puffer.
- Eine Displayseite umfasst bis zu 24 Rezepte.
- Die Mealie-Seiten werden in Fünferpaketen geladen.
- Antworten aus einem vorherigen Filterzustand dürfen nicht in die neue Liste gelangen.
- Die nächste Displayseite lädt den nächsten Bereich der gefilterten Treffer.

## 5. Aktueller Umsetzungsstand

### Phase A – Home-Assistant-Bridge

- [x] Vorhandene offizielle Mealie-Integration wiederverwenden.
- [x] Eigenen HTTP-Endpunkt und separaten Bridge-Key entfernen.
- [x] Native Response-Services für Rezepte, Kategorien und Details registrieren.
- [x] Bestehende Bridge-Konfiguration migrieren.
- [x] Servicebeschreibungen und Dokumentation ergänzen.
- [ ] Services gegen die installierte Home-Assistant-/Mealie-Version live testen.
- [ ] Mealie-Kategorien und Filterparameter live verifizieren.
- [ ] Fehlerfälle und Antwortgrößen testen.

### Phase B – Tessera-Transport

- [x] Direkte Mealie-HTTP-Fetches aus dem Manifest entfernen.
- [x] Mealie-Token-Input entfernen.
- [x] Tessera auf native HA-Response-Commands umstellen.
- [x] Preview-Fixtures auf HA-Commands umstellen.
- [ ] Preview Bench mit allen Zielboards ausführen.
- [ ] Echte Antworten aus Home Assistant testen.

### Phase C – Rezeptübersicht

- [ ] Dynamische Kategorienliste in der UI anzeigen.
- [ ] Suchfeld anbinden.
- [ ] Kategorie- und Suchfilter kombinieren.
- [ ] 3×8-Kachelraster mit bis zu 24 Treffern vervollständigen.
- [ ] Pufferung und Display-Pagination vollständig implementieren.
- [ ] Veraltete asynchrone Antworten sicher verwerfen.
- [ ] Lade-, Leer- und Fehlerzustände prüfen.

### Phase D – Rezeptdetails und Kochfunktionen

- [x] Erste kompakte Detailantwort mit Zeit, Portionen, sechs Zutaten und drei Schritten.
- [ ] Zutaten und Schritte abschnittsweise nachladen.
- [ ] Strukturierte Mengen und Einheiten für spätere Portionsskalierung erhalten.
- [ ] Portionszahl ändern und Mengen skalieren.
- [ ] Zutaten abhaken und Schritt-für-Schritt-Kochansicht ergänzen.

### Phase E – Tests und Release

- [ ] Offiziellen Tessera Checker ausführen.
- [ ] Preview Bench für die unterstützten großen Displays ausführen.
- [ ] Layout bei 1280×800 prüfen.
- [ ] Touch-Ziele, Lesbarkeit und Speicherverbrauch prüfen.
- [ ] Auf dem realen GUITION-Display testen.

## 6. Wichtige technische Hinweise

- Die HA-Bridge nutzt den bereits authentifizierten Mealie-Client.
- Keine privaten URLs, IP-Adressen, Tokens oder Config-Entry-IDs in Git einchecken.
- Rezeptzusammenfassungen bleiben kompakt.
- Die aktuelle Detailantwort ist bewusst begrenzt. Für vollständige Rezepte ist eine abschnittsweise Übertragung erforderlich.
- Mealie-interne API-Routen und Parameter werden ausschließlich in der HA-Bridge verwendet.
- Keine Hardwaretests behaupten, solange sie nicht tatsächlich durchgeführt wurden.

## 7. Repositorys

- [Mealie Tessera Bridge](https://github.com/mark77-DE/mealie-tessera-bridge)
- [Mealie Tessera Plugin](https://github.com/mark77-DE/mealie-tessera-plugin)
