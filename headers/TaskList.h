#ifndef TASKLIST_H
#define TASKLIST_H

#include <iostream>
#include "Task.h"

class TaskList {
  public:
    Task* head;
    Task* tail;
    TaskList(): head(nullptr), tail(nullptr) {}
    void pushBack(std::string, std::string);
    void pushBack(std::string t) { pushBack(t, "No Description"); }
    bool remove(std::string);
    void printList();
    Task* getTask(std::string);
};

#endif