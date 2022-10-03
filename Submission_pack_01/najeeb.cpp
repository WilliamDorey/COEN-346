#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
//#include <sstream>

using namespace std;

bool isInt(const string& input);
void merge_sort(vector<int>&, int, int, ofstream&);
void merge_array(std::vector<int>&, int, int, int);
//string int2Binary(int);

int main() {
    // Because we have no way of knowing the size of the entries, we are using a vector to hold the data
    vector<int> list;

    // Input filestream that reads the unsorted data set into the vector
    // Note that the "input.txt" file needs to be in the same file directory as the executable file
    ifstream inputFile;
    inputFile.open("input.txt", ios::in);
    string var;
    while (inputFile >> var)
        if (isInt(var))
            list.push_back(stoi(var));

    inputFile.close();
    int listSize;
    listSize = static_cast<int>(list.size()) - 1;

    // Output filestream that will store the results and progress of the mergeSort function
    ofstream outFile;
    outFile.open("output.txt");

    // Start primary thread in the recursive function to begin merge sort
    thread mainThread(merge_sort, ref(list), 0, listSize, ref(outFile));

    // Call the join function for the primary thread so the process does not
    // terminate before completing the merge sort
    // <Thread name>.join();
    mainThread.join();

    // Close the output file and terminate the process
    outFile.close();
    return 0;
}

// Function to check if a string contains only digits, and therefor is an integer
bool isInt(const string& input) {
    for (char i : input)
        if (!isdigit(i))
            return false;
    return true;
}

// Function to convert int to Binary
string int2Binary(int thrID) {
    string thrID_bi;
    while (thrID != 0) {
        thrID_bi = (thrID % 2 == 0 ? "0" : "1") + thrID_bi;
        thrID / 2;
    }
    return thrID_bi;
}

void merge_sort(vector<int>& v, int start, int end, ofstream& file) {
    
    string str;
    thread::id thrID = this_thread::get_id(); 
    file << "Thread " << thrID << " started\n";

    //Converting thread ID to int then to binary
    /*
    stringstream strThr;
    strThr << thrID;
    int id = std::stoi(strThr.str());
    string thrID_binary = int2Binary(id);
    */
 
    //Completes algorithm recursively
    if (end <= start) {
        for (int i = start; i <= end; i++) {
            str += std::to_string(v[i]) + ", ";
        }
        str += '\n';
        file << "Thread " << thrID << " finished: " << str;
        return;
    }

    //Calculating the middle
    int middle = start + (end - start) / 2;

    //recursive thread for 1st half of list
    thread thrFront(merge_sort, ref(v), start, middle, ref(file));
    //recursive thread for 2nd half of list
    thread thrBack(merge_sort, ref(v), (middle + 1), end, ref(file));

    //wait for threads to complete before merging
    thrFront.join();
    thrBack.join();

    //Combines the two halves in ascending order
    merge_array(v, start, middle, end); 

    //
    for (int i = start; i <= end; i++) {
        str += std::to_string(v[i]) + ", ";
    }
    str += '\n';
    file << "Thread " << thrID << " finished: " << str;
}

void merge_array(vector<int>& v, int start, int mid, int end)
{
    //Gets size of 2 temporary arrays
    const auto size_array0 = mid - start + 1; //
    const auto size_array1 = end - mid;

    //creates 2 temporary arrays
    auto* under_array0 = new int[size_array0];
    auto* under_array1 = new int[size_array1];

    //stores values into the 2 temporary arrays
    for (int i = 0; i < size_array0; i++)
    {
        under_array0[i] = v[start + i];
    }
    for (int i = 0; i < size_array1; i++)
    {
        under_array1[i] = v[mid + 1 + i];
    }

    int index0 = 0; //index of sub array 0
    int index1 = 0; //index of sub array 1
    int index2 = start; //index of merged array

    //Merges the 2 temporary vectors into 1 in ascending order
    while (index0 < size_array0 && index1 < size_array1)
    {
        if (under_array0[index0] <= under_array1[index1])
        {
            v[index2++] = under_array0[index0++];
        }
        else
            v[index2++] = under_array1[index1++];
    }

    //Copy the remaining elements
    while (index0 < size_array0)
    {
        v[index2++] = under_array0[index0++];
    }
    while (index1 < size_array1)
    {
        v[index2++] = under_array1[index1++];
    }

    //deletes temporary arrays
    delete[] under_array0;
    delete[] under_array1;
}