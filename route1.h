#ifndef __ROUTE_H__
#define __ROUTE_H__
#define MAX_V 600
#define MAX_D_V 50
#define POSITIVE_INFINITY 65535

void search_route(char *graph[5000], int edge_num, char *condition);

struct Edge{
  int from;
  int to;
  int weight;
};

struct Node{
  Edge * edge;
  Node * next;
};

class List{
public:
  Node * first;
  int size;
public:
  List();
  void add(Edge * e);
  Node * interator(){return first;};
};

class Digraph{
public:
  int V;
  int E;
  List adj[MAX_V];
public:


  Digraph();
  int sizeOfV(){return V;}
  int sizeOfE(){return E;}
  void addEgde(Edge * e);
  List * getNextEdge(int v){return &adj[v];}
};

class MiniQueue{
public:
  int * keys;
  int * pq;
  int * qp;
  int size;
public:
  MiniQueue(int V);
  void insert(int v,int k);
  int delMin();
  bool isEmpty(){return size == 0; }
  bool contains(int k){return qp[k] != -1;}
  void change(int v,int k);
  bool isMin(int i, int j);   //i 是父节点 i < j = true

private:
  void exch(int i, int j);
  void swim(int k);
  void sink(int k);
};

class SearchPath{
public:
  Edge * edgeTo[600];
  int * distTo;
  MiniQueue * mq;

public:
  SearchPath(Digraph * g, int s);
  void relax(Digraph * g, int v);
};


struct Point{
  int v;
  Point * next;
};

class Stack{
public:
  Point * first;

public:
  Stack();
  void push(int v);
  int pop();
};

class DirectedDFS{
public:
  int  * edgeTo;
  int * marked;
  Digraph * graph;
  int totalDistance;
  int s;
  int t;
  int lastDistance;
  int * miniEdgeTo;
  int * demandTo;
  int demandLen;
  Stack * stack;
  bool isNone;
public:
  DirectedDFS(Digraph * g, int s, int t, int * demandTo, int demandLen);
  void dfs(int v);
  bool check();
  void generatePath();

private:
  void findParentPoint(int v);
};



#endif
