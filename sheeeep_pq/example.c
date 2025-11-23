#include "pq.h"
#include <stdio.h>
#include <stdlib.h>
int IntCompare(const void *a,const void *b){
    return (*(int*)a - *(int*)b);
}
int main(){
    pq p,q,array;
    int arr[] = {5,3,8,1,4,7,2,6,4,3};
    initpq(&p,10,1);
    initpq(&q,10,0);
    initpq(&array,10,1);
    push(&p,&arr[0],IntCompare);
    push(&p,&arr[1],IntCompare);
    push(&p,&arr[2],IntCompare);
    push(&p,&arr[3],IntCompare);
    printf("Pop elements from priority queue(max):\n");
    while(p.size>0){
        int *val = (int*)pop(&p,IntCompare);
        printf("%d ",*val);
    }
    push(&q,&arr[0],IntCompare);
    push(&q,&arr[1],IntCompare);
    push(&q,&arr[2],IntCompare);
    push(&q,&arr[3],IntCompare);
    printf("\n");
    printf("Pop elements from priority queue(min):\n");
    while(q.size>0){
        int *val = (int*)pop(&q,IntCompare);
        printf("%d ",*val);
    }
    printf("\n");
    printf("After deleting index 1(max):\n");
    push(&p,&arr[0],IntCompare);
    push(&p,&arr[1],IntCompare);
    push(&p,&arr[2],IntCompare);
    push(&p,&arr[3],IntCompare); 
    deletedata(&p,1,IntCompare);
    while(p.size>0){
        int *val = (int*)pop(&p,IntCompare);
        printf("%d ",*val);
    }
    printf("\n");
    printf("build by array(max):\n");
    int array_size = sizeof(arr)/sizeof(int);
    void **data_array = (void**)malloc(sizeof(void*) * array_size);
    for(int i = 0; i < array_size; i++){
        data_array[i] = &arr[i];
    }
    build_by_array(&array,data_array,array_size,IntCompare);
    while(array.size>0){
        int *val = (int*)pop(&array,IntCompare);
        printf("%d ",*val);
    }
}
