#include "time.h"
#include <string>     // std::string, std::stoi

Time::Time(){
    day = 0;
	hour = 0;
	min = 0;
}

Time::Time(int inputDay, int inputHour, int inputMin){
    day = inputDay;
	hour = inputHour;
    min = inputMin;
}

Time::Time(const std::string& input){
    double tempMin  = std::stoi(input.substr(3, 2));
    double tempSeconds = std::stoi(input.substr(6,  2)) / 60;
    min = tempMin + tempSeconds;
    hour = std::stoi(input.substr(0, 2));
}


Time Time::operator + (Time& xTime){
    unsigned int newDay = day+xTime.getDay();
    unsigned int newHour = hour+xTime.getHour();
    double newMin = min+xTime.getMinSec();
    if(newMin >= 60.0){
        newHour++;
        newMin -= 60;
    }
    if(newHour >= 24){
        newDay++;
        newHour -= 24;
    }
    if(newDay >= 7){
        newDay -= 7;
    }
    return Time(newDay, newHour, newMin);
}

// object - xTime
Time Time::operator - (Time& xTime){
    unsigned int newDay = day-xTime.getDay();
    unsigned int newHour = hour-xTime.getHour();
    double newMin = min-xTime.getMinSec();
    if(newMin < 0){
        newHour--;
        newMin += 60;
    }
    if(newHour < 0){
        newDay--;
        newHour += 24;
    }
    if(newDay < 0){
        newDay += 7;
    }
    return Time(newDay, newHour, newMin);
}

// object > xTime
// ! only works if times in same week
bool Time::operator > (Time& xTime){
    if(day > xTime.getDay()){return true;}
    else if(day == xTime.getDay()){

        if(hour > xTime.getHour()){return true;}
        else if(hour == xTime.getHour()){

            return (min > xTime.getMin());
        }
    }
    return false;
}

bool Time::operator == (Time& xTime){
    return day==xTime.getDay() && hour==xTime.getHour() && min==xTime.getMin();
}