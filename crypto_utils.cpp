#include "crypto_utils.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <iostream>

namespace CryptoUtils {

void generateKeyAndIV(CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv) {
    CryptoPP::AutoSeededRandomPool prng;
    
    key.resize(CryptoPP::AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key, key.size());

    iv.resize(CryptoPP::AES::BLOCKSIZE);
    prng.GenerateBlock(iv, iv.size());
}

std::string encrypt(const std::string& plain, const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv) {
    try {
        std::string encrypted;
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor(key, key.size(), iv);
        CryptoPP::StringSource(plain, true,
            new CryptoPP::StreamTransformationFilter(encryptor,
                new CryptoPP::StringSink(encrypted)
            )
        );
        return encrypted;
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Crypto++ Exception during encryption: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Unknown exception during encryption" << std::endl;
        return "";
    }
}

std::string decrypt(const std::string& encrypted, const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv) {
    try {
        std::string decrypted;
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryptor(key, key.size(), iv);
        CryptoPP::StringSource(encrypted, true,
            new CryptoPP::StreamTransformationFilter(decryptor,
                new CryptoPP::StringSink(decrypted)
            )
        );
        return decrypted;
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Crypto++ Exception during decryption: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Unknown exception during decryption" << std::endl;
        return "";
    }
}

}  // namespace CryptoUtils

