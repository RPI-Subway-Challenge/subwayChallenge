//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"

// default constructor
Station::Station(){
	name = "NONE";				// indicator of empty node in hashtable
}


// partial constuctor for when new station is dicovered as a connection
Station::Station(std::string &inputName, int inputHash){
	name = inputName;
	hash = inputHash;
	lines.push_back("NONE");	// indicator of incomplete station in hashtable
}



// constructor
Station::Station(std::string &inputName, int inputHash, std::list<std::string> &inputLines, std::vector<std::pair<Time,Time>> &inputHours,
				std::list<std::pair<int,Time>> &inputTrains, std::list<std::pair<int,Time>> &inputWalks){

	name = inputName;
	lines = inputLines;
	hours = inputHours;
	trains = inputTrains;
	walks = inputWalks;
}




// default constructor
Time::Time(){
	day = 0;
	hour = 0;
	minute = 0;

}



// constructor
Time::Time(int inputDay, int inputHour, int inputMinute){
	day = inputDay;
	hour = inputHour;
	minute = inputMinute;
}



// time addition operator
Time Time::operator + (Time addedTime){

	minute += addedTime.getMinute();
	if(minute >= 60){
		hour++;
		minute -= 60;
	}

	hour += addedTime.getHour();
	if(hour >= 24){
		hour -= 24;
	}

	return *this;
}



// time subtraction operator
Time Time::operator - (Time subtractedTime){

	minute -= subtractedTime.getMinute();
	if(minute < 0){
		hour--;
		minute += 60;
	}

	hour += subtractedTime.getHour();
	if(hour < 0){
		hour = 24+hour;
	}

	return *this;
}



void Time::operator = (Time comparedTime){
	day = comparedTime.getDay();
	hour = comparedTime.getHour();
	minute = comparedTime.getMinute();
}



bool Time::operator > (Time comparedTime){
	if(day == 0 && comparedTime.getDay() == 6){
		std::cout << "Sunday > Saturtday returned true\n";
		return true;
	}
	if(day > comparedTime.getDay()){
		return true;
	}
	if(day == comparedTime.getDay() && hour > comparedTime.getHour()){
		return true;
	}
	if(day == comparedTime.getDay() && hour > comparedTime.getHour() && minute > comparedTime.getMinute()){
		return true;
	}
	return false;
}




// default constructor
Route::Route(){
	duration = Time();
}


// operator =
void Route::operator = (Route &route){
	duration = route.getDuration();
	path = route.getRoute();
}

