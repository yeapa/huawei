#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

void BigEdge::addEdge(Edge * e)
{
  eVector.push_back(e);
  if (e->to!=to) {
    vVector.push_back(e->to);
  }
  size++;
}

BigEdge::BigEdge()
{
    size=0;
    weight=0;
}

List::List()
{
        first=NULL;
        size=0;
}

void List::add(Edge * e)
{
        Node * oldFirst = first;
        first = new Node();
        first->edge = e;
        first->next = oldFirst;
        size++;
}

Digraph::Digraph()
{
        V = 0;
        E = 0;
}

void Digraph::addEdge(Edge * e)
{
        int from = e->from;
        int to=e->to;
        adj[from].add(e);
        E++;
        if (from > (V - 1)) //端点必须连续
          V = from +1;
        if(to>(V-1))
          V=to+1;
}

void Digraph::addEdge1(Edge * e) {
  int from = e->from;
  // int to=e->to;
  eVector[from].push_back(e);
}

void miniDiagraph::addBigEdge(BigEdge * bigedge)
{
  int from=bigedge->from;
  bool flag=false;
  vector<BigEdge*>::iterator iter;
  for (iter=adjBigEdge[from].begin(); iter!=adjBigEdge[from].end(); iter++) {
    if ((*iter)->to!=bigedge->to) {
      continue;
    }
    if ((*iter)->vVector.size()!=bigedge->vVector.size()) {
      continue;
    }
    if (bigedge->vVector.size()==0) {
      flag=true;
    }

    unsigned int count=0;
    vector<int>::iterator iter1=(*iter)->vVector.begin();
    vector<int>::iterator iter2=bigedge->vVector.begin();
    for (; iter1!=(*iter)->vVector.end()&&iter2!=bigedge->vVector.end(); iter1++,iter2++) {
      if ((*iter1)==(*iter2)) {
        count++;
      }
      else break;
      if (count==(bigedge->vVector.size())) {
        flag=true;
      }
    }

    if (flag==true) {
      break;
    }
  }

  if (flag==true) {
    return;
  }

  vector<int>::iterator iter3;
  printf("\n%d  ",bigedge->from );
  for (iter3=bigedge->vVector.begin(); iter3!=bigedge->vVector.end(); iter3++)
  {
    printf("%d  ",*iter3 );
  }
  printf("%d  bigedge->weight=%d\n\n",bigedge->to,bigedge->weight );



  size++;
  adjBigEdge[from].push_back(bigedge);
}

vector<BigEdge*>* miniDiagraph:: getAdjEdge(int v)
{
  return &adjBigEdge[v];
}

void Digraph::deleteVertax(int v)
{
  adj[v].first=NULL;
}
