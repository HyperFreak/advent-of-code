#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 * reads two integers per line of a file and puts them into two lists a and b
 */
void readInput(std::string file, std::vector<int> &a, std::vector<int> &b) {
    std::ifstream inStream(file);
    std::string inA, inB;

    while (inStream >> inA >> inB) {                                                // go through each line until EOF
        a.push_back(std::stoi(inA));                                                // stoi = parseInt
        b.push_back(std::stoi(inB));
    }
    inStream.close();                                                               // close input stream
}

/**
 * stable sorts a vector of integers in n log(n)
 */
void mergeSort(std::vector<int> &vec) {
    if (vec.size() > 1) {
        int mid = vec.size() / 2;
        std::vector<int> left(vec.begin(), vec.begin() + mid);
        std::vector<int> right(vec.begin() + mid, vec.end());

        mergeSort(left);
        mergeSort(right);

        int i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                vec[k] = left[i];
                i++;
            } else {
                vec[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < left.size()) {
            vec[k++] = left[i++];
        }

        while (j < right.size()) {
            vec[k++] = right[j++];
        }
    }
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
    mergeSort(listA);
    mergeSort(listB);

    int finalResult = 0;                                                            // get final result by adding delta(a, b) to finalRes for each line
    for (int i = 0; i < listA.size(); i++) {
        int dif = listA[i] > listB[i] ? listA[i] - listB[i] : listB[i] - listA[i];
        finalResult += dif;
    }
    std::cout << "Final Result: " << finalResult << "\n";

    return 0;
}