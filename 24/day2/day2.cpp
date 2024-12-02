#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

bool isAscending (std::vector<int> numbers) {
    int dir = 0;
    for (size_t i = 0, j = 1; j < numbers.size(); i++, j++) {
        if (numbers[i] < numbers[j]) {
            dir++;
        } else {
            dir--;
        }
    }
    return dir > 0;
}

unsigned int delta(int x, int y) {
    return x > y ? x - y : y - x;
}

bool checkLineSafe(std::vector<int> numbers) {
    bool ascending = numbers[0] < numbers[1];

    for (size_t i = 1; i < numbers.size(); i++) {
        unsigned int d = delta(numbers[i-1], numbers[i]);
        if (d < 1 || d > 3) {
            return false;
        } else if (numbers[i-1] > numbers[i] && ascending) {
            return false;
        } else if (numbers[i-1] < numbers[i] && !ascending) {
            return false;
        }
    }
    return true;
}

std::vector<int> getNumbers(std::string line) {
    std::vector<int> numbers;
    std::istringstream isStram(line);
    int num = 0;
    while (isStram >> num) {
        numbers.push_back(num);
    }
    return numbers;
}

bool checkLineSafeWithDampener(std::vector<int> numbers) {
    bool ascending = isAscending(numbers);

    for (size_t i = 1; i < numbers.size(); i++) {
        if (ascending) {
            if (numbers[i-1] > numbers[i]) {
                std::vector<int> v1(numbers);
                std::vector<int> v2(numbers);
                v1.erase(v1.begin() + i-1);
                v2.erase(v2.begin() + i);
                return checkLineSafe(v1) || checkLineSafe(v2);
            }
        } else {
            if (numbers[i-1] < numbers[i]) {
                std::vector<int> v1(numbers);
                std::vector<int> v2(numbers);
                v1.erase(v1.begin() + i-1);
                v2.erase(v2.begin() + i);
                return checkLineSafe(v1) || checkLineSafe(v2);
            }
        }

        if (delta(numbers[i-1], numbers[i]) < 1 || delta(numbers[i-1], numbers[i]) > 3) {
            std::vector<int> v1(numbers);
            std::vector<int> v2(numbers);
            v1.erase(v1.begin() + i-1);
            v2.erase(v2.begin() + i);
            return checkLineSafe(v1) || checkLineSafe(v2);
        }
    }
    return true;
}


int main(int argc, char** argv) {
    bool test = false;
    if (argc > 1) {
        std::string runAs(argv[1]);
        test = (argv[1] == runAs);
    }
    const bool FULL = !test;

    std::ifstream file(FULL ? "full-input.txt" : "test-input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Couldn\'t open File!\n";
    }

    size_t safe = 0;
    size_t dampSafe = 0;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> numbers = getNumbers(line);
        safe += checkLineSafe(numbers);
        dampSafe += checkLineSafeWithDampener(numbers);
    }
    file.close();

    std::cout << "Part 1 result: " << safe << std::endl;
    std::cout << "Part 2 result: " << dampSafe << std::endl;
    return 0;
}