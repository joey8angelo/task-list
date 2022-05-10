#ifndef SUBTASK_H
#define SUBTASK_H

#include <iostream>
#include "TaskType.h"

class SubTask : public TaskType {
  private:
    std::string title;
    std::string description;
  public:
    SubTask(std::string title, std::string desc) : TaskType(title, desc) {}

    virtual std::string get_full_task();
};

#endif