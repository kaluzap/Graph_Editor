namespace my_graphs{
    
    #ifndef MY_GRAPH_BASE_IS_VERY_NICE
    #define MY_GRAPH_BASE_IS_VERY_NICE
    
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
    
    #endif
}


