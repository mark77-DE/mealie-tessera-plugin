# Mealie-Rezeptbrowser für Tessera

Rezepte aus einer Mealie-Instanz auf einem Tessera-Touchdisplay suchen und anzeigen. Das Plugin nutzt ausschließlich die native Home-Assistant-Verbindung der Tessera-App. Es greift nicht direkt auf Mealie zu.

> **Status: Beta / frühe Entwicklung.** Die native Anbindung an die Home-Assistant-Response-Services ist in Arbeit. Rezeptübersicht und Detailansicht werden schrittweise auf den neuen Datenweg umgestellt.

## Architektur

```text
Mealie
  ↕
Offizielle Mealie-Integration in Home Assistant
  ↕
Mealie Tessera Bridge (HA Custom Integration)
  ↕ native HA-Commands
Tessera-App / Mealie Recipe Browser
  ↕
GUITION Display
```

Das Plugin enthält keine Mealie-IP-Adresse, URL, API-Zugangsdaten oder Bridge-Token. Es benötigt keine `permissions.network`-Freigabe. Die Mealie-Verbindung und Authentifizierung bleiben vollständig in Home Assistant.

## Einrichtung

1. Die offizielle Mealie-Integration in Home Assistant einrichten.
2. Die [Mealie Tessera Bridge](https://github.com/mark77-DE/mealie-tessera-bridge) installieren und mit dem vorhandenen Mealie-Eintrag verknüpfen.
3. Home Assistant neu starten bzw. die Bridge laden.
4. Dieses Tessera-Plugin installieren.
5. Die Rezeptbrowser-Kachel dem Tessera-Layout hinzufügen.

Es sind keine Serveradresse, kein API-Token und keine Eintrag-ID im Tessera-Plugin einzutragen.

## Datenabruf

- Rezepte werden in Seiten zu jeweils fünf Einträgen abgerufen.
- Die Oberfläche kann bis zu 24 Rezepte gleichzeitig anzeigen.
- Suche und Kategorie werden als Home-Assistant-Serviceparameter übergeben.
- Kategorien werden dynamisch aus Mealie geladen.
- Vollständige Rezeptdaten werden erst beim Öffnen eines Rezepts angefordert.

## Entwicklungsstand

Die bisherige HTTP-/Fetch-Variante wird durch native Home-Assistant-Response-Services ersetzt. Die virtuelle Vorschau und die Serviceantworten müssen vor einem Release gemeinsam geprüft werden.

## Sicherheit

Keine Tokens, Zugangsdaten, privaten URLs, IP-Adressen oder Home-Assistant-Config-Entry-IDs in das Plugin oder Repository eintragen.
