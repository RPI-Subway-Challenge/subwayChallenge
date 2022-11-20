//																	D O W N    W I T H    M A T T H E W    A H N
#include <iostream>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include "station.h"

using std::size_t;

int heuristic(std::vector<Station> & stations, int currId, int nextId);

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

//Uniform cost search test algorithm
//ending id is added to goal vector
std::vector<int> testAlg(std::vector<Station> stations, std::vector<int> goal,
  int start){
    //Minimum cost up to goal from root
    std::vector<int> answer;
    for (int i = 0; i < goal.size(); i++) {
        answer.push_back(INT_MAX);
    }
    //Queue stores cumulative distance and station id
    std::priority_queue<std::pair<int,int>> q;
    //map stores station id and bit representing if it was visited
    //0 = unvisited, 1 = visited
    std::map<int,int> visited;
    for (int i = 0; i < stations.size(); i++) {
        visited.insert({stations[i].getId(), 0});
    }

    int count = 0;

    //Insert root into priority queue
    q.push({0, start});

    //Frontier system to create backpointers, stores station ids
    std::vector<int> frontier;
    frontier.push_back(start);

    while (q.size() > 0) {
        //Find top element of the priority queue
        std::pair<int,int> top = q.top();

        //Remove element with the highest priority
        q.pop();

        //Find original cost of the node
        top.first *= -1;

        //Check if top is part of the goal vector 
        if (find(goal.begin(), goal.end(), top.second) != goal.end()) {
            //Get index of top in the goal list
            int index = find(goal.begin(), goal.end(),
                top.second) - goal.begin();
            //If a new goal is reached
            if (answer[index] == INT_MAX) { count++; }
            //If the cost is less
            if (answer[index] > top.first) {
                answer[index] = top.first;
            }
            //Pop the element
            q.pop();
            //Terminate if all goals are reached
            if (count == goal.size()) {
                return answer;
            }
        }

        //Check for non visited neighbors
        if (visited[top.second] == 0) {
            //Add children to the priority queue with
            //cumulative distance as the priority
            std::list<Trip> trips = stations[top.second].getTrips();

            for (std::list<Trip>::iterator i = trips.begin();
             i != trips.end(); ++i) {

                //Multiply cost by -1
                int neighborCost = (top.first + i->getDuration()) * -1;
                int neighborId = i->getEnd();

                q.push({neighborCost, neighborId});

                //Track predecessors with frontier
                //Not visited
                if (visited[i->getEnd()] == 0) {
                    //Not in frontier
                    if (find(frontier.begin(), frontier.end(), 
                    i->getEnd()) == frontier.end()) {
                        frontier.push_back(i->getEnd());
                        //Update predecessor pointer on the heap
                        //Creates memory leak, too bad!
                        Station* p = new Station();
                        p->setId(top.second);

                        stations[i->getEnd()].predecessor = p;
                    }
                    // //Is in frontier but with higher cost
                    // if (find(frontier.begin(), frontier.end(), 
                    // i->getEnd()) != frontier.end()) {
                    //     //Check if it has a higher cost (not sure if needed)
                    //     //replace existing node with current neighbor
                    //     *(find(frontier.begin(), frontier.end(), 
                    //     i->getEnd())) = i->getEnd();
                    //     //Set neighbor's predecessor pointer
                    //     stations[i->getEnd()].predecessor = &stations[top.second];
                    // }
                }
            }

            //Mark current nodes as visited
            visited[top.second] = 1;
        }
    }
    return answer;
}

//Heuristics only test algorithm
void testAlgHeuristics(std::vector<Station> stations, std::vector<int> goal,
  int start) {
    int currStation = start;
    //Print starting station
    std::cout << start;
    std::vector<int> goalCopy = goal;

    //Continue until all goal stations are visited
    // while (goal.size() > 0) {

    //^^^^^^^^^^^ INFINITE LOOP RESULTS BECAUSE LIST OF SUBWAY STATIONS HAS REPEATING IDS.
        for (int i = 0; i < 10; i++) {

        //Map to store station id and heuristic
        std::map<int,int> nextHeuristics;
        //Iterate through possible neighbors
        std::list<Trip> trips = stations[currStation].getTrips();
        std::list<Trip>::iterator iterT;
        for(iterT = trips.begin(); iterT != trips.end(); iterT++){
            int neighbor = iterT->getEnd();

            //Heuristics helper function
            nextHeuristics.insert(
                {heuristic(stations, currStation, neighbor), neighbor}
            );
        }
        
        //Update visited stations
        stations[currStation].setVisited(true);
        //Remove from goal if applicable
        std::vector<int>::iterator itr = std::find(goalCopy.begin(), goalCopy.end(), currStation);
        if (itr != goalCopy.end()) {
            goalCopy.erase(itr);
        }

        //Continue with best choice (min heuristic station)
        //VVVVVVVVVVVVVVVVVVVVVVVVVVVVV
        //BUG: No unvisited stations case - find closest unvisited station
        currStation = nextHeuristics.begin()->second;

        //Print next station
        std::cout << "->" << currStation;

    }
}

// std::vector<Station> BFS(std::vector<Station> stations, int startingID, int goalID){

// }

//Changes heuristic value of current station and all neighboring 
// connected stations
// void heuristic(std::vector<Station> & stations, int currId) {
//     const int penaltyVal = 1;
//     std::list<Trip> trips = stations[currId].getTrips();
//     std::list<Trip>::iterator iterT;

//     // -> branch stations are hard coded from north-west station clockwise
//     // ONLY CONSIDERING THE LONGEST BRANCHES CURRENTLY
//     int branchStarts[] = {
//         26 //3rd Ave - 138th St
//     };

//     //Iterate through all neighboring stations
//     for(iterT = trips.begin(); iterT != trips.end(); iterT++){
//         //Penalize neighbors for being already visited
//         if (stations[iterT->getEnd()].isVisited() == true) {
//             stations[iterT->getEnd()].addHeuristic(penaltyVal);
//         }
        
//         //Penalize neighbors if they are not in the same line
//         std::list<std::pair<std::string,int>> currLines = stations[currId].getLines();
//         std::list<std::pair<std::string,int>>::iterator iterCurr;
//         std::list<std::pair<std::string,int>> nextLines = stations[iterT->getEnd()].getLines();
//         std::list<std::pair<std::string,int>>::iterator iterNext;
//         bool sameLine;
//         //Loop through all lines for the current station
//         for (iterCurr = currLines.begin(); iterCurr != currLines.end(); iterCurr++) {
//             //Loop through all lines for the neighboring station
//             for (iterNext = nextLines.begin(); iterNext != nextLines.end(); iterNext++) { 
//                 //Check if there is a matching line
//                 if (iterCurr->first == iterNext->first) {
//                     sameLine = true;
//                     break;
//                 }
//             }
//             //Skip checking the rest of the current stations
//             if (sameLine) {
//                 break;
//             }
//         }
//         if (!sameLine) {
//             stations[iterT->getEnd()].addHeuristic(penaltyVal);
//         }

//         //Penalize neighbors if entering a dead end branch
//         for (size_t i = 0; i < (sizeof(branchStarts)/sizeof(int)); i++) {
//             if (branchStarts[i] == iterT->getEnd()) {
//                 stations[iterT->getEnd()].addHeuristic(penaltyVal);
//             }
//         }
//     }
// }

//PREVIOUS VERSION OF HEURISTICS FUNCTION (still used in main)
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

    // // penalty for entering a dead end branch vvvvv
    // // merged with penalty for moving away from large masses of connected stations
    // // -> stations are hard coded from north-west station clockwise
    // // ONLY CONSIDERING THE LONGEST BRANCHES CURRENTLY
    // int branchStarts[] = {
    //     26 //3rd Ave - 138th St
    // };

    // //Check if the station is going into a dead end branch
    // for (size_t i = 0; i < (sizeof(branchStarts)/sizeof(int)); i++) {
    //     if (branchStarts[i] == nextId) {
    //         sum += penaltyVal;
    //     }
    // }

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

