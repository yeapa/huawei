#include "dfs.h"
#include "stdlib.h"
#include <vector>
#include<algorithm>
DFS::DFS(Digraph * graph,miniDiagraph * g, int s, int t, int * demandTo, int demandLen,bool * isTimeOut)
{
        printf("DirectedDFS begin\n" );
        printf("miniDiagraph size=%d",g->size );

        this->graph = g;
        this->s = s;
        this->t = t;
        this->demandTo = demandTo;
        this->demandLen = demandLen;
        this->marked = new bool[graph->V];
        this->edgeTo = new int[graph->V];
        this->resultArray=new int[demandLen+2];
        this->isTimeOut=isTimeOut;
        lastDistance=0;
        totalDistance=0;

        stack1 = new StackInt();
        // printf("maxV=%d \n", graph->V);
        for (int i = 0; i < graph->V; i++)
        {
                this->edgeTo[i] = -1;
        }
        for (int i = 0; i < graph->V; i++)
        {
                this->marked[i] = false;
        }

        for (int i = 0; i < MAX_V; i++) {
          vector<BigEdge* >*  list = this->graph->getAdjEdge(i);
          sort(list->begin(),list->end(),comp);
        }
        dfs(s);
}

bool DFS::check()
{
        for (int i = 0; i < demandLen; i++)
        {
                if (marked[demandTo[i]]!=true)
                {
                        return false;
                }
        }
        return true;
}

void DFS::dfs(int v)
{
        if ((totalDistance>lastDistance)&&lastDistance!=0) {
          return;
        }
        vector<BigEdge* >*  list = graph->getAdjEdge(v);
        BigEdge * e = NULL;
        // marked[v] = true;
        if (v==t)
        {
          // printf("here\n");
          // for (int i = 0; i < demandLen; i++) {
          //   printf("%d  ",marked[demandTo[i]] );
          // }
                if (check())
                {
                  // totalDistance=0;
                  // vector<BigEdge *>::iterator iter;
                  // for (iter=bigeResult.begin(); iter!=bigeResult.end(); iter++)
                  // {
                  //   // vector<int> temp1=(*iter)->vVector;
                  //   // vector<int>::iterator iter1;
                  //   //
                  //   // printf("%d  ",((*iter)->from));
                  //   // for (iter1=temp1.begin(); iter1!=temp1.end(); iter1++)
                  //   // {
                  //   //   printf("%d  ",*iter1);
                  //   // }
                  //   totalDistance+=(*iter)->weight;
                  // }
                  // printf("%d\n",t );
                  // printf("lastDistance=%d,totalDistance=%d \n",lastDistance,totalDistance );
                  if ((lastDistance==0)||(lastDistance>totalDistance))
                  {
                          result.clear();
                          lastDistance = totalDistance;
                          vector<BigEdge *>::iterator iter;
                          for (iter=bigeResult.begin(); iter!=bigeResult.end(); iter++)
                          {
                            // vector<int> temp1=(*iter)->vVector;
                            // vector<int>::iterator iter1;
                            //
                            // printf("%d  ",((*iter)->from));
                            // for (iter1=temp1.begin(); iter1!=temp1.end(); iter1++)
                            // {
                            //   printf("%d  ",*iter1);
                            // }

                            vector<Edge *>::iterator iter2;
                            vector<Edge *> temp2=(*iter)->eVector;
                            for (iter2=temp2.begin(); iter2!=temp2.end(); iter2++)
                            {
                              result.push_back((*iter2)->index);
                            }
                          }
                  }
                }
                // return;
        }
        if(*isTimeOut)
          return;
        vector<BigEdge*>::iterator iter;
        // sort(list->begin(),list->end(),comp);
        for (iter=list->begin(); iter!=list->end(); iter++)
        {
                if(*isTimeOut)
                  return;
                e = *iter;
                int w = e->to;
                // printf("here%d\n",w);
                if (marked[w]==false&&mark(e))
                {
                        marked[w] = true;
                        bigeResult.push_back(e);
                        totalDistance+=e->weight;
                        dfs(w);
                        totalDistance-=e->weight;
                        bigeResult.pop_back();
                        marked[w] = false;
                        unmark(e);
                }
        }
        // printf("end V=%d \n", v);
}
bool DFS::comp(BigEdge* a,BigEdge* b){
  return a->weight<b->weight;
}
bool DFS::mark(BigEdge * e)
{
  vector<int>  vec=e->vVector;
  vector<int>::iterator iter;
  vector<int> record;
  record.clear();
  for (iter=vec.begin(); iter!=vec.end(); iter++)
  {
    if (marked[*iter]==true)
    {
      while (!record.empty()) {
        // printf("un mark=%d  ",record.back() );
        marked[record.back()]=false;
        record.pop_back();
      }
      return false;
    }
    else
    {
      // printf("mark %d  ",*iter);
      marked[*iter]=true;
      record.push_back(*iter);
    }
  }
  return true;
}

void DFS::unmark(BigEdge * e)
{
  vector<int>  vec=e->vVector;
  vector<int>::iterator iter;
  for (iter=vec.begin(); iter!=vec.end(); iter++)
  {
    marked[*iter]=false;
  }
}
