#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <string>
#include <cryptopp/secblock.h>

namespace CryptoUtils {
    void generateKeyAndIV(CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv);
    std::string encrypt(const std::string& plain, const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv);
    std::string decrypt(const std::string& encrypted, const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv);
}

#endif // CRYPTO_UTILS_H

