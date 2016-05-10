#ifndef _STACK_
#define _STACK_
#include <iostream>
#include <stdio.h>
template<class T> struct Point{
  T  v;
  Point<T> * next;
};

template<class T> class Stack{
public:
  Point<T> * first;

public:
  Stack();
  bool isEmpty();
  void push(T v);
  int pop();
};

struct PointInt{
  int  v;
  PointInt * next;
};

class StackInt{
public:
  PointInt * first;
  int size;

public:
  StackInt();
  bool isEmpty();
  void push(int v);
  int pop();
  int top();
};

#endif
