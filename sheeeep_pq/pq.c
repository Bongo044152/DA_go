#include "pq.h"
#include <stdio.h>
#include <stdlib.h>
static void swap(void **a, void **b){
    void *temp = *a;
    *a = *b;
    *b = temp;
}
static int parent(int index){
    return (index-1)/2;
}
static int leftchild(int index){
    return index*2+1;
}
static int rightchild(int index){
    return index*2+2;
}
static void heap(pq *p,int index,Compare cmp){
    if(p-> mode == 1){
        while(index <= p->size-1){
            int left = leftchild(index);
            int right = rightchild(index);
            int largest = index;
            if(left <= p->size-1 && cmp(p->data[left],p->data[largest])>0){
                largest = left;
            }
            if(right <= p->size-1 && cmp(p->data[right],p->data[largest])>0){
                largest = right;
            }
            if(largest != index){
                swap(&p->data[index],&p->data[largest]);
                index = largest;
            }
            else break;
        }
    }
    else{
        while(index <= p->size-1){
            int left = leftchild(index);
            int right = rightchild(index);
            int smallest = index;
            if(left <= p->size-1 && cmp(p->data[left],p->data[smallest])<0){
                smallest = left;
            }
            if(right <= p->size-1 && cmp(p->data[right],p->data[smallest])<0){
                smallest = right;
            }
            if(smallest != index){
                swap(&p->data[index],&p->data[smallest]);
                index = smallest;
            }
            else break;
        }
    }
}
void initpq(pq *p, int capacity,int mode){
    p->data = (void**)malloc(sizeof(void*)*capacity);
    p->capacity = capacity;
    p->size = 0;
    p->mode = mode;
}
void push(pq *p, void *data,Compare cmp){
    if(!p || p->capacity-1 == p->size) return;
    if(p->size == 0){
        p->data[0] = data;
        p->size++;
        return;
    }
    p->data[p->size] = data;
    int index = p->size;
    p->size++;
    if(p->mode == 1){
        while(index>0 && cmp(p->data[index],p->data[parent(index)])>0){
            swap(&p->data[index],&p->data[parent(index)]);
            index = parent(index);
        }
    }
    else{
        while(index>0 && cmp(p->data[index],p->data[parent(index)])<0){
            swap(&p->data[index],&p->data[parent(index)]);
            index = parent(index);
        }
    }
};
void *pop(pq *p,Compare cmp){
    if(!p || p->size == 0) return NULL;
    if(p->size == 1){
        p->size--;
        return p->data[0];
    }
    void *res = p->data[0];
    p->data[0] = p->data[p->size-1];
    p->size--;
    heap(p,0,cmp);  
    return res;
};
void deletedata(pq *p, int index,Compare cmp){
    if(!p || index >= p->size) return;
    if(p->size == 1){
        p->size--;
        return;
    }
    swap(&p->data[index],&p->data[p->size-1]);
    p->size--;
    heap(p,index,cmp);
}
void build_by_array(pq *p, void **data,int arrsize,Compare cmp){
    if(!p || arrsize>p->capacity) return;
    for(int i=0;i<arrsize;i++){
        p->data[i] = data[i];
    }
     p->size = arrsize;
    for(int i = (arrsize-1)/2; i >= 0; i--){
        heap(p, i, cmp);
    }
};