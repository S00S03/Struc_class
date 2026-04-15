#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "MedievalQueue.hpp"
#include "Teller.hpp"

int main() {
    srand(time(0));

    int totalTime = rand() % (240 - 120 + 1) + 120;
    int numClients = 10 + rand() % 20;  // Between 10-30 clients

    MedievalQueue q;

    // Adds half of the clients as nobles and the other half as plebeyos
    for (int i = 0; i < numClients / 2; i++) {
        q.enqueue("Plebeyo", false);
    }
    for (int i = 0; i < numClients / 2; i++) {
        q.enqueue("Noble", true);
    }
    std::cout << "Initial queue: ";
    q.print();

    const int numTellers = 3;
    Teller tellers[numTellers] = {Teller(1), Teller(2), Teller(3)};

    int time = 0;
    while (time < totalTime) {
        if (q.isEmpty() && tellers[0].isAvailable() &&
            tellers[1].isAvailable() && tellers[2].isAvailable()) {
            std::cout << "No more clients left. Closing." << std::endl;
            break;
        }

        // Each teller works on their client
        for (int i = 0; i < numTellers; i++) {
            tellers[i].serveClient(q);
        }

        std::cout << "Time: " << time << " / " << totalTime
                  << " | Clients left: " << q.getNumElements() << std::endl;
        q.print();
        std::cout << "---------------------------------\n";

        time++;
        std::this_thread::sleep_for(
            std::chrono::seconds(1));  // Simulate real-time
    }

    // Final statistics
    std::cout << "Final Report: \n";
    for (int i = 0; i < numTellers; i++) {
        std::cout << "Teller " << i + 1 << " attended "
                  << tellers[i].getClientsAttended() << " clients.\n";
    }

    return 0;
}

