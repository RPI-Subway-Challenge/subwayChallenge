//
// Created by Simon Sandrew on 3/7/22.
//

#ifndef SUBWAYCHALLENGE_ALGOS_H
#define SUBWAYCHALLENGE_ALGOS_H
double realDistance(const Station& s1,const Station& s2);
std::vector<Station> BFS(std::vector<Station> stations, int startingID, int goalID);
std::list<int> BFS2(std::vector<Station> & stations, int startingID, int goalID);
std::list<int> BFS_3(std::vector<Station> & stations, int startingID, int goalID);
std::vector<double> Dijkstra(std::vector<Station> & stations, int startingID, int goalID);
int heuristic(std::vector<Station> & stations, int id);
#endif //SUBWAYCHALLENGE_ALGOS_H
