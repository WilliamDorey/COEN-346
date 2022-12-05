#include "MemorySpace.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "MemorySpace.h"
#include "Node.h"
#include "LinkedList.h"

//Constructors
MemorySpace::MemorySpace(){
    MainMem = nullptr;
    List = nullptr;
    size = 1;
    disk.open("../vm.txt");
}
MemorySpace::MemorySpace(int space, fstream& logsRef, int& mainCLK)
{
    clk = &mainCLK;
    logs = &logsRef;
    size = space;
    MainMem = new MemoryPage[space];
    List = new LinkedList;
    disk.open("../vm.txt", ios::in | ios::out);
}

//Destructor
MemorySpace::~MemorySpace() {
    delete MainMem;
    disk.close();
}

//Testing functions
void MemorySpace::printing()
{
    for (int i = 0; i < size; i++) {
        cout << MainMem[i].getId() << " and " << MainMem[i].getValue() << endl;
    }
}
void MemorySpace::printingLL()
{
    Node *temp = List->getHead();
    if(temp == NULL)
    {
        //Prints No element if head is empty
        cout << "No users in queue\n";
    }
    else
    {
        //Prints value of the head
        cout << temp->getID() << ", ";
        //Prints value of the rest of the Linklist until the next is equal the NULL
        while(temp->getNext() != nullptr)
        {
            temp = temp->getNext();
            cout <<  temp->getID() << ", ";
        }
        cout<< endl;
    }
}

//Stores stores variable id and value
void MemorySpace::Store(string id, unsigned int setValue) {
    bool added = false;

    //Checks if there is space in memory
    for (int i = 0; i < size && added == false ; i++)
    {
        //If there is space it adds the id and value to the memory and flags it
        if (MainMem[i].getId() == "") {
            this->MainMem[i] = MemoryPage(id,setValue);
            added = true;
            //Adds the id to the linked list
            List->addNode(id);
        }
    }
    //If there is no space
    if (added == false)
    {
        //It stores the id and value in the disk
        disk << id << " " << setValue << endl;
    }
}

//Function that releases an id and value from memory
void MemorySpace::Release(string id)
{
    bool remove = false;
    //Checks if id is in the memory
    for (int i = 0; i < size && remove == false; i++)
    {
        //If the value is in the memory it flags the id and value were removed
        if (MainMem[i].getId() == id)
        {
            //Moves released value to disk (if we want to delete we comment line below)
            //Cycles to end of file
            disk.seekg(0, ios::end);
            //Writes out to file
            disk << endl << MainMem[i].getId() << " " << MainMem[i].getValue();
            //Id removed from linked list
            List->removeNode(id);
            //Space is cleared in memory
            MainMem[i] = MemoryPage("", -1);
            remove = true;
        }
    }
    //If the value is in the disk it prints that value exists in disk
    if (remove == false)
    {
       cout << "Not removed because it does not exist or is in disk" << endl; //for testing
    }
}

//Looks up id in memory or makes possible swap between memory and disk to return id or returns -1
int MemorySpace::Lookup(string id) {
    bool lookedup=false, found_line = false;

    string temp_log;

    //Looks for id  in memory
    for (int i = 0; i < size && lookedup == false; i++)
    {
        //If value is in memory flags the value was looked up
        if (MainMem[i].getId() == id) {
            lookedup = true;
            //Moves the node with id to tail because it was the most recently used
            List->MovetoTail(id);
            //Returns id value
            return MainMem[i].getValue();
        }
    }
    //If the value is in disk
    if (lookedup == false)
    {
        cout <<"HERE!\n";
        //Stores lines when finding id and value in disk
        string line;
        //Stores lines when rewriting file
        string line2;
        //Stores lines value of disk
        string ValueTBAdded;
        //Stores value of memory
        string ValueTBRemoved;
        //Stores id from memory
        string IDTBRemoved;

        //Resets line of file to start
        disk.clear();
        disk.seekg(0);

        //Cycles line by line until line with id is found
        while(disk >> line)
        {

            //Creation of strings
            if(line == id)
            {
                //Next line
                disk >> line;
                //Stores lines value of disk
                ValueTBAdded = line;
                break;
            }
        }
        //Flag if there is space in memory
        bool space_in_memory = false;
        //Slot of array with free space
        int free_space;
        int newvalue = stoi(ValueTBAdded);
        //Vector to store all lines
        vector<string> linesvector;

        //Cycles through array
        for (int k = 0; k < size && space_in_memory == false ; k++)
        {
            //If there is an empty space it is flagged and the location is stored
            if (MainMem[k].getId() == "") {
                free_space = k;
                space_in_memory = true;
            }
        }
        //If there is an empty space the disk id and value are put into the array
        if(space_in_memory ==true )
        {
            //Loads id and value into Node
            MainMem[free_space].setId(id);
            MainMem[free_space].setValue(newvalue);
            //Adds id to Node
            List->addNode(id);
            //Resets line reading to start
            disk.clear();
            disk.seekg(0);

            //Reads through entire file and stores in vector
            while (disk >> line2)
            {
                linesvector.push_back(line2);
            }
            //Closes file stream
            disk.close();

            //Opens new file stream and clears file by default
            disk.open("../vm.txt", ios::out);

            //Writes in file
            for (int l = 0; l < linesvector.size(); l++)
            {
                //Catches id and value that was added to memory
                if(linesvector[l] == ValueTBAdded)
                {

                }
                else if (linesvector[l] == id)
                {

                }
                else
                {
                    //Writes rest of information
                    disk << linesvector[l]<< " ";
                    if (l%2 == 1)
                    {
                        disk << endl;
                    }
                }
            }
            //Closes the file stream
            disk.close();
            //Opens same filestream
            disk.open("../vm.txt", ios::in | ios::out);
        }
        else //If there is no empty space it is swapped
        {
            //Resets line reading to start
            disk.clear();
            disk.seekg(0);

            //Reads through entire file and stores in vector
            while (disk >> line2)
            {
                linesvector.push_back(line2);
            }
            //Closes file stream
            disk.close();

            //Opens new file stream and clears file by default
            while (disk >> line2)
            {
            }

            disk.open("../vm.txt", ios::out);

            //Writes in file
            for (int l = 0; l < linesvector.size(); l++)
            {
                //Catches id and value that was added to memory
                if(linesvector[l] == ValueTBAdded)
                {

                }
                else if (linesvector[l] == id)
                {

                }
                else
                {
                    //Writes rest of information
                    disk << linesvector[l]<< " ";
                    if (l%2 == 1)
                    {
                        disk << endl;
                    }
                }
            }
            //Closes the file stream
            disk.close();
            //Opens same filestream
            disk.open("../vm.txt", ios::in | ios::app);

            //Get Node to be removed
            IDTBRemoved = List->getHead()->getID();
            temp_log = IDTBRemoved;

            for (int i = 0; i < size; i++)
            {
                //Cycles through all slots of array to find id and value that have to be removed
                if (MainMem[i].getId() == IDTBRemoved)
                {
                    //while (disk >> line2)
                    //{
                        disk << MainMem[i].getId() << " " << MainMem[i].getValue();
                    //}
                    //Adds removed to disk

                    //Sets id and value in memory from didk
                    MainMem[i].setId(id);
                    MainMem[i].setValue(newvalue);
                }
            }
            disk.close();
            //Opens same filestream
            disk.open("../vm.txt", ios::in | ios::out);
            //Removes head because id was swapped to disk
            List->removeHead();

            //Adds node at tail because id was added to memory
            List->addNode(id);
            temp_log = "Clock: " + to_string(*clk) + ", Memory Manager, SWAP: Variable " + id + " with Variable " + temp_log + "\n";
            *logs << temp_log;
        }
        return newvalue;
    }
    this->printing();
    this->printingLL();
    return -1;
}
