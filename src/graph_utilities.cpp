#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "graph_utilities.hxx"
#include "graph.hxx"
#include "DGEEV.hxx"

namespace my_graphs{
    
    graph_utilities::graph_utilities()
    {
        seed = 1;
        started_generator = false;
    }
  
    graph_utilities::graph_utilities(unsigned long in)
    {
        seed = in;
        started_generator = false;
    }

    double graph_utilities::rand(void)
    {
        if(!started_generator){
            my_generator.seed(seed);
            started_generator = true;
        }
        return my_distribution(my_generator);
    }
    
    int graph_utilities::set_seed(unsigned long in)
    {
        if(started_generator){
            std::cout << "The seed is already: " << seed << std::endl;
            return MG_UNSUCCESS;
        }
        seed = in;
        return MG_SUCCESS;
    }
    
    int graph_utilities::read_file(const std::string file_name, std::string the_label, class graph_base &IN)
    {
        
        std::ifstream myfile;
        myfile.open(file_name);
    
        if (!myfile.is_open()){
            std::cout << "Error with file: " << file_name << std::endl;
            return MG_UNSUCCESS;
        }
    
        //IN.input_list.clear();
        int N;
        std::string temp, label, line;
        
        while(getline(myfile,line)){
        
            std::istringstream word(line);
            word >> temp >> label;
        
            if( (temp == "GRAPH") && (label == the_label) ){
        
                getline(myfile,line);
                std::istringstream word(line);
                word >> temp >> N;
        
                IN.resize(N);
            
            
                while(getline(myfile, line)){
                
                    int i, j;
                
                    std::istringstream word(line);
                
                    temp = "_";
                    word >> i >> temp >> j;
        
                    if(temp != "->") break;
                  
                    IN.add_link(j,i);
                
                    //cout << line << endl;
                }
            
            
            
                return MG_SUCCESS;    
            }
        
        
        }
    
        return MG_UNSUCCESS;
    }

    
    
    
    
    std::vector<std::string> graph_utilities::list_file_labels(const std::string file_name)
    {
        std::vector<std::string> the_list;
        
        std::ifstream myfile;
        myfile.open(file_name);
    
        if(myfile.is_open()){
    
            std::string temp, the_label, line;
            
            while ( getline (myfile,line) ){
                
                std::istringstream word(line);
                word >> temp >> the_label;
                
                if( temp == "GRAPH" ) the_list.push_back(the_label);
            }
            myfile.close();
        }
        
        std::sort(the_list.begin(), the_list.end());
        
        return the_list;
    }
    
    
    int graph_utilities::write_file(const std::string file_name, const std::string name, const graph_base &IN, bool no_repeated_labels)
    {
        
        if(no_repeated_labels){
            std::vector<std::string> labels = list_file_labels(file_name);
            auto it = std::find(labels.begin(), labels.end(), name);
            if( it != labels.end()) return MG_UNSUCCESS; 
        }
    
        //open file to add at end the new graph
        std::ofstream myfile;
        myfile.open(file_name, std::ofstream::app );
    
        if (!myfile.is_open()){
            std::cout << "Error with file: " << file_name << std::endl;
            return MG_UNSUCCESS;
        }
    
        myfile << "GRAPH " << name << std::endl;
        myfile << "N " << IN.nodes() << std::endl;
    
        for(int i=0; i < IN.nodes(); i++){
            for(int j=0; j < IN.nodes(); j++){
        
                if(IN.is_link(j,i)) myfile << i << " -> " << j << std::endl;
            }
        }
    
        myfile << std::endl;
        myfile.close();
    
        return MG_SUCCESS;
    }
    
    
    void graph_utilities::print_graph_dot(const std::string file_name, const graph_base &IN)
    {
        std::ofstream myfile;
        myfile.open(file_name);
    
        myfile << "digraph migraph{" << std::endl;
    
        myfile << "node [shape=circle,fixedsize=true]; ";
    
        for(int i=0; i < IN.nodes(); i++) myfile << i << " ";
        myfile << ";" << std::endl;
    
        for(int i=0; i < IN.nodes(); i++){
            for(int j=0; j < IN.nodes(); j++){
                
                if(IN.is_link(j,i)== true){
                    myfile << "\t" << i << " -> " << j << ";" << std::endl;
                }
            }
        }
    
        myfile << "}" << std::endl;
        myfile.close();
    
        return;
    }

    void graph_utilities::print_info(const graph_base &in)
    {
        std::cout << "Info Graph" << std::endl;
        std::cout << "Nodes: " << in.nodes() << std::endl;
        std::cout << "Links: " << in.links() << std::endl;
    }
    
    void graph_utilities::print_matrix(const graph_base &in)
    {

        for(int i=0; i<in.nodes(); i++){
            for(int j=0; j<in.nodes(); j++){
                std::cout << in.is_link(i,j) << " ";
            }
            std::cout << std::endl;
        }
        
        return;
    }
    
    
    int graph_utilities::get_eigenvalues(const graph_base &in, const char kind_of)
    {
        try{
            std::vector<double> A(in.nodes()*in.nodes(), 0.0);
            std::vector<double> Wr(in.nodes(), 0.0);
            std::vector<double> Wi(in.nodes(), 0.0);
            
            for(int i=0; i<in.nodes(); i++){
                for(int j=0; j<in.nodes(); j++){
                    
                    if(i == j){
                        switch(kind_of){
                            case 'A':
                                break;
                            case 'L':
                                A[i*in.nodes() + j] = 1.0;
                                break;
                            case 'T':
                                A[i*in.nodes() + j] = ((double)in.outdegree(i));
                                break;
                            default:
                                return MG_UNSUCCESS;
                        }
                    }
                    else if(in.is_link(i,j)){
                        switch(kind_of){
                            case 'A':
                                A[i*in.nodes() + j] = 1.0;
                                break;
                            case 'L':
                                A[i*in.nodes() + j] = -1.0/((double)in.outdegree(j));
                                break;
                            case 'T':
                                A[i*in.nodes() + j] = -1.0;
                                break;
                            default:
                                return MG_UNSUCCESS;
                        };
                    }
                    
                    
                }
            }
            
            DGEEV(&A.front(), &Wr.front(), &Wi.front(), in.nodes());
        
            eigenvalues.resize(in.nodes());
            coeficients.resize(in.nodes());
            
            for(int i=0; i<in.nodes(); i++){
                eigenvalues[i] = {Wr[i] , Wi[i]};
                coeficients[i] = 0.0;
            }
            
        }
        catch(std::bad_alloc &ba){
            std::cout << "Error with memory in get_eigenvalues()" << std::endl;
            return MG_UNSUCCESS;
        }
    
        return MG_SUCCESS;
    }
    
    
    
    int graph_utilities::line_graph(const graph_base &IN, graph_base &OUT)
    {
    
        OUT.resize(IN.links());
    
        int input_link = 0;
        for(int i=0; i < IN.nodes(); i++){
            for(int j=0; j < IN.nodes(); j++){
            
                if(!IN.is_link(j,i)) continue;
            
                int output_link = 0;
                
                for(int k=0; k < IN.nodes(); k++){
                    for(int l=0; l < IN.nodes(); l++){
                    
                        if(!IN.is_link(l,k)) continue;
                    
                        if( j == k) OUT.add_link(output_link, input_link);
                    
                        output_link++;
                    }
                }
                input_link++;
            }
        }
    
        return MG_SUCCESS;
    }
    
}
