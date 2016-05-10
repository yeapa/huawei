#ifndef _GRAPH_
#define _GRAPH_
#include <iostream>
#include<vector>
using namespace std;

#define MAX_V 600
#define MAX_D_V 50

struct Edge{
  int index;
  int from;
  int to;
  int weight;
};

struct Node
{
  Edge * edge;
  Node * next;
};

class BigEdge
{
public:
    int from ;
    int to;
    int size;
    int weight;
    vector<Edge*> eVector;
    vector<int> vVector;
    vector<int> idVector;
    BigEdge();
    void addEdge(Edge * e);
};

class List
{
public:
  Node * first;
  int size;
public:
  List();
  void add(Edge * e);
  Node * iterator(){return first;};
};

class Digraph
{
public:
  int V;
  int E;
  List adj[MAX_V];
  vector<Edge*>  eVector[MAX_V];
public:
  Digraph();
  void deleteVertax(int v);
  int sizeOfV(){return V;}
  int sizeOfE(){return E;}
  void addEdge(Edge * e);
  void addEdge1(Edge * e);
  void sortEdge();
  List * getAdjEdge(int v){return &adj[v];}
};

class miniDiagraph
{
public:
  int size;
  miniDiagraph(){size=0;}
  vector<BigEdge*> adjBigEdge[MAX_V];
  void addBigEdge(BigEdge * bigedge);
  vector<BigEdge*> * getAdjEdge(int v);
};
#endif
