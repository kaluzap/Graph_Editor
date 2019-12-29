#include "graph_base.hxx"
#include <vector>
#include <complex>
#include <random>



namespace my_graphs{

    #ifndef MY_GRAPH_UTILITIES_ARE_VERY_NICE
    #define MY_GRAPH_UTILITIES_ARE_VERY_NICE

    class graph_utilities{
        public:
            
            graph_utilities();
            graph_utilities(unsigned long in_seed);
            
            void print_info(const graph_base &in);
            void print_matrix(const graph_base &in);
            int get_eigenvalues(const graph_base &in, const char kind_of);
            void print_graph_dot(const std::string file_name, const my_graphs::graph_base &IN);
            
            int line_graph(const graph_base &IN, graph_base &OUT);
            
            std::vector<std::string> list_file_labels(const std::string file_name);
            int write_file(const std::string file_name, const std::string name, const graph_base &IN, bool no_repeated_labels = true);
            int read_file(const std::string file_name, std::string the_label, class graph_base &IN);
            
            double rand(void);
            int set_seed(unsigned long);
            
            std::vector<std::complex<double>> eigenvalues;
            std::vector<double> coeficients;
            
        private:
            
            void get_coefficients(void);
            
            unsigned long seed;
            std::default_random_engine my_generator;
            std::uniform_real_distribution<double> my_distribution;
            
            bool started_generator;
    };

    #endif
}


