# CppFunktionsBaukasten: C++23 Beispielprojekte

## Beschreibung
Der `CppFunktionsBaukasten` ist eine Sammlung von 8 eigenständigen C++23-Projekten, die verschiedene Konzepte der modernen C++-Programmierung demonstrieren. Jedes Projekt enthält Quellcode, eine `README.md` mit detaillierten Anweisungen und eine MIT-Lizenz. Die Projekte sind für Lernzwecke und als Referenz für fortgeschrittene C++-Techniken gedacht.

### Projekte
- **Binding**: Bindung von Funktionsargumenten, Mitgliedsfunktionen und Datenmembern in einem Nachrichtenverarbeitungskontext.
- **Invokable**: Verwendung von `std::invoke` für freie Funktionen, Lambdas, Mitgliedsfunktionen und Funktionsobjekte.
- **Lambda**: Nutzung von Lambdas, Algorithmen (`std::for_each`, `std::partial_sum`, `std::all_of`, `std::none_of`) und Funktionsbindungen.
- **LambdaThread**: Multithreading mit `std::jthread` und Lambda-Ausdrücken, inklusive synchronisierter Ausgabe.
- **Multithreading**: Verwaltung von Haupt-, System-, Status- und Abschlussmeldungen in parallelen Threads.
- **SharedPtr**: Nutzung von `std::shared_ptr` in C++23 für geteilte Ressourcenverwaltung, Multithreading und polymorphen Objekten.
- **ThreadDeadLock**: Demonstration eines Deadlocks und wie man ihn vermeidet.
- **ThreadRaceCondition**: Beispiel für eine Race Condition und deren Lösung mit `std::mutex`.

## Anforderungen
- **Compiler**: GCC 15.1.0 oder höher (MSYS2 UCRT64, `C:\msys64\ucrt64\bin\g++.exe`).
- **CMake**: 4.0.2 oder höher.
- **Ninja**: Build-Tool für CMake.
- **VS Code**: Mit **C/C++** und **CMake Tools** Erweiterungen.
- **MSYS2 UCRT64**: Für Compiler und Tools.

## Einrichtung und Build
1. Repository klonen:
   ```bash
   git clone <repository-URL>
   cd CppFunktionsBaukasten
   ```
2. Abhängigkeiten installieren (MSYS2 UCRT64 Konsole):
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-gdb
   ```
3. VS Code konfigurieren:
   - Öffne den Ordner in VS Code: `File > Open Folder > CppFunktionsBaukasten`.
   - Prüfe `.vscode/settings.json`:
     ```json
     {
         "C_Cpp.default.compilerPath": "C:\\msys64\\ucrt64\\bin\\g++.exe",
         "cmake.generator": "Ninja",
         "cmake.configureOnOpen": true
     }
     ```
   - Prüfe `.vscode/cmake-kits.json`:
     ```json
     [
         {
             "name": "GCC 15.1.0 UCRT64",
             "preferredGenerator": { "name": "Ninja" },
             "compilers": {
                 "C": "C:\\msys64\\ucrt64\\bin\\gcc.exe",
                 "CXX": "C:\\msys64\\ucrt64\\bin\\g++.exe"
             },
             "environmentVariables": { "PATH": "C:\\msys64\\ucrt64\\bin;${env:PATH}" }
         }
     ]
     ```
4. Build und Ausführung:
   - Navigiere in ein Projekt (z. B. `cd Multithreading`).
   - Führe in VS Code „CMake: Configure“ und „CMake: Build“ aus.
   - Starte ohne Debugging: Strg+F5.
   - Starte mit Debugging: F5.

## Lizenz
Dieses Projekt und alle Unterprojekte sind unter der [MIT-Lizenz](LICENSE) lizenziert. Siehe [LICENSE](LICENSE) für Details.

## Beitrag
Beiträge sind willkommen! Bitte öffne ein Issue oder einen Pull Request auf GitHub.