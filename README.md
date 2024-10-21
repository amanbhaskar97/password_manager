# Password Manager

A simple password manager application that allows users to securely store, retrieve, and manage their passwords. The application utilizes encryption to protect stored passwords and provides a user-friendly interface for managing them.

## Features

- **Add Password**: Store a new password associated with a name and ID.
- **Retrieve Password**: Retrieve a password using its associated name and ID.
- **Show All Passwords**: Display all stored passwords (masked).
- **Modify Password**: Change an existing password.
- **Delete Password**: Remove a password from storage.
- **Suggest Strong Password**: Generate a secure, random password.
- **Master Password**: Protects access to the password manager.

## Architecture

The project is structured into several components:

- **`main.cpp`**: Entry point of the application. Manages the user interface and interactions.
- **`password_manager.h` / `password_manager.cpp`**: Implements the password management functionalities.
- **`crypto_utils.h` / `crypto_utils.cpp`**: Provides cryptographic utilities for encryption and decryption.
- **`file_utils.h` / `file_utils.cpp`**: Handles file operations for saving and loading passwords.
- **`input_utils.h` / `input_utils.cpp`**: Manages user input, including password input without echo.
- **`logger.h` / `logger.cpp`**: Logs activities and errors to a file for auditing.

## Dependencies

- **Crypto++**: A C++ library for cryptographic operations.

## Build Instructions

To compile the project, ensure you have `g++` and the Crypto++ library installed. You can build the project using the provided `Makefile`:

```bash
make

