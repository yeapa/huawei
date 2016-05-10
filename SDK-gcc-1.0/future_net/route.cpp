
#include "route.h"
#include "lib/lib_record.h"
#include "graph.h"
#include "direct_dfs.h"
#include "parse.h"
#include "dijkstrasp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>        //pause()
#include <signal.h>        //signal()
#include <string.h>        //memset()
#include <sys/time.h>    //struct itimerval, setitimer()
void setTimeOut(int);
bool isTimeOut;
//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
        isTimeOut = false;
        signal(SIGALRM, setTimeOut);

        itimerval tick;
        tick.it_value.tv_usec = 100000;
        tick.it_value.tv_sec = 9;
        tick.it_interval.tv_sec = 100;
        tick.it_interval.tv_usec = 0;

        if (setitimer(ITIMER_REAL, &tick, NULL) < 0) {
        printf("Failed to set timeout\n");
        }

        Digraph * graph = new Digraph();
        Digraph * graph1=new Digraph();
        int * demandTo = new int[50];
        int S = 0;
        int T = 0;
        // int * result;
        // 解析数据装配到Digraph中
        int demandLen = parse2demand(demand, demandTo, &S, &T);
        for (int i = 0; i <edge_num; i++)
        {
                Edge * e = new Edge;
                e=parse2edge(topo[i]);
                graph->addEdge(e);
                graph1->addEdge1(e);
        }

        if ((graph->V)<35) {
          DirectedDFS * ddfs=new DirectedDFS(graph, S, T, demandTo, demandLen,&isTimeOut);
          for (vector<int>::iterator iter=ddfs->result.begin();iter!=ddfs->result.end();iter++)
          {
            // printf("%d  ",*iter );
            record_result(*iter);
          }
        }
        else{
          DijkstraSP * sp = new DijkstraSP(graph,graph1,S,T,demandLen,demandTo,&isTimeOut);
          vector<int>::iterator iter;
          for (iter=sp->result.begin();iter!=sp->result.end();iter++)
          {
            printf("%d ",*iter );
            record_result(*iter);
          }
        }


        // for (; !ddfs->stack->isEmpty(); ) {
        //   printf("%d  \n",ddfs->stack->pop() );
        // }


        // printf("\n");
        // printf("%d\n",sp->stack.size );
        // while (!(sp->stack.isEmpty())) {
        //   printf("%d  ",sp->stack.pop() );
        // }
        // vector<int> ::iterator iter;
        // iter=sp->result.begin();
        // // printf("length=%d\n",(sp->result).size());
        // for (; iter != sp->result.end(); iter++) {
        //   printf("%d->",*iter );
        //    record_result(*iter);
        // }

        // MiniQueue * miniqueue = new MiniQueue(10);
        // miniqueue->insert(0,10);
        // miniqueue->insert(1,0);
        // miniqueue->insert(2,30);
        // miniqueue->insert(3,40);
        // miniqueue->insert(4,50);
        // for (; !miniqueue->isEmpty();) {
        //   printf("%d\n",miniqueue->delMin() );
        // }

        // unsigned short result[] = {2, 6, 3}; //示例中的一个解
        //


}
void setTimeOut(int){
  isTimeOut = true;
  printf("Time out\n");
}
