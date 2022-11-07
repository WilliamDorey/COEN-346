#include "UserQueueNode.h"

//UserQueueNode functions
UserQueueNode::UserQueueNode(User* newUser) {
    element = newUser;

    prev = nullptr;
    next = nullptr;
}
UserQueueNode::~UserQueueNode(){
    delete element;
    if(next != nullptr)
        next->setPrev(prev);
    if(prev != nullptr)
        prev->setNext(next);
}

void UserQueueNode::setNext(UserQueueNode* newNode) {
    next = newNode;
}
void UserQueueNode::setPrev(UserQueueNode* newNode) {
    prev = newNode;
}
/*not used
UserQueueNode* UserQueueNode::getPrev(){
    return prev;
}
 */
UserQueueNode* UserQueueNode::getNext(){
    return next;
}
User* UserQueueNode::getUser(){
    return element;
}
