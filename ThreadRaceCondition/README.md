# ThreadRaceCondition

## Beschreibung
Dieses Projekt demonstriert thread-sicheren Zugriff auf einen Stapel in C++23 mit `std::jthread`, `std::mutex`, und `std::lock_guard`. Es zeigt, wie Race Conditions durch Synchronisation vermieden werden, und enthält einen Vergleichstest.

Funktionalitäten:
- Thread-sicherer Stapel mit Push- und Pop-Operationen.
- Verarbeitung von Stapel-Elementen in mehreren Threads.
- Synchronisierte Konsolenausgabe.
- Vergleichstest mit `std::invoke_result_t`

## Ausgabe
Das Programm zeigt thread-sichere Stapelverarbeitung und einen Vergleichstest. Ein erfolgreicher Test gibt `0` zurück und druckt „Test erfolgreich“.