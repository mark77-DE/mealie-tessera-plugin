# Tessera-Rezeptdatenvertrag

## Zweck

Dieses Dokument beschreibt die Daten, die das Tessera-Plugin aus Home Assistant benötigt. Es ist ein Entwurf auf Basis der bisher beobachteten Mealie-Antworten, keine vollständige Mealie-API-Spezifikation.

Die Mealie-Feldnamen werden in der Plugin-Logik auf ein übersichtliches internes Modell abgebildet. Die konkrete Serialisierung muss die begrenzten Tessera-Nachrichtengrößen berücksichtigen.

## Grundsätze

- Optionale oder fehlende Werte bleiben optional.
- Suchergebnisse enthalten nur kompakte Metadaten.
- Zutaten und Anweisungen werden erst beim Öffnen eines Rezepts geladen.
- Lange Zutaten- und Anweisungslisten dürfen in mehrere Nachrichten aufgeteilt werden.
- Für die erste Version wird Mealie's formatiertes Zutatenfeld `display` verwendet.

## Rezepttreffer

| Feld | Typ | Bedeutung |
|---|---|---|
| `id` | string | Mealie-Rezept-ID |
| `name` | string | Anzeigename |
| `slug` | string? | Slug |
| `description` | string? | Kurzbeschreibung |
| `image` | string? | Bildreferenz |
| `totalTimeSeconds` | number? | Gesamtzeit |
| `prepTimeSeconds` | number? | Vorbereitungszeit |
| `cookTimeSeconds` | number? | aktive Zubereitungszeit |
| `servings` | number? | Portionen |

## Rezeptdetails

Zusätzlich zu den Trefferfeldern:

- `ingredients: Ingredient[]`
- `instructions: Instruction[]`
- `notes: string[]`
- `yield: string?`
- `yieldQuantity: number?`

### Ingredient

| Feld | Typ | Bedeutung |
|---|---|---|
| `display` | string | formatierte Zutatenzeile |
| `quantity` | number? | numerische Menge, falls vorhanden |
| `unit` | string? | Einheitenbezeichnung |
| `food` | string? | Lebensmittelname |
| `note` | string? | Zusatzhinweis |
| `referenceId` | string? | Zutatenreferenz |

### Instruction

| Feld | Typ | Bedeutung |
|---|---|---|
| `id` | string? | Mealie-Schritt-ID |
| `title` | string? | Schrittüberschrift |
| `text` | string | Zubereitungstext |
| `ingredientReferences` | string[]? | Zutatenreferenzen |
| `notes` | string[]? | Schrittbezogene Notizen |

## Kategorien

| Feld | Typ | Bedeutung |
|---|---|---|
| `id` | string | Mealie-Kategorie-ID |
| `name` | string | Kategoriename |

## Logische Abfragen

- Kategorien abrufen
- Rezepte anhand eines Suchbegriffs abrufen
- Rezeptdetails anhand der Rezept-ID abrufen

Diese Operationen beschreiben den benötigten Funktionsumfang. Die tatsächlichen HA-Service-Aufrufe und der Antworttransport müssen separat anhand der installierten Versionen geprüft werden.

## Offene Punkte

- Kategorienquelle und Filterstrategie
- Bildreferenz und Bildabruf
- Paging und maximale Trefferzahl
- Behandlung langer Texte und Tessera-Payload-Grenzen
- Portionsumrechnung einschließlich Einheiten und nicht skalierbarer Zutaten
