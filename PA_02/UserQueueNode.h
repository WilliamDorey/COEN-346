//
// Created by willi on 2022-11-07.
//

#ifndef ASSIGNMENT_02_USERQUEUENODE_H
#define ASSIGNMENT_02_USERQUEUENODE_H

#include "User.h"

using namespace std;

class UserQueueNode {
private:
    User* element;
    UserQueueNode* prev;
    UserQueueNode* next;
public:
    explicit UserQueueNode(User*);
    ~UserQueueNode();

    //Set functions
    void setPrev(UserQueueNode*);
    void setNext(UserQueueNode*);

    //Get functions
//    UserQueueNode* getPrev();
    UserQueueNode* getNext();
    User* getUser();
};


#endif //ASSIGNMENT_02_USERQUEUENODE_H
