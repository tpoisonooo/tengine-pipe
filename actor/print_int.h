#pragma once
#include "../graph/node.h"

namespace pipe{

class PrintInt: public Node<Param<int>, Param<void>> {
public:
    void exec() override {
        int val;
        if (input<0>()->pop(val)) {
            fprintf(stdout, "fetch %d\n", val);
        }
    }
};

}