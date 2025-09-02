// wallet.cpp
#include "wallet.hpp"
#include "crypto.hpp"
#include <sstream>

Wallet::Wallet() {
    key = EC_KEY_new_by_curve_name(NID_secp256r1);
    EC_KEY_generate_key(key);

    // Приватный ключ
    const BIGNUM* priv_bn = EC_KEY_get0_private_key(key);
    char* priv_char = BN_bn2hex(priv_bn);
    private_key_hex = std::string(priv_char);
    OPENSSL_free(priv_char);

    // Публичный ключ
    const EC_POINT* pub_point = EC_KEY_get0_public_key(key);
    unsigned char pub[65];
    EC_POINT_point2oct(EC_KEY_get0_group(key), pub_point, POINT_CONVERSION_UNCOMPRESSED, pub, 65, nullptr);
    std::stringstream ss;
    for (int i = 0; i < 65; i++) ss << std::hex << std::setw(2) << std::setfill('0') << (int)pub[i];
    public_key_hex = ss.str();

    // Адрес
    address = Crypto::generate_address(public_key_hex);
}

Wallet::~Wallet() {
    EC_KEY_free(key);
}

std::string Wallet::sign(const std::string& data) {
    unsigned char sig[72];
    unsigned int sig_len = 72;
    ECDSA_sign(0, (const unsigned char*)data.c_str(), data.size(),
               sig, &sig_len, key);

    std::stringstream ss;
    for (unsigned int i = 0; i < sig_len; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)sig[i];
    }
    return ss.str();
}
