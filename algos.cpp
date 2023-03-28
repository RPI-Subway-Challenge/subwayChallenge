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


//BFS test algorithm
std::vector<int> testAlg(std::vector<std::vector<int>> stations, int start) {
    //Vector to store path tree
    std::vector<int> path;
    //Visited stations stored here (0 = unvisited, 1 = visited)
    std::vector<int> visited(451, 0);

    //Queue for bfs
    std::queue<int> queue;

    //Add starting node and mark as visited
    visited[start] = 1;
    queue.push(start);

    while (!queue.empty()) {
        //Pop a vertex from queue and add to path
        int s = queue.front();
        path.push_back(s);
        queue.pop();

        //Find all neighbors of dequeued vertex
        for (int i = 1; i < 451; i++) {
            if (stations[s][i] == 1) {
                if (visited[i] == 0) {
                    visited[i] = 1;
                    queue.push(i);
                }
            }
        }
    }
    return path;
}
    

int getDegree(int neighbor, std::vector<std::vector<int>> & stations){
    int degree = 0;
    for(int i = 0; i != stations.size(); i++){
        if(stations[neighbor][i] == 1 && neighbor != i){
            degree++;
        }
    }
    return degree;
}



// take vector of indicies and sort from smallest degree to largest
std::vector<int> degreeSort(std::vector<int> neighbors, std::vector<std::vector<int>> & stations){

    std::vector<int> degrees(neighbors.size());
    for (int i = 0; i < neighbors.size(); i++) {
        int degree = 0;
        for (int j = 0; j < stations.size(); j++) {
            if (stations[neighbors[i]][j] == 1) {
                degree++;
            }
        }
        degrees[i] = degree;
    }

    // Sort the nodes by their degree
    std::sort(neighbors.begin(), neighbors.end(), [&](int a, int b) {
        return degrees[a] < degrees[b];
    });

    return neighbors;

}




std::vector<int> bfs (int start, std::vector<std::vector<int>> & stations) {

    std::queue<int> q;
    std::vector<bool> visited(stations.size(), false);
    std::vector<int> path;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        path.push_back(current);

        std::vector<int> neighbors;
        for (int i = 0; i < stations[current].size(); i++) {
            if (stations[current][i] == 1 && !visited[i]) {
                q.push(i);
                neighbors.push_back(i);
                visited[i] = true;
            }
        }
        neighbors = degreeSort(neighbors,stations);
        // q.push(neighbors)
    }

    return path;
}




std::vector<int> aToB(std::vector<std::vector<int>> & graph, int start, int end) {
    std::queue<int> q;
    std::vector<bool> visited(graph.size(), false);
    std::vector<int> parent(graph.size(), -1);

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < graph.size(); ++neighbor) {
            if (graph[node][neighbor] == 1 && !visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
                parent[neighbor] = node;
            }
        }
    }

    // build shortest path from start to end
    std::vector<int> path;
    if (!visited[end]) {
        return path; // no path exists
    }

    for (int node = end; node != -1; node = parent[node]) {
        path.push_back(node);
    }

    reverse(path.begin(), path.end());
    return path;
}




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

