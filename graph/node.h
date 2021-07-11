#pragma once

#include <vector>
#include <tuple>
#include "edge.h"

namespace  pipe {

template <typename... Args>
class Param {
public:
    using DataTypes = std::tuple<Args...>;
    // using DataPtrTypes = std::tuple<Args*...>;
    // using EdgeTypes = std::tuple<FIFOEdge<Args>...>;
    using EdgePtrTypes = std::tuple<FIFOEdge<Args>*...>;
};

class BaseNode {
public:
    BaseNode() = default;
    virtual ~BaseNode() {}
    virtual void exec() {};
};

template<typename IN, typename OUT>
class Node: public BaseNode {

    template <size_t I>
    using IN_Edge = typename std::tuple_element<I, typename IN::EdgePtrTypes>::type;
    
    template <size_t I>
    using OUT_Edge = typename std::tuple_element<I, typename OUT::EdgePtrTypes>::type;

public:
    template<size_t I>
    IN_Edge<I> input() {
        return std::get<I>(m_inputs);
    }

    template<size_t I>
    inline OUT_Edge<I> output() {
        return std::get<I>(m_outputs);
    }

    template<size_t I>
    void set_input(IN_Edge<I> edge) {
        std::get<I>(m_inputs) = edge;
        edge->set_out_node(this, m_name);
    }

    template<size_t I>
    void set_output(OUT_Edge<I> edge) {
        std::get<I>(m_outputs) = edge;
        edge->set_in_node(this, m_name);
    }

    void exec() {}

protected:
    std::string m_name;
    typename IN::EdgePtrTypes m_inputs;
    typename OUT::EdgePtrTypes m_outputs;
};

}
