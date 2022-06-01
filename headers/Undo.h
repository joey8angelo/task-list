#ifndef UNDO_H
#define UNDO_H

#include "Task.h"
#include "TaskList.h"

class Undo {
  public:
    Undo(Task* task) : task(task) {}
    Undo() {}
    Task* task;
    virtual void undo() = 0;
};

class AddNewTask : public Undo {
  private:
    TaskList* list;
  public:
    AddNewTask(Task* task, TaskList* list) : Undo(task), list(list) {}
    void undo();
};

class EditTask : public Undo {
  protected:
    std::string title;
    std::string desc;
  public:
    EditTask(Task* task, std::string title, std::string desc) : Undo(task), title(title), desc(desc) {}
    void undo();
};

class RemoveTask : public Undo {
  private:
    TaskList* list;
    Task t;
  public:
    RemoveTask(Task* task, TaskList* list) : t(*task), list(list) {}
    ~RemoveTask();
    void undo();
};

class AddNewDate : public Undo {
  public:
    AddNewDate(Task* task) : Undo(task) {}
    void undo();
};

class EditDate : public Undo {
  protected:
    int year;
    int month;
    int day;
    int hour;
    int min;
  public:
    EditDate(Task* task, int y, int m, int d, int h, int min) : 
             Undo(task), year(y), month(m), day(d), hour(h), min(min) {}
    void undo();
};

class RemoveDate : public EditDate {
  public:
    RemoveDate(Task* task, int y, int m, int d, int h, int min) : 
               EditDate(task, y, m, d, h, min) {}
    void undo();
};

class AddNewSubtask : public Undo {
  public:
    AddNewSubtask(Task* task) : Undo(task) {}
    void undo();
};

class EditSubtask : public Undo {
  protected:
    std::string title;
    std::string desc;
  public:
    EditSubtask(Task* task, std::string title, std::string desc) : Undo(task), title(title), desc(desc) {}
    void undo();
};

class RemoveSubtask : public EditSubtask {
  public:
    RemoveSubtask(Task* task, std::string title, std::string desc) : EditSubtask(task, title, desc) {}
    void undo();
};

#endif