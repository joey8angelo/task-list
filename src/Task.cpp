#include <iostream>
#include "../headers/Task.h"

std::string Task::get_full_task() {
    if (this->subTask == nullptr)
        return "Title: " + title + "\nDescription: " + description;
    else
        return "Title: " + title + "\nDescription: " + description + "\nSubask: " + this->subTask->get_title();
}