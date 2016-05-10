#include "parse.h"
#include <string.h>
#include <stdlib.h>

Edge * parse2edge(char * line){
  char * outer;
  char * buf = line;
  char * result[20];
  int index = 0;
  while((result[index]=strtok_r(buf,",",&outer)) != NULL){
    buf = NULL;
    index++;
  }
  Edge * edge = new Edge;
  edge->index = atoi(result[0]);
  edge->from = atoi(result[1]);
  edge->to = atoi(result[2]);
  edge->weight = atoi(result[3]);
  return edge;
}

int parse2demand(char * demand,int * demandTo, int * s, int * t)
{
        char * outer = NULL;
        char * buf = demand;
        char *result[100];
        int index = 0;
        while((result[index]=strtok_r(buf,",",&outer)) != NULL)
        {
                buf = NULL;
                index++;
        }
        *s = atoi(result[0]);
        *t = atoi(result[1]);
        index = 0;
        char *demandResult[100];
        buf = result[2];
        outer = NULL;
        while((demandResult[index]=strtok_r(buf,"|",&outer)) != NULL)
        {
                buf = NULL;
                demandTo[index] = atoi(demandResult[index]);
                index++;
        }
        return index;
}
