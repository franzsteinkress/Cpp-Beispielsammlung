// Copyright (c) 2025 Franz Steinkress
// Licensed under the MIT License - see LICENSE file for details
//
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <sstream>
#include <type_traits>
#include <functional>

// Verwaltet einen thread-sicheren Stapel
class Datenstapel {
public:
    // Konstruktor und Destruktor
    Datenstapel() = default;
    ~Datenstapel() = default;

    // Entfernt das oberste Element
    void entferne_oberstes() {
        std::lock_guard<std::mutex> sperre(ressourcen_mutex);
        if (!daten_vektor.empty()) {
            daten_vektor.pop_back();
        }
    }

    // Gibt das oberste Element zurück
    int gib_oberstes() {
        std::lock_guard<std::mutex> sperre(ressourcen_mutex);
        return daten_vektor.empty() ? 0 : daten_vektor.back();
    }

    // Fügt ein Element hinzu
    void füge_hinzu(int wert) {
        std::lock_guard<std::mutex> sperre(ressourcen_mutex);
        daten_vektor.push_back(wert);
    }

    // Gibt die Größe des Stapels zurück
    int gib_größe() {
        std::lock_guard<std::mutex> sperre(ressourcen_mutex);
        return daten_vektor.size();
    }

    // Druckt den Stapelinhalt
    void drucke_inhalt() {
        std::lock_guard<std::mutex> sperre(ressourcen_mutex);
        std::cout << "Initialer Stapel: ";
        for (int element : daten_vektor) {
            std::cout << element << " ";
        }
        std::cout << '\n';
    }

private:
    std::vector<int> daten_vektor;
    std::mutex ressourcen_mutex;
};

// Verarbeitet ein Element mit synchronisierter Ausgabe
void verarbeite_element(int wert, const std::string& thread_name, std::mutex& ausgabe_mutex) {
    std::lock_guard<std::mutex> sperre(ausgabe_mutex);
    std::cout << thread_name << ": " << wert << '\n';
}

// Führt die Verarbeitung in einem Thread aus
void thread_verarbeitung(Datenstapel& stapel, const std::string& thread_name, std::mutex& ausgabe_mutex) {
    if (stapel.gib_größe() > 0) {
        int wert = stapel.gib_oberstes();
        stapel.entferne_oberstes();
        verarbeite_element(wert, thread_name, ausgabe_mutex);
    }
}

int main() {
    // 1. Initialisierung des Stapels
    Datenstapel stapel;
    for (int i = 0; i < 10; ++i) {
        stapel.füge_hinzu(i);
    }
    stapel.drucke_inhalt();

    // 2. Threads für die Verarbeitung
    {
        std::mutex ausgabe_mutex;
        std::vector<std::jthread> threads;
        while (stapel.gib_größe() > 0) {
            threads.emplace_back(thread_verarbeitung, std::ref(stapel), "Thread1", std::ref(ausgabe_mutex));
            if (stapel.gib_größe() > 0) {
                threads.emplace_back(thread_verarbeitung, std::ref(stapel), "Thread2", std::ref(ausgabe_mutex));
            }
        }
        // Warte auf Abschluss aller Threads
    }

    // 3. Vergleichstest
    std::cout << "3. Vergleichstest\n";
    std::stringstream ausgabe;
    auto alte_ausgabe = std::cout.rdbuf(ausgabe.rdbuf());
    {
        std::mutex ausgabe_mutex;
        std::lock_guard<std::mutex> sperre(ausgabe_mutex);
        std::cout << "Test-Wert: 999\n";
    }
    std::cout.rdbuf(alte_ausgabe);
    std::string erwartet = "Test-Wert: 999\n";
    using AufrufErgebnis = std::invoke_result_t<decltype(verarbeite_element), int, std::string, std::mutex&>;
    static_assert(std::is_same_v<AufrufErgebnis, void>, "Verarbeitung sollte void zurückgeben");
    if (ausgabe.str() == erwartet) {
        std::cout << "Test erfolgreich\n";
        return 0;
    } else {
        std::cout << "Test fehlgeschlagen: erwartet \"" << erwartet << "\", erhalten \"" << ausgabe.str() << "\"\n";
        return 1;
    }
}