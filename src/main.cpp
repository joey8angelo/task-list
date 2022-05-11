#include <iostream>
#include "../headers/TaskList.h"

int main () {
    TaskList j;
    j.pushBack("Do Homework");
    j.pushBack("Feed Dog");
    j.pushBack("test");
    j.pushBack("hello", "test");
    j.getTask("Do Homework")->addSubTask("Do Coding assignment for cs 1500", "This assignment will be really hard I think");
    j.printList();
}