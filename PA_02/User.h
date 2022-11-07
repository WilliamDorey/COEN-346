#ifndef PA_02_USER_H
#define PA_02_USER_H

#include <string>

using namespace std;

class User {
private:
    string id;
    int index;
    int total;
    int* processes;

public:
    //Constructors
    explicit User(string, int);

    //Destructor
    ~User();

    //Member functions
    void addProcess(int&,int,int,int);
    void resume();
    void pause();
    int validate();
    int nextProcess();
    void static process(int&, int, int, int&);


    //Get functions
    string getID();
    int getTotal() const;
    int getIndex() const;
    int getStatus();

    //Set functions
//    void setID(string);
    void setIndex(int);
};


#endif //PA_02_USER_H
