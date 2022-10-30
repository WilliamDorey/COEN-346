//
// Created by willi on 2022-10-27.
//

#ifndef PA_02_USERQUEUE_H
#define PA_02_USERQUEUE_H
#include <string>
#include "User.h"

using namespace std;


class UserQueue{
private:
    User *head;
    User *tail;


public:
    UserQueue();
    //~UserQueue();

    //Get functions
    User *getHead();
    User *getTail();

    //Creates user at end
    void createUserEnd(int);

    //Removes head from queue
    void removefromqueue();

    //Cycles head to back of queue
    void cycleuser();

    //Testing functions
    void nextinqueue();
    void valueofNodeNposition(int pos);
    friend std::ostream & operator<<(ostream&, UserQueue&);
};


#endif //PA_02_USERQUEUE_H
