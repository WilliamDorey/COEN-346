//
// Created by david on 2022-12-03.
//

#ifndef UNTITLED5_LINKEDLIST_H
#define UNTITLED5_LINKEDLIST_H
#include "Node.h"
using namespace std;


class LinkedList {
private:
    //Data types
    Node* head;
    Node* tail;
public:
    //Constructor
    LinkedList();
    //Destructor
    ~LinkedList();

    //Class functions
    void addNode(string);
    void removeHead();
    void removeNode(string);
    void MovetoTail(string);

    //Get function
    Node* getHead();
};
