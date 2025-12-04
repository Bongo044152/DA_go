#ifndef ___pq___
#define ___pq___

typedef enum {
    PQ_MIN_HEAP = 0,
    PQ_MAX_HEAP = 1
} pqtype_t;

typedef int (*cmpf)(const void *, const void *);


typedef struct {
    void **items;
    int capacity;
    int size;
    pqtype_t type;
    cmpf cmp;
} pq_t;


void init(pq_t *pq, int capacity, pqtype_t type, cmpf cmp);
void *pop(pq_t *pq);
void buildbyarray(pq_t *pq, void **data, int arrsize);
void deletedata(pq_t *pq, int index);
void heapify(pq_t *pq, int index);
void insert(pq_t *pq, void *data);
#endif
