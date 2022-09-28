#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>

using namespace std;

bool isInt(const string &input);

int main() {
    // Because we have no way of knowing the size of the entries, we are using a vector to hold the data
    vector<int> list;

    // Input filestream that reads the unsorted data set into the vector
    // Note that the "input.txt" file needs to be in the same file directory as the executable file
    ifstream inputFile;
    inputFile.open("./input.txt", ios::in);
    string var;
    while (inputFile >> var)
        if (isInt(var))
            list.push_back(stoi(var));

    inputFile.close();
    int listSize;
    listSize = static_cast<int>(list.size()) - 1;

    // Output filestream that will store the results and progress of the mergeSort function
    ofstream outFile;
    outFile.open("./output.txt");

    // Start primary thread in the recursive function to begin merge sort


    // Call the join function for the primary thread so the process does not
    // terminate before completing the merge sort
    // <Thread name>.join();

    // Close the output file and terminate the process
    outFile.close();
    return 0;
}

// Function to check if a string contains only digits, and therefor is an integer
bool isInt(const string& input){
    for (char i: input)
        if (!isdigit(i))
            return false;
    return true;
}


