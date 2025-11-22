#include "pq.h"
#include <stdio.h>
#include <stdlib.h>
int IntCompare(void *a, void *b){
    return (*(int*)a - *(int*)b);
}
int main(){
    pq p,array;
    int arr[] = {5,3,8,1,4,7,2,6,4,3,9,0};
    initpq(&p,10,1);
    initpq(&array,10,1);
    push(&p,&arr[0],IntCompare);
    push(&p,&arr[1],IntCompare);
    push(&p,&arr[2],IntCompare);
    push(&p,&arr[3],IntCompare);
    while(p.size>0){
        int *val = (int*)pop(&p,IntCompare);
        printf("%d ",*val);
    }
    printf("\n");
    push(&p,&arr[0],IntCompare);
    push(&p,&arr[1],IntCompare);
    push(&p,&arr[2],IntCompare);
    push(&p,&arr[3],IntCompare);
    deletedata(&p,1,IntCompare);
    while(p.size>0){
        int *val = (int*)pop(&p,IntCompare);
        printf("%d ",*val);
    }
    build_by_array(&array,(int**)arr,IntCompare);
}