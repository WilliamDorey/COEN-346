#include "UserQueue.h"

using namespace std;

//UserQueue Functions
UserQueue::UserQueue(){
    length = 0;
    head = nullptr;
    tail = nullptr;
}
UserQueue::~UserQueue(){
    UserQueueNode* current = head;
    while(current != nullptr) {
        UserQueueNode* temp = current;
        current = current->getNext();
        delete temp;
    }
    delete current;
}

void UserQueue::addUser(User* newUser){
    auto* newNode = new UserQueueNode(newUser);

    if(length == 0){
        head = newNode;
        tail = newNode;
    } else {
        tail->setNext(newNode);
        newNode->setPrev(tail);
        tail = newNode;
    }
    length++;
}
void UserQueue::removeHead(){
    if(length > 0) {
        UserQueueNode *temp = head;
        if (length > 1){
            head = head->getNext();
            head->setPrev(nullptr);
        }
        delete temp;
        length--;
    }
}
void UserQueue::cycleQueue(){
    if(length > 1) {
        head->setPrev(tail);
        tail->setNext(head);

        head = head->getNext();
        head->setPrev(nullptr);

        tail = tail->getNext();
        tail->setNext(nullptr);
    }
}
User* UserQueue::getUser(){
    return head->getUser();
}
int UserQueue::getLength() const{
    return length;
}