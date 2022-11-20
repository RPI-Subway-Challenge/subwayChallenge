//
// Created by Simon Sandrew on 3/7/22.
//

#ifndef SUBWAYCHALLENGE_ALGOS_H
#define SUBWAYCHALLENGE_ALGOS_H

#include <vector>
#include "station.h"

double realDistance(const Station& s1, const Station& s2);

int heuristic(std::vector<Station> & stations, int currId, int nextId);

// Functions for transversal in main

// This function perform the move from one station to another
Station* moveByTrip(std::vector<Station>& stations, Station* startStation, Trip& tripTaken, int& currentTime);

// This function compress continious station with only 2 neibhor station into one station object
void branchReduction(std::vector<Station>& stations);

// This function prints out all the stations in station list and prints out the status
void printStations(std::vector<Station>& stations);
#endif //SUBWAYCHALLENGE_ALGOS_H
