#include "time.h"
#include <string>     // std::string, std::stoi

Time::Time(unsigned inputDay, unsigned inputHour, double inputMin):
    day {inputDay},
	hour{inputHour},
    min {inputMin}
{}

Time::Time(const std::string& input){
    double tempMin  = std::stoi(input.substr(3, 2));
    double tempSeconds = std::stoi(input.substr(6,  2)) / 60;
    min = tempMin + tempSeconds;
    hour = std::stoi(input.substr(0, 2));
}

bool Time::operator==(const Time &tOther) const {
    return day==tOther.getDay() && hour==tOther.getHour() && min==tOther.getMin();
}

Time operator+(const Time &t0, const Time &t1){
    unsigned
        newDay = t0.getDay() + t1.getDay(),
        newHour = t0.getHour() + t1.getHour();
    double newMin = t0.getMinSec() + t1.getMinSec();
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
    return {newDay, newHour, newMin};
}

Time operator-(const Time &t0, const Time &t1){
    unsigned
        newDay = t0.getDay() - t1.getDay(),
        newHour = t0.getHour() - t1.getHour();
    double newMin = t0.getMinSec() - t1.getMinSec();
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

template<template <class T> class Cmp>
bool cmpOpHelper(const Time &t0, const Time &t1) {
    if(Cmp{}(t0.getDay(), t1.getDay())) {return true;}
    else if(t0.getDay() == t1.getDay()) {
        if(Cmp{}(t0.getHour(), t1.getHour())) {return true;}
        else if(t0.getHour() == t1.getHour()) {
            return Cmp{}(t0.getMin(), t1.getMin());
        }
    }
    return false;
}

// ! only works if times in same week
bool operator>(const Time &t0, const Time &t1) {
    return cmpOpHelper<std::greater>(t0, t1);
}

bool operator<(const Time &t0, const Time &t1) {
    return cmpOpHelper<std::less>(t0, t1);
}
