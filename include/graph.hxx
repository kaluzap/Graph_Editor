#include <vector>
#include <utility>

#ifndef MY_GRAPHS_ARE_VERY_NICE
#define MY_GRAPHS_ARE_VERY_NICE

namespace my_graphs{
    
    
    enum{MG_SUCCESS, MG_UNSUCCESS, MG_EXIT_SOFT, MG_EXIT_STRONG};
    
    class graph_base{
        public:
            
            virtual int clean() = 0;
            virtual int resize(int new_number_of_nodes) = 0;
            
            virtual int nodes() const = 0;    //number of nodes
            virtual int links() const = 0;    //number of links
            
            virtual int add_link(int in_j, int in_i) = 0;   //adds a link from i to j ( i -> j)
            virtual int delete_link(int in_j, int in_i) = 0;   //deletes the link from i to j ( i -> j)
            virtual bool is_link(int in_j, int in_i) const = 0;   //checks if the link from i to j ( i -> j) exist
            
            /*
            std::pair<int, int> get_link(const int k);
            */
            virtual int add_node() = 0;
            /*bool insert_node(int in_i);
            bool delete_node(int in_i);
            */
            
            virtual int degree(int in_i) const = 0;
            virtual int outdegree(int in_i) const = 0;
            virtual int indegree(int in_i) const = 0;
            
            virtual ~graph_base() = 0;
            
            
            static int exit_behaviour;
            static int max_number_of_nodes;
    };
    
    
    class graph_matrix: public graph_base{
        public:
            graph_matrix();
            graph_matrix(int in_size);
            
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
            
            ~graph_matrix();
            
        protected:
            std::vector<std::vector<int>> A;    //adjacency matrix
            int number_of_links;
            std::vector<int> in_degrees;
            std::vector<int> out_degrees;
    };
    
    /*
    class graph_input_list: public graph_base{
    };

    class graph_output_list: public graph_base{
    };
    
    class graph_double_list: public graph_base{
    };
    */


}

#endif
