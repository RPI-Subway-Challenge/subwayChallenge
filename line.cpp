//																	D O W N    W I T H    M A T T H E W    A H N

#include "line.h"

// default constructor
Line::Line(){
	name = "NONE";
	std::vector<int> vec;
	lineVec = vec;
}


// constructor
Line::Line(std::string inputName, std::vector<int> inputVec){
	name = inputName;
	lineVec = inputVec;
}
