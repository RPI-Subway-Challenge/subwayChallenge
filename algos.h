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

template<class T>
concept Map =
    requires (T m, typename T::key_type k) {
        {m[k]} -> std::same_as<typename T::mapped_type &>;
    };

/* uniform-cost search */
namespace ucs {

template<class T>
concept Graph = 
    requires (T g, typename T::NodeKeyT nk, typename T::EdgeKeyT ek) {
        {g.order()} -> std::convertible_to<size_t>;
        {g[nk]} -> std::convertible_to<typename T::NodeT>;
        {g[ek]} -> std::convertible_to<typename T::EdgeT>;
        {g[nk].neighbors()} -> std::ranges::range; /* TODO */
        {*g[nk].neighbors().begin()} -> std::convertible_to<typename T::EdgeKeyT>;
        {g[ek].head()} -> std::convertible_to<typename T::NodeKeyT>; /* TODO */
    };

template<class NodeKeyT, class EdgeTab, class CostTab>
struct Result {
    NodeKeyT minCostNodeKey;
    EdgeTab edgeTo;
    CostTab costTo;
};

/**
 * helper for the uniform cost search routine
 * modifies: edgeTo, costTo
 * @returns the node key of the destination with minimum cost
 */
template<Graph G, class NodeKeyT, class EdgeTab, class CostTab>
constexpr auto findMinCost(
    const G &g, NodeKeyT src, EdgeTab &edgeTo, CostTab &costTo, auto costFunc
) {
    auto cmp{[&] (const NodeKeyT &nk0, const NodeKeyT &nk1) {
        return costTo[nk0] < costTo[nk1];
    }};
    std::priority_queue<NodeKeyT, std::vector<NodeKeyT>, decltype(cmp)> pq{cmp};
    costTo[src] = 0;
    pq.push(src);
    auto minCostNK{std::move(src)};
    do {
        auto pqNode{pq.extract()};
        const auto &nk{pqNode.value()};
        for (const auto &edgeKey: g[nk].neighbors()) {
            auto newCost{costTo[nk] + costFunc(g[edgeKey])};
            if (NodeKeyT &&successorKey{g[edgeKey].head()};
                [&] () {
                    if constexpr (Map<CostTab>) {
                        if (!costTo.contains(successorKey)) return true;
                    }
                    return newCost < costTo[successorKey];
                } ()
            ) {
                if (pq.contains(successorKey)/* TODO */) {
                    pq.decreaseKey(successorKey, newCost)/* TODO */;
                } else {
                    costTo[successorKey] = newCost;
                    pq.push(successorKey);
                }
                minCostNK = std::move(successorKey);
                edgeTo[minCostNK] = edgeKey;
            }
        }
    } while (!pq.empty());
    return minCostNK;
}

/**
 * @brief A uniform-cost search. Finds the node with the lowest cost along with the
 * cost to all other nodes and the path to them from a specific starting node.
 * 
 * @tparam G the graph data structure
 * @tparam NodeKeyT the type of the key to index into the graph to access the node.
 * Highly recommended to be trivially copiable. G[NodeKeyT] -> NodeT. Note: if you use
 * std::size_t for this type, it is assumed by default that it can be used to index into
 * an array of size g.order().
 * @tparam EdgeTab table of edge keys. map[NodeKeyT] -> EdgeKeyT. Defaults to
 * std::unordered_map, unless when src is std::size_t it defaults to dynamic array of
 * size g.order().
 * @tparam CostTab cost table. map[NodeKeyT] -> CostT. Defaults to std::unordered_map,
 * unless when src is std::size_t it defaults to dynamic array of size g.order().
 * 
 * @param g the input graph
 * @param src key to the source node. The referenced node must exist in the graph.
 * @param costFunc the function object to calculate the cost of an edge. It should take
 * an edge, preferably by const &, and returns the cost. Recommended example signature:
 * G::EdgeValT (const G::EdgeT &edge).
 */
template<
    Graph G,
    class EdgeTab = std::conditional_t<std::same_as<typename G::NodeKeyT, size_t>,
        std::unique_ptr<typename G::EdgeKeyT []>,
        std::unordered_map<typename G::NodeKeyT, typename G::EdgeKeyT>
    >,
    class CostTab = std::conditional_t<std::same_as<typename G::NodeKeyT, size_t>,
        std::unique_ptr<typename G::EdgeValT []>,
        std::unordered_map<typename G::NodeKeyT, typename G::EdgeValT>
    >
>
constexpr auto search(
    const G &g, const typename G::NodeKeyT &src,
    auto costFunc = [] (const G::EdgeT &e) {return e.val();}
) requires /*std::copy_constructible<NodeKeyT> && std::movable<NodeKeyT> &&*/
std::same_as<decltype(costFunc(typename G::EdgeT{})), typename G::EdgeValT> {
    auto edgeTo{[&] () {
        if constexpr (Map<EdgeTab>)
            return EdgeTab{};
        return std::make_unique<typename G::EdgeKeyT []>(g.order());
    } ()};
    auto costTo{[&] () {
        if constexpr (Map<CostTab>)
            return CostTab{};
        using ValT = CostTab::element_type;
        auto p{std::make_unique_for_overwrite<typename G::EdgeValT []>(g.order())};
        static_assert(std::is_arithmetic_v<ValT>,
            "Unsupported value type for cost, i.e., the edge value type");
        if constexpr (std::integral<ValT>)
            std::fill_n(p, g.order(), std::numeric_limits<ValT>::max());
        else if constexpr (std::floating_point<ValT>)
            std::fill_n(p, g.order(), std::numeric_limits<ValT>::infinity());
        return p;
    } ()};
    return Result{ /* TODO make sure evaluation order is correct! */
        findMinCost(g, src, edgeTo, costTo, costFunc), std::move(edgeTo),
        std::move(costTo)
    };
}

}

#endif //SUBWAYCHALLENGE_ALGOS_H
