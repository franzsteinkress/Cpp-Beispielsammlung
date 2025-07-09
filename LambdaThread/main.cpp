// Copyright (c) 2025 Franz Steinkress
// Licensed under the MIT License - see LICENSE file for details
//
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <mutex>
#include <sstream>
#include <type_traits>

// Synchronisiert die Konsolenausgabe
void synchronisierte_ausgabe(std::mutex& schutz_mutex, const std::string& meldung) {
    std::lock_guard<std::mutex> sperre(schutz_mutex);
    std::cout << meldung << '\n';
    std::cout.flush(); // Sicherstellen, dass die Ausgabe sofort geschrieben wird
}

// Verarbeitet eine Aufgabe und gibt Status aus
void verarbeite_aufgabe(int aufgaben_id, std::mutex& schutz_mutex) {
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    synchronisierte_ausgabe(schutz_mutex, "Aufgabe " + std::to_string(aufgaben_id) + ", Thread: " + oss.str());
}

int main() {
    // 1. Haupt-Thread-Informationen
    std::mutex schutz_mutex;
    std::ostringstream main_oss;
    main_oss << std::this_thread::get_id();
    synchronisierte_ausgabe(schutz_mutex, "Haupt-Thread: " + main_oss.str());

    // 2. Einzelner Thread
    {
        std::jthread einzel_aufgabe([&schutz_mutex]() {
            verarbeite_aufgabe(0, schutz_mutex);
        }); // Automatischer Join
    }

    // 3. Mehrere Threads
    std::vector<std::jthread> aufgaben_vektor;
    int aufgaben_zaehler = 0;
    for (int id = 1; id <= 4; ++id) {
        aufgaben_vektor.emplace_back([id, &schutz_mutex, &aufgaben_zaehler]() {
            verarbeite_aufgabe(id, schutz_mutex);
            ++aufgaben_zaehler;
        });
    }

    // 4. Threads überwachen
    for (const auto& t : aufgaben_vektor) {
        std::ostringstream oss;
        oss << t.get_id();
        synchronisierte_ausgabe(schutz_mutex, "Überwachung Thread: " + oss.str());
    }

    // 5. Zusammenfassung
    {
        synchronisierte_ausgabe(schutz_mutex, "Anzahl Aufgaben: " + std::to_string(aufgaben_vektor.size()));
        synchronisierte_ausgabe(schutz_mutex, "Abgeschlossene Aufgaben: " + std::to_string(aufgaben_zaehler));
    }

    // 6. Vergleichstest
    synchronisierte_ausgabe(schutz_mutex, "Vergleichstest:");
    std::stringstream ausgabe;
    auto alte_ausgabe = std::cout.rdbuf(ausgabe.rdbuf());
    std::cout.flush(); // Flush vor Umleitung
    verarbeite_aufgabe(999, schutz_mutex);
    std::cout.rdbuf(alte_ausgabe);
    std::ostringstream main_oss_test;
    main_oss_test << std::this_thread::get_id();
    std::string erwartet = "Aufgabe 999, Thread: " + main_oss_test.str() + "\n";
    using AufrufErgebnis = std::invoke_result_t<decltype(verarbeite_aufgabe), int, std::mutex&>;
    static_assert(std::is_same_v<AufrufErgebnis, void>, "verarbeite_aufgabe sollte void sein");
    if (ausgabe.str() == erwartet) {
        synchronisierte_ausgabe(schutz_mutex, "Test erfolgreich");
        return 0;
    } else {
        synchronisierte_ausgabe(schutz_mutex, "Test fehlgeschlagen: erwartet \"" + erwartet + "\", erhalten \"" + ausgabe.str() + "\"");
        return 1;
    }
}