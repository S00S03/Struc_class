#include "Teller.hpp"
#include <iostream>

Teller::Teller(int id)
    : id(id), currentClient("free"), remainingTime(0), clientsAttended(0) {}

void Teller::serveClient(MedievalQueue& q) {
    // Pick the next client from the queue
    if (currentClient == "free" && !q.isEmpty()) {
        currentClient = q.front();
        // currentClientStatus = q.isNoble();
        q.dequeue();
        remainingTime = 3 + rand() % 5;  // Random processing time 3-7 seconds
        std::cout << "Teller " << id << " started attending client "
                  << currentClient << " for " << remainingTime << " seconds."
                  << std::endl;
    }
    if (remainingTime > 0) {
        remainingTime--;
        std::cout << "Teller " << id << " is attending client " << currentClient
                  << ". Remaining time: " << remainingTime << std::endl;
    }

    if (remainingTime == 0 && currentClient != "free") {
        std::cout << "Teller " << id << " finished attending client "
                  << currentClient << std::endl;
        currentClient = "free";  // Ready for the next client
        clientsAttended++;
        
    }
}

bool Teller::isAvailable() const { return currentClient == "free"; }

int Teller::getClientsAttended() const { return clientsAttended; }
