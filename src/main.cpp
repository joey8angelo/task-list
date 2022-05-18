#include <iostream>
#include <thread>
#include <chrono>
#include <bits/stdc++.h>
#include "../headers/TaskList.h"
#include "../headers/Task.h"

using std::cout;
using std::cin;
using std::endl;
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
        cout << "Enter \"0\" to quit\n: "; 
        cin >> input;

        switch(input) {
          case 0:
            break;
          case 1:
            cout << "\033[2J\033[1;1H";
            cout << "Insert Task" << endl << endl;;
            cout << "Enter the title for this task: ";
            cin >> title;
            list.pushBack(title);
            break;
          case 2:
            cout << "\033[2J\033[1;1H";
            cout << "Remove a Task" << endl << endl;
            cout << "Enter the name of the task to remove: ";
            cin >> title;
            if (!(list.remove(title))) {
                cout << "\033[2J\033[1;1H";
                cout << "Remove a Task" << endl << endl;
                cout << "Could not find task named \"" << title << "\"\nExiting..." << endl;
                std::this_thread::sleep_for (std::chrono::seconds(3));
            }
            else {
                cout << "\033[2J\033[1;1H";
                cout << "Remove a Task" << endl << endl;
                cout << "Removed \"" << title << "\" Exiting..." << endl;
                std::this_thread::sleep_for (std::chrono::seconds(3));
            }

            break;
          case 3:
            cout << "\033[2J\033[1;1H";
            cout << "Add Subtask" << endl << endl;
            cout << "Enter the name of the task to add a subtask to: ";
            cin >> title;
            cout << "\033[2J\033[1;1H";
            cout << "Add Subtask" << endl << endl;

            curr = list.getTask(title);
            if (curr == nullptr) {
                cout << "Could not find task with the name \"" << title << "\"\nExiting..." << endl;
                std::this_thread::sleep_for (std::chrono::seconds(3));
                break;
            }

            cout << "Task: " << title << endl;
            cout << "Enter the name of the subtask: ";
            cin >> subTitle;
            curr->addSubTask(subTitle);
            cout << "Added subtask \"" << subTitle << "\" to task \"" << title << "\"\nExiting..." << endl;
            std::this_thread::sleep_for (std::chrono::seconds(3));

            break;
          case 4:
            cout << "\033[2J\033[1;1H";
            cout << "Print List" << endl << endl;
            list.printList();
            cout << "Enter \"q\"to exit: ";
            cin >> title; // do nothing
            break;
          default:
            break;
        }
    }
}