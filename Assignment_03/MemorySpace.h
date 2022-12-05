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
    LinkedList* List;


public:
     //Constructor
    MemorySpace();
    explicit MemorySpace(int);
  
    //Destructor
    ~MemorySpace();

    //Class functions
    void Store(string, unsigned int);
    void Release(string);
    int Lookup(string);

};


#endif //ASSIGNMENT_03_MEMORYSPACE_H
