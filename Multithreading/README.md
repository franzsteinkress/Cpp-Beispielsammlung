# Multithreading

## Beschreibung
Dieses Projekt demonstriert Multithreading in C++23 mit `std::jthread` und `std::mutex`. Es zeigt die Verarbeitung von Haupt-, System-, Status- und Abschlussmeldungen in parallelen Threads mit synchronisierter Konsolenausgabe, um Thread-Überschneidungen zu vermeiden. Ein Vergleichstest prüft die Korrektheit der Ausgabe.

Funktionalitäten:
- Verwaltung von Haupt- und Systemmeldungen in separaten Threads.
- Verarbeitung von Statusmeldungen in einem eigenen Thread.
- Verarbeitung von Abschlussmeldungen mit absteigenden IDs.
- Synchronisierte Konsolenausgabe mit `std::mutex`.
- Vergleichstest mit `std::invoke_result_t`

## Ausgabe
Das Programm zeigt synchronisierte Multithreading-Ausgaben und einen Vergleichstest. Ein erfolgreicher Test gibt `0` zurück und druckt „Test erfolgreich“.