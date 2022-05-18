#include <iostream>
#include "../headers/TaskList.h"

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
    Task* curr = head;

    while (curr != nullptr) {
        std::cout << curr->getFullTask() << std::endl << std::endl;
        curr = curr->next;
    }
}

Task* TaskList::getTask(std::string title) {
    Task* curr = head;

    while (curr != nullptr) {
        if (curr->getTitle() == title)
            return curr;
        else
            curr = curr->next;
    }
    return nullptr;
}

bool TaskList::remove(std::string t) {
    Task* curr = getTask(t);
    if (curr == nullptr) { return false; }
    if (curr->subTask != nullptr) {
        delete curr->subTask;
    }
    if (curr == head) {
        if (head == tail) {
            head = nullptr;
            tail = head;
            delete curr;
        }
        else {
            head = head->next;
            delete curr;
        }
    }
    else if (curr == tail) {
        delete curr;
        curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        tail = curr;
    }
    else {
        Task* prev = head;
        while (prev->next != curr) {
            prev = prev->next;
        }
        prev->next = curr->next;
        delete curr;
    }
    return true;
}