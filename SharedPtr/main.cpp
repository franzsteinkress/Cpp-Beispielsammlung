#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <type_traits>
#include <functional>

// Grundlegende Ressource
struct Ressource {
    Ressource() { std::cout << "Ressource erstellt\n"; }
    virtual ~Ressource() { std::cout << "Ressource zerstört\n"; }
};

// Erweiterte Ressource
struct ErweiterteRessource : public Ressource {
    ErweiterteRessource() { std::cout << "ErweiterteRessource erstellt\n"; }
    ~ErweiterteRessource() { std::cout << "ErweiterteRessource zerstört\n"; }
};

// Datenstruktur mit Wert
struct Daten {
    Daten(int wert) : wert{wert} { std::cout << "Daten erstellt: " << wert << '\n'; }
    ~Daten() { std::cout << "Daten zerstört: " << wert << '\n'; }
    int wert;
};

// Basisklasse für Medienobjekte
struct MedienObjekt {
    virtual ~MedienObjekt() = default; // Polymorphismus
};

// Lied als Medienobjekt
struct Lied : public MedienObjekt {
    std::string interpret;
    std::string titel;
    Lied(const std::string& interpret_, const std::string& titel_)
        : interpret{interpret_}, titel{titel_} {}
};

// Bild als Medienobjekt
struct Bild : public MedienObjekt {
    std::string datum;
    std::string ort;
    std::string motiv;
    Bild(const std::string& datum_, const std::string& ort_, const std::string& motiv_)
        : datum{datum_}, ort{ort_}, motiv{motiv_} {}
};

// Zeigt Ressourceninformationen in einem Thread
void zeige_ressource(std::shared_ptr<Ressource> ressourcen_zeiger, std::mutex& meldungs_mutex) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    auto lokaler_zeiger = ressourcen_zeiger; // Thread-sicher
    {
        std::lock_guard<std::mutex> sperre(meldungs_mutex);
        std::cout << "Thread-Ressource: Zeiger=" << lokaler_zeiger.get()
                  << ", Zähler=" << lokaler_zeiger.use_count() << '\n';
    }
}

int main() {
    // 1. Geteilter Zeiger mit polymorpher Ressource
    std::cout << "1. Polymorphe Ressource erstellen\n";
    auto ressourcen_zeiger = std::make_shared<ErweiterteRessource>();
    std::cout << "Ressourcen-Zeiger: " << ressourcen_zeiger.get()
              << ", Zähler=" << ressourcen_zeiger.use_count() << '\n';

    // 2. Threads mit geteiltem Zeiger
    std::cout << "2. Threads mit geteiltem Zeiger\n";
    std::mutex meldungs_mutex;
    std::jthread thread1(zeige_ressource, ressourcen_zeiger, std::ref(meldungs_mutex));
    std::jthread thread2(zeige_ressource, ressourcen_zeiger, std::ref(meldungs_mutex));
    ressourcen_zeiger.reset();
    std::cout << "Haupt-Thread nach Reset: Zeiger=" << ressourcen_zeiger.get()
              << ", Zähler=" << ressourcen_zeiger.use_count() << '\n';

    // 3. Geteilter Zeiger für Daten
    std::cout << "3. Geteiler Zeiger für Daten\n";
    auto daten_zeiger = std::make_shared<Daten>(256);
    std::cout << "Daten-Wert: " << daten_zeiger->wert << '\n';
    {
        auto lokaler_daten_zeiger = daten_zeiger;
        std::cout << "Lokaler Zähler: " << lokaler_daten_zeiger.use_count() << '\n';
    }
    std::cout << "Globaler Zähler: " << daten_zeiger.use_count() << '\n';
    daten_zeiger = std::make_shared<Daten>(512);
    daten_zeiger.reset();

    // 4. Initialisierungsvariationen für Lieder
    std::cout << "4. Initialisierungsvariationen\n";
    auto lied_zeiger1 = std::make_shared<Lied>("Queen", "Bohemian Rhapsody");
    auto lied_zeiger2 = std::make_shared<Lied>("Madonna", "Vogue");
    auto lied_zeiger3 = lied_zeiger2;
    lied_zeiger1.swap(lied_zeiger2);

    // 5. Sammlung von Liedern
    std::cout << "5. Lieder filtern\n";
    std::vector<std::shared_ptr<Lied>> lied_sammlung{
        std::make_shared<Lied>("Sting", "Fields of Gold"),
        std::make_shared<Lied>("Adele", "Rolling in the Deep"),
        std::make_shared<Lied>("Rihanna", "Umbrella")
    };
    std::vector<std::shared_ptr<Lied>> gefilterte_lieder;
    std::remove_copy_if(lied_sammlung.begin(), lied_sammlung.end(),
                        std::back_inserter(gefilterte_lieder),
                        [](const std::shared_ptr<Lied>& lied) {
                            return lied->interpret == "Sting";
                        });
    for (const auto& lied : gefilterte_lieder) {
        std::cout << lied->interpret << ": " << lied->titel << '\n';
    }

    // 6. Sammlung von Medienobjekten
    std::cout << "6. Medienobjekte filtern\n";
    std::vector<std::shared_ptr<MedienObjekt>> medien_sammlung{
        std::make_shared<Lied>("Beyoncé", "Single Ladies"),
        std::make_shared<Bild>("2025-06-22", "Berlin", "Park"),
        std::make_shared<Lied>("Drake", "Hotline Bling")
    };
    std::vector<std::shared_ptr<Bild>> bilder_sammlung;
    for (const auto& objekt : medien_sammlung) {
        if (auto bild = std::dynamic_pointer_cast<Bild>(objekt)) {
            bilder_sammlung.push_back(bild);
        }
    }
    for (const auto& bild : bilder_sammlung) {
        std::cout << "Bild-Ort: " << bild->ort << '\n';
    }

    // 7. Zeigervergleich
    std::cout << "7. Zeigervergleich\n";
    auto lied_zeiger4 = std::make_shared<Lied>("ABBA", "Dancing Queen");
    auto lied_zeiger5 = std::make_shared<Lied>("ABBA", "Dancing Queen");
    auto lied_zeiger6 = lied_zeiger5;
    std::cout << "Zeiger4 < Zeiger5: " << std::boolalpha << (lied_zeiger4 < lied_zeiger5) << '\n';
    std::cout << "Zeiger4 == Zeiger5: " << std::boolalpha << (lied_zeiger4 == lied_zeiger5) << '\n';
    std::cout << "Zeiger6 == Zeiger5: " << std::boolalpha << (lied_zeiger6 == lied_zeiger5) << '\n';

    // 8. Vergleichstest
    std::cout << "8. Vergleichstest\n";
    std::stringstream ausgabe;
    auto alte_ausgabe = std::cout.rdbuf(ausgabe.rdbuf());
    auto test_zeiger = std::make_shared<Daten>(999);
    std::cout << "Test-Wert: " << test_zeiger->wert << '\n';
    std::cout.rdbuf(alte_ausgabe);
    std::string erwartet = "Daten erstellt: 999\nTest-Wert: 999\n";
    using AufrufErgebnis = std::invoke_result_t<decltype([](const std::shared_ptr<Daten>& p) { return p->wert; }), std::shared_ptr<Daten>>;
    static_assert(std::is_same_v<AufrufErgebnis, int>, "Zugriff auf wert sollte int sein");
    if (ausgabe.str() == erwartet) {
        std::cout << "Test erfolgreich\n";
        return 0;
    } else {
        std::cout << "Test fehlgeschlagen: erwartet \"" << erwartet << "\", erhalten \"" << ausgabe.str() << "\"\n";
        return 1;
    }
}