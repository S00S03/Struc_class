#include "Teller.hpp"

Teller::Teller(int id)
    : id(id), currentClient(-1), remainingTime(0), clientsAttended(0) {}

Teller::Teller(const Teller &other) {
    if (this != &other) {
        id = other.id;
        currentClient = other.currentClient;
        remainingTime = other.remainingTime;
        clientsAttended = other.clientsAttended;
    }
}

void Teller::serveCustomer(Queue<int> &q) {
    if (currentClient == -1 && !q.isEmpty()) {
        currentClient = q.getFront();
        q.dequeue();
        remainingTime = 10 + rand() % 20;
        std::cout << "Teller " << id << " serving client " << currentClient
                  << " for " << remainingTime << " minutes " << std::endl;
    }

    if (remainingTime > 0) {
        remainingTime--;
        std::cout << "Teller " << id << " is attending client " << currentClient
                  << "  Remaining time: " << remainingTime << std::endl;
    }

    if (remainingTime == 0 && currentClient != -1) {
        std::cout << "Teller " << id << " finished serving client " << currentClient << std::endl;
        currentClient = -1;
        clientsAttended++;
        
    }
}

bool Teller::isAvailable() const {
    return currentClient == -1;
}
int Teller::getClientsAttended() const {
    return clientsAttended;
}
