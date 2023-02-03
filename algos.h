//
// Created by Simon Sandrew on 3/7/22.
//

#ifndef SUBWAYCHALLENGE_ALGOS_H
#define SUBWAYCHALLENGE_ALGOS_H

#include <vector>
#include "station.h"

double realDistance(const Station& s1, const Station& s2);

int heuristic(std::vector<Station> & stations, int currId, int nextId);
std::vector<int> testAlg(std::vector<std::vector<int>> stations, int start);
std::vector<int> shortestPath(std::vector<std::vector<int>> stations, int start);

// Functions for transversal in main

// This function perform the move from one station to another
Station* moveByTrip(std::vector<Station>& stations, Station* startStation, Trip& tripTaken, int& currentTime);

#endif //SUBWAYCHALLENGE_ALGOS_H
