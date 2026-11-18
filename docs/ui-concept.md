# Bedienkonzept

## Ziel

Der Rezeptbrowser ergänzt das bestehende Tessera-Dashboard. Er ersetzt weder das Dashboard noch verändert er dessen vorhandene Seiten. Der Einstieg erfolgt über eine zusätzliche Tessera-Kachel bzw. Plugin-Ansicht.

Zielgerät ist das Guition JC8012P4A1C-I-W-Y / JC8012P4A1, Hardware V3, mit 1280 × 800 Pixeln und kapazitivem Touch. Kleine Tessera-Displays sind ausdrücklich nicht Ziel.

## Navigation

1. Bestehendes Tessera-Dashboard
2. Rezeptbrowser öffnen
3. Suche oder Kategorie auswählen
4. Trefferliste
5. Rezeptdetails
6. Optional: Kochmodus

Jede Unteransicht erhält eine gut erreichbare Zurück-Schaltfläche. Der Rückweg aus dem Rezeptbrowser führt zum unveränderten Dashboard.

## Ansicht A: Suche und Kategorien

- Kopfzeile mit Titel „Rezepte“ und Schaltfläche zum Dashboard
- gut sichtbares Suchfeld für Rezeptnamen und Zutaten
- separate Suchaktion; die Suche startet nicht bei jedem einzelnen Tastendruck
- dynamisch geladene Kategorien und „Alle Rezepte“
- Lade-, Leer- und Fehlerzustände

## Ansicht B: Trefferliste

- Kopfzeile zeigt Suchbegriff oder ausgewählte Kategorie
- Rezeptkarten in zwei Spalten
- pro Treffer: Bild, falls vorhanden, Name, Zubereitungszeit und Portionen
- Rezepte ohne Bild erhalten eine neutrale Platzhalterdarstellung
- begrenzte Trefferzahl pro Anfrage und einfache Seitennavigation
- Auswahl einer Karte öffnet die Rezeptdetails

## Ansicht C: Rezeptdetails

- Rezeptname und Kurzbeschreibung
- Gesamt-, Vorbereitungs- und aktive Zubereitungszeit, soweit vorhanden
- Portionenzahl
- Zutatenliste links
- Zubereitungsschritte rechts
- Bild nur dann, wenn Mealie eines liefert
- Schaltfläche „Kochmodus starten“

## Ansicht D: Kochmodus

- ein Zubereitungsschritt groß und gut lesbar
- deutliche Schaltflächen „Zurück“ und „Weiter“
- Anzeige „Schritt x von y“
- Zutaten können separat als Checkliste angezeigt werden
- jederzeitige Rückkehr zu den Rezeptdetails

## Bedien- und Layoutregeln

- Touch-Ziele möglichst mindestens 60 × 60 Pixel
- klare Kontraste und große Schrift für die Nutzung aus etwas Abstand
- keine Abhängigkeit von Hover oder Maus
- keine unnötigen Animationen
- lange Inhalte werden in überschaubare Ansichten bzw. Schritte aufgeteilt

## Technische Randbedingungen

- Das offizielle Tessera-Plugin-Template trennt Manifest, ESPHome-Komponente, Übersetzungen und Vorschau.
- Full-Page-Tiles und weitere API-Funktionen werden erst nach Prüfung der tatsächlich eingesetzten Tessera-Version verwendet.
- Home-Assistant-Befehle laufen über die im Manifest deklarierten Berechtigungen; Antworttransport und Payload-Grenzen müssen vor der Implementierung getestet werden.
- Suchtreffer und Rezeptdetails bleiben getrennt; große Zutaten- und Anweisungslisten werden bei Bedarf in mehreren Anfragen übertragen.

## Offene technische Frage: Kategorien

Die Mealie-API stellt eine Kategorienliste über `GET /api/organizers/categories` bereit. Die Home-Assistant-Mealie-Integration stellt dafür nach bisherigem Test keine eigene Aktion bereit; ihr Kategorien-Sensor liefert nur die Anzahl der Kategorien. `mealie.get_recipes` nimmt einen Freitext-Suchbegriff und kein separates Kategorie-ID-Feld entgegen.

Vor der Umsetzung ist zu entscheiden, wie das Plugin die Kategorienliste sicher erreicht und wie eine ausgewählte Kategorie in eine Mealie-Suche übersetzt wird. Die Lösung muss mit der vorhandenen Tessera-/Home-Assistant-Verbindung funktionieren und darf keine Zugangsdaten offenlegen.

## Umsetzungsreihenfolge

1. Tessera-Version, Template und Preview festlegen
2. Kategorienzugriff und Antworttransport technisch klären
3. Bedienoberfläche und Navigation mit Mock-Daten
4. Rezeptsuche über `mealie.get_recipes`
5. Trefferliste und Auswahl
6. Rezeptdetails über `mealie.get_recipe`
7. Zutaten- und Schrittaufteilung anhand realer großer Rezepte
8. Kochmodus und Test auf dem Zielgerät
