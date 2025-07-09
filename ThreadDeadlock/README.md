# ThreadDeadLock

## Beschreibung
Dieses Projekt demonstriert Multithreading in C++23 mit `std::jthread`, `std::mutex`, und `std::scoped_lock`, um Deadlock-Szenarien zu zeigen und zu vermeiden. Es enthält sicheren Zugriff, verzögerten Zugriff und Deadlock-Vermeidung, inklusive eines Vergleichstests.

Funktionalitäten:
- Sicherer Zugriff mit einem Mutex.
- Verzögerter Zugriff mit mehreren Mutexen.
- Deadlock-Simulation und Vermeidung mit `std::scoped_lock`.
- Vergleichstest mit `std::invoke_result_t`

## Ausgabe
Das Programm zeigt Multithreading-Szenarien und einen Vergleichstest. Ein erfolgreicher Test gibt `0` zurück und druckt „Test erfolgreich“.