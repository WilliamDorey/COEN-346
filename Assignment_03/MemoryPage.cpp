//
// Created by willi on 2022-11-21.
//

#include "MemoryPage.h"

using namespace std;

MemoryPage::MemoryPage() = default;
MemoryPage::MemoryPage(string newId, unsigned int newValue){
    id = newId;
    value = newValue;
}

MemoryPage::~MemoryPage() = default;

string MemoryPage::getContent(){
    string temp;
    temp = id + '\t' + to_string(value);
    return temp;
}

string MemoryPage::getId(){
    return id;
}
unsigned int MemoryPage::getValue(){
    return value;
}

void MemoryPage::setId(string newId){
    id = newId;
}
void MemoryPage::setValue(unsigned int newValue) {
    value = newValue;
}


