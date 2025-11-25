#include <stdio.h>
#include <stdlib.h>

#include "pq.h"

List_t* create_node(int p) {
    List_t* n = malloc(sizeof(List_t));
    n->priority = p;
    return n;
}

int main() {
    int raw_data[] = {50, 10, 90, 30, 70, 20, 80};
    int size = 7;
    List_t** array = malloc(size * sizeof(List_t*));
    
    for(int i=0; i<size; ++i) {
        array[i] = create_node(raw_data[i]);
        printf("%d ", raw_data[i]);
    }
    printf("\n");
    
    PriorityQueue* pq = PQ_create_with_array(array, size, Min);

    printf("%d\n", pq->container[0]->priority);

    PQ_switch_mode(pq, Max);

    List_t* item;
    while((item = PQ_pop(pq)) != NULL) {
        printf("%d ", item->priority);
        free(item);
    }

    free(pq);
    return 0;
}