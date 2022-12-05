//
// Created by david on 2022-12-03.
//

#include "MemoryPage.h"

using namespace std;

//Constructor
MemoryPage::MemoryPage() = default;
MemoryPage::MemoryPage(string newId, unsigned int newValue){
    id = newId;
    value = newValue;
}
//Destructor
MemoryPage::~MemoryPage() = default;

string MemoryPage::getContent(){
    string temp;
    temp = id + '\t' + to_string(value);
    return temp;
}

//Get functions
string MemoryPage::getId(){
    return id;
}
unsigned int MemoryPage::getValue(){
    return value;
}

//Set functions
void MemoryPage::setId(string newId){
    id = newId;
}
void MemoryPage::setValue(unsigned int newValue) {
    value = newValue;
}
