# SharedPtr

## Beschreibung
Dieses Projekt demonstriert die Nutzung von `std::shared_ptr` in C++23 für geteilte Ressourcenverwaltung, Multithreading und polymorphen Objekten. Es zeigt verschiedene Initialisierungsmethoden, Thread-Sicherheit und Filterung von Objektsammlungen, inklusive eines Vergleichstests.

Funktionalitäten:
- Polymorphe Ressourcen mit `std::shared_ptr`.
- Thread-sichere Zeiger in mehreren `std::jthread`-Instanzen.
- Verwaltung von Datenobjekten mit Zähler.
- Verschiedene Initialisierungsmethoden für Lieder.
- Filterung von Liedern und Medienobjekten.
- Vergleich von Zeigern.
- Vergleichstest mit `std::invoke_result_t`

## Ausgabe
Das Programm zeigt die Nutzung von `std::shared_ptr` und einen Vergleichstest. Ein erfolgreicher Test gibt `0` zurück und druckt „Test erfolgreich“.