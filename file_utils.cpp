#include "file_utils.h"
#include "crypto_utils.h"
#include <fstream>
#include <iostream>
#include <cryptopp/aes.h>

namespace FileUtils {

void savePasswords(const std::map<std::pair<std::string, std::string>, std::string>& passwords) {
    std::ofstream file(FILENAME, std::ios::binary | std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Could not open file for writing." << std::endl;
        return;
    }

    CryptoPP::SecByteBlock key, iv;
    CryptoUtils::generateKeyAndIV(key, iv);

    file.write(reinterpret_cast<const char*>(key.data()), key.size());
    file.write(reinterpret_cast<const char*>(iv.data()), iv.size());

    for (const auto& entry : passwords) {
        std::string encryptedPassword = CryptoUtils::encrypt(entry.second, key, iv);
        if (!encryptedPassword.empty()) {
            size_t nameSize = entry.first.first.size();
            size_t idSize = entry.first.second.size();
            size_t passwordSize = encryptedPassword.size();

            file.write(reinterpret_cast<const char*>(&nameSize), sizeof(size_t));
            file.write(entry.first.first.c_str(), nameSize);
            file.write(reinterpret_cast<const char*>(&idSize), sizeof(size_t));
            file.write(entry.first.second.c_str(), idSize);
            file.write(reinterpret_cast<const char*>(&passwordSize), sizeof(size_t));
            file.write(encryptedPassword.c_str(), passwordSize);
        }
    }

    file.close();
}

void loadPasswords(std::map<std::pair<std::string, std::string>, std::string>& passwords) {
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open file for reading." << std::endl;
        return;
    }

    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH), iv(CryptoPP::AES::BLOCKSIZE);

    file.read(reinterpret_cast<char*>(key.data()), key.size());
    file.read(reinterpret_cast<char*>(iv.data()), iv.size());

    while (file.good()) {
        size_t nameSize, idSize, passwordSize;
        file.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
        if (file.eof()) break;

        std::string name(nameSize, '\0');
        file.read(&name[0], nameSize);

        file.read(reinterpret_cast<char*>(&idSize), sizeof(size_t));
        std::string id(idSize, '\0');
        file.read(&id[0], idSize);

        file.read(reinterpret_cast<char*>(&passwordSize), sizeof(size_t));
        std::string encryptedPassword(passwordSize, '\0');
        file.read(&encryptedPassword[0], passwordSize);

        std::string password = CryptoUtils::decrypt(encryptedPassword, key, iv);
        if (!password.empty()) {
            passwords[std::make_pair(name, id)] = password;
        }
    }

    file.close();
}

}  // namespace FileUtils

