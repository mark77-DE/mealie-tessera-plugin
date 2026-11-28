# Mealie Recipe Browser – Implementierungsplan für Tessera

> Dieses Dokument ist die verbindliche Projektübergabe für Entwickler und unterstützende KI-Systeme. Vor Änderungen zuerst dieses Dokument, `docs/architecture.md`, `docs/shared-data-contract.md` und die Bridge-Dokumentation lesen.

## 1. Projektziel

Ein eigenständiger Mealie-Rezeptbrowser als Vollbild-Ansicht in Tessera für das GUITION-Display. Die bestehende Tessera-Startseite und andere Dashboard-Seiten bleiben unverändert.

Zielgerät: GUITION mit 1280 × 800 Pixeln. Die Rezeptübersicht nutzt den gesamten Bildschirm.

## 2. Ziel-Layout

Die Oberfläche ist in einen Kopfbereich, eine linke Navigationsspalte und eine rechte Rezeptfläche aufgeteilt.

```text
┌──────────────────────────────────────────────────────────────────────┐
│                           Mealie Rezepte                              │
├───────────────────┬──────────────────────────────────────────────────┤
│ Suche             │  Rezept 01 │ Rezept 02 │ Rezept 03                │
│ [______________]  │────────────┼────────────┼────────────             │
│                   │  Rezept 04 │ Rezept 05 │ Rezept 06                │
│ Alle Rezepte      │────────────┼────────────┼────────────             │
│ Kategorie A       │  Rezept 07 │ Rezept 08 │ Rezept 09                │
│ Kategorie B       │────────────┼────────────┼────────────             │
│ Kategorie C       │  ...       │ ...        │ ...                     │
│ ...               │                                              ...  │
│                   │  bis zu 24 Rezepte (3 Spalten × 8 Reihen)         │
│                   │                                                  │
│                   │  ‹ Zurück          Seite 1 / N          Weiter › │
└───────────────────┴──────────────────────────────────────────────────┘
```

### Kopfbereich
- Überschrift: **Mealie Rezepte**.
- Der Kopfbereich erstreckt sich über die gesamte Displaybreite.

### Linke Navigationsspalte
- Suchfeld.
- Dynamisch geladene Kategorien.
- Eintrag **Alle Rezepte** als Standardauswahl.
- Kategorien sind Single-Select; die Suche kann zusätzlich zur Kategorie aktiv sein.
- Lange Kategorienamen müssen lesbar gekürzt oder umgebrochen werden.

### Rechte Rezeptfläche
- Drei Spalten und acht Reihen.
- Maximal 24 Rezeptkacheln gleichzeitig.
- Eine Kachel zeigt mindestens Rezeptname, Gesamtzeit und Portionen.
- Leere Plätze bei weniger als 24 Treffern bleiben leer und erzeugen keine Dummy-Rezepte.

### Pagination
- Navigation **Zurück / Weiter** und Anzeige der aktuellen Seite.
- Die tatsächliche Seitenzahl kommt aus den Mealie-Pagination-Metadaten.
- Die Tessera-Ansicht fordert fünf Rezepte je Bridge-Anfrage an und sammelt mehrere Antworten bis zu 24 Kacheln gefüllt sind oder keine weiteren Treffer existieren.
- Beim Wechsel der Displayseite wird die nächste Gruppe von bis zu 24 Treffern geladen.

## 3. Filtersemantik – verbindlich

Die Filter gelten für die gesamte Trefferliste und nicht nur für eine einzelne Mealie-Teilantwort.

| Aktion | Erwartetes Verhalten |
|---|---|
| Rezeptbrowser öffnen | Alle Rezepte, Seite 1 |
| Kategorie auswählen | Kategorie aktivieren, Seite 1 neu laden |
| Suche ändern | Suche anwenden, Seite 1 neu laden |
| Suche + Kategorie | Beide Filter gleichzeitig anwenden |
| Weiter blättern | Nächste 24 Treffer mit unveränderten Filtern |
| Zurück blättern | Vorherige 24 Treffer mit unveränderten Filtern |
| Alle Rezepte | Kategorie zurücksetzen; Suchtext bleibt nur dann bestehen, wenn er bewusst nicht gelöscht wird |

**Wichtig:** Seite 2 darf nicht plötzlich ungefilterte Rezepte anzeigen. Suche und Kategorie werden bei jeder Anfrage erneut an die Bridge übergeben.

Ein Wechsel von Kategorie oder Suchtext setzt die Tessera-Seitennummer auf 1 und verwirft den bisherigen Seitenpuffer.

## 4. Datenarchitektur

Tessera spricht ausschließlich mit der Home-Assistant-Bridge, nicht direkt mit Mealie.

- Bridge-Projekt: [mark77-DE/mealie-tessera-bridge](https://github.com/mark77-DE/mealie-tessera-bridge)
- Basis-URL: `/api/mealie-tessera`
- Authentifizierung: `Authorization: Bearer <Bridge-Key>`

| Tessera-Anfrage | Bridge-Endpunkt | Zweck |
|---|---|---|
| Rezeptseite | `GET /recipes?page=N&search=...&category=...` | maximal fünf Rezeptzusammenfassungen |
| Kategorien | `GET /categories` | dynamische Kategorien aus Mealie |
| Detail | `GET /recipe/{slug}` | vollständige Daten eines ausgewählten Rezepts |

Der lange Mealie-API-Token verbleibt in Home Assistant. Tessera erhält nur den separaten Bridge-Key. Der Key darf nicht in Firmware, Screenshots, Fixtures oder Git eingecheckt werden.

### Datenverarbeitung und Speicherstrategie

- Für die Kachelübersicht nur Zusammenfassungsdaten laden.
- Fünf Rezepte je Bridge-Aufruf; Antworten puffern, bis bis zu 24 Kacheln gefüllt sind.
- Nicht die vollständige Rezeptdatenbank auf einmal laden.
- Gesamtzahl und Seitenzahl aus der Bridge-/Mealie-Antwort übernehmen.
- Rezeptdetails erst nach Touch auf eine Kachel laden.
- Strukturierte Zutatenfelder aus dem Detailobjekt unverändert erhalten. Nicht nur `display` speichern: spätere Portionsanpassung benötigt u. a. `quantity`, `unit` und `food`.

## 5. Bedienungs- und Zustandsmodell

Der Zustand der Rezeptübersicht umfasst mindestens:

- `searchText`
- `selectedCategoryId` (leer = alle Kategorien)
- `displayPage` (1-basiert; eine Displayseite entspricht bis zu 24 Treffern)
- `totalRecipes` und `totalPages` für die aktuelle Filterkombination
- `recipeBuffer` mit maximal 24 Rezeptzusammenfassungen
- `isLoading` und einen sichtbaren Fehlerstatus

Ein Filterwechsel muss alte asynchrone Antworten verwerfen, damit Ergebnisse einer vorherigen Suche nicht in der neuen Liste erscheinen.

Die Bridge-Seitennummer und die Tessera-Displayseite sind nicht dasselbe: Bei fünf Einträgen pro Bridge-Aufruf werden für eine Displayseite bis zu fünf Bridge-Seiten benötigt. Für die nächste Displayseite wird der entsprechende nächste Bereich angefordert. Die Implementierung muss dabei die Mealie-Seitennummern aus dem aktuellen Filterzustand ableiten.

## 6. Umsetzungsreihenfolge

### Phase A – Bridge
- [x] Vorhandene Mealie-Integration in Home Assistant wiederverwenden
- [x] Separaten Bridge-Key bereitstellen
- [x] Rezeptdetail-Endpunkt
- [x] Fünf Rezepte je Listenanfrage
- [ ] Rohes Pagination-Metadatum vollständig durchreichen und live verifizieren
- [ ] Kategorien-Endpunkt gegen die installierte Mealie-Version verifizieren
- [ ] Suchparameter und Kategorie-ID-Filter live verifizieren
- [ ] Tests für leere Treffer, letzte Seite, ungültige Filter und Authentifizierung

### Phase B – Tessera-Rezeptübersicht
- [ ] Direkte Mealie-Verbindung und Mealie-Token-Eingabe durch Bridge-Verbindung ersetzen
- [ ] Konfigurierbare Bridge-Basis-URL und Bridge-Key als Plugin-Einstellungen, sofern Tessera dies unterstützt
- [ ] Kopfbereich und linke Navigationsspalte umsetzen
- [ ] Kategorien dynamisch laden und anzeigen
- [ ] Suche implementieren
- [ ] Suche und Kategorie kombinieren
- [ ] 3×8-Kachelraster mit bis zu 24 Treffern
- [ ] Pufferung der fünfteiligen Bridge-Antworten
- [ ] Pagination mit stabilen Filtern
- [ ] Lade-, Leer- und Fehlerzustände

### Phase C – Rezeptdetails
- [ ] Vollständige Details bei Auswahl laden
- [ ] Zutaten und Schritte ohne willkürliche Kürzung darstellen
- [ ] Strukturierte Zutaten für spätere Portionsanpassung erhalten

### Phase D – spätere Kochfunktionen
- [ ] Portionszahl ändern und Mengen skalieren
- [ ] Zutaten abhaken
- [ ] Schritt-für-Schritt-Kochansicht
- [ ] Vorheriger/nächster Schritt
- [ ] Optionaler Timer

### Phase E – Tests und Release
- [ ] Preview Bench
- [ ] Layout bei 1280×800 prüfen
- [ ] Touch-Ziele und Lesbarkeit prüfen
- [ ] Speicherbedarf und Ladezeiten prüfen
- [ ] Test auf dem realen GUITION-Display

## 7. Regeln für weitere KI-Systeme und Entwickler

1. **Vor jeder Änderung Repository-Dokumentation lesen.** Insbesondere dieses Dokument und den gemeinsamen Datenvertrag.
2. **Keine erfundenen API-Felder oder Routen.** Mealie-Version und echte Antwort prüfen. Die lokale Mealie-API-Dokumentation unter `/docs` ist maßgeblich.
3. **Bridge statt direkter Mealie-Zugriff.** Tessera darf keinen Mealie-Token verlangen oder speichern.
4. **Filterzustand erhalten.** Kategorie und Suche müssen über alle Seiten hinweg aktiv bleiben.
5. **Kleine, nachvollziehbare Commits.** Änderungen und Gründe dokumentieren.
6. **Keine bestehenden Tessera-Dashboard-Seiten überschreiben.** Der Browser bleibt eine eigenständige Plugin-Ansicht.
7. **Keine Secrets committen.** Niemals echte URLs mit privaten Pfaden, Tokens oder Bridge-Keys in Fixtures oder Dokumentation aufnehmen.
8. **Strukturierte Rezeptdaten bewahren.** Für zukünftige Portionsskalierung dürfen Zutatenmengen und Einheiten nicht auf formatierten Text reduziert werden.
9. **Unfertige Funktionen ehrlich markieren.** Ein Dokumentations-Häkchen bedeutet erst dann erledigt, wenn Implementierung und passende Tests vorhanden sind.

## 8. Aktuelle wichtige Entscheidungen

- Vollbild-Rezeptbrowser auf dem GUITION, kein Lovelace-Dashboard.
- Layout: Kopfzeile + linke Navigation + rechte 3×8-Rezeptfläche.
- Bis zu 24 Rezepte pro Displayseite.
- Mealie liefert dynamische Kategorien.
- Kategorie und Suche sind kombinierbar.
- Filter bleiben beim Blättern aktiv.
- Bridge-Anfragen holen fünf Rezepte auf einmal.
- Rezeptdetails werden on demand geladen.
- Portionsanpassung ist spätere Ausbaustufe, deshalb strukturierte Zutaten erhalten.
