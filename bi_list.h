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
  char node_name; int max_len;
public:
  element * ele = new element[max_len];
  element * closest;
  element * farthest;
  element * temp;
  int size = 0;

  node(char arg1, int arg2){
    //cout<<arg1;
    node_name = arg1;
    max_len = arg2;
    cout << "Node Object created\n" << endl;
  }

  ~node(){
    delete ele;
    cout << "\nNode Object deleted" << endl;
  }

  void print_list(){
    element *iter_element = closest;
    cout<<"\nList: ";
    for (int i = 0; i<size; i++){
      cout << iter_element->dist << ((i < size-1) ? '<':'|');
      iter_element = iter_element->prev;
    }
    cout<<endl;
    /*
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
    }*/
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
            element * p = iter_element->next;
            p->prev = &ele[size];
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
    cout<<'\n'<<'('<<e.name<<','<<e.dist<<')'<<" element added!";
    print_list();
  }


  /*void sorted_pop(char name){

    element * e;
    for(element *iter_element = closest; iter_element!=NULL; iter_element = iter_element->next){
      if(iter_element->name == name){
        e = iter_element;
        break;
      }
    }

    element * p = e->prev;
    element * n = e->next;
    // both sides elements
    if(p != NULL && n != NULL){
      p->next = n;
      n->prev = p;
    }
    else{
      // no next element but prev element there
      if(p != NULL){
        p->next = NULL;
        closest = p;
      }
      else{
        // no prev element but next element there
        if(n != NULL){
          n->prev = NULL;
          farthest = n;
        }
        // neither prev nor next element
        else{
          closest = NULL;
          farthest = NULL;
        }
      }
    }

    size--;
    cout<<'\n'<<'('<<e->name<<','<<e->dist<<')'<<" element deleted!";
    print_list();
  }*/
};
