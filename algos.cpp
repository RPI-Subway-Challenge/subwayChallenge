//																	D O W N    W I T H    M A T T H E W    A H N
#include <iostream>
#include <cmath>
#include <queue>
#include <set>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include "station.h"

using std::size_t;

// return manhattan distance between two stations
double manhattanDistance(const Station &s1, const Station &s2){
    double diffX = std::abs( s1.getCords().first - s2.getCords().first );
    double diffY = std::abs( s1.getCords().second - s2.getCords().second );
    return diffX + diffY;
}

// Return actual distance (in MILES) between two stations
//  Distance between LONGITUDE and LATITDUE coords is as follows
//  3963.0 * arccos[(sin(lat1) * sin(lat2)) + cos(lat1) * cos(lat2) * cos(long2 – long1)]
//  .first  gives longitude
//  .second gives latitude
double realDistance(const Station& s1, const Station& s2){
    auto [long1, lat1] = s1.getCords();
    auto [long2, lat2] = s2.getCords();
    double sinPart = sin(lat1) * sin(lat2);
    double cosPart = cos(lat1) * cos(lat2) * cos(long2-long1);
    double d = 3963.0 * acos(sinPart + cosPart);
    return d;
}

// returns an estimated time to travel the given distance using proportional constant (k)
double timeDistance(double distance, int k){
    double travelTime = distance * k;
    return travelTime;
}


/*
// takes station returns list of indicies of all stations within a certain radius
// O(num of stations) for single station
std::list<int> walkableRadius(int stationIndex, double radius, std::vector<Station> & stationVec){
    std::list<int> walkable;
    for(int i = 0; i != stationVec.size(); i++){
        if(realDistance(stationVec[stationIndex], stationVec[i]) <= radius && i != stationIndex){
            walkable.push_back(i);
        }
    }
    return walkable;
}
*/


// takes vector of pairs walkable and returns index with longest distance
size_t findLongest(const std::vector<std::pair<int,double>> &walkable){
    return static_cast<size_t>(std::distance(walkable.begin(),
        std::ranges::max_element(walkable,
            [] (const auto &x, const auto &y) {return x.second < y.second;}
        )));
}



// takes station returns vector of x nearest stations indicies
// O(x*num of stations) for single station
std::vector<std::pair<int,double>> walkableNumber(size_t stationIndex, size_t x, std::vector<Station> & stationVec){

    std::vector<std::pair<int,double>> walkable(x); // pair < neighborIndex, distance >
    size_t longest = 0; // index in walkable of farthest away neighbor

    if(x < 1){std::cerr << "ERROR: X in walkableNumber must be >= 1\n"; return walkable;}

    if(x >= stationVec.size()){std::cerr << "ERROR: X in walkableNumber must be < stationVec.size()\n"; return walkable;}

    // put first x stations in walkable
    for(size_t i = 0; i != x; i++){
        // if stationIndex in first x make distance very long so replaced first
        if(i == stationIndex){
            walkable[i] = {i, 9999999999999999};
            longest = i;
        // not stationIndex
        }else{
            walkable[i] = {i, realDistance(stationVec[stationIndex],stationVec[i])};
            // check against longest
            if(realDistance(stationVec[stationIndex],stationVec[i]) > walkable[longest].second){
                longest = i;
            }
        }
    }

    // check stations from index x to end
    for(size_t i = x; i != stationVec.size(); i++){
        if(i != stationIndex){
            // check against longest
            if( realDistance(stationVec[stationIndex],stationVec[i]) > walkable[longest].second ){
                walkable[longest] = {i, realDistance(stationVec[stationIndex],stationVec[i])};
                longest = findLongest(walkable);
            } 
        }
    }
    return walkable;
}

// create trip for all walkable station from a station for all stations given from walkableNumber
// O(x*num of stations^2) for all stations
void createStationsTrips(size_t x, int k, std::vector<Station> & stationVec){

    // Since no data is known about the stations atm, the trips are intializased as being open all days every hour
    // Creating basic time vector full of transportation data. (temporary filler data)
    std::list<Time> weekdayTimes;
    std::list<Time> weekendsTimes;
    for(unsigned i=0; i<24; i++){ // for every hour
        for(unsigned j=0; j<5; j++){ // day
            weekdayTimes.push_back({j, i, 0});
        }
        for(unsigned j=5; j<7; j++){
            weekendsTimes.push_back({j, i, 0});
        }
    }
    // create trips for each station to their walkable stations
    for(size_t i=0; i<stationVec.size(); i++){
        std::vector<std::pair<int,double> > walkableStations = walkableNumber(i, x, stationVec);
        for(size_t j=0; j<walkableStations.size(); j++){
            int duration = (int) timeDistance(walkableStations[i].second, k);
            Trip(i, walkableStations[i].first, duration, 't', weekendsTimes, weekdayTimes);
        }
    }
}



// std::vector<Station> BFS(std::vector<Station> stations, int startingID, int goalID){

// }

// takes current station id and next station id
//      and returns heuristic value for the next station to visit
// Lower value is better than higher value (arbitrary penalty value)
// Function returns heuristic value for next station
int heuristic(std::vector<Station> & stations, int currId, int nextId){
    int sum = 0;
    const int lowPenaltyVal = 1;
    const int penaltyVal = 10;
    
    std::list<Trip> trips = stations[nextId].getTrips();
    std::list<Trip>::iterator iterT;

    // low penalty for each visited neighboring station for the next station
    for(iterT = trips.begin(); iterT != trips.end(); iterT++){
        if( stations[iterT->getEnd()].isVisited() == true ){
            sum += lowPenaltyVal;
        }
    }

    // penalty if next station is already visited
    if(stations[nextId].isVisited() == true){
        sum += penaltyVal;
    }

    std::list<std::pair<std::string,int>> currLines = stations[currId].getLines();
    std::list<std::pair<std::string,int>> nextLines = stations[nextId].getLines();
    bool sameLine = false;

    // penalty for switching lines
    //Loop through all lines for the current station
    for (auto iterCurr = currLines.begin(); iterCurr != currLines.end(); iterCurr++) {
        //Loop through all lines for the next station
        for (auto iterNext = nextLines.begin(); iterNext != nextLines.end(); iterNext++) { 
            //Check if there is a matching line
            if (iterCurr->first == iterNext->first) {
                sameLine = true;
                break;
            }
        }
        //Skip checking the rest of the current stations
        if (sameLine) {
            break;
        }
    }
    if (!sameLine) {
        sum += penaltyVal;
    }

    // penalty for entering a dead end branch vvvvv
    // merged with penalty for moving away from large masses of connected stations
    // -> stations are hard coded from north-west station clockwise
    // ONLY CONSIDERING THE LONGEST BRANCHES CURRENTLY
    int branchStarts[] = {
        26 //3rd Ave - 138th St
    };

    //Check if the station is going into a dead end branch
    for (size_t i = 0; i < (sizeof(branchStarts)/sizeof(int)); i++) {
        if (branchStarts[i] == nextId) {
            sum += penaltyVal;
        }
    }

    return sum;
}


Station* moveByTrip(std::vector<Station>& stations, Station* startStation, Trip& tripTaken, int& currentTime){
    // This function takes the list for all station representation in main, start station, a trip object, and the current time.
    // it is going to update the station traveled, currentTime, and return the station traveled to. It returns nullptr if error.

    //first, check if the startStation is visited
    if (startStation->isVisited() == false){
        std::cerr<<"start station of a move is not visited, stationId: "<<startStation->getId()<<std::endl;
        return nullptr;
        }
    
    stations[tripTaken.getEnd()].setVisited(true); // set the end station as visited

    currentTime += tripTaken.getDuration();

    return &stations[tripTaken.getEnd()]; // return the pointer to the end station 
}


// This function compress continious station with only 2 neibhor station into one station object
void branchReduction(std::vector<Station>& stations){
    // if station is checked: modify_status[i] == true, and vice versa
    std::vector<bool> checkedStatusVec(stations.size(), false);
    // a vector of vector represent all reduction that could be done
    std::vector<std::vector<int>> reducibleVecVec;

    for (int i=0; i<stations.size(); i++){
        if(checkedStatusVec[i] == true){continue;} // we only loop at station hasn't checked
        else{
            // checking if this station is non-branching
            bool nonBranching = false;
            std::vector<Trip>tripsOfThisStation = stations[i].getTripVec();
            if (stations[i].getNumTrainTrips() > 2){// a non-branching station
                checkedStatusVec[i] = true;
                continue;       
            }

            // ------------------------- finding the entire reduceable branch -------------------------
            // stations[i] could be reduced
            std::vector<int> reducedLineVec = {i};
            // move on one direction of the trip in tripsOfThisStation
            int currStationId = i;
            int nextStationToCheck = tripsOfThisStation[0].getEnd(); 
            while (stations[i].getNumTrainTrips() < 2){
                checkedStatusVec[nextStationToCheck] = true;
                // take the first trip in this currStation
                reducedLineVec.push_back(nextStationToCheck);
                currStationId = nextStationToCheck;
                std::vector<Trip> tempTripVec = stations[currStationId].getTripVec();
                if (tempTripVec[0].getEnd() == currStationId){ // if the first trip is not the one we want
                    nextStationToCheck = tempTripVec[1].getEnd();
                }
                else{
                    nextStationToCheck = tempTripVec[0].getEnd();
                }
            }

            if (tripsOfThisStation.size() == 2){ // if the station is has another dir (avoid i being a end station)
                // move on the other direction of the trip in tripsOfThisStation
                currStationId = i;
                nextStationToCheck = tripsOfThisStation[1].getEnd(); 
                while (stations[i].getNumTrainTrips() < 2){
                    checkedStatusVec[nextStationToCheck] = true;
                    // take the first trip in this currStation
                    reducedLineVec.push_back(nextStationToCheck);
                    currStationId = nextStationToCheck;
                    std::vector<Trip> tempTripVec = stations[currStationId].getTripVec();
                    if (tempTripVec[0].getEnd() == currStationId){ // if the first trip is not the one we want
                        nextStationToCheck = tempTripVec[1].getEnd();
                    }
                    else{
                        nextStationToCheck = tempTripVec[0].getEnd(); 
                    }
                }
            }
            reducibleVecVec.push_back(reducedLineVec); // add the reduced line to the vector of vector for reduction at the end
        }
    }
    // ------------------------- compressing the branch -------------------------
    for (int i=0; i<reducibleVecVec.size(); i++){
        // ---------------------find the ends of the branch------------------
        int endId1=-1; // if endId1 == -1, it means we haven't found the the frist end yet
        int endId2=-1; // if endId2 == -1, it means we haven't found the the second end yet or it goes to the end of the line
        int endId1Prev=-1; // if endId1Prev == -1, it means we haven't found the the frist end yet
        int endId2Prev=-1; // if endId2Prev == -1, it means we haven't found the the second end yet, or it goes to the end of the line

        for (int j=0; j<reducibleVecVec[i].size(); j++){
            bool isEnd = false;
            int currStationId = reducibleVecVec[i][j];

            // debug purpose----------------
            if (stations[currStationId].getNumTrainTrips() > 2){ 
                std::cerr<<"error in branchReduction, station has more than 2 trips"<<std::endl;
                return;
            }
            // -----------------------------

            int tempEndPrev;
            // all station in reducibleVecVec[i] are non-branching station, so they have at most 2 trips
            if (find (reducibleVecVec[i].begin(), reducibleVecVec[i].end(), stations[currStationId].getTripVec()[0].getEnd()) == reducibleVecVec[i].end()){
                tempEndPrev = stations[currStationId].getTripVec()[0].getEnd(); 
                isEnd = true;
            }
            else if (stations[currStationId].getNumTrainTrips() == 1 || find (reducibleVecVec[i].begin(), reducibleVecVec[i].end(), stations[currStationId].getTripVec()[1].getEnd()) == reducibleVecVec[i].end()){
                tempEndPrev = stations[currStationId].getTripVec()[1].getEnd();
                isEnd = true;
            }

            if (isEnd){
                if (endId1 == -1){
                    endId1 = currStationId;
                    endId1Prev = tempEndPrev;
                }
                else{
                    endId2 = currStationId;
                    endId2Prev = tempEndPrev;
                    break; // we have found both ends, break the loop
                }
            }
        }

        // --------calculate the time required to complete the trip---------
        int timeRequired = 0;
        // we start taking transit at the endId1 and calculate the time required to get to endId2
        int currStationId = endId1;
        int prevStationId = endId1;
        int nextStationId = -1;

        if (find (reducibleVecVec[i].begin(), reducibleVecVec[i].end(), stations[currStationId].getTripVec()[0].getEnd()) == reducibleVecVec[i].end()){
            prevStationId = stations[currStationId].getTripVec()[0].getEnd();
        }
        else if (stations[currStationId].getNumTrainTrips() == 1 || find (reducibleVecVec[i].begin(), reducibleVecVec[i].end(), stations[currStationId].getTripVec()[1].getEnd()) == reducibleVecVec[i].end()){
            prevStationId = stations[currStationId].getTripVec()[1].getEnd();
        }
        for (int j=0; j<reducibleVecVec[i].size(); j++){
            // debug purpose----------------
            if (stations[currStationId].getNumTrainTrips() > 2){ 
                std::cerr<<"error in branchReduction, station has more than 2 trips"<<std::endl;
                return;
            }
            // -----------------------------

            // move to next station and update timeRequired
            std::vector<Trip> tempTripVec = stations[currStationId].getTripVec();
            if (stations[currStationId].getNumTrainTrips() == 1){ // if it's the end of the line
                break; // we have reached the end of the line
            }
            else if (tempTripVec[0].getEnd() == prevStationId){
                if (tempTripVec[0].getEnd() == endId2){
                    break; // we reached the end of the reducible branch
                }
                nextStationId = tempTripVec[1].getEnd();
                timeRequired += tempTripVec[1].getDuration();
            }
            else{
                if (tempTripVec[1].getEnd() == endId2){
                    break; // we reached the end of the reducible branch
                }
                nextStationId = tempTripVec[0].getEnd();
                timeRequired += tempTripVec[0].getDuration();
            }

            // update prevStationId and currStationId
            prevStationId = currStationId;
            currStationId = nextStationId;  
        }

        // ---------------------create the new station----------------------
        std::string newStationName;
        
        int newStationId = endId1;
        
        if (endId2 == -1){ // if the branch is going to the end of the line
             newStationName = stations[endId1].getName() + "-End of Line";
        }
        else{
            newStationName = stations[endId1].getName() + "-" + stations[endId2].getName();
        }

        // new station initializated here, longitude and latitude are -1 for reduced station
        Station newStation(newStationId, newStationName, -1, -1);

        // ---------------------create the new trip----------------------
        int timeRequiredToEndPrev1 = -1;
        std::vector<Trip> tempTripVecEnd1 = stations[endId1].getTripVec();
        for (int j=0; j<tempTripVecEnd1.size(); j++){
            if (tempTripVecEnd1[j].getEnd() == endId1Prev){
                timeRequiredToEndPrev1 = tempTripVecEnd1[j].getDuration();
                break;
            }
        }
        // for debug purpose ----------------
        if (timeRequiredToEndPrev1 == -1){
            std::cerr<<"error in branchReduction, can't find the time required to endId1Prev"<<std::endl;
            return;
        }
        // ----------------------------------
        Trip tripToEndPrev1(endId1, endId1Prev, timeRequiredToEndPrev1, 't');
        if (endId2 != -1){ // if the branch is not going to the end of the line
            int timeRequiredToEndPrev2 = -1;
            for (int j=0; j<stations[endId2].getTrips().size(); j++){
                if (stations[endId2].getTripVec()[j].getEnd() == endId2Prev){
                    timeRequiredToEndPrev2 = stations[endId2].getTripVec()[j].getDuration();
                    break;
                }
            }
            // for debug purpose ----------------
            if (timeRequiredToEndPrev2 == -1){
                std::cerr<<"error in branchReduction, can't find the time required to endId2Prev"<<std::endl;
                return;
            }
            // ----------------------------------
            Trip tripToEndPrev2(endId2, endId2Prev, timeRequiredToEndPrev2, 't');
            stations[newStationId].addTrip(tripToEndPrev2);
        }

        stations[newStationId].addTrip(tripToEndPrev1);
        if (endId2 != -1){ // if the branch is not going to the end of the line
            Trip tripToEnd2(newStationId, endId2, timeRequired, 't');
            stations[endId2].addTrip(tripToEnd2);
        }


    }
}
