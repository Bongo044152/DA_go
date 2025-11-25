#ifndef _PQ_
#define _PQ_

typedef enum PQ_mode {
    Max,
    Min
}PQ_mode;

// intrusive containers
typedef struct List_t {
    int priority;
} List_t;

// Priority queue class
typedef struct PriorityQueue{
    PQ_mode mode;
    int capacity;
    int size;
    List_t** container;
} PriorityQueue;

PriorityQueue* PQ_create(PQ_mode mode);
PriorityQueue* PQ_create_with_array(List_t** array, int size, PQ_mode mode);
void PQ_push(PriorityQueue* pq, List_t* node);
List_t* PQ_pop (PriorityQueue* pq);
void PQ_switch_mode(PriorityQueue*pq, PQ_mode mode);

#endif