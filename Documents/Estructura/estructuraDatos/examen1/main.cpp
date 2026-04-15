#include "MedievalQueue.hpp"
#include <iostream>
#include <thread>

void kingArthurSimulation(MedievalQueue &medievalQueue) {
    int tiempoAtencion = 3;

    while (!medievalQueue.isEmpty()) {
        std::string person = medievalQueue.front();
        std::cout << "Attending " << person << std::endl;
        
        medievalQueue.dequeue();
        // tiempoAtencion--;
        // sleep(tiempoAtencion) c++?
        std::this_thread::sleep_for(std::chrono::seconds(tiempoAtencion));
    }

    std::cout << "Simulation finished" << std::endl;
}

int main() {
    MedievalQueue medievalQueue;

    medievalQueue.enqueue("Noble", true);
    medievalQueue.enqueue("Noble", true);
    medievalQueue.enqueue("Plebeyo", false);
    medievalQueue.enqueue("Noble", true);
    medievalQueue.enqueue("Noble", true);
    medievalQueue.enqueue("Plebeyo", false);
    medievalQueue.enqueue("Plebeyo", false);
    medievalQueue.enqueue("Plebeyo", false);

    kingArthurSimulation(medievalQueue);

    // medievalQueue.getPosition(4);

    // medievalQueue.print();

    // std::cout << medievalQueue.front() << std::endl;
    // std::cout << medievalQueue.isEmpty() << std::endl;
    // std::cout << medievalQueue.getNumNobles() << std::endl;
    // std::cout << medievalQueue.getNumPlebeyos() << std::endl;

    return 0;
}
