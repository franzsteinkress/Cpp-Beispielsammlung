# Invokable

## Beschreibung
Dieses Projekt demonstriert die Verwendung von `std::invoke` in C++23 für verschiedene Aufrufarten, einschließlich freier Funktionen, Lambda-Ausdrücke, Mitgliedsfunktionen, Datenmember und Funktionsobjekte. Es enthält einen Vergleichstest zur Überprüfung der Ausgabe.

Funktionalitäten:
- Aufruf einer freien Funktion mit `std::invoke`.
- Aufruf eines Lambda-Ausdrucks.
- Aufruf einer Mitgliedsfunktion einer Klasse.
- Zugriff auf einen Datenmember.
- Aufruf eines Funktionsobjekts.
- Verwendung von `std::invoke` für Berechnungen mit Typprüfung.
- Vergleichstest mit `std::invoke_result_t`

## Ausgabe
Das Programm zeigt verschiedene Aufrufarten mit `std::invoke` und einen Vergleichstest. Ein erfolgreicher Test gibt `0` zurück und druckt „Test erfolgreich“.