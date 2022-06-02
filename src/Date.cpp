#include <iostream>
#include <vector>
#include "../headers/Date.h"
#include "../headers/Task.h"

bool Date::setDate(int y, int m, int d, int h, int min) {
    if (!isValidDate(y, m, d, h, min)) { return false; }
    
    this->year = y;
    this->month = m;
    this->day = d;
    this->hour = h;
    this->min = min;
    return true;
}

Date::Date() {
    std::time_t time = std::time(NULL);
    std::tm* localTime = localtime(&time);

    year = 1900 + localTime->tm_year;
    month = 1 + localTime->tm_mon;
    day = localTime->tm_mday;
    hour = localTime->tm_hour;
    min = localTime->tm_min;
}

Date::Date(int y, int m, int d, int h, int min) {
    this->year = y;
    this->month = m;
    this->day = d;
    this->hour = h;
    this->min = min;
}

std::vector<int> Date::timeUntilDate() {
    std::vector<int> vec;
    std::time_t time = std::time(NULL);
    std::tm* localTime = localtime(&time);

    vec.push_back(year - (1900 + localTime->tm_year));
    vec.push_back(month - (1 + localTime->tm_mon));
    vec.push_back(day -(localTime->tm_mday));
    if (hour == -1 || min == -1) {
        vec.push_back(-1);
        vec.push_back(-1);
    }
    else {
        vec.push_back(hour - (localTime->tm_hour));
        vec.push_back(min - (localTime->tm_min));
    }

    return vec;
}

int Date::getNumberOfDays(int y, int m) {
	if( m == 2)
	{
		if((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))	
			return 29;
		else	
			return 28;
	}
	else if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m==12)	
		return 31;
	else 		
		return 30;
}

bool Date::isValidDate(int y, int m, int d, int h, int min) {
    if (y <= 0) { return false; };
    if (m <= 0 || m > 12) { return false; }
    if (d <= 0 || d > getNumberOfDays(y, m)) { return false; }
    if (h == -1 || min == -1) { return true; }
    if (h < 0 || h > 24) { return false; }
    if (min < 0 || min > 60) { return false; }

    return true;
}

std::string Date::getDateFormatted() {
    std::string output = "";

    switch(getDayOfWeek(year, month, day)) {
      case 1:
        output += "Monday ";
        break;
      case 2:
        output += "Tuesday ";
        break;
      case 3:
        output += "Wednesday ";
        break;
      case 4:
        output += "Thursday ";
        break;
      case 5:
        output += "Friday ";
        break;
      case 6:
        output += "Saturday ";
        break;
      case 0:
        output += "Sunday ";
        break;
    }

    switch(month) {
      case 1:
        output += "January ";
        break;
      case 2:
        output += "February ";
        break;
      case 3:
        output += "March ";
        break;
      case 4:
        output += "April ";
        break;
      case 5:
        output += "May ";
        break;
      case 6:
        output += "June ";
        break;
      case 7:
        output += "July ";
        break;
      case 8:
        output += "August ";
        break;
      case 9:
        output += "September ";
        break;
      case 10:
        output += "October ";
        break;
      case 11:
        output += "November ";
        break;
      case 12:
        output += "December ";
        break;  
    }

    output += std::to_string(day) + " ";

    if (hour >= 12) {
        if (hour == 12) { output += std::to_string(hour) + ":" + formatMinute(min) + std::to_string(min) + "PM"; }
        
        else if (hour == 24) { output += std::to_string(hour - 12) + ":" + formatMinute(min) + std::to_string(min) + "AM"; }
        
        else { output += std::to_string(hour - 12) + ":" + formatMinute(min) + std::to_string(min) + "PM"; }
    }
    else if (hour == -1 && min == -1){
        output += std::to_string(year);
        return output;
    }
    else {
        output += std::to_string(hour) + ":" + formatMinute(min) + std::to_string(min) + "AM" + " " + std::to_string(year);;
    }
    return output;
}

std::string Date::formatMinute(int m) {
    if (m < 10) 
        return "0";
     else 
        return "";
}

int Date::getDayOfWeek(int y, int m, int d) {
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if ( m < 3 )
        y -= 1;
    
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

std::string Date::timeUntilDate(Task* task) {
    int amount;
    std::vector<int> TTD = task->date->timeUntilDate();
    std::string output = "";

    for (int i = 0; i < TTD.size(); i++) {

        amount = abs(TTD.at(i));

        if (TTD.at(i) < 0 && i == 0) {
            output += std::to_string(amount) + " year";
            
            if (amount != 1) { output += "s"; }
            
            output += " ago";
            break;
        }
        else if (TTD.at(i) > 0 && i == 0) {
            output +=  "In " + std::to_string(amount) + " year";
            
            if (amount != 1) { output += "s"; }
            break;
        }
        if (TTD.at(i) < 0 && i == 1) {
            output += std::to_string(amount) + " month";
            
            if (amount != 1) { output += "s"; }
            
            output += " ago";
            break;
        }
        else if (TTD.at(i) > 0 && i == 1) {;
            output +=  "In " + std::to_string(amount) + " month";
            
            if (amount != 1) { output += "s"; }
            break;
        }
        if (TTD.at(i) < 0 && i == 2) {
            output += std::to_string(amount) + " day";
            
            if (amount != 1) { output += "s"; }
            
            output += " ago";
            break;
        }
        else if (TTD.at(i) > 0 && i == 2) {
            output +=  "In " + std::to_string(amount) + " day";
            
            if (amount != 1) { output += "s"; }
            break;
        }

        if (TTD.at(i) == -1 && (i == 3 || i == 4)) { 
            output += "Today";
            break;
        } // if no time set

        if (TTD.at(i) < 0 && i == 3) {
            output += std::to_string(amount) + " hour";
            
            if (amount != 1) { output += "s"; }
            
            output += " ago";
            break;
        }
        else if (TTD.at(i) > 0 && i == 3) {
            output += "In " + std::to_string(amount) + " hour";
            
            if (amount != 1) { output += "s"; }
            break;
        }
        if (TTD.at(i) < 0 && i == 4) {
            output += std::to_string(amount) + " minute";
            
            if (amount != 1) { output += "s"; }
            
            output += " ago";
            break;
        }
        else if (TTD.at(i) > 0 && i == 4) {
            output += "In " + std::to_string(amount) + " minute";
            
            if (amount != 1) { output += "s "; }
            break;
        }
    }
    return output;
}

long int Date::getDateInSeconds() {
    long int output = 0;
    std::vector<int> vec = this->timeUntilDate();
    if (vec.at(4) == -1) {
        output += (60 * 60) + (23 * 3600); // equal to 00:00 on the next day
    }
    else {
        output += vec.at(4) * 60;   // desired output is number larger than any time on the same day
        output += vec.at(3) * 3600; // want to make dates with no time appear further down the list than timed counterpart
    }
    output += vec.at(2) * 86400;
    output += vec.at(1) * 86400 * getNumberOfDays(year, month);
    
    if (getNumberOfDays(year, 2) == 28)
        output += vec.at(0) * 365 * 86400;
    else
        output += vec.at(0) * 366 * 86400;

    return output;
}