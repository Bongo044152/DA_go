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
void buildbyarray(pq_t *pq, void **data);
void deletedata(pq_t *pq, int index);
void heapify(pq_t *pq, int index);
#endif

/*設計要求,
支援任意的資料型態,
使用 C 語言,
基本的 Operations,
.h 與 .c 檔案,
.h 只能包含「必須的操作」，輔助 function 不應該出現在其中,
example.c,

進階,
Priority Queue 支持切換 min 與 max,
支持從 array 建構 Priority Queue,
（禁止使用一個一個 insert 的方法，可行方式：使用 heapify慢慢調整）

注意事項,
禁止使用 ai 提供幫助,

截止,
越快越好*/