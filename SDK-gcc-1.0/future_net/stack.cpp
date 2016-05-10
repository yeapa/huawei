#include "stack.h"
template<class T> Stack<T>::Stack()
{
        first = NULL;
}

template<class T> void Stack<T>::push(T  v)
{
        Point<T> * p = new Point<T>();
        p->v = v;
        p->next = first;
        first = p;
}

template<class T> int Stack<T>::pop(){
        if(first == NULL)
        {
                return -1;
        }
        else
        {
                Point<T> * p = first;
                first = first->next;
                return p->v;
        }
}

template<class T> bool Stack<T>::isEmpty()
{
        return (first==NULL);
}

StackInt::StackInt()
{
        first = NULL;
        size=0;
}

void StackInt::push(int  v)
{
        PointInt  * p = new PointInt();
        p->v = v;
        p->next = first;
        first = p;
        size++;
}

int StackInt::pop(){
        if(first == NULL)
        {
                return -1;
        }
        else
        {
                PointInt * p = first;
                first = first->next;
                return p->v;
                size--;
        }
}

int StackInt::top()
{
  return first->v;
}

bool StackInt::isEmpty()
{
        return (first==NULL);
}
