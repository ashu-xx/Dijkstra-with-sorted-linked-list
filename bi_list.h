// Bi-direectional list with sorted push

# include<iostream>
namespace bi_list{
  class node {
    class element{
    public:
      char name;
      int dist;
      element *next;
      element *prev;
    };
    char node_name; int max_len;
  public:
    element * closest;
    element * farthest;
    int size = 0;

    node(char arg1, int arg2){
      //cout<<arg1;
      node_name = arg1;
      max_len = arg2;
      std::cout << "Node Object created\n" << std::endl;
    }

    ~node(){
      //delete ele;
      std::cout << "\nNode Object deleted" << std::endl;
    }

    void print_list();

    // push an element in a sorted list
    void sorted_push(char , int );

    // popping all elements of a specific name
    void sorted_pop(char , int );

    // popping all elements of a specific distance
    void sorted_pop(int , int );
  };
}
