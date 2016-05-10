#include "dijkstrasp.h"
#include "stdlib.h"
#include "stdio.h"
#include "stack.h"
#include "dfs.h"
#include <algorithm>
#define POSITIVE_INFINITY 65530


DijkstraSP::DijkstraSP(Digraph * g,Digraph * g1, int start,int desti,int demandLen,int * demandTo,bool * isTimeOut){
  // printf("start=%d    desti=%d  demandLen=%d  \n",start,desti,demandLen );
  this->demandLen=demandLen;
  this->demandTo=demandTo;
  this->graph=g;
  this->graph1=g1;
  this->start=start;
  this->desti=desti;
  this->isTimeOut=isTimeOut;
  distTo=new int[graph->V];
  minigraph=new miniDiagraph();
  marked = new bool[graph->V];
  //diji产生最短路径
  mq = new MiniQueue(graph->V);
  for (int i = 0; i < graph->V; i++){
          marked[i] = false;
          countV[i]=0;
          distTo[i]=0;
  }
  distTo[start]=0;
  parseBigEdge(start);
  for (int i = 0; i < demandLen; i++) {
    for (int j = 0; j < graph->V; j++){
            distTo[j] = POSITIVE_INFINITY;
            marked[j] = false;
    }
    distTo[(demandTo[i])]=0;
    parseBigEdge(demandTo[i]);
  }
  for (int i = 0; i < MAX_V; i++) {
    vector<Edge* >  list = this->graph1->eVector[i];
    sort(list.begin(),list.end(),comp);
  }
  //
  generateGraph();
  DFS* dfs=new DFS( graph,minigraph, start, desti, demandTo, demandLen,isTimeOut);
  result=dfs->result;
}
void DijkstraSP::parseBigEdge(int begin) {
  mq->insert(begin,0);
  while (!(mq->isEmpty())){
    int v= mq->delMin();
    if (v!=begin&&(demandContain(v)||v==desti)) {
      generateBigEdge(v,begin);
    }
    else  relax(graph,v);
  }
}

void DijkstraSP::generateBigEdge(int v,int begin) {
  BigEdge * bigedge=new BigEdge();
  Edge * e=edgeTo[v];
  bigedge->eVector.push_back(e);
  bigedge->from=begin;
  bigedge->to=v;
  stack.push(v);
  for (int i=e->from; i !=begin; i=edgeTo[i]->from) {
    stack.push(i);
    bigedge->eVector.push_back(edgeTo[i]);
  }
  stack.push(begin);
  for ( ; !stack.isEmpty(); ) {
    int a=stack.pop();
    bigedge->vVector.push_back(a);
    // printf("%d ",a);
  }
  // printf("\n" );
  minigraph->addBigEdge(bigedge);
}
bool DijkstraSP::comp(Edge* a,Edge* b){
  return a->weight<b->weight;
}

bool DijkstraSP::demandContain(int v){
    for (int i = 0; i < demandLen; i++) {
        if (v==demandTo[i]) {
          return true;
        }
    }
    return false;
}

void DijkstraSP::generateGraph()
{
  // printf("demandLen=%d\n",demandLen );
  findRoute(start);
  for (int i = 0; i < demandLen; i++) {
    // printf("demandTo[%d]=%d\n",i,demandTo[i] );
    findRoute(demandTo[i]);
  }
}

void DijkstraSP::findRoute(int a){
  dfscount=0;
  // for (int i = 0; i < graph->V; i++){
  //   marked[i] = false;
  //   edgeToX[i]=NULL;
  // }
  // wfs(a);
  //
  for (int  i = 0; i < 50; i++) {
    for (int j = 0; j < MAX_V; j++){
      marked[j] = false;
      edgeToX[j]=NULL;
    }
    wfs1(a,1);
  }

  // for (int i = 0; i < graph->V; i++){
  //   marked[i] = false;
  //   edgeToX[i]=NULL;
  // }
  // rawdfs(a,a);
}

void DijkstraSP::rawdfs(int v,int from){
  dfscount++;
  if (dfscount>=50) {
     return;
  }
  marked[v] = true;
  // printf("marked[%d]  ",v );
  if ((demandContain(v)||v==desti)&&v!=from) {
    // printf("here v=%d to=%d ",v,to);
      // printf("ready in parseRoute to=%d from=%d\n",to,from);
      parseRoute(v,from);
    return;
  }

  List * list = graph->getAdjEdge(v);
  for(Node * iter = list->iterator(); iter != NULL; iter = iter->next){
    Edge * edge = iter->edge;
    int w=edge->to;
    if(marked[w] ==false){
      edgeToX[w] = edge;
      rawdfs(w,from);
      edgeToX[w] = NULL;
      marked[w]=false;
      dfscount--;
    }
  }
}

void DijkstraSP::wfs(int s){
  // printf("s=%d  \n", s);
  wfsqueue=new queue<int>();
  marked[s]=true;
  wfsqueue->push(s);
  while (!(wfsqueue->empty())) {
      int v=wfsqueue->front();
      // printf("v=%d  ", v );
      wfsqueue->pop();
      List * list = graph->getAdjEdge(v);
      for(Node * iter = list->iterator(); iter != NULL; iter = iter->next){
        Edge * edge = iter->edge;
        int w=edge->to;
        if (marked[w]==false) {
          edgeToX[w] = edge;
          if ((demandContain(w)||w==desti)&&w!=s) {
              parseRoute(w,s);
              // marked[s]=false;
          }
          marked[w]=true;
          wfsqueue->push(w);
          // printf("w=%d  ", w );
        }
        else if ((demandContain(w)||w==desti)&&w!=s) {
          Edge *temp=edgeToX[w];
          edgeToX[w]=edge;
          parseRoute(w,s);
          edgeToX[w]=temp;
        }
      }
  }
}

void DijkstraSP::wfs1(int s,int ins){
  // printf("s=%d  \n", s);
  wfsqueue=new queue<int>();
  marked[s]=true;
  wfsqueue->push(s);
  while (!(wfsqueue->empty())) {
      int v=wfsqueue->front();
      // printf("v=%d  ", v );
      wfsqueue->pop();
      vector<Edge*>::iterator iter;
      reverse(graph1->eVector[v].begin()+ins,graph1->eVector[v].end());
      for(iter = (graph1->eVector[v]).begin(); iter != (graph1->eVector[v]).end(); iter++){
        Edge * edge = *iter;
        int w=edge->to;
        if (marked[w]==false) {
          edgeToX[w] = edge;
          if ((demandContain(w)||w==desti)&&w!=s) {
            // printf("here s=%d w=%d ",s,w);
              // printf("ready in parseRoute to=%d from=%d\n",to,from);
              parseRoute(w,s);
              // marked[s]=false;
          }
          marked[w]=true;
          wfsqueue->push(w);
          // printf("w=%d  ", w );
        }
        else if ((demandContain(w)||w==desti)&&w!=s) {
          Edge *temp=edgeToX[w];
          edgeToX[w]=edge;
          parseRoute(w,s);
          edgeToX[w]=temp;
        }
      }
  }
}


void DijkstraSP::parseRoute(int end,int begin){
  // printf("already in parseRoute");
  int count=0;
  BigEdge * bigedge=new BigEdge();
  Edge * e=edgeToX[end];
  bigedge->weight+=e->weight;
  bigedge->eVector.push_back(e);
  bigedge->from=begin;
  bigedge->to=end;
  for (int i=e->from; i !=begin; i=edgeToX[i]->from) {
    count++;
    // if (count>20) {
    //   return;
    // }
    if (i==end||((demandContain(i)||i==desti)&&i!=begin)) {
      return;
    }

    countV[i]++;
    for (int j = 0; j < MAX_V; j++) {
      if (countV[j]>MAX_V*5) {
        // marked[j]=true;
        graph->deleteVertax(j);
      }
    }

    bigedge->vVector.push_back(i);
    bigedge->eVector.push_back(edgeToX[i]);
    bigedge->weight+=edgeToX[i]->weight;
  }
  reverse(bigedge->eVector.begin(),bigedge->eVector.end());
  reverse(bigedge->vVector.begin(),bigedge->vVector.end());
  minigraph->addBigEdge(bigedge);
}

void DijkstraSP::search() {
  mq->insert(start,0);
  while (!(mq->isEmpty())){
    int v= mq->delMin();
    relax(graph,v);
    }
}

void DijkstraSP::relax(Digraph * g, int from){
        // printf("relax from=%d\n",from );
        List * vAdj = g->getAdjEdge(from);
        Edge * e = NULL;
        for (Node * iter = vAdj->iterator(); iter != NULL; iter=iter->next){
                e = iter->edge;
                int to = e->to;
                if (distTo[to]>distTo[from]+e->weight&&marked[to]==false){
                        // printf("to=%d in\n",to);
                        distTo[to] = distTo[from] + e->weight;
                        edgeTo[to] = e;
                        if (mq->contains(to)){
                                mq->changeKey(to, distTo[to]);
                        }
                        else{
                                mq->insert(to, distTo[to]);
                        }
                }
        }
}
