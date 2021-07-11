#include "../graph/graph.h"
#include "../actor/generate_int.h"
#include "../actor/forward_int.h"
#include "../actor/print_int.h"
#include <chrono>
using namespace pipe;

int main() {
    Graph g;
    auto gen = g.add_node<GenerateInt, int>(20);
    auto forward = g.add_node<ForwardInt>();
    auto print = g.add_node<PrintInt>();

    auto gen_for = g.add_edge<FIFOEdge<std::tuple<int, int>>>(100);
    auto for_print = g.add_edge<FIFOEdge<int>>(100);

    gen->set_output<0>(gen_for);
    forward->set_input<0>(gen_for);
    forward->set_output<0>(for_print);
    print->set_input<0>(for_print);

    g.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    g.finish();
}