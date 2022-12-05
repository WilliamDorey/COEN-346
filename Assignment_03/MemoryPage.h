// Class definition for MemoryPage
// Object holds the relevant information for items stored in Main Memory

#ifndef ASSIGNMENT_03_MEMORYPAGE_H
#define ASSIGNMENT_03_MEMORYPAGE_H

#include <string>

using namespace std;

class MemoryPage {
private:
    //Data types
    string id;
    unsigned int value{};

public:
    //Constructor    
    MemoryPage();
    MemoryPage(string, unsigned int);
    
    //Destructor
    ~MemoryPage();

    string getContent();

    //Get fucntions
    string getId();
    unsigned int getValue();

    //Set functions
    void setId(string);
    void setValue(unsigned int);
};


#endif //ASSIGNMENT_03_MEMORYPAGE_H
