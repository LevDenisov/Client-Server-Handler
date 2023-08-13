#include <thread>
#include <vector>

#include <boost/asio.hpp>

using namespace boost::asio;

#include "src/input_data.h"
#include "src/processing_data.h"
#include "src/data_synchronization.h"

std::vector<std::thread> threads;

int main() {
    std::shared_ptr<SharedData> data(std::make_unique<SharedData>());
    std::shared_ptr<NetworkData> network_data(std::make_unique<NetworkData>("127.0.0.1", 12345));

    InputData input_data(data);
    ProcessingData processing_data(data, network_data);

    threads.reserve(3);

    threads.emplace_back([&input_data]() {
        input_data.inputData();
    });

    threads.emplace_back([&processing_data]() {
        processing_data.dataProcessing();
    });

    threads.emplace_back([&network_data]() {
        network_data->sendData();
    });

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
