# Gemeinsamer Rezept-Datenvertrag

## Zweck

Dieses Dokument definiert die frontend-neutrale Datenstruktur zwischen der Home-Assistant-Daten-/Vermittlungsschicht und den beiden Oberflächen. Es ist ein Entwurf auf Basis der bisher beobachteten Mealie-Antworten, keine Behauptung über eine bereits implementierte API.

Die Lovelace-Karte und das Tessera-Plugin sollen dieselben fachlichen Felddefinitionen verwenden. Die konkrete Serialisierung darf je nach Transport unterschiedlich sein.

## Grundsätze

- Mealie-Feldnamen werden nicht ungeprüft bis in die UI durchgereicht.
- Optionale oder fehlende Werte bleiben optional und werden nicht durch erfundene Standardwerte ersetzt.
- Suchergebnisse enthalten nur kompakte Metadaten.
- Zutaten und Anweisungen werden erst beim Öffnen eines Rezepts geladen.
- Tessera darf lange Inhalte in mehrere Transportpakete aufteilen; die fachliche Bedeutung der Daten bleibt identisch.

## Entitäten

### RecipeSummary

| Feld | Typ | Bedeutung |
|---|---|---|
| `id` | string | Mealie-Rezept-ID |
| `name` | string | Anzeigename |
| `slug` | string? | Slug, falls vorhanden |
| `description` | string? | Kurzbeschreibung |
| `image` | string? | Bildreferenz oder auflösbare Bild-URL |
| `totalTimeSeconds` | number? | Gesamtzeit |
| `prepTimeSeconds` | number? | Vorbereitungszeit |
| `cookTimeSeconds` | number? | Aktive Zubereitungszeit |
| `servings` | number? | Rezeptportionen |
| `categories` | CategoryRef[]? | Kategorien, sofern im Suchergebnis vorhanden |

### RecipeDetail

Enthält alle Felder aus `RecipeSummary` und zusätzlich:

- `ingredients: Ingredient[]`
- `instructions: Instruction[]`
- `notes: string[]`
- `yield: string?`
- `yieldQuantity: number?`

### Ingredient

| Feld | Typ | Bedeutung |
|---|---|---|
| `display` | string | Von Mealie formatierte Zutatenzeile |
| `quantity` | number? | Numerische Menge, falls vorhanden |
| `unit` | string? | Einheitenbezeichnung |
| `food` | string? | Lebensmittelname |
| `note` | string? | Zusatzhinweis |
| `referenceId` | string? | Referenz für Rezept-/Schrittbezüge |

Für die erste UI-Version ist `display` die maßgebliche Darstellung. Eine Portionsumrechnung darf erst aktiviert werden, wenn Mengen, Einheiten und nicht-numerische Angaben zuverlässig behandelt werden.

### Instruction

| Feld | Typ | Bedeutung |
|---|---|---|
| `id` | string? | Mealie-Schritt-ID |
| `title` | string? | Schrittüberschrift |
| `text` | string | Zubereitungstext |
| `ingredientReferences` | string[]? | Verknüpfte Zutatenreferenzen |
| `notes` | string[]? | Schrittbezogene Notizen |

### CategoryRef

| Feld | Typ | Bedeutung |
|---|---|---|
| `id` | string | Mealie-Kategorie-ID |
| `name` | string | Kategoriename |

## Abfragekonzept

Fachliche Operationen:

- `listCategories()` → CategoryRef[]
- `searchRecipes(query, categoryId?, limit, page?)` → RecipeSummary[]
- `getRecipe(recipeId)` → RecipeDetail
- `getRecipeImage(recipeId)` bzw. Bildreferenzauflösung, sofern separat nötig

Die Operationen sind ein logisches Zielbild. Die konkreten Home-Assistant-Services und Rückgabewege werden separat verifiziert. Insbesondere ist noch zu klären, wie Kategorien und echte Kategorie-Filter mit der vorhandenen Mealie-Integration abgebildet werden.

## Fehlerzustände

Frontends müssen mindestens unterscheiden können:

- Ladezustand
- erfolgreiche Antwort mit Treffern
- erfolgreiche Antwort ohne Treffer
- ungültige Eingabe
- Verbindungs-/Authentifizierungsfehler
- nicht gefundenes Rezept
- unerwartete Antwort bzw. Datenfehler

## Offene Entscheidungen

- Einheitliches Paging: Mealie-Parameter und tatsächliche Rückgabeform prüfen.
- Bildreferenzen: Format, Authentifizierung und Auflösung testen.
- Kategorien: API-Zugriff und Filterstrategie in Home Assistant festlegen.
- Portionen: Rundung, Einheiten und nicht skalierbare Zutaten definieren.
- Tessera: Paketierung langer Zutaten-/Anweisungstexte festlegen.
