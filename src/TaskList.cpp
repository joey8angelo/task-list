#include <iostream>
#include "../headers/TaskList.h"
#include "../headers/Task.h"
#include "../headers/SubTask.h"

void TaskList::pushBack(std::string t, std::string d) {
    if (head == nullptr) {
        head = new Task(t, d);
        tail = head;
    }
    else if (head == tail) {
        head->next = new Task(t, d);
        tail = head->next;
    }
    else {
        tail->next = new Task(t, d);
        tail = tail->next;
    }
}

void TaskList::printList() {
    TaskType* curr = head;

    while (curr != nullptr) {
        std::cout << curr->getFullTask() << std::endl << std::endl;
        curr = curr->next;
    }
}

TaskType* TaskList::getTask(std::string title) {
    TaskType* curr = head;

    while (curr != nullptr) {
        if (curr->getTitle() == title) {
            return curr;
        }
    }
    return curr;
}