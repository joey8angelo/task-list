#ifndef TASKTYPE_H
#define TASKTYPE_H

#include <iostream>

class TaskType {
  protected:
    std::string title;
    std::string description;
    //date
  public:
    TaskType* next;
    TaskType(std::string title, std::string desc) : description(desc), title(title), next(nullptr) {}

    void editTitle(std::string t) { title = t; }
    std::string getTitle() { return title; }
    
    void editDescription(std::string d) { description = d; }
    std::string getDescription() { return description; }

    virtual std::string getFullTask() = 0;
    virtual void addSubTask(std::string, std::string) = 0;
    virtual void addSubTask(std::string) = 0;
};

#endif