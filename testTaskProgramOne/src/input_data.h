#ifndef TESTTASK_INPUT_DATA_H
#define TESTTASK_INPUT_DATA_H

#include <iostream>
#include <queue>
#include <algorithm>

#include "data_synchronization.h"

class InputData {
private:
    std::shared_ptr<SharedData> data;

    struct cmp {
        bool operator()(const char &a, const char &b) {
            return a > b;
        }
    };

    // There is no verification that each character is a digit
    // implemented by ASCII
    static inline uint amountEvenNumbers(const std::string &str);

    static inline std::queue<uint> getPositionEvenDigits(const std::string &str);

    static inline void insertKB(std::string &str, std::queue<uint> q);

    static inline void insertDigits(const std::string &a, std::string &b, std::queue<uint> q);

    static std::string convertEvenDigitsToKB(const std::string &str);

    static bool isNumericString(const std::string &str);

    void handlerString(const std::string &str);

public:
    explicit InputData(const std::shared_ptr<SharedData>& data) : data(data) {}
    InputData(const InputData& other) = delete;

    void inputData();
};


#endif //TESTTASK_INPUT_DATA_H
