// Bi-direectional list with sorted push

# include<iostream>

namespace bi_list{

  class element{
  public:
    char name;
    int nm;
    int dist;
    int iAmNull;
    element *next;
    element *prev;
    element(){
      iAmNull = 0;
      dist = -1;
      nm = -1;
      next = NULL;
      prev = NULL;
    }
  };

  class node {
    int size;
    char node_name;
    element * closest;
    element * farthest;

  public:
    node * next;

    node(char arg1='t'){
      size = 0;
      node_name = arg1;
      next = NULL;
      //std::cout << "\nList Object "<< node_name <<" created with no elements\n" << std::endl;
    }

    ~node(){
      //delete ele;
      //std::cout << "\nList Object "<< node_name <<" deleted" << std::endl;
    }

    void set_next(node * nx){
        next = nx;
    }

    node * get_next(){
        return next;
    }

    int get_size(){
      return size;
    }

    char get_name(){
      return node_name;
    }

    element * get_closest(){
      return closest;
    }

    element * get_farthest(){
      return farthest;
    }

    void print_list(int eleWise = 0);

    // push an element in a sorted list
    void sorted_push(char name, int dist,  int nm = -1 );

    // popping all elements of a specific name
    void sorted_pop(char name, int repeat=0);

    // popping by pos
    void pos_pop(int);

    // popping all elements of a specific distance
    void sorted_pop(int dist, int repeat=0 );

    // traverse by pos
    element* traverse_pos(int );

    // traverse by name, if multiple elements present then first one is returned
    element * traverse_name(char );

    // traverse by name (int type), if multiple elements present then first one is returned
    element * traverse_name(int );

    // traverse by name, multiple elements might be returned
    node traverse_nameMulti(char );

  };
  node * traverse_node(node *, int);
}

namespace dijk{
  void dijk_insert(bi_list::node*, bi_list::element*,bi_list::node*);
  void dijkstra_algo(bi_list::node * , bi_list::node * , int , int, int,int all_nodes=0 );
  bi_list::node * add_data_nodes(int *,int );
}
