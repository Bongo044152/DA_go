#include <stdio.h>
#include <stdlib.h>
#include "./include/pq.h"

int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

int main(void)
{
    pq_t p;
    pq_t q;
    init(&p, 10, PQ_MAX_HEAP, compare);
    printf("======================MAX-HEAP-TEST======================\n");
    int arr[10] = {3, 17, 8,  25, 14,
                   9, 1,  32, 6,  20};  //[32, 25, 9, 17, 20, 8, 1, 3, 6, 14]
    buildbyarray(&p, (void **) arr);
    printf("MAX-HEAP: ");
    for (int i = 0; i < p.size; i++) {
        printf("%d ", *(int *) p.items[i]);
    }
    printf("\n");
    void *item = pop(&p);
    printf("AFTER POPPING: ");
    for (int i = 0; i < p.size; i++) {
        printf("%d ", *(int *) p.items[i]);
    }
    printf("\n");
    printf("THE MAX ITEM: ");
    printf("%d", *(int *) item);
    printf("\n");
    deletedata(&p, 5);
    printf("AFTER DELETING INDEX 5: ");
    for (int i = 0; i < p.size; i++) {
        printf("%d ", *(int *) p.items[i]);
    }
    printf("\n======================TEST-COMPLETE======================\n");
    printf("======================MIN-HEAP-TEST======================\n");
    init(&q, 10, PQ_MIN_HEAP, compare);
    buildbyarray(&q, (void **) arr);
    printf("MIN-HEAP: ");
    for (int i = 0; i < q.size; i++) {
        printf("%d ", *(int *) q.items[i]);
    }
    printf("\n");
    void *item2 = pop(&q);
    printf("AFTER POPPING: ");
    for (int i = 0; i < q.size; i++) {
        printf("%d ", *(int *) q.items[i]);
    }
    printf("\n");
    printf("THE MAX ITEM: ");
    printf("%d", *(int *) item2);
    printf("\n");
    deletedata(&q, 5);
    printf("AFTER DELETING INDEX 5: ");
    for (int i = 0; i < q.size; i++) {
        printf("%d ", *(int *) q.items[i]);
    }
    printf("\n======================TEST-COMPLETE======================\n");
}