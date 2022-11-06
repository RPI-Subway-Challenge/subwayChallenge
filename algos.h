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
#include <memory>
#include <ranges>
#include "station.h"

using std::size_t;

double realDistance(const Station& s1, const Station& s2);

int heuristic(std::vector<Station> & stations, int currId, int nextId);

// Functions for transversal in main

// This function perform the move from one station to another
Station* moveByTrip(std::vector<Station>& stations, Station* startStation, Trip& tripTaken, int& currentTime);

template<class NodeKeyT, class EdgeTab, class CostTab>
struct UCSResult {
    NodeKeyT minCostNodeKey;
    EdgeTab edgeTo;
    CostTab costTo;
};

template<class T>
concept MapT =
    requires(T m, typename T::key_type k) {
        {m[k]} -> std::same_as<typename T::mapped_type &>;
    };

// helper for the uniform cost search routine
template<class GraphT, class NodeKeyT, class EdgeTab, class CostTab, class PQT>
constexpr auto ucs(
    const GraphT &g, NodeKeyT src, EdgeTab &edgeTo, CostTab &costTo, PQT &pq,
    auto costFunc
) {
    costTo[src] = 0;
    pq.push(std::move(src));
    NodeKeyT minCostNK; /* TODO init and update */
    do {
        auto pqNode{pq.extract()};
        const auto &nk{pqNode.value()};
        for (const auto &edge: g[nk].neighbors()/* TODO */) {
            const auto &successor{edge.head(NodeKeyT{})/* TODO */};
            auto newCost{costTo[nk] + edge.val()};
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
                    pq.push(std::move(successor));
                }
            }
        }
    } while (!pq.empty());
    return minCostNK;
}

/**
 * @brief The uniform cost search. Finds the node with the lowest cost along with the
 * cost to all other nodes and the path to them from a specific starting node.
 * 
 * @tparam GraphT the graph data structure
 * @tparam NodeKeyT the type of the key to index into the graph to access the node.
 * Highly recommended to be trivially copiable. GraphT[NodeKeyT] -> NodeT.
 * @tparam EdgeTab edge table. map[NodeKeyT] -> EdgeT. Defaults to std::unordered_map,
 * unless when src is std::size_t it defaults to dynamic array of size g.order().
 * @tparam CostTab cost table. map[NodeKeyT] -> CostT. Defaults to std::unordered_map,
 * unless when src is std::size_t it defaults to dynamic array of size g.order().
 * 
 * @param g the input graph
 * @param src key to the source node. The referenced node must exist in the graph.
 * @param costFunc the function object to calculate the cost of an edge
 */
template<
    class GraphT, class NodeKeyT,
    class EdgeTab = std::conditional_t<std::same_as<NodeKeyT, size_t>,
        std::unique_ptr<typename GraphT::EdgeT []>,
        std::unordered_map<NodeKeyT, typename GraphT::EdgeT>
    >,
    class CostTab = std::conditional_t<std::same_as<NodeKeyT, size_t>,
        std::unique_ptr<typename GraphT::EdgeValT []>,
        std::unordered_map<NodeKeyT, typename GraphT::EdgeValT>
    >
>
constexpr auto ucs(
    const GraphT &g, const NodeKeyT &src,
    auto costFunc = [] (const GraphT::EdgeT &e) {return e.val();}
) {
    auto edgeTo{[&] () {
        if constexpr (MapT<EdgeTab>)
            return EdgeTab{};
        return std::make_unique<typename GraphT::EdgeT []>(g.order());
    } ()};
    auto costTo{[&] () {
        if constexpr (MapT<CostTab>)
            return CostTab{};
        using ValT = CostTab::element_type;
        auto p{std::make_unique_for_overwrite<typename GraphT::EdgeValT []>(g.order())};
        static_assert(std::is_arithmetic_v<ValT>, "Unsupported value type for cost");
        if constexpr (std::integral<ValT>)
            std::fill_n(p, g.order(), std::numeric_limits<ValT>::max());
        else if constexpr (std::floating_point<ValT>)
            std::fill_n(p, g.order(), std::numeric_limits<ValT>::infinity());
        return p;
    } ()};
    std::priority_queue<NodeKeyT, std::vector<NodeKeyT>,
        decltype([&] (const NodeKeyT &nk0, const NodeKeyT &nk1) {
            return costTo[nk0] < costTo[nk1];
        })>
        pq;
    return UCSResult{ /* TODO make sure evaluation order is correct! */
        ucs(g, src, edgeTo, costTo, pq, costFunc), std::move(edgeTo), std::move(costTo)
    };
}

#endif //SUBWAYCHALLENGE_ALGOS_H
