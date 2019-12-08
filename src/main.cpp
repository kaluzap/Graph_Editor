#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <memory>

#include <readline/readline.h>
#include <readline/history.h>

#include "commands.hxx"
#include "graph.hxx"
#include "graph_utilities.hxx"


/*
 * A way to compile it
 * g++ main.cpp graph.cpp graph_matrix.cpp graph_utilities.cpp DGEEV.cpp commands.cpp -o run -llapack -lblas -lm -lreadline -O3 -g -Wall
*/


//List of commands used by readline
std::vector<std::string> vocabulary{"exit", "resize", "matrix", "add_link", "info", "delete_link", "clean", "is_link", "new_graph",                 
                                    "delete_graph", "ls", "help", "copy", "eigenvalues", "add_path", "delete_path", "show", "system", "save", "list_labels", "load", "line_graph"};

//List of derivated graphs
std::vector<std::string> graph_types{"graph_matrix"};
int actual_graph_type = 0;

                                    
//Readline functions
char* completion_generator(const char* text, int state);
char** completer(const char* text, int start, int end);


//A graph_utilities object in commands.cpp file
extern my_graphs::graph_utilities the_utility_tool;


int main(int argc, char **argv) {
    
    //Presentation
    std::cout << "Interactive graph designer!" << std::endl;
    std::cout << "18.05.2019 - Berlin - V1.00" << std::endl;
    std::cout << "Use: help [command]" << std::endl;
    

    my_graphs::graph_base::exit_behaviour = my_graphs::MG_EXIT_SOFT;
    
    the_utility_tool.set_seed(10);
    
    std::string actual_graph_name = "G0";
    
    //Map with the graphs of this session
    std::map<std::string, std::unique_ptr<my_graphs::graph_base>> the_graphs;
    
    //the_graphs.insert(std::pair<std::string, std::unique_ptr<my_graphs::graph_base>>(actual_graph_name, new_graph_poliform(graph_types[actual_graph_type])));
    
    the_graphs.insert(std::make_pair(actual_graph_name, new_graph_poliform(graph_types[actual_graph_type])));
    
    if(the_graphs[actual_graph_name] == nullptr){
        std::cout << "Error starting the first graphs with type: \"" << graph_types[actual_graph_type] << "\"" << std::endl;
        the_graphs.erase(actual_graph_name);
        return 0;
    }
    
    
    //Readline 
    char *buf;
    read_history(".graph_history");
    rl_attempted_completion_function = completer;
    
    while(true){
    
        
        std::string prompt = "[\"" + actual_graph_name + "\"](" + std::to_string(the_graphs[actual_graph_name]->nodes()) + ") >> "; 
        
        
        buf = readline(prompt.c_str());
        if (strlen(buf) > 0) add_history(buf);
        
        std::string command_line(buf);
        std::string one_command;
        std::vector<std::string> commands;
        
        free(buf);
        
        std::istringstream words(command_line);
        while(words >> one_command) commands.push_back(one_command);
        
        if(commands.size()){
            if(commands[0] == "exit") break;
            else if(commands[0] == "add_link"   ) g_add_link(commands, *the_graphs[actual_graph_name]);
            else if(commands[0] == "resize"     ) g_resize(commands, *the_graphs[actual_graph_name]);
            else if(commands[0] == "info"       ) the_utility_tool.print_info(*the_graphs[actual_graph_name]);
            else if(commands[0] == "matrix"     ) the_utility_tool.print_matrix(*the_graphs[actual_graph_name]);
            else if(commands[0] == "show"       ) u_show(commands, *the_graphs[actual_graph_name], actual_graph_name);
            else if(commands[0] == "new_graph"  ) s_new_graph(commands, the_graphs, actual_graph_name);
            else if(commands[0] == "system"     ) s_system(commands);
            /*
            else if(commands[0] == "delete_link") delete_link(commands, A[actual_graph_name]);
            else if(commands[0] == "clean") A[actual_graph_name].clean();
            else if(commands[0] == "is_link") is_link(commands, A[actual_graph_name]);
            else if(commands[0] == "new_graph") new_graph(commands, A, actual_graph_name);
            else if(commands[0] == "delete_graph") delete_graph(commands, A, actual_graph_name);
            else if(commands[0] == "ls") ls_graphs(A);
            else if(commands[0] == "help") s_help(commands);
            else if(commands[0] == "copy") copy_graph(commands, A);
            else if(commands[0] == "eigenvalues") u_eigenvalues(commands, A[actual_graph_name]);
            else if(commands[0] == "add_path") g_add_path(commands, A[actual_graph_name]);
            else if(commands[0] == "delete_path") g_delete_path(commands, A[actual_graph_name]);
            else if(commands[0] == "show") u_show(commands, A[actual_graph_name], actual_graph_name);
            else if(commands[0] == "save") u_save_graph(commands, A[actual_graph_name], actual_graph_name);
            else if(commands[0] == "list_labels") u_list_labels(commands);
            else if(commands[0] == "load") u_load_graph(commands, A[actual_graph_name]);
            else if(commands[0] == "line_graph") u_line_graph(commands, A, actual_graph_name);*/
            else std::cout << "unknown command" << std::endl;
        }
    }
    
    write_history(".graph_history");
    rl_clear_history();
    return 0;
}






// Simple completion with readline.
//
// Eli Bendersky [http://eli.thegreenplace.net]
// This code is in the public domain.
char* completion_generator(const char* text, int state)
{
    // This function is called with state=0 the first time; subsequent calls are
    // with a nonzero state. state=0 can be used to perform one-time
    // initialization for this completion session.
    static std::vector<std::string> matches;
    static size_t match_index = 0;

    if (state == 0) {
        // During initialization, compute the actual matches for 'text' and keep
        // them in a static vector.
        matches.clear();
        match_index = 0;

        // Collect a vector of matches: vocabulary words that begin with text.
        std::string textstr = std::string(text);
        for (auto word : vocabulary) {
            if (word.size() >= textstr.size() && word.compare(0, textstr.size(), textstr) == 0) {
                matches.push_back(word);
            }
        }
    }

    if (match_index >= matches.size()) {
        // We return nullptr to notify the caller no more matches are available.
        return nullptr;
    } else {
        // Return a malloc'd char* for the match. The caller frees it.
        return strdup(matches[match_index++].c_str());
    }
}

char** completer(const char* text, int start, int end)
{
    // Don't do filename completion even if our generator finds no matches.
    rl_attempted_completion_over = 0;//1;

    // Note: returning nullptr here will make readline use the default filename
    // completer.
    return rl_completion_matches(text, completion_generator);
}
