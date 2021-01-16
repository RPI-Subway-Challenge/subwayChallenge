
#include "station.h"

Time::Time(){
	day = 0;
	hour = 0;
	min = 0;
}


Time(int inputDay, int inputHour, int inputMin){
	day = inputDay;
	hour = inputHour;
	min = inputMin;
}

Station::Station(){
	name = "NONE";
}


Station::Station(std::string inputName){
	name = inputName;
}

void Station::addLine(std::string lineName, int position){
	std::pair<std::string, int> lineInfo;
	lineInfo = std::make_pair(lineName, position);
}

