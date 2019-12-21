#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <memory>

#include "graph_utilities.hxx"
#include "commands.hxx"
#include "graph_base.hxx"
#include "create_graph.hxx"


//Variables from main.cpp
extern std::vector<std::string> graph_types;
extern int actual_graph_type;


//Utilities here
my_graphs::graph_utilities the_utility_tool;


void s_show_class(void)
{
    std::cout << "You use the graph class: \"" << graph_types[actual_graph_type] << "\"" << std::endl;
    return;
}


void s_change_class(std::vector<std::string> &commands)
{
    if(commands.size() != 2){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    if(commands[1] == "graph_matrix") actual_graph_type = 0;
    else if(commands[1] == "graph_list") actual_graph_type = 1;
    else actual_graph_type = 0;
    return;
}


void u_line_graph(std::vector<std::string> &commands, std::map<std::string, std::unique_ptr<my_graphs::graph_base>> &A, std::string &actual_graph_name)
{
    if(commands.size() != 3){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    
    if( commands[1] == commands[2]){
        std::cout << "Error: the input and output graphs must be different" << std::endl;
        return;
    }
    
    if(A.count(commands[1]) && A.count(commands[2]) ){
        
        the_utility_tool.line_graph(*A[commands[1]], *A[commands[2]]);
    
        actual_graph_name = commands[2];

        
    }
    else{
        std::cout << "At least one graph does not exist." << std::endl;
    }

    return;
}



void u_load_graph(std::vector<std::string> &commands, my_graphs::graph_base &A)
{
    if(commands.size() != 3){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    
    if(the_utility_tool.read_file(commands[1], commands[2], A) == my_graphs::MG_UNSUCCESS){
    
        std::cout << "Error: missing label \"" << commands[2] << "\" in file \"" << commands[1] << "\"" << std::endl;
    }
    
    return;
}

void u_list_labels(std::vector<std::string> &commands)
{
    if(commands.size() != 2){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    
    std::vector<std::string> the_list = the_utility_tool.list_file_labels(commands[1]);
    
    for(int i=0; i< the_list.size(); i++) std::cout << the_list[i] << std::endl;
    
    return;
}


void u_save_graph(std::vector<std::string> &commands, my_graphs::graph_base &A, std::string actual_graph_name)
{
    
    std::string label;
    
    if(commands.size() == 2){
        label = actual_graph_name;
    }
    else if(commands.size() == 3){
        label = commands[2];
    }
    else{
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    
    if( the_utility_tool.write_file(commands[1], label, A, true) == my_graphs::MG_UNSUCCESS){
        std::cout << "Error! the label \"" << label <<"\" already exists." << std::endl;
    }
    
    return;
}


void s_system(std::vector<std::string> &commands)
{
    if(commands.size() == 1){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    
    
    std::string line;
    
    for(int i=1; i < commands.size(); i++){
        line += commands[i] + " ";
    }
    
    std::system(line.c_str());
    return;
}


void u_show(std::vector<std::string> &commands, my_graphs::graph_base &A, std::string actual_graph_name)
{
    the_utility_tool.print_graph_dot(actual_graph_name + ".dot", A);
    
    std::string line = "dot -Tpng " + actual_graph_name + ".dot -o " + actual_graph_name + ".png";
    
    std::system(line.c_str());
    
    line = "feh -g200x200 " + actual_graph_name + ".png";
    
    std::system(line.c_str());
    
    return;
}



void g_delete_path(std::vector<std::string> &commands, my_graphs::graph_base &A)
{
    if(commands.size() < 3){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    
    std::vector<int> nodes;
    
    try{
        for(int i= 1; i < commands.size()-1; i++){
            nodes.push_back(std::stoi(commands[i]));
        }
    }
    catch(...){
        std::cout << "Wrong integer!!!" << std::endl;
        return;
    }
    
    int last = -1;
    try{
        last = std::stoi(commands[commands.size()-1]);         
    }
    catch(...){
        last = -1;
    }
    if(last != -1) nodes.push_back(last);
    
    for(int i=0; i < nodes.size()-1; i++){
        
        if(A.delete_link(nodes[i+1], nodes[i]) == my_graphs::MG_SUCCESS){
            std::cout << "The link from " << nodes[i] << " to " << nodes[i+1] << " has been deleted." << std::endl;
        }
        if(last == -1){
            if(A.delete_link(nodes[i], nodes[i+1]) == my_graphs::MG_SUCCESS){
                std::cout << "The link from " << nodes[i+1] << " to " << nodes[i] << " has been deleted." << std::endl;
            }
        }
    }
    return;
}



void g_add_path(std::vector<std::string> &commands, my_graphs::graph_base &A)
{
    if(commands.size() < 3){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    
    std::vector<int> nodes;
    
    try{
        for(int i= 1; i < commands.size()-1; i++){
            nodes.push_back(std::stoi(commands[i]));
        }
    }
    catch(...){
        std::cout << "Wrong integer!!!" << std::endl;
        return;
    }
    
    int last = -1;
    try{
        last = std::stoi(commands[commands.size()-1]);         
    }
    catch(...){
        last = -1;
    }
    if(last != -1) nodes.push_back(last);
    
    for(int i=0; i < nodes.size()-1; i++){
        
        if(A.add_link(nodes[i+1], nodes[i]) == my_graphs::MG_SUCCESS){
            std::cout << "The link from " << nodes[i] << " to " << nodes[i+1] << " has been added." << std::endl;
        }
        if(last == -1){
            if(A.add_link(nodes[i], nodes[i+1]) == my_graphs::MG_SUCCESS){
                std::cout << "The link from " << nodes[i+1] << " to " << nodes[i] << " has been added." << std::endl;
            }
        }
    }
    return;
}


void u_eigenvalues(std::vector<std::string> &commands, my_graphs::graph_base &A)
{
    if(commands.size() != 2){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    
    if(the_utility_tool.get_eigenvalues(A, commands[1][0]) == my_graphs::MG_SUCCESS){
        for(int i=0; i < the_utility_tool.eigenvalues.size(); i++){
            std::cout << "(" << the_utility_tool.eigenvalues[i].real() << ", ";
            std::cout << the_utility_tool.eigenvalues[i].imag() << ") ";
        }
        std::cout << std::endl;
    }
    else{
    
        std::cout << "Error with the eigenvalues calculation" << std::endl;
    }
    return;
}

void s_help(std::vector<std::string> &commands)
{
    std::ifstream myfile;
    myfile.open("my_help.txt");
    
    std::string line;
    
    if(myfile.is_open()){
        while(std::getline(myfile,line)){
            
            if(commands.size() > 1){
                std::istringstream words(line);
                std::string first_word;
                words >> first_word;
                
                /*a nice tool*/
                first_word.erase(std::remove(first_word.begin(), first_word.end(), ':'), first_word.end());
                
                if(first_word != commands[1]) continue; 
            }
        
            std::cout << line << '\n';
        }
        myfile.close();
    }
    else{
        std::cout << "The help file \"my_help.txt\" is missing!" << std::endl;
    }
    return;
}


void s_copy_graph(std::vector<std::string> &commands, std::map<std::string, std::unique_ptr<my_graphs::graph_base>> &A, std::string &actual_graph_name)
{
    if(commands.size() != 3){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }      
    
    if( commands[2] == commands[1] ){
        std::cout << "Copy to myself?... OK" << std::endl;
        return;
    }
    
    if(A.count(commands[1]) && A.count(commands[2]) ){
        //COPY OPERATOR IS MISSING!!
        *A[commands[2]] = *A[commands[1]];
        std::cout << "The copy operator is missing!!!!" << std::endl;
    }
    else{
        std::cout << "I cannot copy. At least one graph does not exist!" << std::endl;
    }
    
    return;
}



void s_delete_graph(std::vector<std::string> &commands, std::map<std::string, std::unique_ptr<my_graphs::graph_base>> &A, std::string &actual_graph_name)
{
    if(commands.size() != 2){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }      
    if(A.size() == 1){
        std::cout << "You have to have always at least one ;)" << std::endl;
        return;
    }
    
    A.erase(commands[1]);
    
    if(actual_graph_name == commands[1] ) actual_graph_name = A.begin()->first;
    
    std::cout << "The graph " << commands[1] << " has been deleted." << std::endl;
}

void s_ls_graphs(std::map<std::string, std::unique_ptr<my_graphs::graph_base>> &A)
{
    for(auto it = A.begin(); it != A.end(); it++){
        std::cout << it->first << "\t\t" << (*(it->second)).nodes() /*<< "\t" << it->second.links()*/ << std::endl;
    }
    return;
}

void s_new_graph(std::vector<std::string> &commands, std::map<std::string, std::unique_ptr<my_graphs::graph_base>> &A, std::string &actual_graph_name)
{
    if(commands.size() != 2){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    std::string actual_graph_name_old = actual_graph_name;
    actual_graph_name = commands[1];
    
    if(A.count(actual_graph_name)){
        std::cout << "The graph \"" << actual_graph_name << "\" already exist!" << std::endl;
        //actual_graph_name = actual_graph_name_old;
    }
    else{
        A.insert(std::make_pair(actual_graph_name, new_graph_poliform(graph_types[actual_graph_type])));
    }
    
    return;
}

void g_is_link(std::vector<std::string> &commands, my_graphs::graph_base &IN)
{
    if(commands.size() != 3){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    
    int i, j;
    
    try{
        i = std::stoi(commands[1]);
        j = std::stoi(commands[2]);
    }
    catch(...){
        std::cout << "Wrong integer!!!" << std::endl;
        return;
    }
    
    if(IN.is_link(j, i) == true){
        std::cout << "Link " << i << " -> " << j << ": TRUE." << std::endl;
    }
    else{
        std::cout << "Link " << i << " -> " << j << ": FALSE." << std::endl;
    }
    return;
}


void g_delete_link(std::vector<std::string> &commands, my_graphs::graph_base &IN)
{
    if( (commands.size() != 3) && (commands.size() != 4) ){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    
    int i, j;
    
    try{
        i = std::stoi(commands[1]);
        j = std::stoi(commands[2]);
    }
    catch(...){
        std::cout << "Wrong integer!!!" << std::endl;
        return;
    }
    
    if(IN.delete_link(j, i) == my_graphs::MG_UNSUCCESS){
        std::cout << "Not possible to delete that link! It does not exists already." << std::endl;
    }
    else{
        std::cout << "The link from " << i << " to " << j << " has been deleted." << std::endl;
    }
    
    if(commands.size() == 4){
        if(IN.delete_link(i, j) == my_graphs::MG_UNSUCCESS){
            std::cout << "Not possible to delete that link! It does not exists already." << std::endl;
        }
        else{
            std::cout << "The link from " << j << " to " << i << " has been deleted." << std::endl;
        }
    }
    
    return;
}

void g_add_link(std::vector<std::string> &commands, my_graphs::graph_base &IN)
{
    if( (commands.size() != 3) && (commands.size() != 4) ){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    
    int i, j;
    
    try{
        i = std::stoi(commands[1]);
        j = std::stoi(commands[2]);
    }
    catch(...){
        std::cout << "Wrong integer!!!" << std::endl;
        return;
    }
    
    if(IN.add_link(j, i) == my_graphs::MG_UNSUCCESS){
        std::cout << "Not possible to add that link! It already exists or it is to itself" << std::endl;
    }
    else{
        std::cout << "New link from " << i << " to " << j << "." << std::endl;
    }
    
    if(commands.size() == 4){
        if(IN.add_link(i, j) == my_graphs::MG_UNSUCCESS){
            std::cout << "Not possible to add that link! It already exists or it is to itself" << std::endl;
        }
        else{
            std::cout << "New link from " << j << " to " << i << "." << std::endl;
        }
    }
    return;
}

void g_resize(std::vector<std::string> &commands, my_graphs::graph_base &IN)
{
    if(commands.size() != 2){
        std::cout << "Wrong number of parameters!!!" << std::endl;
        return;
    }
    
    int new_size;
    
    try{
        new_size = std::stoi(commands[1]);
    }
    catch(...){
        std::cout << "Wrong integer!!!" << std::endl;
        return;
    }
    
    IN.resize(new_size);
    
    std::cout << "The new size is: " << IN.nodes() << std::endl;
    return;
}

