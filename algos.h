//
// Created by Simon Sandrew on 3/7/22.
//

#ifndef SUBWAYCHALLENGE_ALGOS_H
#define SUBWAYCHALLENGE_ALGOS_H

#include <queue>
double realDistance(const Station& s1,const Station& s2);

int heuristic(std::vector<Station> & stations, int currId, int nextId);

// Functions for transversal in main

// This function perform the move from one station to another
Station* moveByTrip(std::vector<Station>& stations, Station* startStation, Trip& tripTaken, int& currentTime);

template<class EdgeMap, class CostMap>
struct UCSResult {
    EdgeMap edgeTo;
    CostMap costTo;
};

// helper for the uniform cost search routine
template<
    class GraphT,
    class NodeT,
    class EdgeMap,  /* map[NodeT] -> EdgeT */
    class CostMap,  /* map[NodeT] -> CostT */
    class PQT       /* priority queue */
>
void ucs(const GraphT &g, const NodeT &src, EdgeMap &edgeTo, CostMap &costTo, PQT &pq) {
    costTo[src] = 0;
    pq.push(src);
    do {
        auto n{pq.top()};
        pq.pop();
        for (const auto &edge: g[n].neighbors()/* TODO */) {
            auto successor{edge.head()/* TODO */};
            auto d{costTo[successor]},
                newCost{costTo[n] + edge.val()};
            if (/* TODO d indicates "not visited" ||*/ newCost < d) {
                edgeTo[successor] = edge;
                if (pq.contains(successor)/* TODO */) {
                    pq.decreaseKey(successor, newCost)/* TODO */;
                } else {
                    costTo[successor] = newCost;
                    pq.push(successor);
                }
            }
        }
    } while (!pq.empty());
}

/**
 * @brief The uniform cost search. Finds the lowest cost to all other nodes and the path
 * to them from a specific starting node.
 * 
 * @tparam GraphT the graph data structure
 * @tparam NodeT the node type
 * @tparam EdgeMap map[NodeT] -> EdgeT
 * @tparam CostMap map[NodeT] -> CostT
 */
template<class GraphT, class NodeT, class EdgeMap, class CostMap>
UCSResult<EdgeMap, CostMap> ucs(const GraphT &g, const NodeT &src) {
    EdgeMap edgeTo; /* TODO initialize */
    CostMap costTo; /* TODO initialize */
    std::priority_queue<NodeT, std::vector<NodeT>,
        decltype([&] (const NodeT &n1, const NodeT &n2) {
            return costTo[n1] < costTo[n2];
        })>
        pq;
    ucs(g, src, edgeTo, costTo, pq);
    return {std::move(edgeTo), std::move(costTo)};
}

#endif //SUBWAYCHALLENGE_ALGOS_H
