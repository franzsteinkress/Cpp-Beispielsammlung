// Copyright (c) 2025 Franz Steinkress
// Licensed under the MIT License - see LICENSE file for details
//
#include <iostream>
#include <functional>
#include <type_traits>
#include <sstream>

// Zeigt den Status eines Systems mit einer ID
void zeige_status(int system_id, const std::string& beschreibung) {
    std::cout << "System-ID: " << system_id << ", Beschreibung: " << beschreibung << '\n';
}

// Klasse zur Verarbeitung von Systemdaten
class DatenVerarbeiter {
public:
    DatenVerarbeiter(int wert) : system_wert(wert) {}
    // Fügt einen Offset zum Systemwert hinzu und gibt ihn aus
    void verarbeite_daten(int offset) const {
        std::cout << "Ergebnis: " << system_wert + offset << '\n';
    }
    int system_wert;
};

// Funktionsobjekt zur Ausgabe eines Status
struct StatusAusgeber {
    void operator()(int status_code) const {
        std::cout << "Status-Code: " << status_code << '\n';
    }
};

int main() {
    // 1. Aufruf einer freien Funktion
    std::invoke(zeige_status, 1001, "Aktiv");

    // 2. Aufruf eines Lambda-Ausdrucks
    auto ausgabe_lambda = [](const std::string& nachricht) { zeige_status(2002, nachricht); };
    std::invoke(ausgabe_lambda, "Bereit");

    // 3. Aufruf einer Mitgliedsfunktion
    const DatenVerarbeiter verarbeiter(500);
    std::invoke(&DatenVerarbeiter::verarbeite_daten, verarbeiter, 50);

    // 4. Zugriff auf einen Datenmember
    std::cout << "Systemwert: " << std::invoke(&DatenVerarbeiter::system_wert, verarbeiter) << '\n';

    // 5. Aufruf eines Funktionsobjekts
    std::invoke(StatusAusgeber(), 3003);

    // 6. Verwendung von std::invoke (C++23)
    auto berechne_summe = [](int a, int b) { return a + b; };
    auto summe = static_cast<float>(std::invoke(berechne_summe, 15, 25));
    static_assert(std::is_same_v<decltype(summe), float>, "Summe sollte float sein");
    std::cout << "Summe: " << summe << '\n';
    std::invoke(zeige_status, 4004, "Fertig");

    // 7. Vergleichstest
    std::cout << "Vergleichstest: ";
    std::stringstream ausgabe;
    auto alte_ausgabe = std::cout.rdbuf(ausgabe.rdbuf());
    std::invoke(zeige_status, 9999, "Test");
    std::cout.rdbuf(alte_ausgabe);
    std::string erwartet = "System-ID: 9999, Beschreibung: Test\n";
    using AufrufErgebnis = std::invoke_result_t<decltype(zeige_status), int, std::string>;
    static_assert(std::is_same_v<AufrufErgebnis, void>, "zeige_status sollte void zurückgeben");
    if (ausgabe.str() == erwartet) {
        std::cout << "Test erfolgreich\n";
        return 0;
    } else {
        std::cout << "Test fehlgeschlagen: erwartet \"" << erwartet << "\", erhalten \"" << ausgabe.str() << "\"\n";
        return 1;
    }
}