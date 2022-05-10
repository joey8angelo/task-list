#ifndef TASKLIST_H
#define TASKLIST_H

#include <iostream>
#include "Task.h"

class TaskList {
  //private:
    TaskType* head;
    TaskType* tail;
  public:
    TaskList(): head(nullptr), tail(nullptr) {}
    void push_back(std::string, std::string);
    void push_back(std::string t) { push_back(t, "No Description"); }
    void printList();
    
};

#endif