#include "graph_base.hxx"

namespace my_graphs{

    int graph_base::exit_behaviour = MG_EXIT_STRONG;
    int graph_base::max_number_of_nodes = 100;
    
    graph_base::~graph_base(){}

    void copy_graphs(class graph_base &out, class graph_base &in)
    {
        if(out.nodes() != in.nodes()) out.resize(in.nodes());
        
        for(int i=0; i < in.nodes(); i++){
            for(int j=0; j < in.nodes(); j++){
                if(in.is_link(i,j)) out.add_link(i,j);
            }
        }
    }
}
