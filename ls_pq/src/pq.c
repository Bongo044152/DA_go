#include <stdio.h>
#include <stdlib.h>
#include "../include/pq.h"
static int getParent(int index)
{
    return (index - 1) / 2;
}
static int getLeft(int index)
{
    return (index * 2) + 1;
}
static int getRight(int index)
{
    return (index * 2) + 2;
}
static void swap(void **a, void **b)
{
    void *temp = *a;
    *a = *b;
    *b = temp;
}

void init(pq_t *pq, int capacity, pqtype_t type, cmpf cmp)
{
    pq->capacity = capacity;
    pq->items = (void **) malloc(capacity * sizeof(void *));  // 每個索引存void*
    pq->size = 0;
    pq->type = type;
    pq->cmp = cmp;
}

void *pop(pq_t *pq)
{
    if (!pq)
        return NULL;
    if (pq->size == 1) {
        pq->size--;
        return pq->items[0];
    }
    void *result = pq->items[0];
    swap(&pq->items[0], &pq->items[pq->size - 1]);
    pq->size--;
    if (pq->type == PQ_MAX_HEAP)
        heapify(pq, 0);
    else
        heapify(pq, 0);

    return result;
}

void buildbyarray(pq_t *pq, void **data)
{
    if (pq->size >= pq->capacity)
        return;
    for (int i = 0; i < pq->capacity; i++) {
        pq->items[i] = &data[i];
    }
    pq->size = pq->capacity;
    if (pq->type == PQ_MAX_HEAP) {
        for (int i = (pq->size - 1) / 2; i >= 0;
             i--) {  // 略過葉子節點 因為葉子節點不用heapify(沒有左右兒子)
            heapify(pq, i);
        }
    } else {
        for (int i = (pq->size - 1) / 2; i >= 0; i--) {
            heapify(pq, i);
        }
    }
}
void deletedata(pq_t *pq, int index)
{
    if (!pq)
        return;

    swap(&pq->items[index], &pq->items[pq->size - 1]);
    pq->size--;
    if (pq->type == PQ_MAX_HEAP)
        heapify(pq, index);
    else
        heapify(pq, index);
}
void heapify(pq_t *pq, int index)
{
    int left = getLeft(index);
    int right = getRight(index);
    if (pq->type == PQ_MAX_HEAP) {
        int max = index;


        if (left < pq->size && pq->cmp(pq->items[left], pq->items[max]) > 0) {
            max = left;
        }
        if (right < pq->size && pq->cmp(pq->items[right], pq->items[max]) > 0) {
            max = right;
        }
        if (index != max) {
            swap(&pq->items[max], &pq->items[index]);  // 更新根結點
            heapify(
                pq,
                max);  // 子樹需要修正(原本的根從大的變成小的，兒子們有機會比父親大)
        }
    } else {
        int min = index;

        if (left < pq->size && pq->cmp(pq->items[left], pq->items[min]) < 0) {
            min = left;
        }
        if (right < pq->size && pq->cmp(pq->items[right], pq->items[min]) < 0) {
            min = right;
        }
        if (index != min) {
            swap(&pq->items[min], &pq->items[index]);  // 更新根結點
            heapify(pq, min);
        }
    }
}
