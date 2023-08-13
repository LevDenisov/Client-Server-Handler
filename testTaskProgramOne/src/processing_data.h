#ifndef TESTTASKPROGRAMONE_PROCESSING_DATA_H
#define TESTTASKPROGRAMONE_PROCESSING_DATA_H

#include <iostream>

#include "data_synchronization.h"

class ProcessingData {
private:
    std::shared_ptr<SharedData> data;
    std::shared_ptr<NetworkData> network_data;

    static int sumDigitsString(const std::string& str);

public:
    explicit ProcessingData(const std::shared_ptr<SharedData>& data,
                            const std::shared_ptr<NetworkData>& network_data) : data(data), network_data(network_data) {}
    ProcessingData(const ProcessingData& other) = delete;

    void dataProcessing();
};


#endif //TESTTASKPROGRAMONE_PROCESSING_DATA_H
