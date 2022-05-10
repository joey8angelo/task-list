#include <iostream>
#include "../headers/SubTask.h"

std::string SubTask::get_full_task() {
    return "Title: " + title + "\nDescription: " + description;
}