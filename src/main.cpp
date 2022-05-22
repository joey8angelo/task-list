#include <iostream>
#include <thread>
#include <chrono>
#include <bits/stdc++.h>
#include "../headers/TaskList.h"
#include "../headers/Task.h"

using std::cout;
using std::cin;
using std::endl;

void insertTask(TaskList*);
void removeTask(TaskList*);
void addSubtask(TaskList*);
void printList(TaskList*);
void editTask(TaskList*);
void addDate(TaskList*);

int main () {
    int input = 1;
    std::string title;
    std::string subTitle;
    TaskList list;
    Task* curr;

    while (input != 0) {
        cout << "\033[2J\033[1;1H";
        cout << "Task List Menu\nEnter \"1\" to insert a new task" << endl;
        cout << "Enter \"2\" to remove a task" << endl;
        cout << "Enter \"3\" to add a subtask to a task" << endl;
        cout << "Enter \"4\" to print the list" << endl;
        cout << "Enter \"5\" to sort the list in alphabetical order" << endl;
        cout << "Enter \"6\" to edit a task" << endl;
        cout << "Enter \"7\" to set a tasks date" << endl;
        cout << "Enter \"8\" to sort the list in chronological order" << endl;
        cout << "Enter \"0\" to quit\n: ";
        cin >> input;
        cin.clear();
        cin.ignore(10000,'\n');

        switch(input) {
          case 0:
            break;

          case 1:
            insertTask(&list);
            break;

          case 2:
            removeTask(&list);
            break;

          case 3:
            addSubtask(&list);
            break;

          case 4:
            printList(&list);
            break;

          case 5:
            list.sortAlphabetically();
            break;

          case 6:
            editTask(&list);
            break;

          case 7:
            addDate(&list);
            break;
          case 8:
            list.sortByDate();
            break;
            
          default:
            break;
        }
    }
}

void insertTask(TaskList* list) {
    std::string title;

    cout << "\033[2J\033[1;1H";
    cout << "Insert Task" << endl << endl;
    cout << "Enter the title for this task: ";
    std::getline(cin, title);
    list->pushBack(title);
}

void removeTask(TaskList* list) {
    std::string title;

    cout << "\033[2J\033[1;1H";
    cout << "Remove Task" << endl << endl;
    cout << "Enter the name of the task to remove: ";
    std::getline(cin, title);
    if (!(list->remove(title))) {
        cout << "\033[2J\033[1;1H";
        cout << "Remove a Task" << endl << endl;
        cout << "Could not find task named \"" << title << "\"\nExiting Remove Task..." << endl;
        std::this_thread::sleep_for (std::chrono::seconds(3));
    }
}

void addSubtask(TaskList* list){
    std::string title;
    std::string subTitle;
    Task* curr;

    cout << "\033[2J\033[1;1H";
    cout << "Add Subtask" << endl << endl;
    cout << "Enter the name of the task to add a subtask to: ";
    std::getline(cin, title);
    cout << "\033[2J\033[1;1H";
    cout << "Add Subtask" << endl << endl;
    curr = list->getTask(title);

    if (curr == nullptr) {
        cout << "Could not find task with the name \"" << title << "\"\nExiting Add Subtask..." << endl;
        std::this_thread::sleep_for (std::chrono::seconds(3));
        return;
    }

    cout << "Task: " << title << endl;
    cout << "Enter the name of the subtask: ";
    std::getline(cin, subTitle);
    curr->addSubTask(subTitle);
}

void printList(TaskList* list) {
    std::string voidInput;

    cout << "\033[2J\033[1;1H";
    cout << "Print List" << endl << endl;
    list->printList();
    cout << "Enter \"q\"to exit: ";
    std::getline(cin, voidInput); // do nothing
}

void editTask(TaskList* list) {
    std::string title;
    int input;
    Task* curr;

    cout << "\033[2J\033[1;1H";
    cout << "Edit Task" << endl << endl;
    cout << "Enter the name of the task: ";
    std::getline(cin, title);
    cout << "\033[2J\033[1;1H";
    cout << "Edit Task" << endl << endl;
    curr = list->getTask(title);
    if (curr == nullptr) {
        cout << "Could not find task with the name \"" << title << "\"\nExiting Edit Task..." << endl;
        std::this_thread::sleep_for (std::chrono::seconds(3));
        return;
    }
    
    cout << "\033[2J\033[1;1H";
    cout << "Edit " << title << endl << endl;
    cout << "Enter \"1\" to edit the title" << endl;
    cout << "Enter \"2\" to edit the description" << endl;
    cout << "Enter \"3\" to remove the description" << endl;
    cout << "Enter \"4\" to remove the date" << endl;
    if (curr->subTask != nullptr) {
        cout << "Enter \"5\" to edit the subtask" << endl;
    }
    cout << ": ";
    cin >> input;
    cin.clear();
    cin.ignore(10000,'\n');

    switch (input) {
      case 1:
        cout << "\033[2J\033[1;1H";
        cout << "Edit " << title << endl << endl;
        cout << "Enter the new title: ";
        getline(cin, title);
        curr->editTitle(title);
                    
        return;

      case 2:
        cout << "\033[2J\033[1;1H";
        cout << "Edit " << title << endl << endl;
        cout << "Enter the new description: ";
        getline(cin, title);
        curr->editDescription(title);

        return;

      case 3:
        curr->editDescription("");
        break;

      case 4:
        curr->removeDate();

      case 6:
        if (curr->subTask == nullptr) { return; }
        cout << "\033[2J\033[1;1H";
        cout << "Edit " << curr->subTask->getTitle() << endl << endl;
        cout << "Enter \"1\" to edit the subtasks title" << endl;
        cout << "Enter \"2\" to edit the subtasks description" << endl;
        cout << ": ";
        cin >> input;
        cin.clear();
        cin.ignore(10000,'\n');
                    
        switch (input) {
          case 1:
            cout << "\033[2J\033[1;1H";
            cout << "Edit " << curr->subTask->getTitle() << endl << endl;
            cout << "Enter the new title: ";
            getline(cin, title);
            curr->subTask->editTitle(title);
                    
            return;

          case 2:
            cout << "\033[2J\033[1;1H";
            cout << "Edit " << curr->subTask->getTitle() << endl << endl;
            cout << "Enter the new description: ";
            getline(cin, title);
            curr->subTask->editDescription(title);

            return;

          default:
            return;
        }
      default:
        break;
    }          
}

void addDate(TaskList* list) {
    std::string input;
    std::string title;
    Task* curr;
    int y, m, d, h, min;

    cout << "\033[2J\033[1;1H";
    cout << "Set Date" << endl << endl;
    cout << "Enter the name of the task: ";
    std::getline(cin, title);
    cout << "\033[2J\033[1;1H";
    cout << "Set Date" << endl << endl;
    curr = list->getTask(title);

    if (curr == nullptr) {
        cout << "Could not find task with the name \"" << title << "\"\nExiting Set Date..." << endl;
        std::this_thread::sleep_for (std::chrono::seconds(3));
        return;
    }
    if (curr->date == nullptr) { curr->addDate(); }

    cout << "\033[2J\033[1;1H";
    cout << "Set Date" << endl;
    cout << "Enter Date in form MM/DD/YYYY: ";
    cin >> input;
    m = atoi(input.substr(0, 2).c_str());
    d = atoi(input.substr(3, 4).c_str());
    y = atoi(input.substr(6, 9).c_str());

    cout << "\033[2J\033[1;1H";
    cout << "Add Date" << endl;
    cout << "Date: " + std::to_string(m) + "/" + std::to_string(d) + "/" + std::to_string(y) << endl;
    cout << "Would you like to enter a time(Y/N): ";
    cin >> input;

    if (std::toupper(input[0]) == 'Y') {
        cout << "\033[2J\033[1;1H";
        cout << "Date: " + std::to_string(m) + "/" + std::to_string(d) + "/" + std::to_string(y) << endl;
        cout << "Enter time in format HH:MM(24 hour clock): ";
        cin >> input;

        h = atoi(input.substr(0, 2).c_str());
        min = atoi(input.substr(3, 4).c_str());

        bool date = curr->date->setDate(y, m, d, h, min);

        if (!date) {
            curr->removeDate();
            cout << "Invalid date\nExiting Set Date..." << endl;
            std::this_thread::sleep_for (std::chrono::seconds(3));
            return;
        }
        return;
    }
    else {
        bool date = curr->date->setDate(y, m, d);
        if (!date) {
            curr->removeDate();
            cout << "Invalid date\nExiting Set Date..." << endl;
            std::this_thread::sleep_for (std::chrono::seconds(3));
            return;
        }
        return;
    }
}