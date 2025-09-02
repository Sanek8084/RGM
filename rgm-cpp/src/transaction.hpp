// transaction.hpp
#pragma once
#include <string>

struct Transaction {
    std::string sender;
    std::string recipient;
    double amount;
    std::string signature;

    std::string to_string() const;
    bool is_valid() const;
};
