// shortest path algorithm
# include "bi_list.h"
using namespace std;

void bi_list::node::print_list(int eleWise = 0){
  element *iter_element = closest;
  cout<<"\n";
  if(size){
    if(!eleWise){
      for (int i = 0; i<size; i++){
        cout << iter_element->dist << ((i < size-1) ? '<':'|');
        iter_element = iter_element->prev;
      }
    }
    else{
      for (int i = 0; i<size; i++){
        cout << '('<<iter_element->name<<','<<iter_element->dist<<')' << ((i < size-1) ? ',':' ');
        iter_element = iter_element->prev;
      }
    }
  }
  else
    cout<<"Empty";
  cout<<endl;
}

// traverse by pos
bi_list::element * bi_list::node::traverse(int pos){
  if((pos>= size) || (size == 0) || (pos<0)){
    element * nl = new element; // since no element found
    nl->iAmNull = 1;
    //std::nullptr_t n;
    return nl;
  }
  for (bi_list::element * iter_element = closest; iter_element!= NULL;iter_element = iter_element->prev){
    if(!pos){
      return iter_element;
    }
    pos--;
  }
}

// traverse by name, if multiple elements present then first one is returned
bi_list::element * bi_list::node::traverse_name(char name){
  int found  = 0;
  for (bi_list::element * iter_element = closest; iter_element!= NULL;iter_element = iter_element->prev){
    if(iter_element->name == name){
      return iter_element;
    }
  }
  element * nl = new element; // since no element found
  nl->iAmNull = 1;
  //std::nullptr_t n;
  return nl;
}

// traverse by name, all elements with that name put together in a node and returned
bi_list::node bi_list::node::traverse_nameMulti(char name){
  bi_list::node temp('t');
  int found  = 0;
  for (bi_list::element * iter_element = closest; iter_element!= NULL;iter_element = iter_element->prev){
    if(iter_element->name == name){
      temp.sorted_push(iter_element->name, iter_element->dist);
    }
  }
  return temp;
}

void bi_list::node::sorted_push(char name, int dist){
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

void bi_list::node::sorted_pop(char name, int repeat=0){

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
    sorted_pop(name, 1);
  }
  else{
    if (!repeat)
      cout<<'\n'<<'\''<<e->name<<'\''<<" element not found in list!";
  }
  if (!repeat)
    print_list();
}

// popping all elements of a specific distance
void bi_list::node::sorted_pop(int dist, int repeat=0){

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
      cout<<'\n'<<'\''<<dist<<'\''<<" distanced element not found in list!";
  }
  if(!repeat)
    print_list();
}


int main(int argc, char const *argv[]) {
  bi_list::node n('n');
  n.sorted_push('a',9);
  n.sorted_push('b',2);
  n.sorted_push('c',9);
  n.sorted_push('c',1);
  n.sorted_push('d',50);
  n.sorted_push('e',3);
  n.sorted_push('f',77);

  bi_list::element * ele = n.traverse_name('l');
  if (ele->iAmNull==1)
    cout<<"\nElement not found!"<<endl;
  else
    cout<<"\nfound  "<<ele->name<<','<<ele->dist<<endl;
  ele = n.traverse(3);
  if (ele->iAmNull==1)
    cout<<"\nElement not found!"<<endl;
  else
    cout<<"\nfound  "<<ele->name<<','<<ele->dist<<endl;

  bi_list::node nd('j');
  nd = n.traverse_nameMulti('c');
  nd.print_list(1);

  n.print_list();
  n.sorted_pop('c');
  return 0;
}
