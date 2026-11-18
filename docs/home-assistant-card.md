# Home-Assistant-Custom-Card – Konzept

## Ziel

Die Rezeptsuche soll direkt in einem bestehenden Home-Assistant-Dashboard verfügbar sein. Die Karte ist eine eigenständige Lovelace-Custom-Card und benötigt kein separates Dashboard.

Sie ist neben dem Tessera-Plugin ein gleichberechtigtes Frontend des gemeinsamen Mealie-Rezeptbrowsers.

## Geplante Bedienung

### Suche und Kategorien
- Suchfeld für Rezeptnamen und Zutaten
- Suchaktion statt unnötiger Anfrage bei jedem Tastendruck
- Kategorienauswahl inklusive „Alle Rezepte“
- Lade-, Leer- und Fehlerzustände

### Treffer
- responsive Karten- oder Listenansicht
- Rezeptname, Bild (falls vorhanden), Zeit und Portionen
- Auswahl öffnet die Rezeptdetails

### Rezeptdetails
- Titel und Beschreibung
- Zeitangaben und Portionen
- Zutatenliste
- Zubereitungsschritte
- optionaler Kochmodus

### Kochmodus
- Schrittweise Navigation
- Zutaten-Checkliste
- gut sichtbarer Fortschritt

## Integration in Dashboards

- Die Karte soll sich in normale Lovelace-Views einfügen.
- Breite und Höhe sollen sich an den verfügbaren Dashboard-Platz anpassen.
- Auf Tablet und Desktop darf die Karte mehrspaltig arbeiten; auf schmalen Ansichten wird auf eine Spalte gewechselt.
- Konfiguration und Datenzugriff dürfen keine bestehenden Dashboard-Karten verändern.

## Technische Leitlinien

- Home-Assistant-Custom-Cards sind Web Components und erhalten den HA-Kontext über das `hass`-Objekt.
- Mealie-Aufrufe sollen nicht direkt aus beliebigen UI-Komponenten heraus verteilt werden. Eine klar abgegrenzte Datenzugriffsschicht hält Service-Aufrufe und Daten-Normalisierung zusammen.
- Die Karte nutzt den gemeinsamen Vertrag aus [shared-data-contract.md](shared-data-contract.md).
- Die tatsächliche HA-Service-Response-API ist vor der Implementierung gegen die installierte Home-Assistant-Version zu verifizieren.
- Installationsspezifische Config-Entry-IDs und Zugangsdaten werden nicht in den Quellcode geschrieben.

## Offene technische Prüfungen

- Kann die Karte die Rückgabedaten von `mealie.get_recipes` und `mealie.get_recipe` direkt und zuverlässig über die HA-Frontend-API empfangen?
- Wie wird die Mealie-Config-Entry-ID konfigurierbar ermittelt bzw. vom Nutzer ausgewählt?
- Wie werden Kategorien geladen, und wie wird ein Kategorie-Filter in eine tatsächliche Mealie-Suche übersetzt?
- Welche Bild-URLs sind im Browser ohne zusätzliche Authentifizierung erreichbar?
- Welche minimale HA-Version soll unterstützt werden?

## Erste technische Umsetzung

Zuerst ein minimales Custom-Card-Grundgerüst mit Konfigurationseditor und statischem Mock-Datensatz erstellen. Danach wird der echte Datenzugriff angebunden. So lassen sich Layout und Navigation unabhängig von den noch offenen Mealie-/HA-Details entwickeln.
