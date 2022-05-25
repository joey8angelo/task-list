#ifndef TASK_H
#define TASK_H

#include <ctime>

class SubTask;
class Date;

#include "Date.h"

class Task {
  protected:
    std::string title;
    std::string description;

  public:
    Task* next;
    Task* prev;
    SubTask* subTask;
    Date* date;

    Task(std::string title, std::string desc) : title(title), description(desc), subTask(nullptr), next(nullptr), prev(nullptr), date(nullptr) {}
    ~Task();
    
    void editTitle(std::string t) { title = t; }
    std::string getTitle() { return title; }
    
    void editDescription(std::string d) { description = d; }
    std::string getDescription() { return description; }

    virtual void removeDate();
    virtual void addDate() { date = new Date; }
    virtual void removeSubTask();
    virtual void addSubTask(std::string, std::string);
    virtual void addSubTask(std::string t) {addSubTask(t, "");}
    virtual std::string getFullTask();
};

class SubTask : public Task{
  public:
    SubTask(std::string title, std::string desc) : Task(title, desc) {}

    std::string getFullTask();
    void addSubTask(std::string t, std::string d) { return; }
    void addSubTask(std::string t) { return; }
    void addDate() { return; }
    void removeDate() { return; }
    void removeSubTask() { return; }
};

#endif