#pragma once
#include "../graph/node.h"

namespace pipe{

class GenerateInt: public Node<Param<void>, Param<std::tuple<int, int>>> {
public:
    GenerateInt(int max): m_val(0), m_max(max) {
        fprintf(stdout, "max %d\n", m_max);
    }

    void exec() override {
        while(m_val++ < m_max) {
            auto success = output<0>()->try_push(std::make_tuple(m_val, m_val));
            if (not success) {
                fprintf(stdout, "abandon %d\n", m_val);
            }
        };
    }

    int m_val;
    int m_max;
};

}