#include "password_manager.h"
#include "crypto_utils.h"
#include "file_utils.h"
#include "input_utils.h"
#include "logger.h"
#include <iostream>
#include <algorithm>
#include <random>

PasswordManager::PasswordManager() {}

void PasswordManager::loadPasswords() {
    FileUtils::loadPasswords(passwords);
}

void PasswordManager::savePasswords() {
    FileUtils::savePasswords(passwords);
}

bool PasswordManager::checkMasterPassword() {
    if (passwords.find(std::make_pair("MASTER", "PASSWORD")) == passwords.end()) {
        std::cout << "Master password not set. Please set it up." << std::endl;
        setupMasterPassword();
        return true;
    }

    std::cout << "Enter master password: ";
    std::string inputPassword = InputUtils::getPasswordInput();
    std::cout << std::endl;

    if (inputPassword == passwords[std::make_pair("MASTER", "PASSWORD")]) {
        Logger::log("Successful login");
        return true;
    } else {
        Logger::log("Failed login attempt");
        return false;
    }
}

void PasswordManager::addPassword() {
    std::string name, id, password;
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter ID: ";
    std::getline(std::cin, id);
    std::cout << "Enter password: ";
    password = InputUtils::getPasswordInput();
    std::cout << std::endl;

    passwords[std::make_pair(name, id)] = password;
    std::cout << "Password added successfully." << std::endl;
    savePasswords();
    Logger::log("New password added");
}

void PasswordManager::retrievePassword() {
    std::string name, id;
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter ID: ";
    std::getline(std::cin, id);

    auto it = passwords.find(std::make_pair(name, id));
    if (it != passwords.end()) {
        std::cout << "Password: " << it->second << std::endl;
        Logger::log("A Password retrieved");
    } else {
        std::cout << "Password not found." << std::endl;
        Logger::log("Failed password retrieval attempt");
    }
}

void PasswordManager::showAllPasswords() {
    for (const auto& entry : passwords) {
        if (entry.first.first != "MASTER" || entry.first.second != "PASSWORD") {
            std::cout << "Name: " << entry.first.first << ", ID: " << entry.first.second << ", Password: ***" << std::endl;
        }
    }
    Logger::log("All passwords displayed");
}

void PasswordManager::modifyPassword() {
    std::string name, id, newPassword;
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter ID: ";
    std::getline(std::cin, id);

    auto it = passwords.find(std::make_pair(name, id));
    if (it != passwords.end()) {
        std::cout << "Enter new password: ";
        newPassword = InputUtils::getPasswordInput();
        std::cout << std::endl;
        it->second = newPassword;
        std::cout << "Password modified successfully." << std::endl;
        savePasswords();
        Logger::log("A Password modified");
    } else {
        std::cout << "Password not found." << std::endl;
        Logger::log("Failed password modification attempt");
    }
}

void PasswordManager::deletePassword() {
    std::string name, id;
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter ID: ";
    std::getline(std::cin, id);

    auto it = passwords.find(std::make_pair(name, id));
    if (it != passwords.end()) {
        passwords.erase(it);
        std::cout << "Password deleted successfully." << std::endl;
        savePasswords();
        Logger::log("A Password deleted");
    } else {
        std::cout << "Password not found." << std::endl;
        Logger::log("A Failed password deletion attempt");
    }
}

std::string PasswordManager::suggestPassword() {
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits = "0123456789";
    const std::string symbols = "!@#$%^&*()-_=+[]{}|;:,.<>?";
    
    std::string all_chars = lowercase + uppercase + digits + symbols;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, all_chars.length() - 1);
    
    int length;
    do {
        std::cout << "Enter desired password length (minimum 8): ";
        std::cin >> length;
        
        if (length < 8) {
            std::cout << "Password length must be at least 8 characters. Please try again.\n";
        }
    } while (length < 8);
    
    std::string password;
    password.reserve(length); // Reserve memory to avoid reallocations
    
    // Ensure the password contains at least one of each character type
    password += lowercase[dis(gen) % lowercase.length()];
    password += uppercase[dis(gen) % uppercase.length()];
    password += digits[dis(gen) % digits.length()];
    password += symbols[dis(gen) % symbols.length()];
    
    // Fill the rest of the password
    for (int i = 4; i < length; ++i) {
        password += all_chars[dis(gen)];
    }
    
    // Shuffle the password to randomize the positions of the guaranteed characters
    std::shuffle(password.begin(), password.end(), gen);
    
    return password;
}


/*std::string PasswordManager::suggestPassword() {
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string digits = "0123456789";
    const std::string symbols = "!@#$&*+-=.?";
    const std::string allChars = uppercase + lowercase + digits + symbols;
    
    int passwordLength;
    std::cout << "Enter desired password length (minimum 8 characters): ";
    std::cin >> passwordLength;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (passwordLength < 8) {
        passwordLength = 8;
        std::cout << "Password length set to minimum of 8 characters." << std::endl;
    }

    std::string password;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, allChars.length() - 1);
    
    // Ensure at least one of each character type
    password += uppercase[dis(gen)];
    password += lowercase[dis(gen)];
    password += digits[dis(gen)];
    password += symbols[dis(gen)];
    
    // Fill the rest of the password
    for (int i = 4; i < passwordLength; ++i) {
        password += allChars[dis(gen)];
    }
    
    // Shuffle the password
    std::shuffle(password.begin(), password.end(), gen);
    
    return password;
}*/

void PasswordManager::setupMasterPassword() {
    std::cout << "Set up your master password: ";
    std::string masterPassword = InputUtils::getPasswordInput();
    std::cout << std::endl;

    passwords[std::make_pair("MASTER", "PASSWORD")] = masterPassword;
    savePasswords();
    Logger::log("Master password set up");
}

