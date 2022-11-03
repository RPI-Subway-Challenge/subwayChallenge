//
// Created by Simon Sandrew on 3/7/22.
//

#ifndef SUBWAYCHALLENGE_ALGOS_H
#define SUBWAYCHALLENGE_ALGOS_H

#include <vector>
#include <queue>
#include <limits>
#include <concepts>
#include <unordered_map>
#include "station.h"

double realDistance(const Station& s1, const Station& s2);

int heuristic(std::vector<Station> & stations, int currId, int nextId);

// Functions for transversal in main

// This function perform the move from one station to another
Station* moveByTrip(std::vector<Station>& stations, Station* startStation, Trip& tripTaken, int& currentTime);

template<class EdgeTab, class CostTab>
struct UCSResult {
    EdgeTab edgeTo;
    CostTab costTo;
};

template<class T>
concept MapT =
    requires(T m, typename T::key_type k) {
        {m[k]} -> std::same_as<typename T::mapped_type &>;
    };

// helper for the uniform cost search routine
template<
    class GraphT,
    class NodeT,
    class EdgeTab,  /* Edge table: map[NodeT] -> EdgeT */
    class CostTab,  /* Cost table: map[NodeT] -> CostT */
    class PQT       /* priority queue */
>
void ucs(const GraphT &g, const NodeT &src, EdgeTab &edgeTo, CostTab &costTo, PQT &pq) {
    costTo[src] = 0;
    pq.push(src);
    do {
        auto n{std::move(pq.extract().value())};
        for (const auto &edge: g[n].neighbors()/* TODO */) {
            auto successor{edge.head()/* TODO */};
            auto newCost{costTo[n] + edge.val()};
            if ([&] () {
                    if constexpr (MapT<CostTab>) {
                        if (!costTo.contains(successor)) return true;
                    }
                    return newCost < costTo[successor];
                } ()
            ) {
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
 * @tparam EdgeTab edge table. map[NodeT] -> EdgeT.
 * When NodeT is size_t, std::vector is recommended.
 * @tparam CostTab cost table. map[NodeT] -> CostT.
 * When NodeT is size_t, std::vector is recommended.
 */
template<
    class GraphT,
    class NodeT,
    class EdgeTab = std::unordered_map<NodeT, typename GraphT::EdgeT>,
    class CostTab = std::unordered_map<NodeT, typename GraphT::EdgeValT>
>
UCSResult<EdgeTab, CostTab> ucs(const GraphT &g, const NodeT &src) {
    using ValT = CostTab::value_type;
    auto makeTable{[&] <class TabType> (TabType) {
        if constexpr (MapT<TabType>)
            return TabType{};
        else if constexpr (std::floating_point<ValT>)
            return TabType(g.order(), std::numeric_limits<ValT>::infinity());
        else
            return TabType(g.order(), std::numeric_limits<ValT>::max());
    }};
    auto edgeTo{makeTable(EdgeTab{})};
    auto costTo{makeTable(CostTab{})};
    std::priority_queue<NodeT, std::vector<NodeT>,
        decltype([&] (const NodeT &n1, const NodeT &n2) {
            return costTo[n1] < costTo[n2];
        })>
        pq;
    ucs(g, src, edgeTo, costTo, pq);
    return {std::move(edgeTo), std::move(costTo)};
}

#endif //SUBWAYCHALLENGE_ALGOS_H
