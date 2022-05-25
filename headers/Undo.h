#ifndef UNDO_H
#define UNDO_H

#include "Task.h"

class Undo {
  public:
    Undo(Task* task) : task(task) {}
    Task* task;
    virtual void undo() = 0;
};

class editTask : public Undo {
  protected:
    std::string title;
    std::string desc;
  public:
    editTask(Task* task, std::string title, std::string desc) : Undo(task), title(title), desc(desc) {}
    void undo() {
        task->editTitle(title);
        task->editDescription(desc);
    }
};

class addNewDate : public Undo {
  public:
    addNewDate(Task* task) : Undo(task) {}
    void undo() {
        task->removeDate();
    }
};

class editDate : public Undo {
  protected:
    int year;
    int month;
    int day;
    int hour;
    int min;
  public:
    editDate(Task* task, int y, int m, int d, int h, int min) : 
             Undo(task), year(y), month(m), day(d), hour(h), min(min) {}
    void undo() {
        task->date->year = year;
        task->date->month = month;
        task->date->day = day;
        task->date->hour = hour;
        task->date->min = min;
    }
};

class removeDate : public editDate {
  public:
    removeDate(Task* task, int y, int m, int d, int h, int min) : 
               editDate(task, y, m, d, h, min) {}
    void undo() {
        task->addDate();
        task->date->year = year;
        task->date->month = month;
        task->date->day = day;
        task->date->hour = hour;
        task->date->min = min;
    }
};

class addNewSubtask : public Undo {
  public:
    addNewSubtask(Task* task) : Undo(task) {}
    void undo() {
        task->removeSubTask();
    }
};

class editSubtask : public Undo {
  protected:
    std::string title;
    std::string desc;
  public:
    editSubtask(Task* task, std::string title, std::string desc) : Undo(task), title(title), desc(desc) {}
    void undo() {
        task->subTask->editTitle(title);
        task->subTask->editDescription(desc);
    }
};

class removeSubtask : public editSubtask {
  public:
    removeSubtask(Task* task, std::string title, std::string desc) : editSubtask(task, title, desc) {}
    void undo() {
        task->subTask = new SubTask(title, desc);
    }
};

#endif