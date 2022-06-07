#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include "../headers/TaskList.h"
#include "../headers/Task.h"
#include "../headers/Undo.h"

using std::cout;
using std::cin;
using std::endl;

void insertTask();
void removeTask();
void addSubtask();
void printList();
void edit();
void addDate();
void undo();
void insertVec(Undo*);
bool saveData();
bool loadData();

/* Global variables for the ease of not having to pass them through every function */
TaskList list;
std::vector<Undo*> undoVec;

int main () {
    int input = 1;
    std::string title;
    std::string subTitle;
    Task* curr;

	if (!loadData()) { return 1; }

    while (input != 0) {
        saveData();

        /* This clears the terminal */
        cout << "\033[2J\033[1;1H";
        cout << "Task List Menu\nEnter \"1\" to insert a new task" << endl;
        cout << "Enter \"2\" to remove a task" << endl;
        cout << "Enter \"3\" to add a subtask to a task" << endl;
        cout << "Enter \"4\" to set a tasks date" << endl;
        cout << "Enter \"5\" to print the list" << endl;
        cout << "Enter \"6\" to edit a task" << endl;
        cout << "Enter \"7\" to sort the list in alphabetical order" << endl;
        cout << "Enter \"8\" to sort the list in chronological order" << endl;
        cout << "Enter \"9\" to undo" << endl;
        cout << "Enter \"0\" to quit\n: ";
        
        /* invalid input will get cleared */
        cin >> input;
        cin.clear();
        cin.ignore(10000,'\n');

        switch(input) {
          case 1:
            insertTask();
            break;

          case 2:
            removeTask();
            break;

          case 3:
            addSubtask();
            break;

          case 4:
            addDate();
            break;

          case 5:
            printList();
            break;

          case 6:
            edit();
            break;

          case 7:
            list.sortAlphabetically();
            break;
          
          case 8:
            list.sortByDate();
            break;
          
          case 9:
            undo();
            break;

          default:
            input = 0;
            while (!undoVec.empty()) {
                delete undoVec.at(input);
                undoVec.erase(undoVec.begin());
            }
            break;
        }
    }
}

void insertTask() {
    std::string title;

    cout << "\033[2J\033[1;1H";
    cout << "Insert Task" << endl << endl;
    cout << "Enter the title for this task: ";

    std::getline(cin, title);
    list.pushBack(new Task(title));
    insertVec(new AddNewTask(list.getTask(title), &list)); // insert undo object input insertVec
}

void removeTask() {
    std::string title;

    cout << "\033[2J\033[1;1H";
    cout << "Remove Task" << endl << endl;
    cout << "Enter the name of the task to remove: ";

    std::getline(cin, title);
    Task* temp = list.getTask(title);

    if (temp != nullptr) {
        insertVec(new RemoveTask(temp, &list)); // RemoveTask undo object cannot take nullptr as a parameter
        list.softRemove(temp);
    }
    else {
        cout << "\033[2J\033[1;1H";
        cout << "Remove a Task" << endl << endl;
        cout << "Could not find task named \"" << title << "\"\nExiting Remove Task..." << endl;
        std::this_thread::sleep_for (std::chrono::seconds(3));
    }
}

void addSubtask(){
    std::string title;
    std::string subTitle;
    Task* curr;

    cout << "\033[2J\033[1;1H";
    cout << "Add Subtask" << endl << endl;
    cout << "Enter the name of the task to add a subtask to: ";
    std::getline(cin, title);

    cout << "\033[2J\033[1;1H";
    cout << "Add Subtask" << endl << endl;
    curr = list.getTask(title);

    if (curr == nullptr) {
        cout << "Could not find task with the name \"" << title << "\"\nExiting Add Subtask..." << endl;
        std::this_thread::sleep_for (std::chrono::seconds(3));
        return;
    }

    insertVec(new AddNewSubtask(curr));
    cout << "Task: " << title << endl;
    cout << "Enter the name of the subtask: ";

    std::getline(cin, subTitle);
    curr->addSubTask(subTitle);
}

void printList() {
    std::string voidInput;

    cout << "\033[2J\033[1;1H";
    cout << "Print List" << endl << endl;
    list.printList();

    cout << "Enter \"q\"to exit: ";
    std::getline(cin, voidInput); // do nothing
}

void edit() {
    std::string title;
    int input;
    Task* curr;

    cout << "\033[2J\033[1;1H";
    cout << "Edit Task" << endl << endl;
    cout << "Enter the name of the task: ";
    std::getline(cin, title);

    cout << "\033[2J\033[1;1H";
    cout << "Edit Task" << endl << endl;
    curr = list.getTask(title);

    if (curr == nullptr) {
        cout << "Could not find task with the name \"" << title << "\"\nExiting Edit Task..." << endl;
        std::this_thread::sleep_for (std::chrono::seconds(3));
        return;
    }
    
    cout << "\033[2J\033[1;1H";
    cout << "Edit " << title << endl << endl;
    cout << "Enter \"1\" to edit the title" << endl;
    cout << "Enter \"2\" to edit the description" << endl;
    if (curr->getDescription() != "") {
        cout << "Enter \"3\" to remove the description" << endl;
    }
    if (curr->date != nullptr) {
        cout << "Enter \"4\" to remove the date" << endl;
    }
    if (curr->subTask != nullptr) {
        cout << "Enter \"5\" to edit the subtask" << endl;
        cout << "Enter \"6\" to remove the subtask" << endl;
    }

    cout << ": ";
    cin >> input;
    cin.clear();
    cin.ignore(10000,'\n');

    switch (input) {
      case 1:
        insertVec(new EditTask(curr, title, curr->getDescription()));
        cout << "\033[2J\033[1;1H";
        cout << "Edit " << title << endl << endl;
        cout << "Enter the new title: ";
        getline(cin, title);
        curr->editTitle(title);
                    
        return;

      case 2:
        insertVec(new EditTask(curr, title, curr->getDescription()));
        cout << "\033[2J\033[1;1H";
        cout << "Edit " << title << endl << endl;
        cout << "Enter the new description: ";
        getline(cin, title);
        curr->editDescription(title);

        return;

      case 3:
        if (curr->getDescription() == "") { return; }
        insertVec(new EditTask(curr, title, curr->getDescription()));
        curr->editDescription("");
        
        return;

      case 4:
        if (curr->date == nullptr) { return; }
        insertVec(new RemoveDate(curr, curr->date->year, curr->date->month, 
                                 curr->date->day, curr->date->hour, curr->date->min));
        curr->removeDate();

        return;

      case 5:
        if (curr->subTask == nullptr) { return; }

        insertVec(new EditSubtask(curr->subTask, curr->subTask->getTitle(), curr->subTask->getDescription()));

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

      case 6:
        if (curr->subTask == nullptr) { return; }
        insertVec(new RemoveSubtask(curr, curr->subTask->getTitle(), curr->subTask->getDescription()));
        curr->removeSubTask();

        return;

      default:
        return;
    }          
}

void addDate() {
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
    curr = list.getTask(title);

    if (curr == nullptr) {
        cout << "Could not find task with the name \"" << title << "\"\nExiting Set Date..." << endl;
        std::this_thread::sleep_for (std::chrono::seconds(3));
        return;
    }
    if (curr->date == nullptr) {
        insertVec(new AddNewDate(curr));
        curr->addDate();
    }else {
        insertVec(new EditDate(curr, curr->date->year, curr->date->month, 
                               curr->date->day, curr->date->hour, curr->date->min));
    }

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
            undo();
            cout << "Invalid date\nExiting Set Date..." << endl;
            std::this_thread::sleep_for (std::chrono::seconds(3));
            return;
        }
        return;
    }
    else {
        bool date = curr->date->setDate(y, m, d);

        if (!date) {
            undo();
            cout << "Invalid date\nExiting Set Date..." << endl;
            std::this_thread::sleep_for (std::chrono::seconds(3));
            return;
        }
        return;
    }
}

void undo() {
    int vecSize = undoVec.size();
    
    if (vecSize == 0) {
        cout << "Cannot undo further" << endl;
        std::this_thread::sleep_for (std::chrono::seconds(2));
        return;
    }
    else { // call undo on Undo object, then delete it
        undoVec.at(vecSize - 1)->undo();
        delete undoVec.at(vecSize - 1);
        undoVec.erase(undoVec.end() - 1);
    } 
}

void insertVec(Undo* undoObj) {
    if (undoVec.size() > 10) { // only undo up to 10 times, arbitrarily chosen
        delete undoVec.at(0);
        undoVec.erase(undoVec.begin());
    }
    undoVec.push_back(undoObj);
}

bool saveData() {
	std::ofstream fout;
	Task* curr = list.head;
	
	fout.open("../data.csv");

	if (!fout.is_open()) {
		return false;
	}

  /* traverse through list, write task, date, subtask to data.csv */
	while (curr != nullptr) {
		fout << "task," << curr->getTitle() << "," << curr->getDescription() << "\n";
		if (curr->date != nullptr) {
			fout << "date," << std::to_string(curr->date->year) << "," << std::to_string(curr->date->month) << "," 
			                << std::to_string(curr->date->day) << "," << std::to_string(curr->date->hour) << "," << std::to_string(curr->date->min) << "\n";
		}
		if (curr->subTask != nullptr) {
			fout << "subtask," << curr->subTask->getTitle() << "," << curr->subTask->getDescription() << "\n";
		}
		curr = curr->next;
	}
	fout.close();
	return true;
}

bool loadData() {
	std::ifstream fin;
	std::string line, word;
	std::vector<std::string> vec;

	fin.open("../data.csv");

	if (!fin.is_open()) {
		return false;
	}

  /* store each word of a line in vector. Depending on the type, specified by the first word will push to back of list
  task,title,description
  date,year,month,day,hour,minute
  subtask,title,description */
	while (std::getline(fin, line)) {
		vec.clear();

		word = "";
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == ',') {
				vec.push_back(word);
				word = "";
			}
			else
				word += line[i];
		}
		vec.push_back(word);

		if (vec.at(0) == "task") {
			list.pushBack(new Task(vec.at(1), vec.at(2)));
		}
		else if (vec.at(0) == "date") {
			int y, m, d, h, min;
			y = atoi(vec.at(1).c_str());
			m = atoi(vec.at(2).c_str());
			d = atoi(vec.at(3).c_str());
			h = atoi(vec.at(4).c_str());
			min = atoi(vec.at(5).c_str());
			list.tail->date = new Date(y, m, d, h, min);
		}
		else if (vec.at(0) == "subtask") {
		    list.tail->subTask = new SubTask(vec.at(1), vec.at(2));
		}
	}
	return true;
}

