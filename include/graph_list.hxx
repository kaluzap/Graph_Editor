#include <vector>
#include "graph_base.hxx"

namespace my_graphs{

    #ifndef MY_GRAPH_LIST_IS_VERY_NICE
    #define MY_GRAPH_LIST_IS_VERY_NICE

    class graph_list: public graph_base{
        public:
            graph_list();
            graph_list(int in_size);
            
            int clean() override;
            int resize(int new_number_of_nodes) override;
            
            int nodes() const override;
            int links() const override;
            
            int add_link(int in_j, int in_i) override;
            int delete_link(int in_j, int in_i) override;
            bool is_link(int in_j, int in_i) const override;
            
            int add_node() override {return false;};
            
            int degree(int in_i) const override {return in_degrees[in_i] + out_degrees[in_i];};
            int outdegree(int in_i) const override {return out_degrees[in_i];};
            int indegree(int in_i) const override {return in_degrees[in_i];};
            
            ~graph_list();
            
        protected:
            std::vector<std::vector<int>> A;    //adjacency matrix
            int number_of_links;
            std::vector<int> in_degrees;
            std::vector<int> out_degrees;
    };

    #endif
}


