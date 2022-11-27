// Class definition for MemoryPage
// Object holds the relevant information for items stored in Main Memory

#ifndef ASSIGNMENT_03_MEMORYPAGE_H
#define ASSIGNMENT_03_MEMORYPAGE_H

#include <string>

using namespace std;

class MemoryPage {
private:
    string id;
    unsigned int value{};

public:
    MemoryPage();
    MemoryPage(string, unsigned int);

    ~MemoryPage();

    string getContent();

    string getId();
    unsigned int getValue();

    void setId(string);
    void setValue(unsigned int);
};


#endif //ASSIGNMENT_03_MEMORYPAGE_H
