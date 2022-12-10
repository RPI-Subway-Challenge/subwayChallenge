#pragma once

#include <cstddef>
#include <vector>
#include <concepts>
#include <functional>
#include <type_traits>
#include "station.h"
#include "trip.h"


/**
 * @brief The coupler between the data structure and the search algorithm. Its behavior
 * is designed to be like a directed graph.
 * 
 * @tparam NRepT Node representation type. Defaults to Station &. Reference or pointers 
 * should be used as the graph does not own the value object.
 * 
 * @tparam ERepT Edge representation type. Defaults to Trip &. Reference or pointers
 * should be used as the graph does not own the value object.
 * 
 * @tparam NValF The value access function type for node. Returns the representation by
 * default. Current design is that it cannot have captures. Example signature:
 * NodeValT (const NRepT &)
 * 
 * @tparam EValF The value access function type for edge. Returns the representation by
 * default. Current design is that it cannot have captures. Example signature:
 * EdgeValT (const ERepT &)
 */
template<
    class NRepT = Station &, class ERepT = Trip &,
    class NValF = std::identity, class EValF = std::identity
>
class SubwayGraph {
public:
    struct Node;
    struct Edge;

    using NodeKeyT = std::size_t;
    using EdgeKeyT = Edge *;
    using NodeValT = std::remove_cvref_t<decltype(NValF{}(std::declval<NRepT>()))>;
    using EdgeValT = std::remove_cvref_t<decltype(EValF{}(std::declval<ERepT>()))>;

    template<class ViewT, class Rep>
    struct View {
        View(ViewT, const Rep &r): rep{r} {}
        template<class RepItr>
        struct Iterator: public std::iterator<std::input_iterator_tag, ViewT> {
            explicit Iterator(RepItr i): itr{i} {}
            Iterator& operator++() {++itr; return *this;}
            Iterator operator++(int) {auto ret{*this}; ++*this; return ret;}
            bool operator==(Iterator other) const {return itr == other.itr}
            bool operator!=(Iterator other) const {return itr != other.itr}
            reference operator*() const {return ViewT{*itr};}
        private:
            Iterator itr;
        };
        const Rep &rep;
        auto begin() {return Iterator{rep.begin()};}
        auto end() {return Iterator{rep.end()};}
    };

    struct Node {
        using RepT = NRepT;
        using ValT = NodeValT;

        Node(RepT &r): rep{r} {}
        [[nodiscard]] constexpr decltype(auto) val() const noexcept {
            if constexpr (std::is_lvalue_reference_v<decltype(valF(rep))>)
                return std::as_const(valF(rep));
            else
                return valF(rep);
        }
        [[nodiscard]] constexpr decltype(auto) val() noexcept {return valF(rep);}
        [[nodiscard]] const auto &outEdges() const {return View{*this, rep.getTrips()};}
    private:
        RepT rep;
        [[no_unique_address]] NValF valF;
    };

    struct Edge {
        using RepT = ERepT;
        using ValT = EdgeValT;
        Edge(RepT &r): rep{r} {}
        [[nodiscard]] constexpr decltype(auto) val() const noexcept {
            if constexpr (std::is_lvalue_reference_v<decltype(valF(rep))>)
                return std::as_const(valF(rep));
            else
                return valF(rep);
        }
        [[nodiscard]] constexpr decltype(auto) val() noexcept {return valF(rep);}
        [[nodiscard]] NodeKeyT headKey() const {return rep.getEnd();}
        [[nodiscard]] NodeKeyT tailKey() const {return rep.getStart();}
    private:
        RepT rep;
        [[no_unique_address]] EValF valF;
    };

    constexpr explicit SubwayGraph(std::vector<NRepT> &stations, NValF = {}, EValF = {}):
        nodes{stations}
    {
        static_assert(!std::same_as<NodeKeyT, EdgeKeyT>,
            "Error: NodeKey and EdgeKey has type clashes."); // otherwise the overloaded operator[] will be ambiguous
    }

    [[nodiscard]] constexpr
    std::size_t order() const noexcept                      {return nodes.size();}

    [[nodiscard]] constexpr
    const Node &operator[](NodeKeyT nKey) const noexcept    {return {nodes[nKey]};}

    [[nodiscard]] constexpr
    const Edge &operator[](EdgeKeyT eKey) const noexcept    {return {*eKey};}

    [[nodiscard]] constexpr
    NodeKeyT key(const Node &n) const {
        return std::distance(&nodes[0], n.rep);
    }

    [[nodiscard]] constexpr
    EdgeKeyT key(const Edge &e) const {
        return &e.rep;
    }

private:
    std::vector<NRepT> &nodes;
};
