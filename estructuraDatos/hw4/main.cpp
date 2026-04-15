#include "Queue.hpp"
#include "Teller.hpp"
#include <cstdlib>
#include <iostream>
#include <thread>

int main() {

    // Attention time
    // get random between 120, 240
    srand(time(0));
    int totalTime = rand() % (240 - 120 + 1) + 120;

    // put new clients in the queue at random
    int numClients = 10 + rand() % 20;

    Queue<int> q;
    for (int i = 0; i < numClients; i++) {
        q.enqueue(i + 1);
    }
    q.print();

    const int numTellers = 3;
    Teller tellers[numTellers] = {Teller(1), Teller(2), Teller(3)};

    int time = 0;
    while (time < totalTime) {
        if (q.isEmpty() && tellers[0].isAvailable() && tellers[1].isAvailable() && tellers[2].isAvailable()) {
            std::cout << "No more clients left" << std::endl;
            break;
        }

        for (int i = 0; i < numTellers; i++) {
            tellers[i].serveCustomer(q);
        }

        std::cout << "Time: " << time << " / " << totalTime << " | Clients left: " << q.getNumElements() << std::endl;
        q.print();
        std::cout << "-------------------------------------------------------" << std::endl;

        time++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Finished Simulation" << std::endl;
    for (int i = 0; i < numTellers; i++) {
        std::cout << "Teller " << i + 1 << " Attended " << tellers[i].getClientsAttended() << " clients" << std::endl;
    }
    if (!q.isEmpty()) {
        std::cout << "Clients left to Attend: " << q.getNumElements() << std::endl;
        q.print();
    }
    return 0;
}
