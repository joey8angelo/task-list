#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <string>
#include <vector>

class Task;

class Date {
  private:
    bool isValidDate(int, int, int, int, int);  
    int getNumberOfDays(int, int);
    int getDayOfWeek(int, int, int);
    std::string formatMinute(int);
    std::vector<int> timeUntilDate();
  
  public:
    int year;
    int month;
    int day;
    int hour;
    int min;

    Date();
    Date(int, int, int, int, int);

    bool setDate(int, int, int, int h = -1, int min = -1);
    std::string getDateFormatted();
    std::string timeUntilDate(Task*);
    long int getDateInSeconds();
};

#endif