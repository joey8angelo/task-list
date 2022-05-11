#ifndef TASKLIST_H
#define TASKLIST_H

#include <iostream>
#include "Task.h"

class TaskList {
  public:
    TaskType* head;
    TaskType* tail;
    TaskList(): head(nullptr), tail(nullptr) {}
    void pushBack(std::string, std::string);
    void pushBack(std::string t) { pushBack(t, "No Description"); }
    void printList();
    TaskType* getTask(std::string);
};

#endif