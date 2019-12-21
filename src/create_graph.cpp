#include <string>

#include "graph_matrix.hxx"
#include "graph_list.hxx"

//It creates a new object graph
my_graphs::graph_base *new_graph_poliform(std::string kind)
{
    if(kind == "graph_matrix") return new my_graphs::graph_matrix;
    if(kind == "graph_list") return new my_graphs::graph_list;
    return nullptr;
}

