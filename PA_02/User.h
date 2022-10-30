//
// Created by willi on 2022-10-27.
//

#ifndef PA_02_USER_H
#define PA_02_USER_H
#include <string>

using namespace std;

class User {
private:
    string id;
    int *processes;
    int index;
    int total;
    
    //Data types for Users in Queue
    User *next;
    User *previous;
    int element;

public:
    //Constructors
    User();
    User(string, int);

    //Destructor
    ~User();

    //Member functions
    void addProcess();
    void resume();
    void pause();
    int validate();
    void sortProcesses();

    //Get functions
    string getID();
    int getTotal() const;
    int getIndex() const;

    //Set functions
    void setID(string);
    void setIndex(int);
    
    //Get functions for Users in Queue
    User *getNext();
    User *getPrevious();
    int getElement();

    //Set functions for Users in Queue
    void setNexttoNULL();
    void setPrevioustoNULL();
    void setNext(User*);
    void setPrevious(User*);
    void setElement(int);

};


#endif //PA_02_USER_H
