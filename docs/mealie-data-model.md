# Mealie-Datenmodell – beobachtete Antworten

Diese Datei dokumentiert die in Home Assistant manuell getesteten Antworten. Sie ist keine vollständige Mealie-API-Spezifikation.

## Get recipes – Suchtreffer

Getesteter Suchbegriff: `sauce`, Limit: 3. Die Einträge unter `recipes.items[]` enthielten unter anderem:

| Feld | Verwendung |
|---|---|
| `recipe_id` | UUID zum späteren Laden des Rezepts |
| `name` | Anzeigename |
| `slug` | URL-/Namensslug |
| `description` | Beschreibung, im Test `None` |
| `total_time_seconds` | Gesamtzeit in Sekunden |
| `prep_time_seconds` | Vorbereitungszeit in Sekunden |
| `perform_time_seconds` | aktive Zubereitungszeit in Sekunden |
| `image` | Bildreferenz; im Test `null` |
| `recipe_servings` | Portionen |
| `recipe_yield`, `recipe_yield_quantity` | Ertrag und Menge |
| `rating` | Bewertung; im Test `null` |

Das Rezept **Pizzasauce** hatte die ID `406fd7ba-2df2-43f7-950f-5e725194fbbb`.

## Get Recipe – vollständiges Rezept

Die Antwort hat den Wurzelknoten `recipe`.

### Zutaten

`recipe.ingredients[]` enthält:

| Feld | Verwendung |
|---|---|
| `display` | Formatierte Zutatenzeile, z. B. `300 Milliliter passierte Tomaten` |
| `quantity` | Numerische Menge, kann `null` sein |
| `unit.name` | Einheitenname, kann fehlen |
| `food.name` | Lebensmittelname |
| `note` | Zusatzhinweis |
| `reference_id` | Zutatenreferenz |

**Für die erste Version ist `display` die primäre Anzeigequelle.** Mealie formatiert Menge, Einheit und Lebensmittel bereits. `quantity` bleibt für eine spätere Portionsanpassung relevant.

### Zubereitung

`recipe.instructions[]` enthält:
- `instruction_id`
- `text`
- `title`
- `ingredient_references[]`
- `recipe_notes[]`

Die Reihenfolge der Liste entspricht der Reihenfolge der Zubereitungsschritte.

### Weitere Felder

- `recipe.notes[]`: Rezeptnotizen
- `recipe.nutrition`: Nährwerte; im Test waren alle Werte `null`
- `recipe.image`: im Test `null`

## Pizzasauce – Testinhalt

Das Rezept hat 2 Portionen und 40 Minuten Gesamtzeit.

Zutaten:
- 1 Schalotte
- 2 Zehe/n Knoblauch
- 300 Milliliter passierte Tomaten
- 1 Teelöffel Oregano
- 1 Prise Zucker
- 1 Teelöffel gekörnte Brühe
- Salz
- Pfeffer

Die drei Zubereitungsschritte werden aus `instructions[].text` übernommen.

## Offene Prüfungen

- Bildreferenz bei Rezepten mit Bild
- Nachrichtengröße bei Rezepten mit vielen Zutaten und Schritten
- Verhalten bei langen Anweisungstexten
- Weitere Filterparameter der Mealie-Aktion
