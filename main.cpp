//																	D O W N    W I T H    M A T T H E W    A H N

#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>

#include "line.h"
#include "station.h"
#include "time.h"
#include "algos.h"


// Ahn's starting point:		Far Rockaway Mott (id: 54)		2:02am
// Ahn's ending point:			Flushing Main Street

//CHANGED STATION INITIALIZATON BECAUSE STATION ID WAS ARBITRARY
std::vector<Station> stations;
std::vector<Line> lines;

using std::size_t;

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

            stations.push_back({id, stationName, std::stod(longitude), std::stod(latitude)});
            id++;
        }
        file.close();
    }

    // im just using the normal read in method for C++, so will differ from above
    // bitbucket for collecting all strings
    std::string bitbucket;
    // ifstream of stationData based on the second argument


    std::ifstream stationData(argv[2]);

    for(int stationId = -1; stationData >> bitbucket;){
        if(bitbucket == "Line:"){
            // feed into bitbucket
            stationData >> bitbucket;
            // push back into the line vector, matching with the Id.
            lines.push_back({++stationId, bitbucket});
        }
        if(bitbucket == "index:"){
            //place index into bitbucket
            stationData >> bitbucket;
            // convert bitbucket into int and add to the station
            lines[stationId].addStation(std::stoi(bitbucket));
        }
    }

    createTrips();
    for(auto &station: stations) {
        station.removeDups();
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

    //TEST

    //starting id for testing: 270
    std::vector<int> path = testAlg(stations, 270);
    for (int i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i != path.size()-1) { std::cout << " -> "; }
    }
    std::cout << "\n" << std::endl;

    //starting id for testing: 22
    //PROOF THAT GRAPH IS DISCONNECTED. vvvvvvvvvvvvv
    std::vector<int> path2 = testAlg(stations, 22);
    for (int i = 0; i < path2.size(); i++) {
        std::cout << path2[i];
        if (i != path2.size()-1) { std::cout << " -> "; }
    }
    std::cout << std::endl;

	// int c;
    // std::cout << "Please enter the id of a starting station\n";
    // int curr;
    // std::cin >> curr;

    // int timeTravel = 0;
	// do {

    //     stations[curr].setVisited(true); // the station is set as visited now
        
    //     std::cout << "\n\nTOTAL TIME ELAPSED: " << timeTravel << "\n";
    //     std::cout << "Enter -1 to quit\n";
    //     std::cout << "Your current location is " << stations[curr].getName() << " with ID " << curr << "\n";
    //     std::cout << "Here are all of the following trips you can take!"<<std::endl<<std::endl;


    //     // Printing out the possible trip you can take 
    //     std::list<Trip> canGo = stations[curr].getTrips();
    //     for (const auto &trip: canGo){
        
    //         std::cout   << "\tStart ID: "    << trip.getStart() 
    //                     << "    End ID: "    << trip.getEnd() 
    //                     << "    Time: "       << trip.getDuration()
    //                     << "    Line: "         << trip.getLineName()  // ! what if its a walking route
    //                     << "    Visited: "         << stations[trip.getEnd()].isVisited()
    //                     // HEURISTIC NEEDS TWO ARGUMENTS, STARTING STATION AND ENDING STATION
    //                     // manual traversal currently passes in the same station for both args
    //                     // WILL NEED TO CHANGE FOR ACTUAL ALGORITHM
    //                     << "    Heuristic: "       << heuristic(stations, trip.getStart(), trip.getStart()) <<  "\n";
    //     }

    //     std::cout << "\nEnter the ID of the station you would like to travel to"<<std::endl;
    //     std::cin >> c;

    //     if (c != -1) {
    //         bool isInputValid = false; // used to check if user's choice is a trip option suggested
    //         for (const auto &trip: canGo){
    //             if (trip.getEnd() == c) {
    //                 timeTravel += trip.getDuration();
    //                 isInputValid = true;
    //                 break;
    //             }
    //         }
    //         if (isInputValid == false){
    //             std::cout<<"---this station number is not a trip suggested above.---"<<std::endl;
    //         }
    //     }


    //     curr = c;

	// } while(c != -1);

}

void createTrips(){
    for(const auto &line: lines){
        for(size_t i = 0; i < line.getNumStations()-1; i++){
            //get each station
            int stationOne =  line.getStation(i);
            int stationTwo = line.getStation(i+1);
            double distance = realDistance(stations[stationOne],stations[stationTwo]);

            double duration = (1.2*60*distance)/17.4; // arbitrary until we figure out normal speed

            Trip f (stationOne, stationTwo, duration, 't');
            Trip b (stationTwo, stationOne, duration, 't');

            f.setLine(line.getName());
            b.setLine(line.getName());

            // add trips to the first station.
            stations[stationOne].addTrip(f);
            stations[stationTwo].addTrip(b);

            stations[stationOne].addLine(line.getName(), i);
        }
    }
}
