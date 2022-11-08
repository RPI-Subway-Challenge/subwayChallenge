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


/*
std::vector<int> dist;   // Holds the distances from the source
std::vector<int> status; // The vector of ints that holds the visited status of the node:
                         // 0 is unvisited, 1 is partially visited, and 2 is visited.
std::vector<int> parent; // Stores the parent

// BFS algorithm
// Should output the optimal BFS trail
// vector of pairs of id's to take and along what line along with time
// outside pair to record the time

//        vector               stationid      method        time    total time
std::pair<std::vector<std::pair<int, std::pair<std::string, int>>>, int> BFS(std::vector<Station> &stations, int startingID)
{
    // hold the path from the beginning to the end
    std::vector<std::pair<int, std::pair<std::string, int>>> output;

    // the queue for BFS
    std::queue<int> queue;
    std::list<Trip>::iterator StationTripItr;

    // holding the distances and visited statuses 
    queue.push(startingID);
    dist[startingID] = 0;
    status[startingID] = 0;

    // initialize the variables used down the line
    std::string method = "STARTING";
    int time = 0;
    int totaltime = 0;

    // the pair represents the station and the method
    std::pair<int, std::string> node;
    node.first = queue.front();


    while (!(queue.empty()))
    {
        int u = queue.front(); // top element from queue, then delete it
        queue.pop();

        StationTripItr = stations[u].getTrips().begin();
        for (StationTripItr; StationTripItr != stations[u].getTrips().end(); StationTripItr++)
        {
            if (status[StationTripItr->getEnd()] == 0)
            {                                         // 0 is unvisited node
                status[StationTripItr->getEnd()] = 1; // 1 is visited but not completed
                dist[StationTripItr->getEnd()] = dist[u] + 1;
                parent[StationTripItr->getEnd()] = u;
                queue.push(StationTripItr->getEnd());
            }
        }
        status[u] = 2; // black is completed node
    }
} 
*/


// Trying out new algorithm, still BFS. Recursively goes through each station and iteratively
// goes thorugh each station's trips and runs it each time. Adds the time from each run
void findShortestPath(std::vector<Station>&stations, int currentID, int Time) {

    // BASE CASE TO STOP RECURSION
    if(stations[currentID].isVisited() == false) {

        stations[currentID].setVisited(true);
        return;
    }

    std::list<Trip>::iterator StationTripItr;
    StationTripItr = stations[currentID].getTrips().begin();

    // TODO: IMPLEMENT GOING TO THE NEXT STATION

    for (StationTripItr; StationTripItr != stations[currentID].getTrips().end(); StationTripItr++)
    {
        if (*StationTripItr->getEnd().isVisited() == false)
        {                                        
            findShortestPath(stations, *StationTripItr->getEnd(), Time);
        }
    }


}