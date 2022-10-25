//																	D O W N    W I T H    M A T T H E W    A H N

#ifndef station_h_
#define station_h_


#include <utility>	// pair
#include <vector>
#include "trip.h"


class Station{
public:
	// defualt constructor
	Station();

	// constructor
	Station(int id, std::string inName, double lon, double lat, std::list<std::pair<std::string,int>> inLines = {});

	// setters
	void setTrips(std::list<Trip> inTrips);
	void addTrip(Trip inTrip);
	void addLine(std::string inStr, int inIndex);
	// void removeTrip(Trip& t)									{trips.remove(t);}
	void removeDups();
    void setVisited(bool inVisited)                             {visited = inVisited;}
    void addLine(std::pair<std::string, int> line);

	// getters
	int getId() const 	 	 				    				{return id;}
	const std::string &getName() const 		        			{return name;}
    const std::list<std::pair<std::string,int>> &getLines() const
	                                                            {return lines;}
    const std::list<Trip> &getTrips() const						{return trips;}
	bool isOpen() const											{return open;}
    bool isVisited() const                                      {return visited;}
	int getHeuristic() const {return heuristic;}
	std::string getCordStr() const;

    const std::pair<double, double>& getCords() const           {return cords;}

private:
	int id;
	std::string name;
	std::pair<double,double> cords;
	std::list<std::pair<std::string,int> > lines;
	std::list<Trip> trips;
	bool open;
    bool visited;
	int heuristic = 0;
	// ? possibly operating hours
};
std::ostream& operator<<(std::ostream& os, const Station& s);

#endif