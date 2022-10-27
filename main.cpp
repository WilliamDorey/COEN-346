#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

bool isInt(const std::string &input);
void mergeSort(std::vector<int>&, int, int, std::ofstream&, const std::string&);
void merge(std::vector<int>&, int, int, int);

int main() {
    // Because we have no way of knowing the size of the entries, we are using a vector to hold the data
    std::vector<int> list;

    // Input filestream that reads the unsorted data set into the vector
    std::ifstream inputFile;
    inputFile.open("./input.txt", std::ios::in);
    std::string var;
    while (inputFile >> var)
        if (isInt(var))
            list.push_back(std::stoi(var));

    inputFile.close();
    int listSize;
    listSize = static_cast<int>(list.size()) - 1;

    // Output filestream that will store the results and progress of the mergeSort function
    std::ofstream outFile;
    outFile.open("./output.txt");

    // Primary thread in the recursive mergeSort function
    std::thread thr_root(mergeSort, std::ref(list), 0, listSize, std::ref(outFile), "1");

    // Waiting for initial thread to end and closing the output file stream before terminating program
    thr_root.join();
    outFile.close();
    return 0;
}

// Function to check if a string contains only digits, and therefor is an integer
bool isInt(const std::string& input){
    for (char i: input)
        if (!isdigit(i))
            return false;
    return true;
}

// Recursive function for performing a merge sort on a vector using threads
void mergeSort(std::vector<int>& list, int const first, int const last, std::ofstream &file, const std::string& thrID){
    std::string str;
    str = "Thread " + thrID + " started\n";
    file << str;

    str = "Thread " + thrID + " finished: ";
    if (last <= first) {
        for (int i = first; i <= last; i++) {
            str += std::to_string(list[i]) + ", ";
        }
        str += '\n';
        file << str;
        return;
    }

    // Mid-point of the current section that is to be sorted
    auto mid = first + (last - first) / 2;

    // Threads to run the front and back halves of the section's mergeSort
    std::thread thr_front(mergeSort, std::ref(list), first, mid, std::ref(file), thrID + "0");
    std::thread thr_back(mergeSort, std::ref(list), mid + 1, last, std::ref(file), thrID + "1");
    thr_front.join();
    thr_back.join();

    // Combine the two sorted halves
    merge(list, first, mid, last);

    // Log the completion of thread in the output file before closing the thread
    for (int i = first; i <= last; i++) {
        str += std::to_string(list[i]) + ", ";
    }
    str += '\n';
    file << str;
}

// Function to merge/sort two already sorted sections of the referenced vector
void merge(std::vector<int>& list, int const first, int const mid, int const last){
    // The lengths of the 2 sections that are to be merged
    auto const listSize0 = mid - first + 1;
    auto const listSize1 = last - mid;

    // Allocating temporary arrays to store the sorted values
    auto *subList0 = new int[listSize0];
    auto *subList1 = new int[listSize1];

    // Storing the 2 sets of sorted values
    for (int i = 0; i < listSize0; i++)
        subList0[i] = list[first + i];
    for (int i = 0; i < listSize1; i++)
        subList1[i] = list[mid + 1 + i];

    // Merging the 2 sets of sorted values in ascending order into the specified range of the vector
    int index0 = 0, index1 = 0, index2 = first;
    while(index0 < listSize0 && index1 < listSize1){
        if (subList0[index0] <= subList1[index1])
            list[index2++] = subList0[index0++];
        else
            list[index2++] = subList1[index1++];
    }

    // Replacing the remaining largest values to the section within the vector
    while (index0 < listSize0)
        list[index2++] = subList0[index0++];
    while (index1 < listSize1)
        list[index2++] = subList1[index1++];

    // Cleaning up temporary memory locations
    delete[] subList0;
    delete[] subList1;
}
