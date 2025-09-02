cmake_minimum_required(VERSION 3.14)
project(RGM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(OpenSSL REQUIRED)

add_executable(rgm
    src/main.cpp
    src/blockchain.cpp
    src/wallet.cpp
    src/transaction.cpp
)

target_link_libraries(rgm OpenSSL::Crypto)
