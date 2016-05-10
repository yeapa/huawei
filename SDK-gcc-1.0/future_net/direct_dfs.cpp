#include "direct_dfs.h"
#include "stdlib.h"
DirectedDFS::DirectedDFS(Digraph * g, int s, int t, int * demandTo, int demandLen,bool * isTimeOut)
{
        // printf("DirectedDFS begin\n" );
        // printf("%d,%d  %d\n",s,t,demandLen );

        this->graph = g;
        this->s = s;
        this->t = t;
        this->demandTo = demandTo;
        this->demandLen = demandLen;
        totalDistance = 0;
        lastDistance = -1;
        this->marked = new int[graph->V];
        this->miniEdgeTo=new int[graph->V];
        this->edgeTo=new int[graph->V];
        this->resultArray=new int[demandLen+2];
        this->isTimeOut=isTimeOut;

        isNone = true;
        stack = new StackInt();
        // printf("maxV=%d \n", graph->V);
        for (int i = 0; i < graph->V; i++)
        {
                this->edgeTo[i] = -1;
                this->marked[i] = -1;
        }
        dfs(s);
        // generatePath();
}

bool DirectedDFS::check()
{
        for (int i = 0; i < demandLen; i++)
        {
                if (marked[demandTo[i]]!=1)
                {
                        return false;
                }
        }
        return true;
}

void DirectedDFS::dfs(int v)
{
        // printf("V=%d \n", v);
        List * list = graph->getAdjEdge(v);
        Edge * e = NULL;
        marked[v] = 1;
        if (totalDistance>lastDistance&&lastDistance!=-1) {
          return;
        }
        if (v==t)
        {
                if (check())
                {
                        if ((lastDistance==-1)||(lastDistance>totalDistance))
                        {
                                lastDistance = totalDistance;
                                isNone = false;
                                result=resultemp;
                                for (int i = 0; i < graph->V; i++)
                                {
                                        miniEdgeTo[i] = edgeTo[i];
                                }
                        }
                }
                return;
        }
        if(*isTimeOut)
          return;
        for (Node * iter=list->iterator();iter!=NULL; iter=iter->next)
        {
                if(*isTimeOut)
                  return;
                e = iter->edge;
                int w = e->to;
                if (marked[w]==-1)
                {
                        edgeTo[w] = v;
                        totalDistance += e->weight;
                        resultemp.push_back(e->index);
                        dfs(w);
                        resultemp.pop_back();
                        totalDistance -= e->weight;
                        marked[w] = -1;
                        edgeTo[w] = -1;
                }
        }
        // printf("end V=%d \n", v);
}

void DirectedDFS::findParentPoint(int v)
{
        if(v == s)
        {
          stack->push(v);
            return;
        }
        stack->push(v);
        findParentPoint(miniEdgeTo[v]);
}

void DirectedDFS::generatePath()
{
        findParentPoint(t);
}
