// shortest path algorithm
# include "bi_list.h"
using namespace std;

bi_list::node * bi_list::traverse_node(bi_list::node * n, int pos){
  bi_list::node * temp = new bi_list::node;
  temp = n;
  for(int i=0;i<pos;i++)
    temp = temp->next;
  return temp;
}

int bi_list::dijkstra_algo(bi_list::node * n_start, int offset, int * shortest, int num_nodes, int from, int dest, int stop){
  cout<<"\ncheck\n";
  bi_list::node * n_from = NULL;
  n_from = bi_list::traverse_node(n_start, from);

  for(bi_list::element *e = n_from->get_closest(); e!=NULL; e=e->prev){
    cout<<"\n working on element: "<<e->nm<<','<<e->dist<<" offset="<<offset<< endl;
    cout<<"\npop: ";
    n_from->print_list();n_from->pos_pop(0);
    cout<<"\npoped: ";
    n_from->print_list();
    if (e->nm == dest){
      cout<<"\nIn dist"<<e->dist<<"\n";
      *shortest = offset + e->dist;
      return 1;
    }
    if(!(e->nm == from)){
      cout<<'f'<<e->nm;
      stop = bi_list::dijkstra_algo(n_start, e->dist + offset, shortest, num_nodes, e->nm, dest, 0);
      if (stop)
        break;
    }
  }
  return stop;
}

void bi_list::node::print_list(int eleWise){
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
bi_list::element * bi_list::node::traverse_pos(int pos){
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

// traverse by name, if multiple elements present then first one is returned
bi_list::element * bi_list::node::traverse_name(int name){
  int found  = 0;
  for (bi_list::element * iter_element = closest; iter_element!= NULL;iter_element = iter_element->prev){
    if(iter_element->nm == name){
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

void bi_list::node::sorted_push(char name, int dist, int nm){
  element * e = new element;
  e->name = name;
  e->dist = dist;
  e->nm = nm;
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

void bi_list::node::pos_pop(int pos){
  if((pos>= size) || (size == 0) || (pos<0)){
    return;
  }
  for (bi_list::element * iter_element = closest; iter_element!= NULL;iter_element = iter_element->prev){
    if(!pos){
      bi_list::element * e = iter_element;
      bi_list::element * p = e->prev;
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
    }

    pos--;
  }
}
void bi_list::node::sorted_pop(char name, int repeat){

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
    //cout<<'\n'<<'('<<e->name<<','<<e->dist<<')'<<" element deleted!";
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
void bi_list::node::sorted_pop(int dist, int repeat){

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


/*int main(int argc, char const *argv[]) {
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
  ele = n.traverse_pos(3);
  if (ele->iAmNull==1)
    cout<<"\nElement not found!"<<endl;
  else
    cout<<"\nfound  "<<ele->name<<','<<ele->dist<<endl;

  bi_list::node nd('j');
  nd = n.traverse_nameMulti('c');
  nd.print_list(1);

  n.print_list();
  n.pos_pop(6);
  n.print_list();
  cout<<"\n\nSuccess!";
  return 0;
}*/

int main(int argc, char const *argv[]) {
  bi_list::node * nodes_start;
  bi_list::node * nodes_end;
  bi_list::node * nodes_ptr[100];


  bi_list::node * nd = new bi_list::node;
  nd->sorted_push(static_cast<char>(65+0), 0, 0);
  nd->sorted_push(static_cast<char>(65+1), 1, 1);
  nd->sorted_push(static_cast<char>(65+2), 2, 2);
  nodes_start = nd;
  nd->print_list();

  bi_list::node *nd1 = new bi_list::node;
  nd1->sorted_push(static_cast<char>(65+1), 0, 1);
  nd1->sorted_push(static_cast<char>(65+2), 1, 2);
  nd1->sorted_push(static_cast<char>(65+0), 1, 0);
  nd->set_next(nd1);
  nd1->print_list();

  bi_list::node *nd2 = new bi_list::node;
  nd2->sorted_push(static_cast<char>(65+2), 0, 2);
  nd2->sorted_push(static_cast<char>(65+1), 1, 1);
  nd2->sorted_push(static_cast<char>(65+0), 2, 0);
  nd1->set_next(nd2);
  nd2->print_list();
  nodes_end = nd2;

  bi_list::node * tm = new bi_list::node;
  tm = traverse_node(nodes_start,1);
  tm->print_list(1);
  cout<<"\n starting algo\n\n";
  int * shortest_dst = new int;
  //int dijkstra_algo(node * n_start, int offset, int * shortest, int num_nodes, int from, int dest, int stop=0);
  int success = bi_list::dijkstra_algo(nodes_start, 0, shortest_dst, 3, 2, 0, 0);

  if(success)
    cout<<"shortest dist = "<<*shortest_dst;
  else
    cout<<"Unable to find!";

  return 0;
}
