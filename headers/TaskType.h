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

    void edit_title(std::string t) { title = t; }
    std::string get_title() { return title; }
    
    void edit_description(std::string d) { description = d; }
    std::string get_description() { return description; }

    virtual std::string get_full_task() = 0;
};

#endif