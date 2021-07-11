#pragma once
#include "../graph/node.h"

namespace pipe{

class ForwardInt: public Node<Param<int>, Param<int>> {
public:
    ForwardInt() = default;
    
    void exec() override {
        int val;
        if (input<0>()->pop(val)) {
            fprintf(stdout, "foward %d\n", val);
            output<0>()->try_push(val);
        }
    }
};

}