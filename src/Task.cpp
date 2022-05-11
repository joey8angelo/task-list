#include <iostream>
#include "../headers/Task.h"
#include "../headers/SubTask.h"

std::string Task::getFullTask() {
    if (this->subTask == nullptr)
        return "Title: " + title + "\nDescription: " + description;
    else
        return "Title: " + title + "\nDescription: " + description + "\n" + this->subTask->getFullTask();
}

void Task::addSubTask(std::string title, std::string description) {
    this->subTask = new SubTask(title, description);
}