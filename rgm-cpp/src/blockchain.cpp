// blockchain.cpp
#include "blockchain.hpp"
#include "crypto.hpp"
#include <iostream>
#include <thread>
#include <chrono>

Block::Block(int i, const std::string& prev, const std::vector<Transaction>& txs, const std::string& val)
    : index(i), previous_hash(prev), transactions(txs), validator(val), timestamp(std::time(nullptr)) {
    this->hash = calculate_hash();
}

std::string Block::calculate_hash() const {
    std::string data = std::to_string(index) + previous_hash + std::to_string(timestamp);
    for (const auto& tx : transactions) {
        data += tx.to_string();
    }
    data += validator;
    return Crypto::sha256(data);
}

Blockchain::Blockchain() {
    // Genesis block
    chain.emplace_back(0, "0", std::vector<Transaction>(), "system");
}

void Blockchain::add_transaction(const Transaction& tx) {
    if (tx.is_valid()) {
        pending_transactions.push_back(tx);
    }
}

void Blockchain::add_stake(const std::string& address, double amount) {
    staking[address] += amount;
}

std::string Blockchain::select_validator() {
    if (staking.empty()) return "";
    double total = 0;
    for (const auto& s : staking) total += s.second;

    double r = ((double)rand() / RAND_MAX) * total;
    double current = 0;
    for (const auto& s : staking) {
        current += s.second;
        if (current >= r) return s.first;
    }
    return staking.begin()->first;
}

void Blockchain::create_block() {
    std::string validator = select_validator();
    if (validator.empty()) return;

    // Ждём 12 секунд
    static std::time_t last = std::time(nullptr);
    std::time_t now = std::time(nullptr);
    if (now - last < 12) {
        std::this_thread::sleep_for(std::chrono::seconds(12 - (now - last)));
    }

    Block new_block(chain.size(), get_latest_block().hash, pending_transactions, validator);
    chain.push_back(new_block);

    // Вознаграждение
    Transaction reward;
    reward.sender = "network";
    reward.recipient = validator;
    reward.amount = 5.0;
    pending_transactions = {reward};

    std::cout << "✅ Блок #" << new_block.index
              << " от " << validator.substr(0, 8) << "... | Хеш: " << new_block.hash.substr(0, 10) << "...\n";

    last = std::time(nullptr);
}

const Block& Blockchain::get_latest_block() const {
    return chain.back();
}

void Blockchain::print_chain() const {
    for (const auto& block : chain) {
        std::cout << "Блок #" << block.index << ": " << block.hash.substr(0, 10) << "...\n";
    }
}
