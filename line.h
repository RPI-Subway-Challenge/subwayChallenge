//																	D O W N    W I T H    M A T T H E W    A H N

#ifndef line_h_
#define line_h_

#include <vector>
#include "time.h"



class Line{
public:
	// constructor
	Line(int inID = -1, std::string inName = "");

	// setters
	void addStation(const int stationIndex);

	// getters
	int getId() const 	 	 				    				{return id;}
	const std::string &getName() const 		        			{return name;}
    int getStation(int index) const	                            {return lineVec[index];}
	bool getOpen() const										{return open;}
    std::size_t getNumStations() const                          {return lineVec.size();}
	

private:
	int id;
	std::string name;
	std::vector<int> lineVec;
	bool open;
};


#endif