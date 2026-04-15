#ifndef TELLER_HPP
#define TELLER_HPP

#include "Queue.hpp"

class Teller {
public:
    Teller(int id);
    Teller(const Teller &other);

    void serveCustomer(Queue<int>& q);
    bool isAvailable() const;
    int getClientsAttended() const;


private:
    int id;
    int currentClient; // -1 if free
    int remainingTime; // Time left to finish the current client
    int clientsAttended;
};

#endif // !TELLER_HPP 
