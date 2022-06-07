#include "../headers/Undo.h"

void AddNewTask::undo() {
    list->remove(task);
}

void EditTask::undo() {
    task->editTitle(title);
    task->editDescription(desc);
}

void RemoveTask::undo() {
    list->pushBack(task);
    task = nullptr;
}

RemoveTask::~RemoveTask() { // RemoveTask is the only Undo that stores a pointer to a Task
    if (task != nullptr)    // that is not in the list, its deletion is not handled by TaskList anymore
        delete task;        // unless it gets put back in the list
}

void AddNewDate::undo() {
    task->removeDate();
}

void EditDate::undo() {
    task->date->year = year;
    task->date->month = month;
    task->date->day = day;
    task->date->hour = hour;
    task->date->min = min;
}

void RemoveDate::undo() {
    task->addDate();
    EditDate::undo();
}

void AddNewSubtask::undo() {
    task->removeSubTask();
}

void EditSubtask::undo() {
    task->subTask->editTitle(title);
    task->subTask->editDescription(desc);
}

void RemoveSubtask::undo() {
    task->subTask = new SubTask(title, desc);
}