# LambdaThread: C++23 Lambda Multithreading Demo

## Beschreibung
Dieses Projekt demonstriert Multithreading in C++23 mit `std::jthread` und Lambda-Ausdrücken. Es verarbeitet Aufgaben in parallelen Threads mit synchronisierter Konsolenausgabe, um Überschneidungen zu vermeiden. Ein Vergleichstest prüft die Korrektheit der Ausgabe.

Funktionalitäten:
- Ausgabe der Haupt-Thread-ID.
- Einzelner Thread mit Lambda-basierter Aufgabe.
- Mehrere Threads in einem Vektor mit Lambda-Ausdrücken.
- Überwachung der Thread-IDs.
- Zählung und Zusammenfassung der Aufgaben.
- Synchronisierte Ausgabe mit `std::mutex`.
- Vergleichstest mit `std::invoke_result_t`.

## Anforderungen
- Compiler: GCC 15.1.0 oder höher (MSYS2 UCRT64, `C:\msys64\ucrt64\bin\g++.exe`).
- CMake: 4.0.2 oder höher.
- Ninja: Build-Tool für CMake.
- VS Code: Mit **C/C++** und **CMake Tools** Erweiterungen.
- MSYS2 UCRT64: Für Compiler und Tools.

## Einrichtung und Build
1. Repository klonen (Teil von `CppFunktionsBaukasten`):
   ```bash
   cd CppFunktionsBaukasten/LambdaThread
   ```
2. Abhängigkeiten installieren (MSYS2 UCRT64 Konsole):
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-gdb
   ```
3. VS Code konfigurieren:
   - Projekt in VS Code öffnen: `File > Open Folder > CppFunktionsBaukasten/LambdaThread`.
   - `.vscode/settings.json` prüfen:
     ```json
     {
         "C_Cpp.default.compilerPath": "C:\\msys64\\ucrt64\\bin\\g++.exe",
         "cmake.generator": "Ninja",
         "cmake.configureOnOpen": true
     }
     ```
   - `.vscode/cmake-kits.json` prüfen:
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
   - Befehlspalette (Strg+Shift+P): „CMake: Configure“.
   - „CMake: Build“ ausführen.
   - Ohne Debugging: Strg+F5 („Run LambdaThread“).
   - Mit Debugging: F5 („Debug LambdaThread“).

## Lizenz
Dieses Projekt ist unter der [MIT-Lizenz](../LICENSE) lizenziert. Siehe die Haupt-[LICENSE](../LICENSE) für Details.

## Ausgabe
Das Programm zeigt klare, synchronisierte Multithreading-Ausgaben und einen Vergleichstest. Ein erfolgreicher Test gibt `0` zurück und druckt „Test erfolgreich“.