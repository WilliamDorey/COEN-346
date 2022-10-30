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
    next = nullptr;
    previous = nullptr;
    element = 0;
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

//Get fucntions
User *User::getNext()
{
    return next;
}
User *User::getPrevious()
{
    return previous;
}
int User::getElement()
{
    return element;
}

//Functions to set to NULL
void User::setNexttoNULL()
{
    next = nullptr;
}
void User::setPrevioustoNULL()
{
    previous = nullptr;
}

//Set functions
void User::setNext(User* user)
{
    next = user;
}
void User::setPrevious(User *user)
{
    previous = user;
}
void User::setElement(int a)
{
    element = a;
}
