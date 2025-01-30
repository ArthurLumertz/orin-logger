# Logger Utility for Orin 1.0.0

## Overview

The **Logger** utility is a lightweight logging system designed to track and display various log levels in an organized manner within the **Orin 1.0.0** framework. This utility supports multiple log levels, formatted logging, log retrieval, and persistent log storage in files.

The logger supports five different log levels to help categorize log messages:

- **Debug**: Used for development and troubleshooting.
- **Info**: Logs general application flow information.
- **Warning**: Indicates non-critical issues or potential problems.
- **Error**: Logs errors that require attention or resolution.
- **Fatal**: Captures critical errors that might stop the application.

## Features

- **Multiple Log Levels**: Logs messages with different severity levels: Debug, Info, Warning, Error, Fatal.
- **Log Retrieval**: Retrieves all logs as a vector
- **Persistent Logs**: Allows logs to be written to a file.
- **Custom Log Colors**: Each log level is displayed with a unique color for better visibility and differentiation.
  - **Info**: White
  - **Debug**: Light Gray
  - **Warning**: Yellow
  - **Error**: Red
  - **Fatal**: Dark Red

## Installation

To use the **Logger** utility, follow these steps:

### 1. Clone the Repository or Add the Files

Download the logger source files and add them to your project. Ensure the following files are available in your project:

- `logger.cpp` – The main logger implementation file.
- `logger.h` – The header file for the logger functions.

### 3. Include Logger Header

In your source files, include the logger header file:

```c
#include <logger/logger.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    /* Sets the log level, meaning anything below WARNING is not printed.
       The full list (order=low->high):
       (
        DEBUG,
        WARNING,
        ERROR,
        FATAL,
        INFO
       )
    */
    logger::setLogLevel(logger::WARNING);

    // Makes the logger use the primary thread (default=true)
    // Highly recommended to use main thread
    logger::usePrimaryThread(true);

    // Log messages with different severity levels
    logger::debug("This is a debug message!"); // Won't print because log level is warning
    logger::info("This is a info message!");
    logger::warn("This is a warning message!");
    logger::error("This is a warning message!");
    logger::fatal("This is a fatal message!");

    // Get all logs as a concatenated string
    std::vector<std::string> fullLog = logger::getFullLog();

    // Preparing file
    std::ofstream file("example.log");
    if (!file.is_open()) {
      logger::fatal("Failed to open file!");
      return -1;
    }

    // Write all of the logs to the output stream
    logger::writeLog(file);

    // Preparing file
    std::ifstream inputFile("example.log");
    if (!inputFile.is_open()) {
      logger::fatal("Failed to open file!");
      return -1;
    }

    // Read the contents and set the logs as the specified file
    logger::readLog(inputFile);

    return 0;
}
