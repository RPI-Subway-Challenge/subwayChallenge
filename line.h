
#ifndef line_h_
#define line_h_

#include "station.h"

class Line{
public:
	// contructor
	Line(std::string inputName, std::vector<int> inputVec);

	// setters


	// getters
	int getStation(int index)	{return lineVec[index];}

private:
	std::string name;
	std::vector<int> lineVec;	// stations represented as their index in main's station vector
};



#endif