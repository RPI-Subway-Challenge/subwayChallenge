//																	D O W N    W I T H    M A T T H E W    A H N
#include <iostream>
#include <cmath>
#include "station.h"


// return manhattan distance between two stations
double manhattanDistance(Station s1, Station s2){
    double diffX = std::abs( s1.getCords().first - s2.getCords().first );
    double diffY = std::abs( s1.getCords().second - s2.getCords().second );
    return diffX+diffY;
}



// return actual distance between two stations using pythagorean theorem
double realDistance(Station s1, Station s2){
    double diffX = std::abs( s1.getCords().first - s2.getCords().first );
    double diffY = std::abs( s1.getCords().second - s2.getCords().second );
    return std::sqrt( std::pow(diffX,2) + std::pow(diffX,2) );
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