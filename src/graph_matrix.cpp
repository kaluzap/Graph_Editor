#include "graph_matrix.hxx"
#include <iostream>
#include <cstdlib>

//graph matrix functions
    
namespace my_graphs{

    graph_matrix::graph_matrix()
    {
        resize(0);
    }
    
    graph_matrix::graph_matrix(int in_size)
    {
        resize(in_size);
    }

    int graph_matrix::nodes() const
    {
        return A.size();
    }
    
    int graph_matrix::links() const
    {
        return number_of_links;
    }

    int graph_matrix::resize(int new_number_of_nodes)
    {
        //removes all conections and resize the vectors
        
        if( new_number_of_nodes < 0){
            std::cout << "Error in graph_matrix::resize(): new size (" << new_number_of_nodes << ") smaller than zero!!" << std::endl;
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
            std::cout << "Error with memory in graph_matrix::resize()" << std::endl;
            if(exit_behaviour == MG_EXIT_STRONG){
                std::exit(0);
            }
            return MG_UNSUCCESS;
        }
        return MG_SUCCESS;
    }
    
    int graph_matrix::clean()
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

    
    int graph_matrix::add_link(int in_j, int in_i)
    {
        if( (in_j < 0) || (in_i < 0 ) || (in_j >= A.size()) || (in_i >= A.size()) ){
            std::cout << "Error in graph_matrix::add_link(j,i): index range problem." << std::endl;
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

    int graph_matrix::delete_link(int in_j, int in_i)
    {
        if( (in_j < 0) || (in_i < 0 ) || (in_j >= A.size()) || (in_i >= A.size()) ){
            std::cout << "Error in graph_matrix::delete_link(j,i): index range problem." << std::endl;
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

    bool graph_matrix::is_link(int in_j, int in_i) const
    {
        if( (in_j < 0) || (in_i < 0 ) || (in_j >= A.size()) || (in_i >= A.size()) ){
            std::cout << "Error in graph_matrix::is_link(j,i): index range problem." << std::endl;
            std::cout << "It muss be: 0 <= (i = " << in_i << ") < " << A.size() << " and 0 <= (j = ";
            std::cout << in_j << ") < " << A.size() << "." << std::endl;
            if(exit_behaviour == MG_EXIT_STRONG){
                std::exit(0);
            }
            return MG_UNSUCCESS;
        }
        return A[in_j][in_i];
    }

    
    graph_matrix::~graph_matrix()
    {
        std::cout << "Killing a graph_matrix object" << std::endl;
    }
    

}
