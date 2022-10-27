//
// Created by willi on 2022-10-27.
//
#include <string>

#include "User.h"

using namespace std;
//Default Constructor
User::User() {
    id = "";
    index = 0;
}

User::User(string newId, int i) {
    id = newId;
    processes = new int[i];
    index = 0;
}

//Destructor
User::~User(){
    delete[] processes;
}

//Member Functions
void User::addProcess(){}
void User::resume(){}
void User::pause(){}
int User::validate(){}
void User::sortProcesses(){}

string User::getID(){}
int User::getTotal() const {
    return total;
}
int User::getIndex() const {
    return index;
}

void User::setID(string newId) {
    id = newId;
}
void User::setIndex(int) {

}
