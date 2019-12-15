#include "graph_list.hxx"
#include <iostream>
#include <cstdlib>

//graph matrix functions
    
namespace my_graphs{

    graph_list::graph_list()
    {
        resize(0);
    }
    
    graph_list::graph_list(int in_size)
    {
        resize(in_size);
    }

    int graph_list::nodes() const
    {
        return A.size();
    }
    
    int graph_list::links() const
    {
        return number_of_links;
    }

    int graph_list::resize(int new_number_of_nodes)
    {
        //removes all conections and resize the vectors
        
        if( new_number_of_nodes < 0){
            std::cout << "Error in graph_list::resize(): new size (" << new_number_of_nodes << ") smaller than zero!!" << std::endl;
            if(exit_behaviour == MG_EXIT_STRONG){
                std::exit(0);
            }
            return MG_UNSUCCESS;
        }
        
        //if(new_number_of_nodes == 0) return MG_SUCCESS;
        
        try{
            A.clear();
            std::vector<int> temp(new_number_of_nodes);
            for(int i=0; i<new_number_of_nodes; i++) A.push_back(temp);
        
            number_of_links = 0;
        
            in_degrees.clear();
            in_degrees.resize(new_number_of_nodes, 0);

            out_degrees.clear();
            out_degrees.resize(new_number_of_nodes, 0);
        }
        catch(std::bad_alloc &ba){
            std::cout << "Error with memory in graph_list::resize()" << std::endl;
            if(exit_behaviour == MG_EXIT_STRONG){
                std::exit(0);
            }
            return MG_UNSUCCESS;
        }
        return MG_SUCCESS;
    }
    
    int graph_list::clean()
    {
        for(int i=0; i < A.size(); i++){
            for(int j=0; j < A.size(); j++){
                A[i][j] = 0;
            }
            out_degrees[i] = 0;
            in_degrees[i] = 0;
        }
        number_of_links = 0;
        return MG_SUCCESS;
    }

    
    int graph_list::add_link(int in_j, int in_i)
    {
        if( (in_j < 0) || (in_i < 0 ) || (in_j >= A.size()) || (in_i >= A.size()) ){
            std::cout << "Error in graph_list::add_link(j,i): index range problem." << std::endl;
            std::cout << "It muss be: 0 <= (i = " << in_i << ") < " << A.size() << " and 0 <= (j = ";
            std::cout << in_j << ") < " << A.size() << "." << std::endl;
            if(exit_behaviour == MG_EXIT_STRONG){
                std::exit(0);
            }
            return MG_UNSUCCESS;
        }
        
        if( in_j == in_i) return MG_UNSUCCESS;
        if(A[in_j][in_i] == 1) return MG_UNSUCCESS;
        
        A[in_j][in_i] = 1;    //i -> j
        
        in_degrees[in_j]++;
        out_degrees[in_i]++;
        number_of_links++;
            
        return MG_SUCCESS;
    }

    int graph_list::delete_link(int in_j, int in_i)
    {
        if( (in_j < 0) || (in_i < 0 ) || (in_j >= A.size()) || (in_i >= A.size()) ){
            std::cout << "Error in graph_list::delete_link(j,i): index range problem." << std::endl;
            std::cout << "It muss be: 0 <= (i = " << in_i << ") < " << A.size() << " and 0 <= (j = ";
            std::cout << in_j << ") < " << A.size() << "." << std::endl;
            if(exit_behaviour == MG_EXIT_STRONG){
                std::exit(0);
            }
            return MG_UNSUCCESS;
        }
        
        if(A[in_j][in_i] == 0) return MG_UNSUCCESS;
        
        A[in_j][in_i] = 0;    //i -> j
        
        in_degrees[in_j]--;
        out_degrees[in_i]--;
        number_of_links--;
            
        return MG_SUCCESS;
    }

    bool graph_list::is_link(int in_j, int in_i) const
    {
        if( (in_j < 0) || (in_i < 0 ) || (in_j >= A.size()) || (in_i >= A.size()) ){
            std::cout << "Error in graph_list::is_link(j,i): index range problem." << std::endl;
            std::cout << "It muss be: 0 <= (i = " << in_i << ") < " << A.size() << " and 0 <= (j = ";
            std::cout << in_j << ") < " << A.size() << "." << std::endl;
            if(exit_behaviour == MG_EXIT_STRONG){
                std::exit(0);
            }
            return MG_UNSUCCESS;
        }
        return A[in_j][in_i];
    }

    
    graph_list::~graph_list()
    {
        std::cout << "Killing a graph_list object" << std::endl;
    }
    

}
