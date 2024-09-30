#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "./includes/malloc.h"

void* base = NULL;


metaInfo* findSuitable(metaInfo** last, size_t size) {
    metaInfo* b = base; 
    while(b && !(b->free && b->size >= size)) {
        *last = b;
        b = b->next;
    }
    return *last;
}

metaInfo* extendHeap(metaInfo* last, size_t size) {
    metaInfo* oldB, *newB;
    oldB = sbrk(0); //current
    newB = sbrk(MetaSize + size); //opened
    if(newB == (void*)-1) return NULL;
    oldB->free = 0;
    oldB->size = size;
    oldB->next = NULL;
    oldB->prev = NULL;
    oldB->ptr = oldB->data;
    if(last){
        last->next = oldB;
    } 
    return oldB;
}

void splitBlocks(metaInfo* block, size_t size) {
    metaInfo* newB;
    newB = (metaInfo*)block->data + size;
    newB->size = block->size - size - MetaSize; 
    newB->next = block->next;
    newB->free = 1;
    newB->prev = block;
    newB->size = size;
    newB->ptr = newB->data;
    if(newB->next){
        newB->next->prev = newB;
    }
}

void* myMalloc(size_t size) {
    if(!size) return NULL;
    metaInfo* block, *last;


    int s = ALIGN8(size);
    if(base){
        last = base;
        block = findSuitable(&last, s);

        if(block) {
            if(block->size - s >= (MetaSize+4)) {
                splitBlocks(block, s);
            }
            block->free = 0;
        }else {
            block = extendHeap(last, s);
            if(!block) {
                return NULL;
            }
        }


    }else {
        block = extendHeap(NULL, s);
        if(!block) {
            return NULL;
        }
        base = block;
     }

    return block->data;
}

