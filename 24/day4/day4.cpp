#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool isWord(std::string searchTerm, std::vector<std::string> &grid, size_t startY, size_t startX, int ydir, int xdir) {
    int count = 0;
    const size_t wordLength = searchTerm.size();
    bool word = true;

    for (size_t i = 1; i < wordLength; i++) {
        size_t y = startY + i * ydir;
        size_t x = startX + i * xdir;

        if (y >= grid.size() || x >= grid[0].size()) {
            word = false;
            break;
        }
        if (grid[y][x] != searchTerm[i]) {
            word = false;
            break;
        }
    }

    return word;
}

int countWord(std::string searchTerm, std::vector<std::string> &grid) {
    int res = 0;

    int directions[8][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},
        {1, 1}, {-1, -1}, {1, -1}, {-1,1}
    };

     for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {

            if (grid[i][j] == searchTerm[0]) {
                for (int k = 0; k < 8; k++) {
                    res += isWord(searchTerm, grid, i, j, directions[k][0], directions[k][1]);
                }
            }

        }
    }

    return res;
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
    file.close();

    std::cout << "Result Part 1: " << countWord("XMAS", grid) << ".\n";

    return 0;
}