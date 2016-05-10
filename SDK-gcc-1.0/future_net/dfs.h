#ifndef _DFS_
#define  _DFS_
#include "graph.h"
#include "stack.h"
#include <queue>
class DFS
{
public:
  int  * edgeTo;
  bool * marked;
  miniDiagraph * graph;
  int totalDistance;
  int s;
  int t;
  int lastDistance;
  int * miniEdgeTo;
  int * demandTo;
  int demandLen;
  vector<int> result;
  vector<BigEdge *> bigeResult;
  vector<BigEdge *> temp;
  StackInt * stack1;

  int * resultArray;
  bool * isTimeOut;

public:
  DFS(Digraph * graph,miniDiagraph * g, int s, int t, int * demandTo, int demandLen,bool * isTimeOut);
  void dfs(int v);
  bool mark(BigEdge * e);
  void unmark(BigEdge * e);
  bool check();
  void generatePath();
  bool static comp(BigEdge* a,BigEdge* b);

private:
  void findParentPoint(int v);
};
#endif
