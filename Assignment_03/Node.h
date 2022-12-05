#ifndef UNTITLED5_NODE_H
#define UNTITLED5_NODE_H

#include <string>
using namespace std;

class Node{
private:
    //Data types
    Node *next;
    string NodeID;
public:
    //Constructors and Destructor
    Node();
    Node(string);
    ~Node();

    //Get functions
    Node *getNext();
    Node *getPrevious();
    string getID();

    //Set functions
    void setNexttoNULL();
    void setNext(Node *);
    void setID(string);
};

#endif //UNTITLED5_NODE_H
