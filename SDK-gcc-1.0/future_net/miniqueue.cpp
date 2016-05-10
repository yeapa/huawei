#include "miniqueue.h"
MiniQueue::MiniQueue(int max)
{
        keys = new int[max+1];
        pq = new int[max+1];
        qp = new int[max+1];
        size = 0;
        for (int i = 0; i < max; i++)
        {
                qp[i] = -1;
        }
}

bool MiniQueue::greater(int i, int j)
{
        return keys[pq[i]] > keys[pq[j]];
}

void MiniQueue::changeKey(int v, int key)
{
        keys[v] = key;
        swim(qp[v]);
        sink(qp[v]);
}

void MiniQueue::insert(int v, int key)
{
        size++;
        pq[size] = v;
        keys[v] = key;
        qp[v] = size;
        swim(size);
}

void MiniQueue::exch(int i, int j)
{
        int temp=pq[i];
        pq[i] = pq[j];
        pq[j] = temp;
        qp[pq[i]] = i;
        qp[pq[j]] = j;
}

int MiniQueue::delMin()
{
        int min = pq[1];
        exch(1, size);
        size--;
        sink(1);
        qp[min] = -1;
        pq[size + 1] = -1;
        return min;
}

void MiniQueue::swim(int k)
{
        while (k>1 && greater(k/2, k))
        {
                exch(k / 2, k);
                k = k / 2;
        }
}

void MiniQueue::sink(int k)
{
        while (2*k<=size)
        {
                int j = 2 * k;
                if (j + 1 <= size)
                {
                        if (j < size && greater(j, j + 1))
                        {
                                j++;
                        }
                }

                if (!greater(k,j))
                {
                        break;
                }
                exch(k, j);
                k = j;
        }
}
