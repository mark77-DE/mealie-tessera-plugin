# Bedienkonzept

## Ziel

Der Rezeptbrowser ergänzt das bestehende Tessera-Dashboard. Er ersetzt weder das Dashboard noch verändert er dessen vorhandene Seiten. Der Einstieg erfolgt über eine zusätzliche Tessera-Kachel bzw. Plugin-Ansicht.

Zielgerät für das Layout ist das Guition JC8012P4A1C-I-W-Y mit 1280 × 800 Pixeln und kapazitivem Touch. Die Entwicklung beginnt ohne das Display; Datenfluss und Ansichten werden zunächst mit Tessera-Vorschau und Mock-Daten vorbereitet.

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
- darunter bzw. daneben eine dynamische Kategorienauswahl
- Kategorie „Alle Rezepte“ als Rückkehr zur ungefilterten Suche
- Lade-, Leer- und Fehlerzustände

Die Kategorien werden nicht als feste Liste in den Plugin-Code geschrieben. Sie sollen aus Mealie geladen und zur Laufzeit als Touch-Schaltflächen dargestellt werden.

## Ansicht B: Trefferliste

- Kopfzeile zeigt Suchbegriff oder ausgewählte Kategorie
- Rezeptkarten in zwei Spalten
- pro Treffer: Bild, falls vorhanden, Name, Zubereitungszeit und Portionen
- Rezepte ohne Bild erhalten eine neutrale Platzhalterdarstellung
- begrenzte Trefferzahl pro Anfrage und einfache Seitennavigation
- Auswahl einer Karte öffnet die Rezeptdetails

Die Trefferliste verwendet zunächst die kompakte Antwort von `mealie.get_recipes`. Vollständige Rezeptdaten werden erst nach Auswahl geladen.

## Ansicht C: Rezeptdetails

- Rezeptname und Kurzbeschreibung
- Gesamt-, Vorbereitungs- und aktive Zubereitungszeit, soweit vorhanden
- Portionenzahl
- Zutatenliste links
- Zubereitungsschritte rechts
- Bild nur dann, wenn Mealie eines liefert
- Schaltfläche „Kochmodus starten“

Für Zutaten wird bevorzugt das von Mealie bereits formatierte Feld `display` verwendet. Damit bleiben optionale Mengen und Einheiten korrekt darstellbar.

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
- Texte werden über Tessera-Übersetzungsdateien gepflegt

## Technische Randbedingungen

- Das offizielle Tessera-Plugin-Template trennt Manifest, ESPHome-Komponente, Übersetzungen und Vorschau.
- Die aktuelle Plugin-Dokumentation kennt vollständige Seiten-Tiles über `sizes.full` ab Plugin-API 0.25. Die stabile Tessera-App kann je nach Release noch eine ältere API mitbringen. Deshalb wird vor der Wahl zwischen Full-Page-Tile und Card die tatsächlich eingesetzte Tessera-Version geprüft.
- Tessera-Fetches dürfen nur fest deklarierte öffentliche Hosts ansprechen. Ein interner Mealie-Host im Heimnetz kann nicht einfach als normaler Plugin-Fetch verwendet werden.
- Home-Assistant-Befehle laufen über `permissions.ha_commands` und `tessera::send()`. Die Antwort wird in `on_message()` verarbeitet.
- Nachrichten sind begrenzt. Suchtreffer und Rezeptdetails bleiben getrennt; große Zutaten- und Anweisungslisten werden bei Bedarf in mehreren Anfragen übertragen.

## Offene technische Frage: Kategorien

Die Mealie-API stellt eine Kategorienliste über `GET /api/organizers/categories` bereit. Die Home-Assistant-Mealie-Integration stellt dafür jedoch keine eigene Aktion bereit; ihr Kategorien-Sensor liefert nur die Anzahl der Kategorien. `mealie.get_recipes` nimmt einen Freitext-Suchbegriff und kein separates Kategorie-ID-Feld entgegen.

Vor der Umsetzung ist daher zu entscheiden, wie das Plugin die Kategorienliste sicher erreicht:

1. Direkter Mealie-API-Zugriff über HTTPS, sofern die Mealie-Instanz öffentlich erreichbar ist; das API-Token würde als Tessera-Secret verwaltet und nicht im Repository gespeichert.
2. Ein Home-Assistant-seitiger Helfer, falls Mealie nur intern erreichbar ist. Dieser muss die Kategorienliste als Antwort an Tessera liefern können.

Die Rezeptsuche und der Rezeptabruf bleiben zunächst über die bereits getesteten Home-Assistant-Aktionen vorgesehen.

## Umsetzungsreihenfolge

1. Bedienoberfläche und Navigation mit Mock-Daten
2. Kategorienquelle verbindlich festlegen
3. Rezeptsuche über `mealie.get_recipes`
4. Trefferliste und Auswahl
5. Rezeptdetails über `mealie.get_recipe`
6. Zutaten- und Schrittaufteilung anhand realer großer Rezepte
7. Kochmodus
8. Test auf dem Zielgerät und Anpassung der Touch-Größen
