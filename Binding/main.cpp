#include <iostream>
#include <random>
#include <memory>
#include <functional>
#include <sstream>
#include <type_traits>

// Gibt eine Nachricht mit drei Werten aus
void sende_nachricht(int prioritaet, const std::string& text, int id) {
    std::cout << "Priorität: " << prioritaet << ", Text: " << text << ", ID: " << id << '\n';
}

// Verdoppelt einen Wert
int verdopple(int wert) {
    return wert * 2;
}

// Klasse für Nachrichtenverarbeitung
class NachrichtenVerarbeiter {
public:
    void verarbeite_nachricht(int schweregrad, const std::string& inhalt) {
        std::cout << "Schweregrad: " << schweregrad << ", Inhalt: " << inhalt << '\n';
    }
    int status = 100;
};

int main() {
    // 1. Argumente binden und umordnen mit std::bind
    std::cout << "1. Argumente binden und umordnen: ";
    std::string nachricht = "Wichtig";
    auto nachricht_binder = std::bind(sende_nachricht, std::placeholders::_2, std::cref(nachricht), std::placeholders::_1);
    nachricht = "Dringend";
    nachricht_binder(101, 5); // Aufruf: sende_nachricht(5, nachricht, 101)

    // 2. Lambda als moderne Alternative
    std::cout << "2. Lambda für gleiche Funktionalität: ";
    auto nachricht_lambda = [nachricht_ref = std::cref(nachricht)](int id, int prio) {
        sende_nachricht(prio, nachricht_ref, id);
    };
    nachricht_lambda(101, 5); // Aufruf: sende_nachricht(5, nachricht, 101)

    // 3. Verschachtelte Bindung
    std::cout << "3. Verschachtelte Bindung: ";
    auto verschachtelte_bindung = std::bind(sende_nachricht, std::placeholders::_1, "Info", std::bind(verdopple, std::placeholders::_1));
    verschachtelte_bindung(10); // Aufruf: sende_nachricht(10, "Info", verdopple(10))

    // 4. Zufallszahlengenerator mit std::bind_front
    std::cout << "4. Zufallszahlengenerator binden: ";
    std::default_random_engine zufallsgenerator;
    std::uniform_int_distribution<> verteilung(1, 100);
    auto zufalls_binder = std::bind_front(verteilung, zufallsgenerator);
    for (int i = 0; i < 10; ++i) {
        std::cout << zufalls_binder() << ' ';
    }
    std::cout << '\n';

    // 5. Mitgliedsfunktion binden mit std::bind_front
    std::cout << "5. Mitgliedsfunktion binden: ";
    NachrichtenVerarbeiter verarbeiter;
    auto nachricht_verarbeiter = std::bind_front(&NachrichtenVerarbeiter::verarbeite_nachricht, &verarbeiter, 3);
    nachricht_verarbeiter("Alarm"); // Aufruf: verarbeiter.verarbeite_nachricht(3, "Alarm")

    // 6. std::mem_fn für Mitgliedsfunktion
    std::cout << "6. std::mem_fn für Mitgliedsfunktion: ";
    auto verarbeite_ptr = std::mem_fn(&NachrichtenVerarbeiter::verarbeite_nachricht);
    auto verarbeiter_binder = std::bind_front(verarbeite_ptr, &verarbeiter, 3);
    verarbeiter_binder("Alarm"); // Aufruf: verarbeiter.verarbeite_nachricht(3, "Alarm")

    // 7. Datenmember binden mit std::bind_front
    std::cout << "7. Datenmember binden: ";
    auto status_binder = std::bind_front(&NachrichtenVerarbeiter::status);
    std::cout << status_binder(&verarbeiter) << '\n'; // Ausgabe: verarbeiter.status

    // 8. std::mem_fn für Datenmember
    std::cout << "8. std::mem_fn für Datenmember: ";
    auto status_ptr = std::mem_fn(&NachrichtenVerarbeiter::status);
    auto status_mem_binder = std::bind_front(status_ptr);
    std::cout << status_mem_binder(&verarbeiter) << '\n'; // Ausgabe: verarbeiter.status

    // 9. Smart Pointer mit gebundenen Funktionen
    std::cout << "9. Smart Pointer verwenden: ";
    auto shared_verarbeiter = std::make_shared<NachrichtenVerarbeiter>(verarbeiter);
    auto unique_verarbeiter = std::make_unique<NachrichtenVerarbeiter>(verarbeiter);
    std::cout << status_mem_binder(shared_verarbeiter) << ' ' << status_mem_binder(unique_verarbeiter) << '\n';

    // 10. Vergleichstest mit std::invoke_result_t
    std::cout << "10. Vergleichstest: ";
    int test_prioritaet = 50;
    auto test_binder = std::bind(sende_nachricht, std::placeholders::_1, "Test", std::cref(test_prioritaet));

    // Rückgabetyp prüfen mit std::invoke_result_t
    using TestErgebnis = std::invoke_result_t<decltype(test_binder), int>;
    static_assert(std::is_same_v<TestErgebnis, void>, "test_binder sollte void zurückgeben");

    std::stringstream ausgabe;
    auto alte_ausgabe = std::cout.rdbuf(ausgabe.rdbuf());
    test_binder(99); // Soll ausgeben: "Priorität: 99, Text: Test, ID: 50"
    std::cout.rdbuf(alte_ausgabe);
    std::string erwartet = "Priorität: 99, Text: Test, ID: 50\n";
    if (ausgabe.str() == erwartet) {
        std::cout << "Test erfolgreich\n";
        return 0;
    } else {
        std::cout << "Test fehlgeschlagen: erwartet \"" << erwartet << "\", erhalten \"" << ausgabe.str() << "\"\n";
        return 1;
    }
}
