# Bedienkonzept

Das Projekt besitzt zwei Oberflächen mit gemeinsamer Rezeptdatenbasis: eine Lovelace-Custom-Card für Home Assistant und ein Tessera-Plugin für das große Küchendisplay. Dieses Dokument beschreibt vor allem die Tessera-Oberfläche; das Home-Assistant-Konzept steht in [home-assistant-card.md](home-assistant-card.md).

## Tessera-Zielgerät

Zielgerät ist das Guition JC8012P4A1C-I-W-Y / JC8012P4A1, Hardware V3, mit 1280 × 800 Pixeln und kapazitivem Touch. Die Entwicklung beginnt ohne das Display; Datenfluss und Ansichten werden zunächst mit Preview und Mock-Daten vorbereitet.

Kleine Tessera-Displays sind vorerst kein Ziel. Die Rezeptoberfläche soll die Größe des Küchendisplays nutzen und nicht auf kleine Displays heruntergebrochen werden.

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

Die gemeinsame Architektur muss daher eine verlässliche Kategorienquelle und eine Strategie für die Kategorie-Suche festlegen. Diese Lösung soll nicht ausschließlich für Tessera gebaut werden, sondern auch der HA-Karte dienen.

## Umsetzungsreihenfolge

1. Gemeinsamen Datenvertrag und Kategorienzugriff klären
2. HA-Karte mit Mock-Daten und anschließend echten Mealie-Daten umsetzen
3. Suche, Trefferliste und Details vervollständigen
4. Kochmodus und Portionsanpassung ergänzen
5. Tessera-Oberfläche auf Basis desselben Datenvertrags implementieren
6. Test auf dem Zielgerät
