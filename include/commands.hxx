#include <vector>
#include <string>
#include <map>
#include <memory>

#include "graph_base.hxx"
#include "graph_utilities.hxx"


//Functions related to graph_utilities class
void u_line_graph(std::vector<std::string> &commands, std::map<std::string, std::unique_ptr<my_graphs::graph_base>> &A, std::string &actual_graph_name);
void u_load_graph(std::vector<std::string> &commands, my_graphs::graph_base &A);
void u_list_labels(std::vector<std::string> &commands);
void u_save_graph(std::vector<std::string> &commands, my_graphs::graph_base &A, std::string actual_graph_name);
void u_eigenvalues(std::vector<std::string> &commands, my_graphs::graph_base &A);
void u_show(std::vector<std::string> &commands, my_graphs::graph_base &A, std::string actual_graph_name);


//Functions related to graph class
void g_add_path(std::vector<std::string> &commands, my_graphs::graph_base &A);
void g_delete_path(std::vector<std::string> &commands, my_graphs::graph_base &A);
void g_resize(std::vector<std::string> &commands, my_graphs::graph_base &IN);
void g_add_link(std::vector<std::string> &commands, my_graphs::graph_base &IN);
void g_delete_link(std::vector<std::string> &commands, my_graphs::graph_base &IN);
void g_is_link(std::vector<std::string> &commands, my_graphs::graph_base &IN);
void g_delete_node(std::vector<std::string> &commands, my_graphs::graph_base &IN);


//Functions related to the system
void s_system(std::vector<std::string> &commands);
void s_help(std::vector<std::string> &commands);
void s_ls_graphs(std::map<std::string, std::unique_ptr<my_graphs::graph_base>> &A);
void s_new_graph(std::vector<std::string> &commands, std::map<std::string, std::unique_ptr<my_graphs::graph_base>> &A, std::string &actual_graph_name);
void s_delete_graph(std::vector<std::string> &commands, std::map<std::string, std::unique_ptr<my_graphs::graph_base>> &A, std::string &actual_graph_name);
void s_copy_graph(std::vector<std::string> &commands, std::map<std::string, std::unique_ptr<my_graphs::graph_base>> &A, std::string &actual_graph_name);
void s_show_class(void);
void s_change_class(std::vector<std::string> &commands);


