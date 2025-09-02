// transaction.cpp
#include "transaction.hpp"
#include "wallet.hpp"
#include "crypto.hpp"

std::string Transaction::to_string() const {
    return sender + recipient + std::to_string(amount);
}

bool Transaction::is_valid() const {
    if (sender == "network") return true;  // Вознаграждение
    return !signature.empty();  // Упрощённо
}
