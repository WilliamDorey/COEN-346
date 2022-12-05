#include "Node.h"
#include <string>
using namespace std;
//Constructors
Node::Node() {
    NodeID = "";
    next = nullptr;
}

Node::Node(string newId) {
    NodeID = newId;
}
//Destructor
Node::~Node()
{

}

//Get functions
string Node::getID()  {
    return NodeID;
}
Node *Node::getNext()
{
    return next;
}

//Set functions
void Node::setID(string newNodeID) {
    NodeID = newNodeID;
}
void Node::setNext(Node *node)
{
    next = node;
}
void Node::setNexttoNULL()
{
    next = nullptr;
}
