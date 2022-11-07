#ifndef PA_02_USERQUEUE_H
#define PA_02_USERQUEUE_H

#include "User.h"
#include "UserQueueNode.h"

using namespace std;

class UserQueue {
private:
    UserQueueNode* head;
    UserQueueNode* tail;
    int length;
public:
    UserQueue();
    ~UserQueue();

    void addUser(User*);
    void removeHead();
    void cycleQueue();
    User* getUser();
    int getLength() const;
};

#endif //PA_02_USERQUEUE_H
