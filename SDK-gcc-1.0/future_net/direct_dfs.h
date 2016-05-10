#ifndef _DIRECTDFS_
#define  _DIRECTDFS_
#include "graph.h"
#include "stack.h"
class DirectedDFS
{
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
  StackInt * stack;
  bool isNone;
  int * resultArray;
  bool * isTimeOut;
  vector<int> resultemp;
  vector<int> result;

public:
  DirectedDFS(Digraph * g, int s, int t, int * demandTo, int demandLen,bool * isTimeOut);
  void dfs(int v);
  bool check();
  void generatePath();

private:
  void findParentPoint(int v);
};
#endif
