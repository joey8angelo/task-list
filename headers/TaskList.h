#ifndef TASKLIST_H
#define TASKLIST_H

#include <iostream>
#include "Task.h"

class TaskList {
  public:
    TaskType* head;
    TaskType* tail;
    TaskList(): head(nullptr), tail(nullptr) {}
    void push_back(std::string, std::string);
    void push_back(std::string t) { push_back(t, "No Description"); }
    void printList();
};

#endif