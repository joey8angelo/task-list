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

void TaskList::pushBack(std::string t, std::string d) {
    if (head == nullptr) {
        head = new Task(t, d);
        tail = head;
    }
    else if (head == tail) {
        head->next = new Task(t, d);
        tail = head->next;
        tail->prev = head;
    }
    else {
        Task* temp = tail;
        tail->next = new Task(t, d);
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

bool TaskList::remove(std::string t) {
    Task* curr = getTask(t);
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

void TaskList::sortAlphabetically() {
    Task* i;
    Task* j;
    if (head == nullptr) { return; }
    else if (head == tail) { return; }
    else if (head->next == tail) {
        if (compareTitle(tail, head)) {
            swap(tail, head);
        }
    } 
    else {
        i = head->next;
        while (i != nullptr) {
            j = i;
            while (j->prev != nullptr && compareTitle(j, j->prev)) {
                swap(j, j->prev);
                j = j->prev;
            }
            i = i->next;
        }

    }
}

bool TaskList::compareTitle(Task* r, Task* l) {
    if (r->getTitle() < l->getTitle()) { return true; }
    else {return false; }
}

void TaskList::sortByDate() {
    Task* i;
    Task* j;
    if (head == nullptr) { return; }
    else if (head == tail) { return; }
    else if (head->next == tail) {
        if (compareDate(tail, head)) {
            swap(tail, head);
        }
    } 
    else {
        i = head->next;
        while (i != nullptr) {
            j = i;
            while (j->prev != nullptr && compareDate(j, j->prev)) {
                swap(j, j->prev);
                j = j->prev;
            }
            i = i->next;
        }

    }
}

bool TaskList::compareDate(Task* r, Task* l) {
    if (l->date == nullptr) { return true; }
    if (r->date == nullptr) { return false; }

    if (r->date->getDateInSeconds() < l->date->getDateInSeconds()) { return true; }
    else { return false; }
}

void TaskList::swap(Task* r, Task* l) {
    std::string temp = r->getTitle();
    r->editTitle(l->getTitle());
    l->editTitle(temp);
    
    temp = r->getDescription();
    r->editDescription(l->getDescription());
    l->editDescription(temp);

    SubTask* tempT = r->subTask;
    r->subTask = l->subTask;
    l->subTask = tempT;

    Date* tempD = r->date;
    r->date = l->date;
    l->date = tempD;
}