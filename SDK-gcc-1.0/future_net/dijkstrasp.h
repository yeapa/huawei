#ifndef _DIJKSTRASP_
#define  _DIJKSTRASP_
#include "graph.h"
#include "miniqueue.h"
#include<vector>
#include <iostream>
#include <stack>
#include <queue>
#include "stack.h"
using namespace std;


class DijkstraSP
{
public:
  Edge * edgeTo[600];
  Edge * edgeToX[600];
  int demandLen;
  int * demandTo;
  bool * marked;
  Digraph * graph;
  Digraph * graph1;
  MiniQueue * mq;
  int start;
  int * distTo;
  int desti;
  int dfscount;
  vector<int> result;
  bool * isTimeOut;
  StackInt stack;
  miniDiagraph * minigraph;
  queue<int> * wfsqueue;
  int countV[MAX_V];

public:
  DijkstraSP(Digraph * g,Digraph * g1, int s,int desti,int demandLen,int * demandTo,bool * isTimeOut);
  // DijkstraSP(Digraph * g, int start,int desti,int demandLen,int * demandTo,int * ranked);
  bool demandContain(int v);
  void parseBigEdge(int begin);
  void generateBigEdge(int v,int begin);
  void search();
  void relax(Digraph * g, int from);
  void generateGraph();
  void findRoute(int a);
  void rawdfs(int v,int from);
  void parseRoute(int v,int b);
  void wfs(int v);
  void wfs1(int v,int ins);
  bool static comp(Edge* a,Edge* b);
};

#endif
