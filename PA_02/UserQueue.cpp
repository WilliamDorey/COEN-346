//
// Created by willi on 2022-10-27.
//
#include <iostream>
#include "UserQueue.h"

#include <string>

using namespace std;

//Default Connstructor
UserQueue::UserQueue()
{
    head = nullptr;
    tail = nullptr;
}

//Gets head variable
User *UserQueue::getHead()
{
    return head;
}
//Gets tail variable
User *UserQueue::getTail()
{
    return tail;
}

//Function that add user at the end of the queue
void UserQueue::createUserEnd(int elem)
{
    //New user object is created
    User *newUser = new User;

    //Element is assigned to new user
    newUser->setElement(elem);

    //Next is set to Null for new user
    newUser->setNexttoNULL();

    //Copies head to temporary object
    User* temp = head;

    if(head == NULL)
    {
        //Sets the new Node be the tail and head of the queue
        head = newUser;
        tail = newUser;

        //Sets next and previous to NULL
        newUser->setPrevioustoNULL();
        newUser->setNexttoNULL();
    }
    else
    {
        //Cycles to tail of the linked list
        while (temp->getNext() != NULL)
            temp = temp->getNext();

        //Sets the next of the tail to the new Node
        tail->setNext(newUser);

        //Sets tail of the queue to be the next of the the previous tail
        tail = tail->getNext();

        //Sets previous of new tail to the old tail
        tail->setPrevious(temp);
    }
}

void UserQueue::removefromqueue()
{
    if(head->getNext() == NULL)
    {
        //If queue only has 1 user
        head = NULL;
    }
    else {
        //Sets the temporary Node to the next of head of the LinkedList
        User *temporary = head->getNext();

        delete head;
        //Sets the temporary Node as the head

        //Makes temporary head of then linked list
        head = temporary;

        //Sets previous to Null of head
        head->setPrevioustoNULL();
    }
    return;
}
void UserQueue::cycleuser()
{
    if(head == NULL)
    {
        //If the queue is empty
        cout << "Queue empty\n";
    }
    else if (head->getNext() == NULL)
    {
        //If the queue only has 1 user
        cout << "No cycle possible\n";
    }
    else
    {
        //Creates two temporary users 1 for head and 1 for next of head
        User *temporary1 = head;
        User *temporary2 = head->getNext();

        //Sets head to the next of the tail
        tail->setNext(temporary1);

        //Sets next of new tail to NULL
        temporary1->setNexttoNULL();

        //Makes the old head the tail of the queue
        tail = temporary1;

        //Makes the next of the old head the head of the queue
        head = temporary2;

        //Sets previous of new head to NULL
        head->setPrevioustoNULL();
    }
}
//Prints value of next in queue
void UserQueue::nextinqueue()
{
    if(head == NULL)
    {
        //If the queue is empty
        cout << "Queue empty\n";
    }
    else
    {
        //If the queue has users print element of head
        cout << head->getElement();
    }
}

//Testing functions
void UserQueue::valueofNodeNposition(int pos)
{
    User *temporary2 = head->getPrevious();
    if (pos == 0)
    {
        //Returns value of head
        cout<< temporary2->getElement() << endl;
        return;
    }
    User *temporary = head;
    User *temporary3 = head;
    for (int i = 0; i < pos; i++)
    {
        temporary = temporary->getNext();
    }
    temporary3 = temporary->getPrevious();
    //Prints value of Node in position N
    cout<< temporary3->getElement() << endl;
}
std::ostream& operator<<(std::ostream& out, UserQueue& Q)
{
    User *temp = Q.getHead();
    if(temp == NULL)
    {
        //Prints No element if head is empty
        out << "No users in queue\n";
    }
    else
    {
        //Prints value of the head
        out << temp->getElement() << endl;
        //Prints value of the rest of the Linklist until the next is equal the NULL
        while(temp->getNext() != nullptr)
        {
            temp = temp->getNext();
            out <<  temp->getElement() << endl;
        }
    }
    return out;
}
