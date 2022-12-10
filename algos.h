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
#include <functional>
#include <boost/heap/fibonacci_heap.hpp>
#include "station.h"
#include "subwayGraph.h"

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
        requires std::copyable<decltype(nk)> && std::copyable<decltype(ek)>;
        {g.order()} -> std::convertible_to<size_t>;
        {g[nk]} -> std::same_as<const typename T::Node &>;
        {g[ek]} -> std::same_as<const typename T::Edge &>;
        {g[nk].val()} -> std::convertible_to<typename T::NodeValT>;
        {g[ek].val()} -> std::convertible_to<typename T::EdgeValT>;
        {g.key(g[nk])} -> std::same_as<decltype(nk)>;
        {g.key(g[ek])} -> std::same_as<decltype(ek)>;
        {g[ek].headKey()} -> std::convertible_to<typename T::Node>;
        {g[nk].outEdges()} -> std::ranges::range;
        {*g[nk].outEdges().begin()} -> std::convertible_to<typename T::Edge>;
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
    using PriorityQ = boost::heap::fibonacci_heap<NodeKeyT, decltype(cmp)>;
    PriorityQ pq{cmp};
    std::unordered_map<NodeKeyT, typename PriorityQ::handle_type> handleTo;
    costTo[src] = 0;
    handleTo[src] = pq.push(src);
    auto minCostNK{src};
    do {
        auto nk{pq.top()};
        pq.pop();
        handleTo.erase(nk);
        for (const auto &edge: g[nk].outEdges()) {
            auto newCost{costTo[nk] + costFunc(edge)};
            if (NodeKeyT successorK{edge.headKey()};
                [&] () {
                    if constexpr (Map<CostTab>)
                        if (!costTo.contains(successorK)) return true;
                    return newCost < costTo[successorK];
                } ()
            ) {
                costTo[successorK] = newCost;
                if (handleTo.contains(successorK)) {
                    pq.decrease(handleTo[successorK]);
                } else {
                    handleTo[successorK] = pq.push(successorK);
                }
                edgeTo[successorK] = g.key(edge);
                minCostNK = successorK;
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
 * @tparam Dense whether to use a dense data structure for the returning edge table and
 * cost table. Defaults to true only when the graph node key type is std::size_t.
 * Therefore, if std::size_t is used for the graph node key type, it is assumed by
 * default that the key can be used to index into an array of size g.order().
 * 
 * @param g the input graph
 * @param src key to the source node. The referenced node must exist in the graph.
 * @param costFunc the function object to calculate the cost of an edge. It should take
 * an edge by const &, and returns the cost. Example signature:
 * CostT (const G::Edge &edge).
 */
template<
    Graph G, bool Dense = std::same_as<typename G::NodeKeyT, size_t>,
    class CostF = decltype([] (const G::Edge &e) {return e.val();})
>
constexpr auto search(const G &g, typename G::NodeKeyT src, CostF costFunc = {}) {
    using CostT = decltype(costFunc(typename G::Edge{}));
    using EdgeTab = std::conditional_t<Dense,
        std::unique_ptr<typename G::EdgeKeyT []>,
        std::unordered_map<typename G::NodeKeyT, typename G::EdgeKeyT>
    >;
    using CostTab = std::conditional_t<Dense,
        std::unique_ptr<CostT []>,
        std::unordered_map<typename G::NodeKeyT, CostT>
    >;
    auto edgeTo{[&] () {
        if constexpr (Map<EdgeTab>)
            return EdgeTab{};
        return std::make_unique_for_overwrite<typename G::EdgeKeyT []>(g.order());
    } ()};
    auto costTo{[&] () {
        if constexpr (Map<CostTab>)
            return CostTab{};
        auto p{std::make_unique_for_overwrite<CostT []>(g.order())};
        static_assert(std::is_arithmetic_v<CostT>,
            "Unsupported value type for cost");
        if constexpr (std::integral<CostT>)
            std::fill_n(p, g.order(), std::numeric_limits<CostT>::max());
        else if constexpr (std::floating_point<CostT>)
            std::fill_n(p, g.order(), std::numeric_limits<CostT>::infinity());
        return p;
    } ()};
    return Result{ /* TODO make sure evaluation order is correct! */
        findMinCost(g, src, edgeTo, costTo, costFunc), std::move(edgeTo),
        std::move(costTo)
    };
}

template<class NodeKeyT>
constexpr auto pathTraceback(auto edgeTo, NodeKeyT src, NodeKeyT dst) {
    std::deque<NodeKeyT> path;
    return path;
}

}


constexpr void findMinCostPath(std::vector<Station> &stations) {
    const SubwayGraph g{
        stations, {}, [] (Trip &eRep) -> decltype(auto) {return eRep.getDuration();}};
    ucs::Result r{ucs::search(g, 0)};
}

#endif //SUBWAYCHALLENGE_ALGOS_H
