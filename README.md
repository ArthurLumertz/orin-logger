# Orin Logger
the orin logger is a lightweight and fast logger inspired by log4j made for performance intensive tasks but with some minimal customization.

# Performance
77.27% performance boost compared to `std::cout` and `std::endl`

68.75% performance boost compared to `printf()`

# How to use
its header-only library, meaning you only have to move the `orinlogger.hpp` file into the source of your C++ project

## Code Example
```c++
/**
 * ORIN_TIME_IMPLEMENTATION
 * makes it that the time appears in the log
 * downside is that it makes the log 50% slower.
 */
#define ORIN_TIME_IMPLEMENTATION

// include the library
#include "src/orinlogger.hpp"

int main() {
    // create the logger with the log level set to all
    orin::logger logger(orin::level::all);

    // log some basic text to demonstrate the log levels
    // each log level has a custom color when outputted to the console
    logger.info("Info message!"); // white color
    logger.debug("Debug message!"); // dim gray color
    logger.warn("Warning message!"); // yellow color
    logger.error("Error message!"); // red color
    logger.fatal("Fatal message!"); // dark red color

    return 0;
}
```
