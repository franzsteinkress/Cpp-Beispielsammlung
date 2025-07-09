// Copyright (c) 2025 Franz Steinkress
// Licensed under the MIT License - see LICENSE file for details
//
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <functional>
#include <sstream>
#include <type_traits>

// Verarbeitet Daten und gibt sie formatiert aus
void verarbeite_daten(int id, int wert, const std::string& beschreibung) {
    std::cout << "ID: " << id << ", Wert: " << wert << ", Beschreibung: " << beschreibung << '\n';
}

// Addiert zwei Werte
int addiere(int a, int b) {
    return a + b;
}

// Funktionsobjekt zur Datenausgabe
struct DatenAusgeber {
    void operator()(int wert) const {
        std::cout << "Wert: " << wert << '\n';
    }
};

// Delegierte Funktion zur Verarbeitung
int delegiere(int(*operation)(int, int), int x, int y) {
    return operation(x, y);
}

int main() {
    // 1. for_each zur Ausgabe und Transformation
    std::vector<int> werte{10, 20, 30, 40, 50, 60};
    std::cout << "1. for_each Ausgabe und Transformation:\n";
    auto ausgabe_lambda = [](const int& w) { std::cout << " " << w; };
    std::cout << "Vorher:";
    std::for_each(werte.begin(), werte.end(), ausgabe_lambda);
    std::cout << "\nErhöht:";
    std::for_each(werte.begin(), werte.end(), [](int& w) { w += 5; std::cout << " " << w; });
    int summe = 0;
    std::for_each(werte.begin(), werte.end(), [&summe](const int& w) { summe += w; });
    std::cout << "\nSumme: " << summe << '\n';

    // 2. for_each zur Filterung
    std::cout << "\n2. for_each Filterung:\n";
    std::cout << "Größer 30:";
    std::for_each(werte.begin(), werte.end(), [](const int& w) { if (w > 30) std::cout << " " << w; });
    std::cout << "\nKleiner oder gleich 30:";
    std::for_each(werte.begin(), werte.end(), [](const int& w) { if (w <= 30) std::cout << " " << w; });

    // 3. Funktionsdelegierung
    std::cout << "\n3. Funktionsdelegierung:\n";
    auto addition_lambda = [](int x, int y) { return x + y; };
    std::cout << "Ohne Delegierung: " << addition_lambda(5, 7) << '\n';
    std::cout << "Mit Delegierung: " << delegiere(addition_lambda, 5, 7) << '\n';

    // 4. Numerische Algorithmen
    std::cout << "\n4. Numerische Algorithmen:\n";
    std::vector<int> zahlen(8, 3);
    std::cout << "Summenfolge:";
    std::partial_sum(zahlen.begin(), zahlen.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
    std::partial_sum(zahlen.begin(), zahlen.end(), zahlen.begin(), std::multiplies<int>());
    std::cout << "Produktfolge:";
    for (const auto& z : zahlen) {
        std::cout << " " << z;
    }
    std::cout << '\n';
    if (std::all_of(zahlen.cbegin(), zahlen.cend(), [](int z) { return z % 3 == 0; })) {
        std::cout << "Alle Zahlen sind durch 3 teilbar\n";
    }
    if (std::none_of(zahlen.cbegin(), zahlen.cend(), [](int z) { return z % 2 == 0; })) {
        std::cout << "Keine Zahl ist gerade\n";
    }

    // 5. Funktionsbindung
    std::cout << "\n5. Funktionsbindung:\n";
    std::string beschreibung = "Wichtig";
    auto daten_binder = std::bind_front(verarbeite_daten, 100, 200);
    daten_binder(beschreibung);
    auto daten_lambda = [beschreibung_ref = std::cref(beschreibung)](int id, int wert) {
        verarbeite_daten(id, wert, beschreibung_ref);
    };
    daten_lambda(300, 400);

    // 6. Vergleichstest
    std::cout << "\n6. Vergleichstest:\n";
    std::stringstream ausgabe;
    auto alte_ausgabe = std::cout.rdbuf(ausgabe.rdbuf());
    std::for_each(werte.begin(), werte.end(), ausgabe_lambda);
    std::cout.rdbuf(alte_ausgabe);
    std::string erwartet = " 15 25 35 45 55 65";
    using AufrufErgebnis = std::invoke_result_t<decltype(ausgabe_lambda), int>;
    static_assert(std::is_same_v<AufrufErgebnis, void>, "ausgabe_lambda sollte void zurückgeben");
    if (ausgabe.str() == erwartet) {
        std::cout << "Test erfolgreich\n";
        return 0;
    } else {
        std::cout << "Test fehlgeschlagen: erwartet \"" << erwartet << "\", erhalten \"" << ausgabe.str() << "\"\n";
        return 1;
    }
}