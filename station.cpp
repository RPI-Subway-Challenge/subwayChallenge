//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"

/*Time::Time(){
	day = 0;
	hour = 0;
	min = 0;
}


Time::Time(int inputDay, int inputHour, int inputMin){
	day = inputDay;
	hour = inputHour;
	min = inputMin;
}*/

Station::Station(){
	name = "NONE";
}


Station::Station(std::string inputName){
	name = inputName;
}

void Station::addLine(int lineNum, int position){
	std::pair<int, int> lineInfo;
	lineInfo = std::make_pair(lineNum, position);
}

