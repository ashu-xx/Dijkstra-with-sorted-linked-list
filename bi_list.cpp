// shortest path algorithm
# include "dijkstra.h"
using namespace std;
int main(int argc, char const *argv[]) {
  node n('n',10);
  n.sorted_push('a',9);
  n.sorted_push('b',2);
  n.sorted_push('c',1);
  n.sorted_push('d',50);
  n.sorted_push('e',3);
  n.sorted_push('f',77);

  cout<<"\n\n\n Final: \n";
  n.print_list();
  return 0;
}
