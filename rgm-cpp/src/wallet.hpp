// wallet.hpp
#pragma once
#include <string>
#include <openssl/ec.h>
#include <openssl/evp.h>

class Wallet {
private:
    EC_KEY* key;
    std::string private_key_hex;
    std::string public_key_hex;

public:
    std::string address;

    Wallet();
    ~Wallet();

    std::string sign(const std::string& data);
    bool verify(const std::string& signature, const std::string& data, const std::string& pub_key_hex);

    std::string get_private_key() const { return private_key_hex; }
    std::string get_public_key() const { return public_key_hex; }
};
