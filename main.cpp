#include "password_manager.h"
#include "input_utils.h"
#include "logger.h"
#include <iostream>
#include <limits>

int main() {
    Logger::log("Program started");

    PasswordManager manager;
    manager.loadPasswords();

    if (!manager.checkMasterPassword()) {
        std::cout << "Incorrect master password. Exiting..." << std::endl;
        Logger::log("Program exited due to incorrect master password");
        return 1;
    }

    while (true) {
        std::cout << "\n________________________________________\n";
        std::cout << "Password Manager Menu:" << std::endl;
        std::cout << "1. Add Password" << std::endl;
        std::cout << "2. Retrieve Password" << std::endl;
        std::cout << "3. Show All Passwords" << std::endl;
        std::cout << "4. Modify Password" << std::endl;
        std::cout << "5. Delete Password" << std::endl;
        std::cout << "6. Suggest Strong Password" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "________________________________________\n";
        std::cout << "Enter your choice: ";

        int choice = InputUtils::getIntInput();

        std::cout << "________________________________________\n";

        switch (choice) {
            case 1:
                manager.addPassword();
                break;
            case 2:
                manager.retrievePassword();
                break;
            case 3:
                manager.showAllPasswords();
                break;
            case 4:
                manager.modifyPassword();
                break;
            case 5:
                manager.deletePassword();
                break;
            case 6:
                std::cout << "Suggested Password: " << manager.suggestPassword() << std::endl;
                Logger::log("Strong password suggested");
                break;
            case 7:
                std::cout << "Exiting..." << std::endl;
                Logger::log("Program exited");
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                Logger::log("Invalid menu choice");
        }
    }

    return 0;
}