# LambdaThread

## Beschreibung
Dieses Projekt demonstriert Multithreading in C++23 mit `std::jthread` und Lambda-Ausdrücken. Es verarbeitet Aufgaben in parallelen Threads mit synchronisierter Konsolenausgabe, um Überschneidungen zu vermeiden. Ein Vergleichstest prüft die Korrektheit der Ausgabe.

Funktionalitäten:
- Ausgabe der Haupt-Thread-ID.
- Einzelner Thread mit Lambda-basierter Aufgabe.
- Mehrere Threads in einem Vektor mit Lambda-Ausdrücken.
- Überwachung der Thread-IDs.
- Zählung und Zusammenfassung der Aufgaben.
- Synchronisierte Ausgabe mit `std::mutex`.
- Vergleichstest mit `std::invoke_result_t`

## Ausgabe
Das Programm zeigt klare, synchronisierte Multithreading-Ausgaben und einen Vergleichstest. Ein erfolgreicher Test gibt `0` zurück und druckt „Test erfolgreich“.