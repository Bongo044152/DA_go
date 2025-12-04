#include <stdio.h>
#include <stdlib.h>
#include "pq.h"  //編譯時使用gcc -I

int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

int main(void)
{
    pq_t p;
    pq_t q;
    printf("======================MAX-HEAP-TEST======================\n");
    printf("INITIAL STATUS: ");
    if (init(&p, 10, PQ_MAX_HEAP, compare) == PQ_FAIL) {
        printf("FAILED!!\n");
        exit(1);
    } else {
        printf("SUCCESS!!\n");
    }
    int arr[] = {3, 17, 8,  25, 14,
                 9, 1,  32, 6,  20};  //[32, 25, 9, 17, 20, 8, 1, 3, 6, 14]
    int size = sizeof(arr) / sizeof(arr[0]);
    void **data = (void **) malloc(sizeof(void *) * size);
    for (int i = 0; i < size; i++) {
        data[i] = &arr[i];  // void*可存任意類型指標 只需取出時轉換正確
    }
    buildbyarray(&p, data, size);
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
    printf("\n======================TEST-COMPLETE======================\n\n");
    printf("======================MIN-HEAP-TEST======================\n");
    printf("INITIAL STATUS: ");
    if (init(&q, 10, PQ_MIN_HEAP, compare) == PQ_FAIL) {
        printf("FAILED!!\n");
        exit(1);
    } else {
        printf("SUCCESS!!\n");
    }
    buildbyarray(&q, data, size);
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
    printf("THE MIN ITEM: ");
    printf("%d", *(int *) item2);
    printf("\n");
    deletedata(&q, 5);
    printf("AFTER DELETING INDEX 5: ");
    for (int i = 0; i < q.size; i++) {
        printf("%d ", *(int *) q.items[i]);
    }
    printf("\n======================TEST-COMPLETE======================\n");
}