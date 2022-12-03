#include "processQueue.h"

processQueue::processQueue(int newSize){
    size = newSize;
    start = new int[size];
    burst = new int[size];
    id = new int[size];
    index = 0;
}

processQueue::~processQueue(){
    delete[] start;
    delete[] burst;
    delete[] id;
}

void processQueue::addProc(int newStart, int newBurst, int newID){
    start[index] = newStart;
    burst[index] = newBurst;
    id[index++] = newID;
}

int processQueue::nextProc(){
    if (++index == size)
        return -1;
    return index;
}

int * processQueue::getInfo(){
    int* info = new int[3];
    info[0] = start[index];
    info[1] = burst[index];
    info[2] = id[index];
    return info;
}

void processQueue::setIndex(int newIndex){
    index = newIndex;
}

void processQueue::sort() {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            if (start[j] > start[j+1]){
                int temp = start[j];
                start[j] = start[j+1];
                start[j+1] = temp;
                temp = burst[j];
                burst[j] = burst[j+1];
                burst[j+1] = temp;
                temp = id[j];
                id[j] = id[j+1];
                id[j+1] = temp;
            }
        }
    }
}
