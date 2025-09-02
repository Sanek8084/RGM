// crypto.cpp
#include "crypto.hpp"
#include <sstream>
#include <iomanip>

std::string Crypto::sha256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string Crypto::generate_address(const std::string& pub_key) {
    return "0x" + sha256(pub_key).substr(0, 62);  // Упрощённо
}
