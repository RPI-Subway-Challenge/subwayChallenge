#include "time.h"
#include <string>     // std::string, std::stoi

Time::Time(){
	hour = 0;
	min = 0;
}

Time::Time(int inputHour, int inputMin){
	hour = inputHour;
    min = inputMin;
}

Time::Time(const std::string& input){
    double tempMin  = std::stoi(input.substr(3, 2));
    double tempSeconds = std::stoi(input.substr(6,  2)) / 60;
    min = tempMin + tempSeconds;
    hour = std::stoi(input.substr(0, 2));
}