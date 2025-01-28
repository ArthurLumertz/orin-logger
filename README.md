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
- **Formatted Logging**: Supports `printf`-style formatted logging.
- **Log Retrieval**: Retrieves all logs as a concatenated string.
- **Persistent Logs**: Allows logs to be written to a file.
- **Cross-Platform**: Compatible with both Windows and Linux.

## Installation

To use the **Logger** utility, follow these steps:

### 1. Clone the Repository or Add the Files

Download the logger source files and add them to your project. Ensure the following files are available in your project:

- `logger.c` – The main logger implementation file.
- `logger.h` – The header file for the logger functions.

### 2. Link Required DLL and LIB Files

If you’re building a shared library (`DLL`), ensure that the logger’s DLL and the corresponding `.LIB` file are linked correctly.

#### For Windows

1. **DLL and LIB Files**: If the logger is compiled into a DLL, ensure that the `logger.dll` and `logger.lib` files are linked to your project.
2. **Linking the LIB File**:
    - Add the path to `logger.lib` in your project's linker settings.
    - For example, in Visual Studio, go to the **Project Properties** > **Linker** > **Input** > **Additional Dependencies** and add `logger.lib`.
3. **Runtime DLL**:
    - Ensure `logger.dll` is available at runtime (usually in the same directory as your executable).

#### For Linux

1. Compile the logger as a shared object (`.so`).
2. Link it with your application using `-l` flag.
    - Example: `gcc -o myapp myapp.c -llogger -L/path/to/logger/lib`

### 3. Include Logger Header

In your source files, include the logger header file:

```c
#include <logger/logger.h>#include <logger/logger.h>

int main() {
    // Log messages with different severity levels
    LOGGER_debug("This is a debug message");
    LOGGER_info("This is an informational message");
    LOGGER_warning("This is a warning message");
    LOGGER_error("This is an error message");
    LOGGER_fatal("This is a fatal error message");

    // Log a formatted message
    LOGGER_info("The current count is: %i", 42);

    // Get all logs as a concatenated string
    const char* allLogs = LOGGER_logs();

    // Write all logs to a file
    LOGGER_write("logs.txt");

    return 0;
}
