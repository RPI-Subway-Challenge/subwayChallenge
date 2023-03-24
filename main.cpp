//																	D O W N    W I T H    M A T T H E W    A H N

#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>
#include <map>

#include "line.h"
#include "station.h"
#include "time.h"
#include "algos.h"


// Ahn's starting point:		Far Rockaway Mott (id: 54)		2:02am
// Ahn's ending point:			Flushing Main Street

//CHANGED STATION INITIALIZATON BECAUSE STATION ID WAS ARBITRARY
using std::size_t;

// void createTrips();

int main(int argc, char* argv[]) {

    // check for 4 arguments
    if (argc != 3) {
        std::cerr << "You provided " << argc << "arguments intead of 3.\n";
        exit(1);
    }

    //Rewritten station file read into a vector
    std::ifstream myfile(argv[2]);
    std::vector<std::string> lineData;
    std::string line;
    while (std::getline(myfile, line)) {
        lineData.push_back(line);
    }


    //Map to store station id's and names for easy access
    std::map<int, std::string> stationInfo;

    //Parse station info
    for (int i = 0; i < lineData.size(); i++) {

        if (lineData[i].find("station") != std::string::npos) {
            //Find index of station
            std::string indexStr = lineData[i].substr(lineData[i].rfind(": ") + 2);
            int index = std::stoi(indexStr);
            //Find name of station
            int endIndex = lineData[i].find(",") - lineData[i].find(": ") - 2;
            std::string name = lineData[i].substr(lineData[i].find(": ") + 2, endIndex);
            //Add station information to map
            if (stationInfo.find(index) == stationInfo.end()) {
                stationInfo.insert({index, name});
            }
        }
    }

    // //Test print station info
    // for (auto i = stationInfo.begin(); i != stationInfo.end(); ++i) {
    //     if (i->first != counter) {
    //         std::cout << i->first << " " << i->second << std::endl;
    //     }
    // }

    // //Missing stations test print
    // int counter = 0;
    // for (int i = 1; i < 451; i++) {
    //     if (stationInfo.find(i) == stationInfo.end()) {
    //         std::cout << i << std::endl;
    //         counter++;
    //     }
    // }
    // std::cout << "size: " << stationInfo.size() << " total skipped: " <<
    // counter << std::endl;

    //KNOWN ISSUES: =====================================================
    // SKIPPED STATION IDS: 82, 122, 234-243(inclusive), 261-269(inclusive), 377
    // total skipped id count: 22 | actual station count = 428
    // Park Pl on the S line in Brooklyn also DOES NOT EXIST -> can add manually

    //Matrix representation of stations, edges set to zero
    //Zeroth row is empty, using 1-based indexing
    std::vector<std::vector<int>> stations (
        451,
        std::vector<int>(451));

    //Set edges
    for (int i = 0; i < lineData.size(); i++) {
        //Two adjacent stations
        if (lineData[i].find("station") != std::string::npos) {
            if (lineData[i+1].find("station") != std::string::npos) {
                //Find indices of stations
                std::string indexStr = lineData[i].substr(lineData[i].rfind(": ") + 2);
                int index = std::stoi(indexStr);
                std::string indexStr2 = lineData[i+1].substr(lineData[i+1].rfind(": ") + 2);
                int indexNext = std::stoi(indexStr2);
                //Set edges between adjacent stations
                stations[index][indexNext] = 1;
                stations[indexNext][index] = 1;
            }
        }
    }

    // Manually set walking route possibilities: 207St(A)-207St(1), 
    // BedfordPkBlvd(4)-BedfordPkBlvd(B/D), 96St(6)-96St(Q)

    //207St
    stations[172][6] = 1;
    stations[6][172] = 1;
    //BedfordPkBlvd
    stations[97][213] = 1;
    stations[213][97] = 1;
    //96St
    stations[422][142] = 1;
    stations[142][422] = 1;


    // Print adjacency matrix for Gephi visualization

    // std::ofstream gephiFile;
    // gephiFile.open("gephiSubway.txt");
    // gephiFile << "Source,Target" << std::endl;
    // for (int i = 0; i != 451; i++){
    //     for (int j = 0; j != 451; j++){
    //         if(stations[i][j] == 1){
    //             gephiFile << i << "," << j << std::endl;
    //         } 
    //     }
    // }


    //                                                          M A N U A L   T R A V E R S A L

    //TESTING

    // //starting id for testing: 1
    // std::vector<int> path = testAlg(stations, 1);
    // for (int i = 0; i < path.size(); i++) {
    //     std::cout << path[i];
    //     if (i != path.size()-1) { std::cout << " -> "; }
    // }
    // std::cout << "\n" << std::endl;
    // std::cout << "Path size: " << path.size() << std::endl;


    //                                                          R U N    A L G O R I T H M

    //Actual start for route: 212
    int startStation = 212;

    // std::vector<int> sim = aToB(stations, 212, 400);

    // std::cout << sim[0] << " :::::: " << sim[sim.size()-1] << std::endl;

    // for(int i = 0; i != sim.size(); i++){
    //     std::cout << i << " : " << sim[i] << std::endl;
    // }

    std::vector<int> path = bfs(startStation, stations);


    std::vector<int> fullPath;
    fullPath.push_back(startStation);
    for(int i = 1; i != path.size(); i++){
        std::vector<int> pathToNew = aToB(stations, path[i-1], path[i]);

        for(int j = 0; j != pathToNew.size(); j++){
            if(pathToNew[j] != path[i-1] && pathToNew[j] != path[i]){
                fullPath.push_back(pathToNew[j]);
            }
        }

        fullPath.push_back(path[i]);

    }

    // turn path into full path, including revisited stations
    // std::vector<int> fullPath;
    // for(int i = 0; i != path.size()-1; i++){
    //     std::vector<int> segment = aToB(path[i], path[i+1], stations);
    //     fullPath.insert(fullPath.begin(), segment.begin(), segment.end());
    // }


    std::cout << stations.size() << std::endl;

    std::cout << path.size() << std::endl;

    for (int i : fullPath) {
        std::cout << i << " ";
    }
    std::cout << std::endl;


    // revisit check
    int revisitedCount = 0;
    for(int i = 0; i != stations.size(); i++){
        int occurCount = 0;
        for(int j = 0; j != fullPath.size(); j++){
            if(fullPath[j] == i){
                occurCount++;
            }
        }
        // std::cout << i << " : " << occurCount << std::endl;
        if(occurCount > 1){revisitedCount += occurCount-1;}
    }
    std::cout << "REVISITED : " << revisitedCount << std::endl;


    // ! uncomment for old printing
    // //Print result
    // for (int i = 0; i < path.size(); i++) {
    //     std::cout << i+1 << "/" << path.size() << " | " ;
    //     std::cout << path[i] << " | " << stationInfo[path[i]];

    //     if (i != path.size()-1 && stations[path[i]][path[i+1]] == 0) {
    //         std::cout << " => backtrack";
    //     }
    //     // if (i != path.size()-1) {
    //     //     std::cout << " => ";
    //     // }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;



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

// void createTrips(){
//     for(const auto &line: lines){
//         for(size_t i = 0; i < line.getNumStations()-1; i++){
//             //get each station
//             int stationOne =  line.getStation(i);
//             int stationTwo = line.getStation(i+1);
//             double distance = realDistance(stations[stationOne],stations[stationTwo]);

//             double duration = (1.2*60*distance)/17.4; // arbitrary until we figure out normal speed

//             Trip f (stationOne, stationTwo, duration, 't');
//             Trip b (stationTwo, stationOne, duration, 't');

//             f.setLine(line.getName());
//             b.setLine(line.getName());

//             // add trips to the first station.
//             stations[stationOne].addTrip(f);
//             stations[stationTwo].addTrip(b);

//             stations[stationOne].addLine(line.getName(), i);
//         }
//     }
// }
