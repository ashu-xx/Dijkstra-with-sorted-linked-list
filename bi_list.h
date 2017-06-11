// Bi-direectional list with sorted push

# include<iostream>
using namespace std;
class node {
  class element{
  public:
    char name;
    int dist;
    element *next;
    element *prev;
  };
  char my_name; int max_len;
public:
  element * ele = new element[max_len];
  element * closest;
  element * farthest;
  element * temp;
  int size = 0;

  node(char arg1, int arg2){
    //cout<<arg1;
    my_name = arg1;
    cout<<my_name;
    max_len = arg2;
    cout << "Node Object created" << endl;
  }

  ~node(){
    delete ele;
    cout << "Node Object deleted" << endl;
  }

  void print_list(){
    element *iter_element = closest;
    cout<<"\n\nList: ";
    for (int i = 0; i<size; i++){
      std::cout << iter_element->dist << ((i < size-1) ? '<':' ');
      iter_element = iter_element->prev;
    }
    cout<<"\nElement wise\n";
    for (int i = 0; i<size;i++){
      int nxt = -1, prv = -1;
      if ( ele[i].next != NULL){
        element *t = ele[i].next;
        nxt = t->dist;
      }
      if ( ele[i].prev != NULL){
        element *t = ele[i].prev;
        prv = t->dist;
      }
      cout<<"element "<< ele[i].name <<": ditance "<< ele[i].dist << ", next dist=" << nxt << ", prev dist=" << prv << endl;
      //n.temp = n.temp->next;
    }
  }

  void sorted_push(char name, int dist){
    element e;
    e.name = name;
    e.dist = dist;
    e.next = NULL;
    e.prev = NULL;
    ele[size] = e;
    if(size){
      element *iter_element = closest;
      for (int i = 0; i<size; i++){

        // inserting in start or somewhere in the middle
        if(iter_element->dist > dist ){
          //  in the start
          if(iter_element->dist == closest->dist){
            ele[size].prev = closest;
            element * p = closest;
            closest = &ele[size];
            p->next = &ele[size];
          }
          else{
            element * p = iter_element->prev;
            p->next = &ele[size];
            ele[size].next = p;
            ele[size].prev = iter_element;
            ele[i].next = &ele[size];
          }
          break;
        }
        if (i==size-1){
          // when inserted element is farthest
          element * p = farthest;
          p->prev = &ele[size];
          ele[size].next = p;
          farthest = &ele[size];
        }
        iter_element = iter_element->prev;
      }
    }
    else{
      closest = &ele[0];
      farthest = &ele[0];
      ele[0].prev = NULL;
      ele[0].next = NULL;
    }
    size++;
    print_list();
  }
};
