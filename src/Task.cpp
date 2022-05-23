#include <iostream>
#include "../headers/Task.h"
#include "../headers/Date.h"

Task::~Task() {
    if (this->subTask != nullptr) { 
        delete this->subTask; 
    }
    if (this->date != nullptr) { 
        delete this->date; 
    }
}

std::string Task::getFullTask() {
    std::string output = "Title: " + title;
    if (description != "") { output += "\nDescription: " + description; }
    if (this->subTask != nullptr) { output += "\n" + this->subTask->getFullTask(); }
    if (this->date != nullptr) {
        output += "\n" + this->date->getDateFormatted();
        output += "\n" + this->date->timeUntilDate(this); 
    }
    return output;
}

void Task::addSubTask(std::string title, std::string description) {
    this->subTask = new SubTask(title, description);
}

void Task::removeDate() {
    delete date;
    this->date = nullptr;
}

void Task::removeSubTask() {
    delete subTask;
    this->subTask = nullptr;
}