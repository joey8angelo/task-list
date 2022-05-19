#ifndef TASKLIST_H
#define TASKLIST_H

#include <iostream>
#include "Task.h"

class TaskList {
  private:
    bool compareTitle(Task*, Task*);
    void swap(Task*, Task*);
  public:
    Task* head;
    Task* tail;
    TaskList(): head(nullptr), tail(nullptr) {}
    ~TaskList() {
        while (head != nullptr) {
            Task* curr = head;
            head = head->next;
            if (curr->subTask != nullptr) { delete curr->subTask; }
            delete curr;
        }
        head = nullptr;
        tail = nullptr;
    }
    void pushBack(std::string, std::string);
    void pushBack(std::string t) { pushBack(t, "No Description"); }
    bool remove(std::string);
    void printList();
    Task* getTask(std::string);
    void sortAlphabetically();
};

#endif