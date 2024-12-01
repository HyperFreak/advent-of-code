#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

/**
 * reads two integers per line of a file and puts them into two lists a and b
 */
void readInput(std::string file, std::vector<int> &a, std::vector<int> &b) {
    std::ifstream inStream(file);
    std::string inA, inB;

    if (!inStream) {
        std::cout << "Error couldn\'t open file.\n";
        return;
    }

    while (inStream >> inA >> inB) {                                                // go through each line until EOF
        a.push_back(std::stoi(inA));                                                // stoi = parseInt
        b.push_back(std::stoi(inB));
    }
    inStream.close();                                                               // close input stream
}

int main(int argc, char** argv) {
    // check if the program should run the test of full input
    bool test = false;
    if (argc > 1) {
        std::string runAs(argv[1]);                                                 // check if the user put the text "test" as a start
        test = (argv[1] == runAs);                                                  //      argument, and if yes set boolean flag FULL to false
    }
    const bool FULL = !test;

    std::vector<int> listA, listB;                                                  // create two integer lists
    int size = FULL ? 1000 : 6;                                                     // set size to be reseved for test and full input case
    listA.reserve(size);                                                            // reserve size to reduce space and runtime consumption
    listB.reserve(size);

    readInput(FULL ? "full-input.txt" : "test-input.txt", listA, listB);            // input and sort lists
    std::sort(listA.begin(), listA.end());
    std::sort(listB.begin(), listB.end());

    int part1Res = 0;                                                               // get final result by adding delta(a, b) to finalRes for each line
    for (int i = 0; i < listA.size(); i++) {
        int dif = listA[i] > listB[i] ? listA[i] - listB[i] : listB[i] - listA[i];
        part1Res += dif;
    }
    std::cout << "Part 1 Final Result: " << part1Res << "\n";


    // PART 2
    std::map<int, int> counter;                                                     // Use map as a counter to count occurances of each number in listB
    for (int i = 0; i < listB.size(); i++) {                                        
        counter[listB[i]]++;
    }

    int part2Res = 0;
    for (int i = 0; i < listA.size(); i++) {                                        // Go through each number and add how often it appears in listB * the value
        part2Res += counter[listA[i]] * listA[i];
    }
    std::cout << "Part 2 Final Result: " << part2Res << "\n";

    return 0;
}