#pragma once
#include "../graph/node.h"

namespace pipe{

class ForwardInt: public Node<Param<std::tuple<int, int>>, Param<int>> {
public:
    ForwardInt() = default;
    
    void exec() override {
        std::tuple<int, int> val;
        if (input<0>()->pop(val)) {
            fprintf(stdout, "foward %d\n", std::get<0>(val));
            output<0>()->try_push(std::get<0>(val));
        }
    }
};

}