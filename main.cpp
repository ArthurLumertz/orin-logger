#include <iostream>
#include <cstdint>

#define ORIN_TIME_IMPLEMENTATION
#include <orinlogger.hpp>

uint64_t getTime() {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return duration.count();
}

int main() {
    orin::logger logger(orin::level::all);

    double millis[3];

    const char *textToPrint = "Hello world! Hello world! Hello world! Hello world! Hello world! Hello world!"; // 6 Hello world's

    for (int i = 0; i < 3; i++) {
        uint64_t startTime = getTime();

        unsigned int count = 0;
        while (count < 10000) {
            if (i == 0) logger.info(textToPrint); // 5 milliseconds
            else if (i == 1) std::cout << textToPrint << std::endl; // 22 milliseconds
            else if (i == 2) printf("%s\n", textToPrint); // 16 milliseconds

            count++;
        }

        uint64_t endTime = getTime();
        millis[i] = endTime - startTime;

    }

    for (int i = 0; i < 3; i++) {
        double duration = millis[i];
        std::cout << "[" << (i == 0 ? "logger" : i == 1 ? "std::cout" : "printf") << "] Took " << duration << " millisecond(s) (" << duration / 1000.0 << " seconds)" << std::endl;
    }



    return 0;
}