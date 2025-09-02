// blockchain.hpp
#pragma once
#include <vector>
#include <string>
#include "transaction.hpp"
#include <ctime>

struct Block {
    int index;
    std::string previous_hash;
    std::time_t timestamp;
    std::vector<Transaction> transactions;
    std::string validator;
    std::string hash;

    Block(int index, const std::string& prev_hash, const std::vector<Transaction>& txs, const std::string& validator);
    std::string calculate_hash() const;
};

class Blockchain {
private:
    std::vector<Block> chain;
    std::vector<Transaction> pending_transactions;
    std::map<std::string, double> staking;

public:
    Blockchain();
    void add_transaction(const Transaction& tx);
    void add_stake(const std::string& address, double amount);
    std::string select_validator();
    void create_block();
    const Block& get_latest_block() const;
    void print_chain() const;
};
