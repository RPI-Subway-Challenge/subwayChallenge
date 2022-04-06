//																	D O W N    W I T H    M A T T H E W    A H N
#include <iostream>
#include <cmath>
#include "station.h"
#include <queue>
#include <set>
#include <utility>
#include<unordered_map>

typedef std::pair<Station, int > pair;

// return manhattan distance between two stations
double manhattanDistance(Station s1, Station s2){
    double diffX = std::abs( s1.getCords().first - s2.getCords().first );
    double diffY = std::abs( s1.getCords().second - s2.getCords().second );
    return diffX+diffY;
}

// Return actual distance (in MILES) between two stations
//  Distance between LONGITUDE and LATITDUE coords is as follows
//  3963.0 * arccos[(sin(lat1) * sin(lat2)) + cos(lat1) * cos(lat2) * cos(long2 – long1)]
//  .first  gives longitude
//  .second gives latitude
double realDistance(const Station& s1,const Station& s2){
    double lat1 = s1.getCords().second;
    double lat2 = s2.getCords().second;
    double long1 = s1.getCords().first;
    double long2 = s2.getCords().first;
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



// takes vector of pairs walkable and returns index with longest distance
int findLongest(std::vector<std::pair<int,double> > walkable){
    int longest = 0;
    for(int i = 1; i != walkable.size(); i++){
        if(walkable[i].second > walkable[longest].second){ longest = i; }
    }
    return longest;
}



// takes station returns vector of x nearest stations indicies
// O(x*num of stations) for single station
std::vector<std::pair<int,double> > walkableNumber(int stationIndex, int x, std::vector<Station> & stationVec){

    std::vector<std::pair<int,double> > walkable(x);      // pair < neighborIndex, distance >
    int longest = 0;                                     // index in walkable of farthest away neighbor

    if(x < 1){std::cerr << "ERROR: X in walkableNumber must be >= 1\n"; return walkable;}

    if(x >= stationVec.size()){std::cerr << "ERROR: X in walkableNumber must be < stationVec.size()\n"; return walkable;}

    // put first x stations in walkable
    for(int i = 0; i != x; i++){
        // if stationIndex in first x make distance very long so replaced first
        if(i == stationIndex){
            walkable[i] = std::make_pair(i, 9999999999999999);
            longest = i;
        // not stationIndex
        }else{
            walkable[i] = std::make_pair(i, realDistance(stationVec[stationIndex],stationVec[i]));
            // check against longest
            if(realDistance(stationVec[stationIndex],stationVec[i]) > walkable[longest].second){
                longest = i;
            }
        }
    }

    // check stations from index x to end
    for(int i = x; i != stationVec.size(); i++){
        if(i != stationIndex){
            // check against longest
            if( realDistance(stationVec[stationIndex],stationVec[i]) > walkable[longest].second ){
                walkable[longest] = std::make_pair(i, realDistance(stationVec[stationIndex],stationVec[i]));
                longest = findLongest(walkable);
            } 
        }
    }
    return walkable;
}

// create trip for all walkable station from a station for all stations given from walkableNumber
// O(x*num of stations^2) for all stations
void createStationsTrips(int x, int k, std::vector<Station> & stationVec){

    // Since no data is known about the stations atm, the trips are intializased as being open all days every hour
    // Creating basic time vector full of transportation data. (temporary filler data)
    std::list<Time> weekdayTimes;
    std::list<Time> weekendsTimes;
    for(int i=0; i<24; i++){ // for every hour
        for(int j=0; j<5; j++){ // day
            weekdayTimes.push_back(Time(j, i, 0));
        }
        for(int j=5; j<7; j++){
            weekendsTimes.push_back(Time(j, i, 0));
        }
    }
    // create trips for each station to their walkable stations
    for(int i=0; i<stationVec.size(); i++){
        std::vector<std::pair<int,double> > walkableStations = walkableNumber(i, x, stationVec);
        for(int j=0; j<walkableStations.size(); j++){
            int duration = (int) timeDistance(walkableStations[i].second, k);
            Trip(i, walkableStations[i].first, duration, 't', weekendsTimes, weekdayTimes);
        }
    }
}

std::vector<double> Dijkstra(std::vector<Station> & stations, int startingID, int goalID){
    std::vector<double> dists;
    std::unordered_map<int, int> parents;

    for(int i = 0; i < stations.size(); i++)
        dists.push_back(1000000);
    dists[startingID] = 0; //initialize start to 0

    std::set<int> visited; //set containing vertices where shortest path has been found
    int curr_id = startingID;
    while(visited.size() < stations.size()){
        //get adjacent vertices of curr vertex
        std::list<Trip> trips = stations[curr_id].getTrips();
        for (Trip t: trips){
            int t_index = t.getEnd();
            double temp_dist = realDistance(stations[curr_id], stations[t_index]);
            if(dists[curr_id] + temp_dist < dists[t_index]){
                //if the dist is smaller, update
                dists[t_index] = dists[curr_id] + temp_dist;
                parents[t_index] = curr_id;
            }
        }
        visited.insert(curr_id);

        //find unvisited vertex w smallest distance
        double minDist = 100000000;
        for(int i = 0; i < stations.size(); i++){
            if(visited.find(i) == visited.end()){
                if(dists[i] < minDist){
                    curr_id = i;
                    minDist = dists[i];
                }
            }
        }
        //resulting curr id has the min dist
    }

    std::list<int> path;
    bool path_found = true;
    int curr = goalID;
    path.push_back(curr);
    while(curr != startingID){
        if(parents.find(curr) == parents.end()){
            std::cout << "No path exists" << std::endl;
            path_found = false;
            break;
        }
        else{
            curr = parents[curr];
            path.push_front(curr);
        }
    }

    if(path_found){
        std::cout << "Found the goal with Dijkstra's" << std::endl;
        std::cout << "Size of path: " << path.size() << std::endl;
        int c = 0;
        for (int i : path){
            std::cout << i;
            if(++c < path.size())
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }
    //currently returns distances from start
    return dists;
}

//caped-doshi version of BFS
std::list<int> BFS_3(std::vector<Station> & stations, int startingID, int goalID){ 
    std::queue<pair> bfs_queue;
    bool goal_found = false;

    Station init_station = stations[startingID];

    pair init_pair;
    init_pair.first = init_station;
    init_pair.second = -1;

    std::unordered_map<int, int> parents;

    std::set<int> visited; //all ids that have been visited

    pair end_pair;

    bfs_queue.push(init_pair);

    while(bfs_queue.size() > 0){   // loop until find goal id
        pair q_front = bfs_queue.front();
        bfs_queue.pop();
        int start_id = q_front.first.getId();

        if (start_id == goalID){
            std::cout << "Found the goal with BFS" << std::endl;
            //std::cout << visited.size() << std::endl;
            end_pair = q_front;
            goal_found = true;
            break;
        }
        else{
            visited.insert(start_id);
            std::vector<Station> children;
            std::list<Trip> trips = q_front.first.getTrips();

            for(Trip t: trips){
                int end_index = t.getEnd();
                //std::cout << end_index << std::endl;
                if (visited.find(end_index) == visited.end()){
                    parents[end_index] = start_id;
                    bfs_queue.push(std::make_pair(stations[end_index], start_id));
                }
                if(parents[start_id] != end_index)
                    parents[end_index] = start_id;
                    //std::cout << bfs_queue.size() << std::endl;
            }
        }
    }

    //reverse engineer path from the parents unordered map 
    std::list<int> path;
    if(goal_found){
        int curr_index = goalID;
        path.push_back(curr_index);
        while(curr_index != startingID){
            //std::cout << curr_index << std::endl;
            curr_index = parents[curr_index];
            path.push_front(curr_index);
        }
    }
    
    return path;

}

std::vector<Station> BFS(std::vector<Station> stations, int startingID, int goalID) {           // ? pass stations by reference
    std::queue <std::pair <Station, std::vector <Station> > > q;

    Station initStation = stations[startingID];             // ? making a copy of start station
    std::vector<Station> initList;                     // ? whyb not list

    std::pair<Station, std::vector<Station> > initPair;
    initPair = std::make_pair(initStation, initList);

    q.push(initPair);

    while (!q.empty()) {
        // Get the last element and pop it
        std::pair <Station, std::vector <Station> > curr = q.back();
        q.pop();

        // Split the pair into station and path parts
        Station currStation = curr.first;
        std::vector<Station> currPath = curr.second;

        // Core of BFS. Check not visited, check if goal, add to queue
        std::cout   << "Station ID: "      << (currStation).getId() 
        << " Name: " << (currStation).getName() << "\n";

        if (currStation.isVisited()) {
            continue;
        } else if (currStation.getId() == goalID) {
            return currPath;
        } else {
            currStation.setVisited(true);

            std::list<Trip> canGo = currStation.getTrips();
            std::list<Trip>::iterator it;

            for (it = canGo.begin(); it != canGo.end(); it++) {
                Station nextStation = stations[(*it).getEnd()];
            
                std::vector<Station> modifiedPath = currPath;
                modifiedPath.push_back(nextStation);

                std::pair <Station, std::vector <Station> > newPair = std::make_pair(nextStation, modifiedPath);
                q.push(newPair);
            }
        }
    }

    return initList;
}



std::list<int> BFS2(std::vector<Station> & stations, int startingID, int goalID) {
    std::list <int> q;
    std::list <int> output;

    int current = startingID;

    // put start in queue and mark visited
    q.push_back(startingID);
    stations[startingID].setVisited(true);

    while (!q.empty()) {

        current = q.front();
        output.push_back(current);
        q.pop_front();


        // Core of BFS. Check not visited, check if goal, add to queue
        std::cout   << "Station ID: "      << (stations[current]).getId() 
        << " Name: " << (stations[current]).getName() << "\n";

        // check if goal
        if( current == goalID ){
            return output;
        }

        std::list<Trip>::iterator iter;
        for(iter = stations[current].getTrips().begin(); iter != stations[current].getTrips().end(); iter++){
            if(stations[iter->getEnd()].isVisited() == false){
                stations[iter->getEnd()].setVisited(true);
                q.push_back(iter->getEnd());
            }
            //std::cout << i << " HELLo\n";
            //i++;
        }
    }

    return output;
}




// takes station and returns value
int heuristic(std::vector<Station> & stations, int id){
    int sum = 0;

    // add 10 if not visited
    if(stations[id].isVisited() == false){
        sum += 10;
    }
    
    // add 1 for visited neighbor, 5 for unvisited neighbor
    std::list<Trip> trips = stations[id].getTrips();
    std::list<Trip>::iterator iterT;
    for(iterT = trips.begin(); iterT != trips.end(); iterT++){
        if( stations[iterT->getEnd()].isVisited() == false ){
            sum += 4;               // add 4 for every unvisited neighboring station
        }
        sum++;                      // add 1 for every neighboring station
    }

    // add 1 for every line
    std::list<std::pair<std::string,int> > lines = stations[id].getLines();
    std::list<std::pair<std::string,int> >::iterator iterL;
    for(iterL = lines.begin(); iterL != lines.end(); iterL++){
        sum++;
    }

    return sum;
}