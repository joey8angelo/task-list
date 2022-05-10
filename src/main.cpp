#include <iostream>
#include "../headers/TaskList.h"

int main () {
    TaskList j;
    j.push_back("Do Homework", "Finish coding assignent 3 for CS 1500");
    j.push_back("Feed Dog");
    j.push_back("test");
    j.push_back("hello", "test");
    j.printList();
}