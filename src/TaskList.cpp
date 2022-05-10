#include <iostream>
#include "../headers/TaskList.h"
#include "../headers/Task.h"
#include "../headers/SubTask.h"

void TaskList::push_back(std::string t, std::string d) {
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
        std::cout << curr->get_full_task() << std::endl;
    }
}