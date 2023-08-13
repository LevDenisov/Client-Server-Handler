#include "input_data.h"


uint InputData::amountEvenNumbers(const std::string &str) {
    uint amount = 0;

    for (auto &ch: str) {
        if (not (int(ch) % 2)) {
            amount++;
        }
    }

    return amount;
}

std::queue<uint> InputData::getPositionEvenDigits(const std::string &str)  {
    std::queue<uint> q;

    for (uint i = 0; i < str.size(); i++) {
        if (not (int(str[i]) % 2)) {
            q.push(i);
        }
    }

    return q;
}

void InputData::insertKB(std::string &str, std::queue<uint> q) {
    uint shift = 0;

    while (not q.empty()) {
        str[q.front() + shift] = 'K';
        str[q.front() + 1 + shift] = 'B';

        q.pop();
        shift++;
    }
}

void InputData::insertDigits(const std::string &a, std::string &b, std::queue<uint> q) {
    uint shift = 0;
    uint left = 0;

    while(not q.empty()) {
        std::copy(a.begin() + left, a.begin() + q.front(), b.begin() + left + shift);

        left = q.front() + 1;
        shift++;
        q.pop();
    }

    if (left != a.size()) {
        std::copy(a.begin() + left, a.end(), b.begin() + left + shift);
    }
}

std::string InputData::convertEvenDigitsToKB(const std::string &str) {
    uint amount_even_digits = amountEvenNumbers(str);

    std::string result_str;
    result_str.resize(str.size() + amount_even_digits);

    std::queue<uint> q = getPositionEvenDigits(str);

    insertKB(result_str, q);
    insertDigits(str, result_str, q);

    return result_str;
}

bool InputData::isNumericString(const std::string &str) {
    return std::all_of(str.begin(), str.end(), [](char c) {
        return std::isdigit(c);
    });
}

void InputData::handlerString(const std::string &str) {
    if (str.size() > 64 || not isNumericString(str)) {
        return;
    }

    std::string result = str;

    std::sort(result.begin(), result.end(), cmp());

    {
        std::unique_lock<std::mutex> locker(data->g_lockqueue);
        data->g_string.push(convertEvenDigitsToKB(str));
        data->g_queuecheck.notify_one();
    }
}

void InputData::inputData() {
    while (data->g_work_input) {
        std::string input_str;
        getline(std::cin, input_str);

        handlerString(input_str);
    }
}

