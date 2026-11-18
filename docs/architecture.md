# Architektur

## Zielbild

Das Mealie-Plugin ergänzt Tessera um eine Rezeptoberfläche, ohne das vorhandene Dashboard zu ersetzen oder dessen Layout umzubauen.

Datenfluss:

1. Der Nutzer öffnet den Rezeptbereich auf dem Tessera-Display.
2. Die Oberfläche fordert eine Rezeptsuche mit dem eingegebenen Suchtext an.
3. Die Tessera-App führt den im Manifest deklarierten Home-Assistant-Befehl aus.
4. Home Assistant ruft die Mealie-Integration auf.
5. Die Tessera-App übergibt die Antwort an das Plugin.
6. Das Plugin stellt die Treffer dar.
7. Beim Öffnen eines Rezepts wird dessen Detaildatensatz separat geladen.

## Warum Suche und Details getrennt werden

Rezeptdetails enthalten viele Zutaten, Anweisungen und verschachtelte Metadaten. Suchergebnisse sollen deshalb nur kompakte Felder enthalten. Zutaten und Zubereitung werden erst beim Öffnen eines Rezepts angefordert.

Die tatsächliche Nachrichtengröße wird mit realen Rezepten geprüft. Falls nötig, werden Zutaten und Anweisungen in getrennten Antworten geladen.

## Zuständigkeiten

### Home Assistant
- Verbindung zur Mealie-Instanz
- Ausführung der Mealie-Aktionen
- Bereitstellung der Antworten für Tessera

### Tessera-Plugin
- Touch-Eingabe und Suchoberfläche
- Trefferliste und Navigation
- Darstellung der Rezeptdetails
- Portionenfaktor und Zutaten-Checkliste
- Kochmodus und Schritt-Navigation

### Tessera-App
Die App liest das Plugin-Manifest, führt deklarierte Home-Assistant-Befehle aus und reicht deren Antworten an die Firmware weiter. Das Plugin baut keine eigene Netzwerkverbindung vom Display zu Mealie auf.

## Geplante Ansichten

1. **Rezeptsuche:** Suchfeld, Suchaktion und Trefferliste
2. **Rezeptdetails:** Name, Zeiten, Portionen, Zutaten und Anleitung
3. **Kochmodus:** ein Zubereitungsschritt pro Ansicht, Vor/Zurück-Navigation
4. **Optionale Einstellungen:** Standard-Portionen, Darstellung und Sprache

## Technische Leitplanken

- Vorhandenes Tessera-Dashboard bleibt unangetastet.
- Keine Zugangsdaten auf dem Display oder im Git-Repository.
- Nur benötigte Mealie-Felder übertragen.
- Lange Texte und große Listen nicht unnötig in einer Nachricht bündeln.
- UI-Texte über Tessera-Übersetzungsdateien pflegen.
- Plugin-API-Version so niedrig wie möglich wählen, aber nur nach Prüfung der benötigten Funktionen.
