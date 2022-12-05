#include "LinkedList.h"
#include "Node.h"
#include "MemorySpace.h"
#include <string>
using namespace std;

//Constructor
LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
}

//Destructor
LinkedList::~LinkedList(){
    Node* current = head;
    while(current != nullptr) {
        Node* temp = current;
        current = current->getNext();
        delete temp;
    }
    delete current;
}

//Get function (least recently used)
Node *LinkedList::getHead()
{
    return head;
}

//Add node to tail position (most recently used)
void LinkedList::addNode(string id){

    //Creates new node
    Node *newNode = new Node;

    //Sets id of new node
    newNode->setID(id);

    //If linked list is empty it makes the new node the head and tail
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    //If linked list is not empty
    else
    {
        //Sets next of tail to new node
        tail->setNext(newNode);

        //Makes new node the tail
        tail = newNode;

        //Sets next of tail to nullptr
        tail->setNexttoNULL();
    }
}

//Removes head from linked list (least recently used)
void LinkedList::removeHead()
{
    //If linked list only has head
    if(head->getNext() == NULL)
    {
        delete head;
    }
    else
    {
        //Sets the temporary Node to the next of head of the LinkedList
        Node *temporary = head->getNext();

        //Deletes head
        delete head;

        //Makes temporary head of then linked list
        head = temporary;

    }
}

//Removes a node from linked list
void LinkedList::removeNode(string id)
{
    //If Node to be removed is head
    if (head->getID() == id)
    {
        //Removes head
       removeHead();
    }
    //If Node to be removed is tail
    else if (tail->getID() == id)
    {
        //Makes temp3 = head
        Node *temp3 = head;
        //Cycles through linked list until the next of node has the same id as tail
        while (temp3->getNext()->getID() != tail->getID())
        {
            temp3 = temp3->getNext();
        }
        //deletes tail
        delete tail;

        //Makes temp3 the new tail and sets its next to nullptr
        tail = temp3;
        tail->setNexttoNULL();
    }
    else
    {
        //Makes temp1 = head
        Node *temp1 = head;

        //Cycles through linked list until the id of the next of temp 1 = id
        while (temp1->getNext()->getID() != id)
        {
            temp1 = temp1->getNext();
        }

        //Makes temp 2 the next of temp 1
        Node *temporary2 = temp1->getNext();

        //Sets the next of temp 1 to the next of temp 2
        temp1->setNext(temporary2->getNext());
    }

}

//Moves node with id to tail position (most recently used)
void LinkedList::MovetoTail(string id)
{
    //Removes the node with id
    removeNode(id);

    //Adds a new node with id at the tail position
    addNode(id);
}
