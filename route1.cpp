#include "route.h"
#include "lib/lib_record.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


List::List(){
  first = NULL;
  size = 0;
}
void List::add(Edge * e)
{
  Node * oldFirst = first;
  first = new Node;
  first->edge = e;
  first->next = oldFirst;
  size++;
}

Digraph::Digraph(){
  V = 0;
  E = 0;
}

void Digraph::addEgde(Edge * e){
  int index = e->from;
  adj[index].add(e);
  E++;
  if(index > (V -1))
    V = index + 1;
}

MiniQueue::MiniQueue(int V){
  keys = new int[V];
  pq = new int[V];
  qp = new int[V];
  size = 0;
  for(int i = 0; i < V; i++){
    qp[i] = -1;
  }
}

void MiniQueue::insert(int v, int k){
  ++size;
  pq[size] = v;
  keys[size] = k;
  qp[v] = size;
  swim(size);
}

void MiniQueue::change(int v, int k){
  keys[v] = k;
  swim(qp[v]);
  sink(qp[v]);
}

int  MiniQueue::delMin(){
  int min = pq[1];
  exch(1,size--);
  sink(1);
  return min;
}

void MiniQueue::exch(int i, int j){
  int temp = pq[i];
  pq[i] = pq[j];
  pq[j] = temp;
  int keyTemp = keys[i];
  keys[i] = keys[j];
  keys[j] = keyTemp;
}

bool MiniQueue::isMin(int i, int j){
    return (keys[i] < keys[j]) ? true : false;
}

void MiniQueue::swim(int k){
  while((k > 1) && (isMin(k, k/2))){
    exch(k/2, k);
    k /= 2;
  }
}

void MiniQueue::sink(int k){
  while(2 * k <= size){
    int j = 2 * k;
    if((j < size)&&isMin(j+1,j))
      j++;
    if(isMin(k,j))
      break;
    exch(k,j);
    k = j;
  }
}


SearchPath::SearchPath(Digraph *g, int s){
  distTo = new int[g->V];
  mq = new MiniQueue(g->V);
  for(int i = 0; i < g->V; i++){
    distTo[i] = POSITIVE_INFINITY;
  }
  mq->insert(s,0);
  distTo[s] = 0;
  while(!mq->isEmpty()){
    relax(g,mq->delMin());
  }
}

void SearchPath::relax(Digraph * g, int v){
  List * list = g->getNextEdge(v);
  Edge * e =  NULL;
  for(Node * iter = list->interator(); iter != NULL; iter=iter->next){
    e = iter->edge;
    int w = e->to;
    if(distTo[w] > (distTo[v] + e->weight)){
      distTo[w] = distTo[v] + e->weight;
      edgeTo[w] = e;
      if(mq->contains(w))
        mq->change(w,distTo[w]);
      else
        mq->insert(w,distTo[w]);

    }
  }
}

DirectedDFS::DirectedDFS(Digraph * g, int s, int t, int * demandTo, int demandLen){
  this->graph = g;
  this->s = s;
  this->t = t;
  this->demandTo = demandTo;
  this->demandLen = demandLen;
  totalDistance = 0;
  lastDistance = -1;
  this->marked = new int[graph->V];
  this->edgeTo = new int[graph->V];
  this->miniEdgeTo = new int[graph->V];
  isNone = true;
  stack = new Stack();
  for(int i = 0; i < graph->V; i++){
    this->edgeTo[i] = -1;
    this->marked[i] = -1;
  }
  dfs(s);
}

bool DirectedDFS::check(){
  for(int i = 0; i < demandLen; i++){
    if(marked[demandTo[i]] != 1){
      return false;
    }
  }
  return true;
}

void DirectedDFS::dfs(int v){
  List * list = graph->getNextEdge(v);
  Edge * e = NULL;
  marked[v] = 1;
  if((v == t)){
    if(check()){
      if((lastDistance == -1) || (lastDistance > totalDistance)){
        lastDistance = totalDistance;
        isNone = false;
        for(int i = 0; i < graph->V; i++){
          miniEdgeTo[i] = edgeTo[i];
        }
      }
    }
    return;
  }
  for(Node * iter = list->interator(); iter != NULL; iter=iter->next){
    e = iter->edge;
    int w = e->to;
    if(marked[w] == -1){
      edgeTo[w] = v;
      totalDistance += e->weight;
      dfs(w);
      totalDistance -= e->weight;
      marked[w] = -1;
      edgeTo[w] = -1;
    }
  }
}

void DirectedDFS::findParentPoint(int v){
  stack->push(v);
  if(v == s){
    return;
  }
  findParentPoint(miniEdgeTo[v]);
}

void DirectedDFS::generatePath(){
  findParentPoint(t);
}

Stack::Stack(){
  first = NULL;
}

void Stack::push(int v){
  Point * p = new Point;
  p->v = v;
  p->next = first;
  first = p;
}

int Stack::pop(){
  if(first == NULL){
    return -1;
  }else{
    Point * p = first;
    first = first->next;
    return p->v;
  }
}

void parse2edge(char * line,Edge * e){
  char * outer;
  char * buf = line;
  char * result[20];
  int index = 0;
  while((result[index]=strtok_r(buf,",",&outer)) != NULL){
    buf = NULL;
    index++;
  }
  e->from = atoi(result[1]);
  e->to = atoi(result[2]);
  e->weight = atoi(result[3]);
}

int parse2demand(char * demand,int * demandTo, int * s, int * t){
  char * outer = NULL;
  char * buf = demand;
  char *result[100];
  int index = 0;
  while((result[index]=strtok_r(buf,",",&outer)) != NULL){
    buf = NULL;
    index++;
  }
  *s = atoi(result[0]);
  *t = atoi(result[1]);
  index = 0;
  char *demandResult[100];
  buf = result[2];
  outer = NULL;
  while((demandResult[index]=strtok_r(buf,"|",&outer)) != NULL){
    buf = NULL;
    demandTo[index] = atoi(demandResult[index]);
    index++;
  }
  return index;
}



//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand) {
  Digraph * graph = new Digraph();
  int * demandTo = new int[50];
  int S = 0;
  int T = 0;
  // 解析数据装配到Digraph中
	for (int i = 0; i < edge_num; i++) {
    Edge * e = new Edge;
    parse2edge(topo[i],e);
    graph->addEgde(e);
	}

  int demandLen = parse2demand(demand, demandTo, &S, &T);

  printf("demand len:%d\n",demandLen);

  SearchPath * sp = new SearchPath(graph,7);
  for(int i = 0; i < graph->V; i++){
    Edge * e = sp->edgeTo[i];
    if(e != NULL)
      printf("edge[%d] = %d\n",i,e->from);
  }

  // DirectedDFS * dfs = new DirectedDFS(graph,S,T,demandTo,demandLen);
  // if(!dfs->isNone){
  //   dfs->generatePath();
  //   printf("mini distance is %d \n",dfs->lastDistance);
  //   int p = -1;
  //   while((p = dfs->stack->pop()) != -1){
  //     record_result(p);
  //   }
  // }else{
  //   printf("<-----------Nothing----------->\n");
  // }
  delete sp;
  // delete dfs;
  delete graph;
}
