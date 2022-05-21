#include <iostream>
#include "../headers/Task.h"

std::string SubTask::getFullTask() {
    std::string output = "\tTitle: " + title;
    if (description != "") { output += "\n\tDescription: " + description; }
    return output;
}