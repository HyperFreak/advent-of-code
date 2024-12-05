#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

void orderList(std::vector<int> &inputList, std::map<int, std::vector<int>> &order) {
    std::map<int, std::set<int>> orderSet;
    for (const auto& [key, values] : order) {
        orderSet[key] = std::set<int>(values.begin(), values.end());
    }

    bool changed;
    do {
        changed = false;

        for (size_t i = 0; i < inputList.size(); ++i) {
            for (int n : orderSet[inputList[i]]) {
                auto pos = std::find(inputList.begin(), inputList.end(), n);

                if (pos != inputList.end() && pos > inputList.begin() + i) {
                    inputList.erase(pos);
                    inputList.insert(inputList.begin() + i, n);
                    changed = true;
                    break;
                }
            }
        }
    } while (changed);
}

std::pair<int, int> getOrderPair(std::string input) {
    size_t seperatorPos = input.find('|');
    std::pair<int, int> output;

    output.first = std::stoi(input.substr(0, seperatorPos));
    output.second = std::stoi(input.substr(seperatorPos + 1));

    return output;
}

std::vector<int> extractNumbers(std::string line) {
    std::stringstream sStream(line);
    std::string number;
    std::vector<int> numbers;

    while (std::getline(sStream, number, ',')) {
        try {
            int num = std::stoi(number);
            numbers.push_back(num);
        } catch (const std::invalid_argument &e) {
            std::cerr << "Parsing Error: " << number << "!\n";
        }
    }
    return numbers;
}

bool isInOrder(std::vector<int> numbers, std::map<int, std::vector<int>> &order) {
    for (size_t i = 0; i < numbers.size(); i++) {
        for (size_t j = i; j < numbers.size(); j--) {
            for (size_t k = 0; k < order[numbers[i]].size(); k++) {
                if (numbers[j] == order[numbers[i]][k]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main(int argc, char** argv) {
    bool TEST = false;
    if (argc > 1) {
        std::string runAs(argv[1]);
        TEST = runAs == "test";
    }

    std::string filePath = TEST ? "test-input.txt" : "full-input.txt";
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error! Couldn\'t open file: \"" << filePath << "\"!\n";
    }

    std::map<int, std::vector<int>> orderAfter;

    size_t part1Res = 0;
    size_t part2Res = 0;

    bool orderPart = true;
    std::string line;
    while (std::getline(file, line)) {
        if (orderPart) {
            if (line.size() == 0) {  // check for the empty line between the input parts
                orderPart = false;
                continue;
            }
            std::pair<int, int> order = getOrderPair(line);
            orderAfter[order.first].push_back(order.second);
        } else {
            std::vector<int> numbers = extractNumbers(line);
            if (isInOrder(numbers, orderAfter)) {
                part1Res += numbers[numbers.size() / 2];
            } else {
                orderList(numbers, orderAfter);
                part2Res += numbers[numbers.size() / 2];
            }
        }
    }
    file.close();

    std::cout << "Result Part 1: " << part1Res << ".\n";
    std::cout << "Result Part 2: " << part2Res << ".\n"; 
    return 0;
}