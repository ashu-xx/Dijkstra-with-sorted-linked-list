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
  element * closest;
  element * farthest;
  int size = 0;

  node(char arg1, int arg2){
    //cout<<arg1;
    node_name = arg1;
    max_len = arg2;
    cout << "Node Object created\n" << endl;
  }

  ~node(){
    //delete ele;
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
  }

  // push an element in a sorted list
  void sorted_push(char name, int dist){
    element * e = new element;
    e->name = name;
    e->dist = dist;
    e->next = NULL;
    e->prev = NULL;
    if(size){
      element *iter_element = closest;
      for (int i = 0; i<size; i++){

        // inserting in start or somewhere in the middle
        if(iter_element->dist > dist ){
          //  in the start
          if(iter_element->dist == closest->dist){
            e->prev = closest;
            element * p = closest;
            closest = e;
            p->next = e;
          }
          else{
            element * p = iter_element->next;
            p->prev = e;
            e->next = p;
            e->prev = iter_element;
            iter_element->next = e;
          }
          break;
        }
        if (i==size-1){
          // when inserted element is farthest
          element * p = farthest;
          p->prev = e;
          e->next = p;
          farthest = e;
        }
        iter_element = iter_element->prev;
      }
    }
    else{
      closest = e;
      farthest = e;
      e->prev = NULL;
      e->next = NULL;
    }
    size++;
    cout<<'\n'<<'('<<e->name<<','<<e->dist<<')'<<" element added!";
    print_list();
  }


  // popping all elements of a specific name
  void sorted_pop(char name){

    element * e;
    bool found = false;
    for(element *iter_element = closest; iter_element!=NULL; iter_element = iter_element->prev){
      if(iter_element->name == name){
        e = iter_element;
        found = true;
        break;
      }
    }
    if (found){
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
    }
    else{
      cout<<'\n'<<'\''<<e->name<<'\''<<" element not found in list!";
    }
    print_list();
  }

  // popping all elements of a specific distance
  void sorted_pop(int dist, int repeat=0){

    element * e;
    bool found = false;
    for(element *iter_element = closest; iter_element!=NULL; iter_element = iter_element->prev){
      if(iter_element->dist == dist){
        e = iter_element;
        found = true;
        break;
      }
    }
    if (found){
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
      sorted_pop(dist, 1);
    }
    else{
      if (!repeat)
        cout<<'\n'<<'\''<<e->name<<'\''<<" element not found in list!";
    }
    if(!repeat)
      print_list();
  }
};
