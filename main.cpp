//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"
#include "time.h"
#include "assert.h"
#include "algos.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <iostream>
#include <sstream>
#include "line.h"

// Ahn's starting point:		Far Rockaway Mott (id: 54)		2:02am
// Ahn's ending point:			Flushing Main Street


std::vector<Station> stations;
std::vector<Line> lines;



void createTrips();

int main(int argc, char* argv[]) {

    // check for 4 arguments
    if (argc != 3) {
        std::cerr << "You provided " << argc << "arguments intead of 3.\n";
        exit(1);
    }

    // Read in the data via a .txt file
    // Reading in from a CSV is garbage if you ever want to use commas anywhere else
    // So we will be using a raw text file copy and pasted from the master CSV
    std::fstream file;
    file.open(argv[1], std::ios::in);

    int id = 0;
    if (file.is_open()) {
        // This string will hold each entire line
        std::string timetable;
        while (getline(file, timetable)) {

            // Convert the whole line to a stream so we can use getline()
            std::stringstream ss(timetable);

            std::string stationName;
            std::string longitude;
            std::string latitude;

            // Getline will get parts of a string based on char seperators
            getline(ss, stationName, ',');
            getline(ss, longitude, ',');
            getline(ss, latitude, ',');

            // Erase extra garbage from our floats
            longitude.erase(0, 2);
            latitude.erase(0, 1);
            latitude.erase(latitude.size() - 2);

            stations.push_back(Station(id, stationName,std::stod(longitude), std::stod(latitude)));
            id++;
        }
        file.close();
    }

    // im just using the normal read in method for C++, so will differ from above
    // bitbucket for collecting all strings
    std::string bitbucket;
    // ifstream of stationData based on the second argument


    std::ifstream stationData(argv[2]);
    // start at -1 so that we can increment here.
    int stationId = -1;

    while(stationData >> bitbucket){
        if(bitbucket == "Line:"){
            // feed into bitbucket
            stationData >>  bitbucket;
            // increase the id
            stationId++;
            // push back into the line vector, matching with the Id.
            lines.push_back(Line(stationId, bitbucket));
        }
        if(bitbucket == "index:"){
            //place index into bitbucket
            stationData >> bitbucket;
            // convert bitbucket into int and add to the station
            lines[stationId].addStation(std::stoi(bitbucket));
        }
    }

    createTrips();
    for( int i = 0; i != stations.size(); i++){
        stations[i].removeDups();
    }

    // printing method for varifying loading in data
    // for(unsigned int i = 0; i < lines.size(); i++){

    //     std::cout << "Line:  "<<lines[i].getName();
    //     std::cout << " | ID: "<<lines[i].getId();
    //     std::cout << " | Number Stations: " << lines[i].getNumStations() << std::endl;
    //     std::cout << "          Stations" << std::endl;
    //     std::cout << "------------------------------------------------------" << std::endl;
    //     for(int j = 0; j < lines[i].getNumStations(); j++){
    //         std::cout << "          "<<stations[lines[i].getStation(j)];
    //     }
    // }
    // std::cout << "COMPLETE\n\n\n";


    //                                                          M A N U A L   T R A V E R S A L

	int c;
    std::cout << "Please enter the id of a starting station\n";
    int curr;
    std::cin >> curr;

    Station startStation;
    int timeTravel = 0;
	do {


        startStation = stations[curr];

        std::cout << "\n\nTOTAL TIME ELAPSED: " << timeTravel << "\n";
        std::cout << "Enter -1 to quit\n";
        std::cout << "Your current location is " << startStation.getName() << " with ID " << startStation.getId() << "\n";
        std::cout << "Here are all of the following trips you can take!\n";

        std::list<Trip> canGo = startStation.getTrips();
        std::list<Trip>::iterator it;
        for (it = canGo.begin(); it != canGo.end(); it++){
            std::cout   << "Starting ID: "      << (*it).getStart() 
                        << " to ending ID: "    << (*it).getEnd() 
                        << " with time: "       << (*it).getDuration()
                        << " in line: "         << (*it).getLineName()
                        << " heuristic: "       << heuristic(stations, (*it).getStart()) <<  "\n";
        }

        std::cout << "Enter the ID of the station you would like to travel to\n";
        std::cin >> c;

        if (c != -1) {
            for (it = canGo.begin(); it != canGo.end(); it++){
                if ((*it).getEnd() == c) {
                    timeTravel += (*it).getDuration();
                }
            }
        }


        curr = c;

	} while(c != -1);

}



void createTrips(){
    for(int i = 0; i < lines.size(); i++){
        for(int j = 0; j < lines[i].getNumStations()-1; j++){
            //get each station
            int stationOne =  lines[i].getStation(j);
            int stationTwo = lines[i].getStation(j+1);
            double distance = realDistance(stations[stationOne],stations[stationTwo]);

            double duration = (1.2*60*distance)/17.4; // arbitrary until we figure out normal speed

            Trip f (stationOne, stationTwo, duration, 't');
            Trip b (stationTwo, stationOne, duration, 't');

            f.setLine(lines[i].getName());
            b.setLine(lines[i].getName());

            // add trips to the first station.
            stations[stationOne].addTrip(f);
            stations[stationTwo].addTrip(b);

            stations[stationOne].addLine(lines[i].getName(), i);
        }
    }

}

