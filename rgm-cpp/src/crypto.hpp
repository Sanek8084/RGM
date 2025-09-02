// crypto.hpp
#pragma once
#include <string>
#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/sha.h>

class Crypto {
public:
    static std::string sha256(const std::string& data);
    static std::string generate_address(const std::string& pub_key);
};
