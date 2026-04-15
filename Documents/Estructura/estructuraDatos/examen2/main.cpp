#include <iostream>
#include "List.hpp"

// n People, k steps
void game(int n, int k) {
    List list;
    for (int i = 1; i <= n; i++) {
        list.addHead(i);
    }

    // Initial list
    std::cout << "Initial List" << std::endl;
    list.printConnections();
    std::cout << std::endl;

    int i = 1;
    while (list.getSize() > 1) {
        std::cout << "Round " << i << std::endl;

        list.removeAt(k);
        list.printConnections();
        std::cout << std::endl;

        i++;
    }

    // finaLIST hehe
    std::cout << "The winner is: #" << list.getFront() << std::endl;

}

int main() {
    int n, k;
    std::cout << "Enter the number of people" << std::endl;
    std::cin >> n;

    if (n <= 1) {
        std::cout << "Invalid number of people" << std::endl;
        return 0;
    }

    std::cout << "Enter the number of steps" << std::endl;
    std::cin >> k;

    if (k <= 1) {
        std::cout << "Invalid number of steps" << std::endl;
        return 0;
    }

    game(n, k);

    return 0;
}
