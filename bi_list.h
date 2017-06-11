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
    int size = 0;
    char node_name;
    element * closest;
    element * farthest;

  public:
    node(char arg1='t'){
      node_name = arg1;
      //std::cout << "\nList Object "<< node_name <<" created with no elements\n" << std::endl;
    }

    ~node(){
      //delete ele;
      //std::cout << "\nList Object "<< node_name <<" deleted" << std::endl;
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

    void print_list(int );

    // push an element in a sorted list
    void sorted_push(char , int );

    // popping all elements of a specific name
    void sorted_pop(char , int );

    // popping by pos
    void pos_pop(int);

    // popping all elements of a specific distance
    void sorted_pop(int , int );

    // traverse by pos
    element* traverse_pos(int );

    // traverse by name, if multiple elements present then first one is returned
    element * traverse_name(char );

    // traverse by name (int type), if multiple elements present then first one is returned
    element * traverse_name(int );

    // traverse by name, multiple elements might be returned
    node traverse_nameMulti(char );

  };
}
