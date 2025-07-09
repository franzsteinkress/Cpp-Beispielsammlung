// Copyright (c) 2025 Franz Steinkress
// Licensed under the MIT License - see LICENSE file for details
//
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <sstream>
#include <type_traits>
#include <functional>

// Synchronisiert die Konsolenausgabe
void synchronisierte_ausgabe(std::mutex& ausgabe_mutex, const std::string& meldung) {
    std::lock_guard<std::mutex> sperre(ausgabe_mutex);
    std::cout << meldung << std::endl;
}

// Verwaltet Meldungen mit unterschiedlichen Prioritäten
class MeldungsVerwaltung {
public:
    // Startet die Verarbeitung von Meldungen
    void verarbeite_meldungen(std::mutex& ausgabe_mutex) {
        std::jthread thread1(&MeldungsVerwaltung::verarbeite_hauptmeldungen, this, std::ref(ausgabe_mutex));
        std::jthread thread2(&MeldungsVerwaltung::verarbeite_systemmeldungen, this, std::ref(ausgabe_mutex));
    }

private:
    // Verarbeitet Hauptmeldungen
    void verarbeite_hauptmeldungen(std::mutex& ausgabe_mutex) {
        synchronisierte_ausgabe(ausgabe_mutex, "Haupt-Thread-ID: " + std::to_string(thread_id_zaehler++));
        for (int meldungs_id = 0; meldungs_id < 5; ++meldungs_id) {
            synchronisierte_ausgabe(ausgabe_mutex, "Haupt-Meldungs-ID: " + std::to_string(meldungs_id) + ", Thread-ID: " + std::to_string(thread_id_zaehler));
        }
    }

    // Verarbeitet Systemmeldungen
    void verarbeite_systemmeldungen(std::mutex& ausgabe_mutex) {
        synchronisierte_ausgabe(ausgabe_mutex, "Systemmeldung: Systemstart, Thread-ID: " + std::to_string(thread_id_zaehler++));
        for (int meldungs_id = -50; meldungs_id < -45; ++meldungs_id) {
            synchronisierte_ausgabe(ausgabe_mutex, "Meldungs-ID: " + std::to_string(meldungs_id) + ", Thread-ID: " + std::to_string(thread_id_zaehler));
        }
    }

    int thread_id_zaehler = 1;
};

// Verwaltet Statusmeldungen
class StatusVerwaltung {
public:
    // Startet die Verarbeitung von Statusmeldungen
    void verarbeite_statusmeldungen(std::mutex& ausgabe_mutex) {
        std::jthread thread(&StatusVerwaltung::verarbeite_status, this, std::ref(ausgabe_mutex));
    }

private:
    // Verarbeitet Statusmeldungen
    void verarbeite_status(std::mutex& ausgabe_mutex) {
        synchronisierte_ausgabe(ausgabe_mutex, "Statusmeldung: Initialisierung, Thread-ID: " + std::to_string(thread_id_zaehler++));
        for (int status_id = -10; status_id < -5; ++status_id) {
            synchronisierte_ausgabe(ausgabe_mutex, "Typ: Status, ID: " + std::to_string(status_id) + ", Thread-ID: " + std::to_string(thread_id_zaehler));
        }
    }

    int thread_id_zaehler = 1;
};

// Verwaltet Abschlussmeldungen
class AbschlussVerwaltung {
public:
    // Startet die Verarbeitung von Abschlussmeldungen
    void verarbeite_abschlussmeldungen(std::mutex& ausgabe_mutex) {
        std::jthread thread(&AbschlussVerwaltung::verarbeite_abschluss, this, std::ref(ausgabe_mutex));
    }

private:
    // Verarbeitet Abschlussmeldungen
    void verarbeite_abschluss(std::mutex& ausgabe_mutex) {
        synchronisierte_ausgabe(ausgabe_mutex, "Abschlussmeldung: Beendigung, Thread-ID: " + std::to_string(thread_id_zaehler++));
        for (int abschluss_id = 10; abschluss_id > 5; --abschluss_id) {
            synchronisierte_ausgabe(ausgabe_mutex, "Typ: Abschluss, ID: " + std::to_string(abschluss_id) + ", Thread-ID: " + std::to_string(thread_id_zaehler));
        }
    }

    int thread_id_zaehler = 1;
};

int main() {
    // 1. Initialisierung der Verwaltungsklassen
    MeldungsVerwaltung meldungs_verwaltung;
    StatusVerwaltung status_verwaltung;
    AbschlussVerwaltung abschluss_verwaltung;
    std::mutex ausgabe_mutex;

    // 2. Starten der Meldungsverarbeitung
    meldungs_verwaltung.verarbeite_meldungen(ausgabe_mutex);

    // 3. Starten der Statusverarbeitung
    status_verwaltung.verarbeite_statusmeldungen(ausgabe_mutex);

    // 4. Starten der Abschlussverarbeitung
    abschluss_verwaltung.verarbeite_abschlussmeldungen(ausgabe_mutex);

    // 5. Vergleichstest
    {
        std::stringstream ausgabe;
        auto alte_ausgabe = std::cout.rdbuf(ausgabe.rdbuf());
        std::cout << "Test-Meldung: 42\n";
        std::cout.rdbuf(alte_ausgabe);
        synchronisierte_ausgabe(ausgabe_mutex, "5. Vergleichstest:");
        std::string erwartet = "Test-Meldung: 42\n";
        using AufrufErgebnis = std::invoke_result_t<decltype([](const std::string& msg) { std::cout << msg; }), std::string>;
        static_assert(std::is_same_v<AufrufErgebnis, void>, "Ausgabe sollte void sein");
        if (ausgabe.str() == erwartet) {
            synchronisierte_ausgabe(ausgabe_mutex, "Test erfolgreich");
            return 0;
        } else {
            synchronisierte_ausgabe(ausgabe_mutex, "Test fehlgeschlagen: erwartet \"" + erwartet + "\", erhalten \"" + ausgabe.str() + "\"");
            return 1;
        }
    }
}