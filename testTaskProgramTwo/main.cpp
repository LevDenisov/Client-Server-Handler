#include <iostream>

#include <boost/asio.hpp>

uint numberLength(int number) {
    uint length = 1;
    number /= 10;

    while (number) {
        length++;
        number /= 10;
    }

    return length;
}

bool checkNumber(int number) {
    return not (number % 32) && numberLength(number) > 2;
}


int main() {
    boost::asio::io_service service;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 12345);
    boost::asio::ip::tcp::acceptor acceptor(service, ep);

    boost::asio::ip::tcp::socket socket(service);

    while (true) {
        acceptor.accept(socket);

        int data;
        socket.read_some(boost::asio::buffer(&data, sizeof(data)));

        if (checkNumber(data)) {
            std::cout << "Data received: " << data << std::endl;
        } else {
            std::cout << "Incorrect data: " << data << std::endl;
        }

        socket.close();
    }

    return 0;
}
