#ifndef ASSIGNMENT_03_MEMORYSPACE_H
#define ASSIGNMENT_03_MEMORYSPACE_H

#include "Node.h"
#include "LinkedList.h"
#include "MemoryPage.h"
#include <fstream>

using namespace std;

class MemorySpace {
private:
    //Data types
    MemoryPage* MainMem{};
    int size{};
    fstream disk;
    fstream* logs;
    LinkedList* List;
    int* clk;

public:
     //Constructor
    MemorySpace();
    explicit MemorySpace(int, fstream&, int&);
  
    //Destructor
    ~MemorySpace();

    //Class functions
    void Store(string, unsigned int);
    void Release(string);
    int Lookup(string);

    void printing();
    void printingLL();

};


#endif //ASSIGNMENT_03_MEMORYSPACE_H
