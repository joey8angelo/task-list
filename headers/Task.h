#ifndef TASK_H
#define TASK_H

#include <iostream>
#include "TaskType.h"

class Task : public TaskType {
  private:
    std::string title;
    std::string description;
  public:
    TaskType* next;
    TaskType* subTask;
    Task(std::string title, std::string desc) : TaskType(title, desc) {}

    virtual std::string get_full_task();
};

#endif