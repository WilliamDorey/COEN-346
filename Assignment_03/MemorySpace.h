#ifndef ASSIGNMENT_03_MEMORYSPACE_H
#define ASSIGNMENT_03_MEMORYSPACE_H

#include "MemoryPage.h"
#include <fstream>

using namespace std;

class MemorySpace {
private:
    MemoryPage* MainMem{};
    int size{};
    fstream disk;

public:
    MemorySpace();
    explicit MemorySpace(int);

    ~MemorySpace();

    void Store(string, unsigned int);
    void Release(string);
    int Lookup(string);

};


#endif //ASSIGNMENT_03_MEMORYSPACE_H
