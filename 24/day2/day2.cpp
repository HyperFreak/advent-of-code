#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

/**
 * checks if a int vector is mostly ascending
 */
bool isAscending (std::vector<int> numbers) {
    int dir = 0;
    for (size_t i = 1; i < numbers.size(); i++) {
        dir += numbers[i-1] < numbers[i] ? 1 : -1;
    }
    return dir > 0;
}

/**
 * returns the absolute difference between two numbers
 */
unsigned int delta(int x, int y) {
    return x > y ? x - y : y - x;
}

/**
 * Checks if a list of number is ordered and doesn't have gaps lower than 1 or higher than 3
 */
bool checkLineSafe(std::vector<int> numbers) {
    bool ascending = numbers[0] < numbers[1];
    for (size_t i = 1; i < numbers.size(); i++) {
        unsigned int d = delta(numbers[i-1], numbers[i]);
        if (d < 1 || d > 3) {
            return false;
        }
        if (numbers[i-1] > numbers[i] && ascending) {
            return false;
        }
        if (numbers[i-1] < numbers[i] && !ascending) {
            return false;
        }
    }
    return true;
}

/**
 * Generates a list of integers from a string
 */
std::vector<int> getNumbers(std::string line) {
    std::vector<int> numbers;
    std::istringstream isStram(line);
    int num = 0;
    while (isStram >> num) {
        numbers.push_back(num);
    }
    return numbers;
}

/**
 * removes one error space if it exists and checks if the report is safe
 */
bool checkLineSafeWithDampener(std::vector<int> numbers) {
    bool ascending = isAscending(numbers);
    int remove = -1;
    for (size_t i = 1; i < numbers.size(); i++) {
        if (ascending && (numbers[i-1] > numbers[i])) {
            remove = i;
            break;
        }
        if (!ascending && (numbers[i-1] < numbers[i])) {
            remove = i;
            break;
        }
        if (delta(numbers[i-1], numbers[i]) < 1 || delta(numbers[i-1], numbers[i]) > 3) {
            remove = i;
            break;
        }
    }
    if (remove >= 0) {
        std::vector<int> v1(numbers), v2(numbers);
        v1.erase(v1.begin() + remove-1);
        v2.erase(v2.begin() + remove);
        return checkLineSafe(v1) || checkLineSafe(v2);
    }
    return checkLineSafe(numbers);
}

int main(int argc, char** argv) {
    bool FULL = true;
    if (argc > 1) {
        std::string runAs(argv[1]);
        FULL = !(argv[1] == runAs);
    }
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