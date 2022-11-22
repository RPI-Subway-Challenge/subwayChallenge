#include <string>     // std::string, std::stoi
#include <algorithm>
#include "time.h"

using namespace std::chrono;

Time::Time(const std::string& input):
    timeOfDay{
        hours{std::stoi(input.substr(0, 2))} +
        minutes{std::stoi(input.substr(3, 2))} +
        seconds{std::stoi(input.substr(6, 2))}
    }
{}

Time::Time(weekday day, duration<unsigned> timeOfDay):
	day{day}, timeOfDay{timeOfDay} {}

Time operator+(const Time &t0, const Time &t1) {
    using namespace std::chrono_literals;
    auto newDay = t0.getDay() + days{t1.dayCode()};
    auto newTimeOfDay = t0.getTimeOfDay() + t1.getTimeOfDay();
    if(newTimeOfDay >= 24h) {
        ++newDay;
        newTimeOfDay -= 24h;
    }
    return {newDay, newTimeOfDay};
}

Time operator-(const Time &t0, const Time &t1) {
    using namespace std::chrono_literals;
    auto newDay = t0.getDay() - days{t1.dayCode()};
    auto newTimeOfDay = t0.getTimeOfDay() - t1.getTimeOfDay();
    if(t0.getTimeOfDay() < t1.getTimeOfDay()) {
        --newDay;
        newTimeOfDay += 24h;
    }
    return {newDay, newTimeOfDay};
}

template<template <class T> class Cmp>
bool cmpOpHelper(const Time &t0, const Time &t1) {
    if(Cmp{}(t0.dayCode(), t1.dayCode())) {return true;}
    else if(t0.dayCode() == t1.dayCode()) {
        return Cmp{}(t0.getTimeOfDay(), t1.getTimeOfDay());
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
