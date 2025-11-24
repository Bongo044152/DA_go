#include <stdio.h>
#include <stdlib.h>

#include "pq.h"

// helper func!!
/* rellocate memory： 
** 傳入參數：傳入欲 rellocate 的 pq
** 回傳值  ：無
** 函式功能：將傳入的 pq 中的 container 進行擴容，並將原 container 的內容移植。
**          擴大後的容量為原 capacity 的兩倍(若 capacity 為 0 擴容後則為 1)，
**          capacity 也會一併更新。
*/ 
void realloc_mem(PriorityQueue* pq) {
    int new_capacity = (pq->capacity == 0)? 1 : pq->capacity * 2;
    List_t** new_container = malloc(new_capacity * sizeof(List_t*));

    for(int i=0 ; i<pq->capacity ; ++i) {
        new_container[i] = pq->container[i];
        pq->container[i] = NULL;
    }

    free(pq->container);

    pq->capacity = new_capacity;
    pq->container = new_container;
}


// helper func!!
void PQ_bubble_down(PriorityQueue* pq, int index) {
    if(pq->mode == Max) {
        while(1) {
            int left_index = index * 2 + 1;
            int right_index = index * 2 + 2;
            int tar_index = index;

            if(!(left_index < pq->size)) break;
            if(right_index < pq->size && pq->container[right_index]->priority > pq->container[left_index]->priority) {
                tar_index = right_index;
            } 
            else {
                if(left_index < pq->size) {
                    tar_index = left_index;
                }
            }

            if(pq->container[tar_index]->priority > pq->container[index]->priority) {
                List_t* temp = pq->container[index];
                pq->container[index] = pq->container[tar_index];
                pq->container[tar_index] = temp;
                
                index = tar_index;
            } 
            else {
                break;
            }
        }
    }
    else {
        while(1) {
            int left_index = index * 2 + 1;
            int right_index = index * 2 + 2;
            int tar_index = index;

            if(!(left_index < pq->size)) break;
            if(right_index < pq->size && pq->container[right_index]->priority < pq->container[left_index]->priority) {
                tar_index = right_index;
            }
            else {
                if(left_index < pq->size) {
                    tar_index = left_index;
                }
            }

            if(pq->container[tar_index]->priority < pq->container[index]->priority) {
                List_t* temp = pq->container[index];
                pq->container[index] = pq->container[tar_index];
                pq->container[tar_index] = temp;
                
                index = tar_index;
            }
            else {
                break;
            }
        }
    }
}

void PQ_switch_mode(PriorityQueue* pq, PQ_mode mode) {
    if(pq->mode == mode) {
        return;
    }
    
    pq->mode = mode;
    for(int i = (pq->size - 1) / 2 ; i>= 0 ; --i) {
        PQ_bubble_down(pq, i);
    }
}

PriorityQueue* PQ_create(PQ_mode mode) {
    PriorityQueue* pq = malloc(sizeof(PriorityQueue));

    pq->mode = mode;
    pq->capacity = 0;
    pq->size = 0;
    pq->container = NULL;

    return pq;
}

PriorityQueue* PQ_create_with_array(List_t** array, int size, PQ_mode mode) {
    PriorityQueue* pq = PQ_create(mode);
    
    pq->capacity = size;
    pq->size = size;
    pq->container = array;

    PQ_switch_mode(pq, mode);

    return pq;
}

void PQ_push(PriorityQueue* pq, List_t* node) {
    if(pq->size == pq->capacity) {realloc_mem(pq); }

    pq->container[pq->size] = node;
    if(pq->mode == Max) {
        int index = pq->size;
        while(index != 0) {
            if(pq->container[(index - 1) / 2]->priority < pq->container[index]->priority) {
                List_t* temp = pq->container[(index - 1) / 2];
                pq->container[(index - 1) / 2] = pq->container[index];
                pq->container[index] = temp;
            }
            else {
                break;
            }

            index = (index - 1) / 2;
        }
    }   
    else {
        int index = pq->size;
        while(index != 0) {
            if(pq->container[(index - 1) / 2]->priority > pq->container[index]->priority) {
                List_t* temp = pq->container[(index - 1) / 2];
                pq->container[(index - 1) / 2] = pq->container[index];
                pq->container[index] = temp;
            }
            else {
                break;
            }

            index = (index - 1) / 2;
        }
    }

    ++pq->size;
}

List_t* PQ_pop(PriorityQueue* pq) {
    if(pq->size == 0) {return NULL;}

    List_t* res = pq->container[0];
    if(pq->size == 1) {
        pq->container[0] = NULL;
        --pq->size;
        return res;
    }

    pq->container[0] = pq->container[--pq->size];

    int index = 0;
    PQ_bubble_down(pq, index);

    return res;
}