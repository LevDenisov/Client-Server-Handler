#include "processing_data.h"


int ProcessingData::sumDigitsString(const std::string &str) {
    int sum = 0;

    for (auto &ch: str) {
        if (isdigit(ch)) {
            sum += ch - '0';
        }
    }

    return sum;
}

void ProcessingData::dataProcessing() {
    while (data->g_work_processing) {
        std::unique_lock<std::mutex> locker(data->g_lockqueue);
        data->g_queuecheck.wait(locker, [&]() {
            return not data->g_string.empty();
        });

        while (!data->g_string.empty()) {
            std::cout << data->g_string.front() << std::endl;

            int sum = sumDigitsString(data->g_string.front()); // Отправить как-то данные во вторую программу

            data->g_string.pop();

            network_data->push(sum);
        }
    }
}