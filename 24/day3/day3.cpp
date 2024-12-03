#include <iostream>
#include <string>
#include <fstream>
#include <regex>

#define INPUT_FILE "full-input.txt"

/**
 * extracts and executes the mul instructions from a string and adds the results together
 */
int mulInstructions(std::string input) {
    int res = 0;
    std::regex pattern(R"(mul\(([0-9]{1,3}),([0-9]{1,3})\))");
    std::smatch match;

    std::string::const_iterator searchStart(input.begin());                 
    while (std::regex_search(searchStart, input.cend(), match, pattern)) {  
        int x = std::stoi(match[1].str());                                 
        int y = std::stoi(match[2].str());
        res += x * y;
        searchStart = match.suffix().first;
    }
    return res;
}

/**
 * extracts and executes the mul, do and don't instructions from a string and adds results together
 */
int mulInstructionsWithDo(std::string input, bool& active) {
    int res = 0;
    std::regex pattern(R"((mul\(([0-9]{1,3}),([0-9]{1,3})\))|(don\'t\(\))|(do\(\)))");
    std::smatch match;
    std::string::const_iterator searchStart(input.begin());                 
    while (std::regex_search(searchStart, input.cend(), match, pattern)) {
        if (match[1].matched && active) {
            int x = std::stoi(match[2].str());                                
            int y = std::stoi(match[3].str());
            res += x * y;
        } else if (match[4].matched) {
            active = false;
        } else if (match[5].matched) {
            active = true;
        }
        searchStart = match.suffix().first;
    }
    return res; 
}

int main() {    
    std::ifstream file(INPUT_FILE);
    if (!file.is_open()) {
        std::cout << "Error! Couldn\'t open \"" << INPUT_FILE << "\"!\n";
        return -1;
    }
    std::string line;
    int part1Res = 0;
    int part2Res = 0;
    bool active = true;
    while(std::getline(file, line)) {
        part1Res += mulInstructions(line);
        part2Res += mulInstructionsWithDo(line, active);
    }
    std::cout << "Part 1 Result: " << part1Res << "\n";
    std::cout << "Part 2 Result: " << part2Res << "\n";
    return 0;
}
