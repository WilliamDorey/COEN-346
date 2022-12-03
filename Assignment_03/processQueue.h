#ifndef ASSIGNMENT_03_PROCESSQUEUE_H
#define ASSIGNMENT_03_PROCESSQUEUE_H


class processQueue {
private:
    int* start{};
    int* burst{};
    int* id{};
    int size{};
    int index{};

public:
    explicit processQueue(int);
    ~processQueue();

    void addProc(int,int,int);
    int nextProc();
    int * getInfo();
    void sort();

    void setIndex(int);
};


#endif //ASSIGNMENT_03_PROCESSQUEUE_H
