#include <iostream>
#include "../headers/TaskList.h"

TaskList::~TaskList() {
    while (head != nullptr) {
        Task* curr = head;
        head = head->next;
        delete curr;
    }
    head = nullptr;
    tail = nullptr;
}

void TaskList::pushBack(Task* task) {
    if (head == nullptr) { // 0
        head = task;
        tail = head;
    }
    else if (head == tail) { // 1
        head->next = task;
        tail = head->next;
        tail->prev = head;
    }
    else { // 2+
        Task* temp = tail;
        tail->next = task;
        tail = tail->next;
        tail->prev = temp;
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
    return curr;
}

bool TaskList::remove(Task* curr) {
    if (curr == nullptr) { return false; }
    if (curr == head) {
        if (head == tail) {
            head = nullptr;
            tail = head;
            delete curr;
        }
        else {
            head = head->next;
            delete curr;
            head->prev = nullptr;
        }
    }
    else if (curr == tail) {
        tail = curr->prev;
        tail->next = nullptr;
        delete curr;
    }
    else {
        Task* prev = curr->prev;
        prev->next = curr->next;
        prev->next->prev = prev;
        delete curr;
    }
    return true;
}

/* insertion sort */
void TaskList::sortAlphabetically() {
    Task* i;
    Task* j;
    if (head == nullptr) { return; }
    else if (head == tail) { return; }
    else if (head->next == tail) {
        if (compareTitle(tail, head)) {
            swap(head, tail); // (l, r)
        }
    } 
    else {
        i = head->next;
        while (i != nullptr) {
            j = i;
            while (j->prev != nullptr && compareTitle(j, j->prev)) {
                swap(j->prev, j); // (l, r)
            }
            i = i->next;
        }

    }
}

void TaskList::sortByDate() {
    Task* i;
    Task* j;
    if (head == nullptr) { return; }
    else if (head == tail) { return; }
    else if (head->next == tail) {
        if (compareDate(tail, head)) {
            swap(head, tail); // (l, r)
        }
    } 
    else {
        i = head->next;
        while (i != nullptr) {
            j = i;
            while (j->prev != nullptr && compareDate(j, j->prev)) {
                swap(j->prev, j); // (l, r)
            }
            i = i->next;
        }

    }
}

bool TaskList::compareTitle(Task* r, Task* l) {
    if (r->getTitle() < l->getTitle()) { return true; }
    else {return false; }
}

bool TaskList::compareDate(Task* r, Task* l) {
    if (l->date == nullptr && r->date == nullptr) { return false; } // tasks with on date are "larger" than dated tasks
    if (l->date == nullptr) { return true; }
    if (r->date == nullptr) { return false; }

    if (r->date->getDateInSeconds() < l->date->getDateInSeconds()) { return true; }
    else { return false; }
}

/* get left, right, left previous, and right next to swap pointers */
void TaskList::swap(Task* l, Task* r) {
    if (l == head) {
        swapHelper(l, r, nullptr, r->next);
        head = r;
    }
    else if (r == tail) {
        swapHelper(l ,r, l->prev, nullptr);
        tail = l;
    }
    else {
        swapHelper(l, r, l->prev, r->next);
    }
}

void TaskList::swapHelper(Task* l, Task* r, Task* ll, Task* rr) {
    r->next = l;
    r->prev = ll;
    l->next = rr;
    l->prev = r;
    if (ll != nullptr) { ll->next = r; }
    if (rr != nullptr) { rr->prev = l; }
}