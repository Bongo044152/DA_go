#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pq.h"

// helper func!!
// create a List_t node
List_t* create_node(int p) {
    List_t* n = malloc(sizeof(List_t));
    n->priority = p;
    return n;
}

int main() {
    
    // 搞個簡單玩玩
    PriorityQueue* pq = PQ_create(Max);
    
    int data[] = {10, 5, 20, 3, 8, 40, 15};
    int size = 7;
    
    for(int i=0 ; i<size ; ++i) {
        PQ_push(pq, create_node(data[i]));
    }
    
    List_t* item;
    while((item = PQ_pop(pq)) != NULL) {
        printf("%d ", item->priority);
        
        free(item);
    }

    free(pq);
    
    return 0;
}