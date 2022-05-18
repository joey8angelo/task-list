#ifndef TASK_H
#define TASK_H

#include <iostream>

class SubTask;

class Task {
  protected:
    std::string title;
    std::string description;
  public:
    Task* next;
    SubTask* subTask;

    Task(std::string title, std::string desc) : title(title), description(), subTask(nullptr), next(nullptr) {}
    
    void editTitle(std::string t) { title = t; }
    std::string getTitle() { return title; }
    
    void editDescription(std::string d) { description = d; }
    std::string getDescription() { return description; }

    virtual void addSubTask(std::string, std::string);
    virtual void addSubTask(std::string t) {addSubTask(t, "No Description");}
    virtual std::string getFullTask();
};

class SubTask : public Task{
  public:
    SubTask(std::string title, std::string desc) : Task(title, desc) {}

    virtual std::string getFullTask();
    virtual void addSubTask(std::string t, std::string d) { return; }
    virtual void addSubTask(std::string t) { return; }
};

#endif