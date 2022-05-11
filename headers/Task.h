#ifndef TASK_H
#define TASK_H

#include <iostream>
#include "TaskType.h"

class Task : public TaskType {
  public:
    TaskType* next;
    TaskType* subTask;
    Task(std::string title, std::string desc) : TaskType(title, desc), subTask(nullptr) {}
    
    virtual void addSubTask(std::string, std::string);
    virtual void addSubTask(std::string t) {addSubTask(t, "No Description");}
    virtual std::string getFullTask();
};

#endif