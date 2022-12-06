#pragma once

#include <cstddef>
#include <vector>
#include <concepts>
#include "station.h"
#include "trip.h"


/**
 * @brief The coupler between the data structure and the search algorithm.
 * 
 * @tparam NodeValT Node value type. Defaults to Station &. Reference or pointers should
 * be used as the graph does not own the value object.
 * 
 * @tparam EdgeValT Edge value type. Defaults to Trip &. Reference or pointers should
 * be used as the graph does not own the value object.
 */
template<class NValT = Station &, class EValT = Trip &>
class SubwayGraph {
public:
    struct NodeT {
        using ValT = NValT;
        NodeT(ValT &v): v{v} {}
        [[nodiscard]] const ValT &val() const {return v;}
        [[nodiscard]] ValT &val() {return v;}
        [[nodiscard]] const auto &neighbors() const {return v.getTrips();}
    private:
        ValT v;
    };

    struct EdgeT {
        using ValT = EValT;
        EdgeT(ValT &v): v{v} {}
        [[nodiscard]] const ValT &val() const {return v;}
        [[nodiscard]] ValT &val() {return v;}
    private:
        ValT v;
    };

    using NodeKeyT = std::size_t;
    using EdgeKeyT = EdgeT *;
    using NodeValT = NValT;
    using EdgeValT = EValT;

    SubwayGraph(std::vector<NValT> &stations): nodes{stations} {
        static_assert(!std::same_as<NodeKeyT, EdgeKeyT>,
            "Error: NodeKey and EdgeKey has type clashes.");
        static_assert(std::copyable<NodeKeyT> && std::copyable<EdgeKeyT>,
            "Error: NodeKey and EdgeKey must be copyable");
    }

    [[nodiscard]] constexpr
    std::size_t order() const noexcept                      {return nodes.size();}

    [[nodiscard]] constexpr
    const NodeT &operator[](NodeKeyT nKey) const noexcept   {return {nodes[nKey]};}

    [[nodiscard]] constexpr
    NodeT &operator[](NodeKeyT nKey) noexcept               {return {nodes[nKey]};}

    [[nodiscard]] constexpr
    const EdgeT &operator[](EdgeKeyT eKey) const noexcept   {return {*eKey};}

    [[nodiscard]] constexpr
    EdgeT &operator[](EdgeKeyT eKey) noexcept               {return {*eKey};}

private:
    std::vector<NValT> &nodes;
};
