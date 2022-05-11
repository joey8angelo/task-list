#include <iostream>
#include "../headers/SubTask.h"

std::string SubTask::getFullTask() {
    return "\tTitle: " + title + "\n\tDescription: " + description;
}