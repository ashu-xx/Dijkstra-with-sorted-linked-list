# include "dijkstra.h"

using namespace std;

/*bi_list::node * bi_list::traverse_node(bi_list::node * n, int pos){
  bi_list::node * temp = new bi_list::node;
  temp = n;
  for(int i=0;i<pos;i++)
    temp = temp->next;
  return temp;
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
  //cout<<'\n'<<'('<<e->name<<','<<e->dist<<')'<<" element added!";
  //print_list();
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
  /*else{
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
    //cout<<'\n'<<'('<<e->name<<','<<e->dist<<')'<<" element deleted!";
    sorted_pop(dist, 1);
  }
  /*else{
    if (!repeat)
      cout<<'\n'<<'\''<<dist<<'\''<<" distanced element not found in list!";
  }
  if(!repeat)
    print_list();
}

bi_list::node * dijk::add_data_nodes(int *dist,int num){
  int *temp = dist;
  bi_list::node * n = new bi_list::node;
  for(int i=0;i<num; i++){
    if (*temp < 0)  {temp++;continue;}
    else{
      n->sorted_push(static_cast<char>(65+i), *temp, i);
      temp++;
    }
  }
  return n;
}

void dijk::dijk_insert(bi_list::node *n, bi_list::element *e,bi_list::node *t){
  bi_list::element *search_t = t->traverse_name(e->nm);
  if(!search_t->iAmNull){
    //cout<<"\n sorry, found in t "<<search_t->nm;
    //t->print_list(1);
    return;}
  bi_list::element *search = n->traverse_name(e->nm);
  if(!search->iAmNull){
    //cout<<search->dist<<','<<e->dist<<endl;
    if(search->dist > e->dist){
      //cout<<'\n'<<"putting in place larger val "<< static_cast<char>(65+e->nm)<<','<<e->nm<<','<<e->dist<<" than "<<search->dist<<endl;
      n->sorted_pop(static_cast<char>(e->nm+65));
      n->sorted_push(static_cast<char>(e->nm+65), e->dist, e->nm);
      //n->print_list(1);
    }
  }
  else{
    //cout<<'\n'<<"not there, putting in "<< static_cast<char>(65+e->nm)<<','<<e->nm<<','<<e->dist;
    n->sorted_push(static_cast<char>(e->nm+65), e->dist, e->nm);
    //n->print_list(1);
  }
}

void dijk::dijkstra_algo(bi_list::node * n_start, bi_list::node * shortest, int from, int dest,int num_nodes, int all_nodes){
  // if all_nodes is true, entire MST is traced out otherwise its stopped when
  // shortest distanced to desired destination is obtained
  if(!all_nodes)
    if(dest<0)
      return;
  bi_list::node * n_from = NULL;
  bi_list::node * trav = new bi_list::node;

  n_from = bi_list::traverse_node(n_start, from);

  // add the immediately connected nodes to the starting node
  for(bi_list::element *e = n_from->get_closest(); e!=NULL; e=e->prev){
    dijk_insert(trav, e, shortest);
    n_from->pos_pop(0);
  }

  // 'ans' keeps looking when we would have the desired destination in the shortest
  // path collection ie. bi_list::node shortest
  bi_list::element * ans = shortest->traverse_name(dest);

  while(shortest->get_size()<num_nodes && (all_nodes ? 1:ans->iAmNull)){
    n_from = NULL;

    // 'el' is the closest node element in node object trav (trav stores the distances
    // under considersation for transfer to the shortest path node object)
    bi_list::element* cl = trav->get_closest();
    if(cl!= NULL){
      trav->pos_pop(0);
      shortest->sorted_push(cl->name, cl->dist, cl->nm);

      n_from = bi_list::traverse_node(n_start, cl->nm);
      for(bi_list::element *e = n_from->get_closest(); e!=NULL; e=e->prev){
        e->dist += cl->dist;
        dijk_insert(trav, e, shortest);
      }
    }
    else{
      // all elements traversed in the network
      break;
    }
    if(!all_nodes)
      ans = shortest->traverse_name(dest);
    //else
      //shortest->print_list(1);
    //cout<<"shortest: "; shortest->print_list(1);
  }
  //cout<<"shortest: "; shortest->print_list(1);
}
*/
int main(int argc, char const *argv[]) {

  int *arr_pt[num_elements];
  int arr[num_elements][num_elements]=
    {
        {0,1,-1,1,-1},
        {1,0,3,-1,-1},
        {-1,3,0,2,-1},
        {1,-1,2,0,9},
        {-1,-1,-1,9,0}
    };
  for (int i=0; i<num_elements;i++){
    arr_pt[i] = new int[num_elements];
    for (int j=0;j<num_elements;j++)
      arr_pt[i][j] = arr[i][j];
  }
  //int *arr_pt[num_elements][num_elements];
  //arr_pt = &arr;
  bi_list::node * nodes_start;
  bi_list::node * nodes_end;
  bi_list::node * nodes_ptr;

  for(int i=0;i<num_elements; i++){
    bi_list::node * tempo = dijk::add_data_nodes(arr_pt[i], num_elements);
    if(!i)  {
      nodes_ptr = tempo;nodes_start = nodes_ptr;

    }
    else{
      nodes_ptr->next = tempo;
      nodes_ptr = tempo;
      nodes_ptr->next = NULL;
    }
  }


	int start; int dest;
	cout<<"\n\tShortest Distance:\n";
	cout<<"From Node: ";cin>>start;
	cout<<"\nTo Node: ";cin>>dest;
	int flag= 0;
	if(start<0 || start>=num_elements)
	  start = 0;
	if(dest<0 || dest>=num_elements)
		flag=1;
	bi_list::node * shortest_dst = new bi_list::node;

	dijk::dijkstra_algo(nodes_start, shortest_dst, start, dest, num_elements, flag);
	shortest_dst->print_list(1);
	bi_list::element * ans = shortest_dst->traverse_name(dest);
	if (!ans->iAmNull){
	  cout<<"shortest dist from "<<static_cast<char>(65+start)<<" to "<< static_cast<char>(65+dest)<<" is "<< ans->dist<<endl;
	}
	else
	  cout<<static_cast<char>(65+dest)<<"is not conneccted to "<< static_cast<char>(65+start)<<endl;
}
