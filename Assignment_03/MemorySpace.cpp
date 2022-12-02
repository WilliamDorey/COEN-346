#include "MemorySpace.h"

MemorySpace::MemorySpace(){
    MainMem = nullptr;
    size = 0;
    disk.open("../vm.txt");
}

MemorySpace::MemorySpace(int space) {
    size = space;
    MainMem = new MemoryPage[space];
}

MemorySpace::~MemorySpace() {
    delete MainMem;
}

void MemorySpace::Store(string id, unsigned int value) {
    // TODO: Look for first open space in MainMem and store new var there,
    //  If there is no space, append to the disk
    for (int i = 0; i < size; i++){
    }
}

void MemorySpace::Release(string id) {
    // TODO: Find variable in MainMem or disk and remove it
}

int MemorySpace::Lookup(string id) {
    // TODO: Look for variable in MainMem
    //  If found, return value
    //   Else Search in disk
    //    If found in disk, swap into MainMem with least recently accessed variable there
    //    Else, return -1 to indicate the variable does not exist
    return 0;
}
