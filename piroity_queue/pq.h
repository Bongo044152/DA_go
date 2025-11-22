#ifndef _PQ_H_
#define _PQ_H_
typedef int (*Compare)(const void*, const void*);
typedef struct pq{
    void **data;
    int capacity;
    int size;
    int mode;
}pq;
void initpq(pq *p, int capacity,int mode);
void push(pq *p, void *data,Compare cmp);
void *pop(pq *p,Compare cmp);
void deletedata(pq *p, int index,Compare cmp);
void build_by_array(pq *p, void **data,Compare cmp);
#endif