#include "logger.h"
#include <iostream>
#include <chrono>

int main() {
    //logger::usePrimaryThread(false);

    std::cout << "Enter: ";
    unsigned int count;
    std::cin >> count;

    auto start = std::chrono::steady_clock::now();

    //logger::info("Hello!");
    //unsigned int count = 10000;
    while (count > 0) {
        logger::info(std::to_string(count));
        count--;
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    logger::info("Took " + std::to_string(duration.count()/1000.0f) + " seconds.");

    return 0;
}
