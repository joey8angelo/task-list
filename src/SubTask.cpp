#include <iostream>
#include "../headers/Task.h"

std::string SubTask::getFullTask() {
    return "\tTitle: " + title + "\n\tDescription: " + description;
}