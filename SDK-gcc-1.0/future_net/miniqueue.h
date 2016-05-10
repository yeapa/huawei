#ifndef _MINIQUEUE_
#define  _MINIQUEUE_

class MiniQueue
{
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
  void changeKey(int v,int k);
  bool greater(int i, int j);   //i 是父节点 i < j = true

private:
  void exch(int i, int j);
  void swim(int k);
  void sink(int k);
};
#endif
