# Binding Beispiele: C++23 Funktionale Programmierung Demo

## Beschreibung
Dieses Projekt demonstriert funktionale Programmierung in C++23 mit `std::bind`, `std::bind_front` (C++20), Lambdas und `std::invoke_result_t` (C++23). Es zeigt Techniken zur Bindung von Funktionsargumenten, Mitgliedsfunktionen und Datenmembern in einem Nachrichtenverarbeitungskontext.

Funktionalitäten:
- Argumentbindung und -umordnung.
- Lambda-Alternativen zu Bindungen.
- Verschachtelte Bindungen.
- Zufallszahlengenerierung.
- Verwendung von Smart Pointern.
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
   cd CppFunktionsBaukasten/Binding
   ```
2. Abhängigkeiten installieren (MSYS2 UCRT64 Konsole):
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-gdb
   ```
3. VS Code konfigurieren:
   - Projekt in VS Code öffnen: `File > Open Folder > CppFunktionsBaukasten/Binding`.
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
   - Ohne Debugging: Strg+F5 („Run Binding“).
   - Mit Debugging: F5 („Debug Binding“).

## Lizenz
Dieses Projekt ist unter der [MIT-Lizenz](../LICENSE) lizenziert. Siehe die Haupt-[LICENSE](../LICENSE) für Details.

## Ausgabe
Das Programm zeigt Beispiele für funktionale Bindungen und einen Vergleichstest, der die Korrektheit der Bindung prüft. Ein erfolgreicher Test gibt `0` zurück und druckt „Test erfolgreich“.