#ifndef SUBTASK_H
#define SUBTASK_H

#include <iostream>
#include "TaskType.h"

class SubTask : public TaskType {
  public:
    SubTask(std::string title, std::string desc) : TaskType(title, desc) {}

    virtual std::string getFullTask();
    virtual void addSubTask(std::string t, std::string d) { return; }
    virtual void addSubTask(std::string t) { return; }
};

#endif