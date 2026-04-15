#ifndef TELLER_HPP
#define TELLER_HPP

#include "MedievalQueue.hpp"

class Teller {
public:
    Teller(int id);

    void serveClient(MedievalQueue& q);

    bool isAvailable() const;

    int getClientsAttended() const;

private:
    int id;               // Teller ID
    std::string currentClient;    // Client being attended (-1 if free)
    int remainingTime;    // Time left to finish current client
    int clientsAttended;  // Clients attended by this teller
};

#endif // TELLER_HPP
