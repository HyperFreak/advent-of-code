#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>

int pathLength(std::vector<std::string> grid, size_t startX, size_t startY, size_t startDirection) {
    std::set<std::pair<size_t, size_t>> visitedPositions;

    std::map<size_t, std::pair<int, int>> directions;
    directions[0].first = 0;
    directions[0].second = -1;

    directions[1].first = 1;
    directions[1].second = 0;

    directions[2].first = 0;
    directions[2].second = 1;

    directions[3].first = -1;
    directions[3].second = 0;

    bool reachedWall = false;
    size_t currentDir = startDirection;
    size_t x = startX, y = startY;
    visitedPositions.insert({x, y});
    while (!reachedWall) {
        size_t nX = x + directions[currentDir].first;
        size_t nY = y + directions[currentDir].second;

        if (nY >= grid.size()) {
            reachedWall = true;
            break;
        }
        if (nX >= grid[nY].size()) {
            reachedWall = true;
            break;
        }
        if (grid[nY][nX] == '#') {
            currentDir++;
            currentDir %= 4;
            continue;
        }
        visitedPositions.insert({nX, nY});
        x = nX;
        y = nY;
    }

    return visitedPositions.size();
}

void getStartPosAndDirection(std::vector<std::string> &grid, size_t &xPos, size_t &yPos, size_t &dir) {
    const char directionChars[] = { '^', '>', 'v', '<' }; 

    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            for (size_t k = 0; k < 4; k++) {
                if (grid[i][j] == directionChars[k]) {
                    dir = k;
                    yPos = i;
                    xPos = j;
                    return;
                }
            }
        }
    } 
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

    std::vector<std::string> grid;
    std::string line;
    while (std::getline(file, line)) { 
        grid.push_back(line);
    } 

    size_t startX, startY, startDir;
    getStartPosAndDirection(grid, startX, startY, startDir);
    size_t resPart1 = pathLength(grid, startX, startY, startDir);
    std::cout << "Result Part 1: " << resPart1 << ".\n";

    //size_t resPart2 = countLoops(grid, startX, startY, startDir);
    //std::cout << "Result Part 2: " << resPart2 << ".\n";

    return 0;
}