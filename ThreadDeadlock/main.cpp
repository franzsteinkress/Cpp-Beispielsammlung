#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <sstream>
#include <type_traits>
#include <functional>

// Verwaltet sicheren Zugriff auf eine gemeinsame Ressource
class SichererZugriff {
public:
    // Startet Threads mit synchronisiertem Zugriff
    void starte_sicheren_zugriff() {
        std::jthread thread1(&SichererZugriff::verarbeite_meldungen, this, 1); // 0-9
        std::jthread thread2(&SichererZugriff::verarbeite_meldungen, this, 2); // 10-19
        std::jthread thread3(&SichererZugriff::verarbeite_meldungen, this, 3); // 20-29
        for (int meldungs_id = 0; meldungs_id > -10; --meldungs_id) {
            sende_meldung(meldungs_id); // -1 bis -9
        }
    }

private:
    // Verarbeitet Meldungen für einen Thread
    void verarbeite_meldungen(int thread_nummer) {
        for (int meldungs_id = 10 * (thread_nummer - 1); meldungs_id < 10 * thread_nummer; ++meldungs_id) {
            sende_meldung(meldungs_id);
        }
    }

    // Sendet eine synchronisierte Meldung
    void sende_meldung(int meldungs_id) {
        std::lock_guard<std::mutex> sperre(ressourcen_mutex);
        std::cout << "Meldung: " << meldungs_id << ", Thread-ID: " << std::this_thread::get_id() << '\n';
    }

    std::mutex ressourcen_mutex;
};

// Verwaltet verzögerten Zugriff mit mehreren Mutexen
class VerzögerterZugriff {
public:
    // Startet Threads mit potenziellen Deadlock-Risiken
    void starte_verzögerten_zugriff() {
        std::jthread thread1(&VerzögerterZugriff::verarbeite_meldungen, this, 1); // 0-9
        std::jthread thread2(&VerzögerterZugriff::verarbeite_meldungen, this, 2); // 10-19
        std::jthread thread3(&VerzögerterZugriff::verarbeite_meldungen, this, 3); // 20-29
        for (int meldungs_id = 0; meldungs_id > -meldungs_größe; --meldungs_id) {
            sende_meldung_haupt(meldungs_id); // -1 bis -9
        }
    }

private:
    // Verarbeitet Meldungen mit unterschiedlichen Mutex-Reihenfolgen
    void verarbeite_meldungen(int thread_nummer) {
        for (int meldungs_id = meldungs_größe * (thread_nummer - 1); meldungs_id < meldungs_größe * thread_nummer; ++meldungs_id) {
            if (thread_nummer % 2 == 0) {
                sende_meldung_gerade(meldungs_id);
            } else {
                sende_meldung_ungerade(meldungs_id);
            }
        }
    }

    // Sendet Meldung mit gerader Thread-Nummer
    void sende_meldung_gerade(int meldungs_id) {
        std::lock_guard<std::mutex> sperre1(ressourcen_mutex1);
        std::lock_guard<std::mutex> sperre2(ressourcen_mutex2);
        std::cout << "Gerade Meldung: " << meldungs_id << ", Thread-ID: " << std::this_thread::get_id() << '\n';
    }

    // Sendet Meldung mit ungerader Thread-Nummer
    void sende_meldung_ungerade(int meldungs_id) {
        std::lock_guard<std::mutex> sperre2(ressourcen_mutex2);
        std::lock_guard<std::mutex> sperre1(ressourcen_mutex1);
        std::cout << "Ungerade Meldung: " << meldungs_id << ", Thread-ID: " << std::this_thread::get_id() << '\n';
    }

    // Sendet Meldung im Haupt-Thread
    void sende_meldung_haupt(int meldungs_id) {
        std::lock_guard<std::mutex> sperre(ressourcen_mutex);
        std::cout << "Haupt-Meldung: " << meldungs_id << ", Thread-ID: " << std::this_thread::get_id() << '\n';
    }

    const int meldungs_größe = 10;
    std::mutex ressourcen_mutex, ressourcen_mutex1, ressourcen_mutex2;
};

// Demonstriert Deadlock-Szenarien und deren Vermeidung
class DeadlockSzenario {
public:
    // Simuliert einen Deadlock
    void simuliere_deadlock() {
        std::mutex mutex1, mutex2;
        std::jthread thread1([&mutex1, &mutex2] {
            std::cout << "Thread 1: Erwerbe mutex1\n";
            mutex1.lock();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::cout << "Thread 1: Erwerbe mutex2\n";
            mutex2.lock();
            mutex2.unlock();
            mutex1.unlock();
        });
        std::jthread thread2([&mutex1, &mutex2] {
            std::cout << "Thread 2: Erwerbe mutex2\n";
            mutex2.lock();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::cout << "Thread 2: Erwerbe mutex1\n";
            mutex1.lock();
            mutex1.unlock();
            mutex2.unlock();
        });
    }

    // Vermeidet einen Deadlock mit scoped_lock
    void vermeide_deadlock() {
        std::mutex mutex1, mutex2;
        std::jthread thread1([&mutex1, &mutex2] {
            std::cout << "Thread 1: Erwerbe beide Mutex\n";
            std::scoped_lock sperre(mutex1, mutex2);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::cout << "Thread 1: Mutex freigegeben\n";
        });
        std::jthread thread2([&mutex1, &mutex2] {
            std::cout << "Thread 2: Erwerbe beide Mutex\n";
            std::scoped_lock sperre(mutex2, mutex1);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::cout << "Thread 2: Mutex freigegeben\n";
        });
    }
};

int main() {
    // 1. Initialisierung der Szenarien
    SichererZugriff sicherer_zugriff;
    VerzögerterZugriff verzögerter_zugriff;
    DeadlockSzenario deadlock_szenario;

    // 2. Ausführung der Szenarien
    std::cout << "Sicherer Zugriff starten\n";
    sicherer_zugriff.starte_sicheren_zugriff();
    // std::cout << "Verzögerter Zugriff starten\n";
    // verzögerter_zugriff.starte_verzögerten_zugriff();
    std::cout << "Deadlock vermeiden\n";
    deadlock_szenario.vermeide_deadlock();

    // 3. Vergleichstest
    std::cout << "3. Vergleichstest\n";
    std::stringstream ausgabe;
    auto alte_ausgabe = std::cout.rdbuf(ausgabe.rdbuf());
    std::mutex test_mutex;
    {
        std::lock_guard<std::mutex> sperre(test_mutex);
        std::cout << "Test-Meldung: 999\n";
    }
    std::cout.rdbuf(alte_ausgabe);
    std::string erwartet = "Test-Meldung: 999\n";
    using AufrufErgebnis = std::invoke_result_t<decltype([](std::mutex& m, const std::string& msg) {
        std::lock_guard<std::mutex> sperre(m);
        std::cout << msg;
    }), std::mutex&, std::string>;
    static_assert(std::is_same_v<AufrufErgebnis, void>, "Meldung sollte void zurückgeben");
    if (ausgabe.str() == erwartet) {
        std::cout << "Test erfolgreich\n";
        return 0;
    } else {
        std::cout << "Test fehlgeschlagen: erwartet \"" << erwartet << "\", erhalten \"" << ausgabe.str() << "\"\n";
        return 1;
    }
}