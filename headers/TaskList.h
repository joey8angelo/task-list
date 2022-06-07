#ifndef TASKLIST_H
#define TASKLIST_H

#include <string>
#include "Task.h"

class TaskList {
  private:
    bool compareTitle(Task*, Task*);
    bool compareDate(Task*, Task*);
    void swap(Task*, Task*);
    void swapHelper(Task*, Task*, Task*, Task*);
  public:
    Task* head;
    Task* tail;
    TaskList(): head(nullptr), tail(nullptr) {}
    ~TaskList();
    void pushBack(Task*);
    bool remove(Task*);
    bool softRemove(Task*);
    void printList();
    Task* getTask(std::string);
    void sortAlphabetically();
    void sortByDate();
};

#endif