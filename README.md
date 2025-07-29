# c-key-value-socket-server
# C Key-Value Store mit Socket-Kommunikation

Dies ist mein persönlicher Beitrag zu einem Teamprojekt im Rahmen des Informatikstudiums.  
Ziel war die Entwicklung eines Servers in C, der über TCP-Sockets mit einem Telnet-Client kommuniziert und einfache Datenhaltung über Key-Value-Paare ermöglicht.

# Projektbeschreibung

Das Projekt besteht aus einem einfachen, selbst implementierten Key-Value-Store, der über einen Socket-Server angesprochen werden kann. Die Kommunikation erfolgt über einen Telnet-Client auf Port 5678. Unterstützt werden die Kommandos `GET`, `PUT`, `DEL` und `QUIT`.

# Hauptfunktionen:
- `put(char* key, char* value)` – speichert oder überschreibt ein Key-Value-Paar.
- `get(char* key, char* res)` – gibt den Wert zu einem Schlüssel zurück.
- `del(char* key)` – löscht einen Eintrag anhand des Schlüssels.
- Socket-Kommunikation mit Telnet nach dem Muster:  
  `PUT key value` → `PUT:key:value`

# Projektstruktur

- `main.c / main.h` – Einstiegspunkt, initialisiert den Server
- `keyValStore.c / keyValStore.h` – Funktionen für Datenhaltung
- `sub.c / sub.h` – allgemeine Hilfsfunktionen (z. B. Parsing, Validierung)
- Optional: `CMakeLists.txt` – zur einfachen Kompilierung mit CLion

# Beispiel-Nutzung mit Telnet:

```bash
PUT name Alice
> PUT:name:Alice

GET name
> GET:name:Alice

DEL name
> DEL:name:key_deleted

QUIT
