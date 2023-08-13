#ifndef TESTTASK_DATA_SYNCHRONIZATION_H
#define TESTTASK_DATA_SYNCHRONIZATION_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <iostream>

#include <boost/asio.hpp>

struct SharedData {
    bool                            g_work_input = true;
    bool                            g_work_processing = true;
    std::mutex                      g_lockqueue;
    std::mutex                      g_lockprint;
    std::condition_variable         g_queuecheck;
    std::queue<std::string>         g_string;
};

class NetworkData {
private:
    boost::asio::io_service service;
    boost::asio::ip::tcp::endpoint ep;

    std::mutex                      g_lockqueue;
    std::condition_variable         g_queuecheck;
    std::queue<int>                 g_numbers;
public:
    NetworkData(const std::string& ip, int port) : ep(boost::asio::ip::address::from_string(ip), port) {}

    void push(int value) {
        std::unique_lock<std::mutex> locker(g_lockqueue);
        g_numbers.push(value);

        g_queuecheck.notify_one();
    }

    void sendData() {
        while (true) {
            {
                std::unique_lock<std::mutex> locker(g_lockqueue);
                g_queuecheck.wait(locker, [&]() {
                    return not g_numbers.empty();
                });
            }

            while(not g_numbers.empty()) {
                std::this_thread::sleep_for(std::chrono::seconds(2));

                try {
                    boost::asio::ip::tcp::socket socket(service);

                    socket.connect(ep);

                    int data = g_numbers.front();

                    boost::asio::write(socket, boost::asio::buffer(&data, sizeof(data)));

                    g_numbers.pop();

                } catch (const std::exception &e) {
                   // std::cout << "Connection error: " << e.what() << std::endl;
                }
            }
        }
    }
};


#endif //TESTTASK_DATA_SYNCHRONIZATION_H
