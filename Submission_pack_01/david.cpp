#include <iostream>
#include<vector>
using namespace std;

void merge_array(vector<int>& v, int start, int mid, int end)
{
    //Gets size of 2 temporary arrays
    const auto size_array0 = mid - start + 1; //
    const auto size_array1 = end - mid;

    //creates 2 temporary arrays
    auto *under_array0 = new int[size_array0];
    auto *under_array1 = new int[size_array1];

    //stores values into the 2 temporary arrays
    for (int i = 0; i < size_array0; i++)
    {
        under_array0[i] =  v[start +i];
    }
    for (int i = 0; i < size_array1; i++)
    {
        under_array1[i]= v[mid + 1 + i];
    }

    int index0 = 0; //index of sub array 0
    int index1 = 0; //index of sub array 1
    int index2 = start; //index of merged array

    //Merges the 2 temporary vectors into 1 in ascending order
    while(index0 < size_array0 && index1 < size_array1)
    {
        if (under_array0[index0] <= under_array1[index1])
        {
            v[index2++] = under_array0[index0++];
        }
        else
        v[index2++] = under_array1[index1++];
    }

    //Copy the remaining elements
    while(index0 < size_array0)
    {
        v[index2++] = under_array0[index0++];
    }
    while(index1 < size_array1)
    {
        v[index2++] = under_array1[index1++];
    }

    //deletes temporary arrays
    delete[] under_array0;
    delete[] under_array1;
}
void merge_sort(vector<int>& v, int start, int end)
{
    //Completes algorithm recursively
    if(end <= start)
    {
        return;
    }
    //Calculating the middle
    int middle = start + (end - start)/2;

    merge_sort(v, start, middle); //Sorts first half
    merge_sort(v,(middle+1), end); //Sorts second half
    merge_array(v,start,middle,end); //Combines the two halves in ascending order
}

int main() {

    vector<int> v ={3304, 8221, 26849, 14038, 1509, 6367, 7856, 21362}; //declares vector with values

    int listSize = static_cast<int>(v.size()) - 1; //calculates size of array

    merge_sort(v,0, listSize);//calls merge sort function

    for(int i = 0; i < listSize; i++)//for loop to print sorted vector
    {
        cout<< v[i]<<", ";
    }
    return 0;
}