// main.cpp
#include "blockchain.hpp"
#include "wallet.hpp"
#include <iostream>
#include <thread>

int main() {
    Blockchain rgm;
    Wallet miner;

    std::cout << "🚀 Запуск RGM (C++ версия)...\n";
    rgm.add_stake(miner.address, 100.0);

    // Добавим транзакцию
    Transaction tx;
    tx.sender = "user1";
    tx.recipient = "user2";
    tx.amount = 10.0;
    rgm.add_transaction(tx);

    // Цикл PoS
    while (true) {
        rgm.create_block();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
