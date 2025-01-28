# Logger
A simple logging utility made in C used in **Orin 1.0.0** to track and display various log levels in an organized manner.

## Overview
The logger provides functionality to log messages at different levels, including:
- **Debug**: Used for development and debugging.
- **Info**: General information about the application's execution.
- **Warning**: Indicates potential issues or non-critical problems.
- **Error**: Logs critical issues that might require attention.
- **Fatal**: Logs severe errors that may terminate the application.

## Example Usage

Below is an example of how to integrate and use the logger in your application.

```cpp
// Include the logger header file
#include <logger/logger.h>

int main() {
    // Log a debug message
    LOGGER_debug("This is a debug message");

    // Log an info message
    LOGGER_info("This is an informational message");

    // Log a warning message
    LOGGER_warning("This is a warning message");

    // Log an error message
    LOGGER_error("This is an error message");

    // Log a fatal message
    LOGGER_fatal("This is a fatal error message");

    return 0;
}
