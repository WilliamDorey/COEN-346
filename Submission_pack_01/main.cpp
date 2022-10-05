// Included Header Files
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <sstream>

// Used Namespace
using namespace std;

// Declaring Functions
bool isInt(const string& input);
void merge_sort(vector<int>&, int, int, ofstream&);
void merge(std::vector<int> &v, int start, int mid, int end);

// Main driver function
int main() {

    // Because we have no way of knowing the size of the entries, we are using a vector to hold the data
    vector<int> list;

    // Input filestream that reads the unsorted data set into the vector
    // Note that the "input.txt" file needs to be in the same file directory as the executable file
    // and only whole numbers are accepted as valid data entries
    ifstream inputFile;
    inputFile.open("input.txt", ios::in);
    string var;
    while (inputFile >> var)
        if (isInt(var))
            list.push_back(stoi(var));

    // Close the input file since it is no longer needed, and acquire the final amount of data entries to be sorted
    inputFile.close();
    int listSize;
    listSize = static_cast<int>(list.size()) - 1;

    // Output filestream that will store the results and progress of the merge_sort function
    ofstream outFile;
    outFile.open("output.txt");

    // Start the recursive function to commence merge sort
    merge_sort(list, 0, listSize, outFile);

    // Close the output file and terminate the process
    outFile.close();
    return 0;
}

// Function to check if a string contains only digits, and is therefor is an integer
// returning true -> integer, false -> is not an integer
bool isInt(const string& input) {
    for (char i : input)
        if (!isdigit(i))
            return false;
    return true;
}

// Recursive function for running a merge sort through a vector of integers
// Target vector is passed by reference and the progress is logged in a filestream that is also passed by reference
void merge_sort(vector<int>& v, int start, int end, ofstream& file) {
    // Defining the thread ID and creating a string stream for logging start of the thread in the output file
    thread::id thrID = this_thread::get_id();
    stringstream strID;
    strID << "Thread " << thrID << " started\n";
    file << strID.str();

    // So long as there is more than a single value in the range of the vector
    if (end > start) {
        // Calculating the middle
        int middle = start + (end - start) / 2;

        // Threads to recursively run merge_sort for both halves
        thread thrFront(merge_sort, ref(v), start, middle, ref(file));
        thread thrBack(merge_sort, ref(v), (middle + 1), end, ref(file));

        // Wait for threads to complete before merging
        // Order does not matter since both are needed
        thrFront.join();
        thrBack.join();

        // Combines the two halves in ascending order
        merge(v, start, middle, end);
    }

    // Completes algorithm and formats outputs for ending of threads before sending to the file
    strID.str("");
    strID << "Thread " << thrID << " finished: ";
    for (int i = start; i <= end; i++) {
        strID << std::to_string(v[i]) << ", ";
    }
    strID << '\n';
    file << strID.str();
}

// Function to combine two pre-sorted (ascending) sections of a vector in ascending order within the space of the vector
// Target vector is passed by reference
void merge(vector<int>& v, int start, int mid, int end){
    // Get the size needed for the 2 temporary arrays
    const auto size_array0 = mid - start + 1;
    const auto size_array1 = end - mid;

    // Create the 2 temporary arrays
    auto* under_array0 = new int[size_array0];
    auto* under_array1 = new int[size_array1];

    // Store relevant values into the 2 temporary arrays
    for (int i = 0; i < size_array0; i++)
        under_array0[i] = v[start + i];
    for (int i = 0; i < size_array1; i++)
        under_array1[i] = v[mid + 1 + i];

    // Create an index for both sub arrays and the vector
    int index0 = 0;
    int index1 = 0;
    int index2 = start;

    // Merge the 2 temporary arrays into the vector's relevant positions in ascending order
    while (index0 < size_array0 && index1 < size_array1){
        if (under_array0[index0] <= under_array1[index1])
            v[index2++] = under_array0[index0++];
        else
            v[index2++] = under_array1[index1++];
    }

    // Copy the remaining largest elements to the vector
    while (index0 < size_array0)
        v[index2++] = under_array0[index0++];
    while (index1 < size_array1)
        v[index2++] = under_array1[index1++];

    // Delete the temporary arrays
    delete[] under_array0;
    delete[] under_array1;
}