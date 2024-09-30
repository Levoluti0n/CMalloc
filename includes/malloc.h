
#ifndef MALLOC_H
#define MALLOC_H

void* myMalloc(size_t size);
typedef struct metaInfo {
    size_t size:63,
           free:1;
    struct metaInfo* next;
    struct metaInfo* prev; 
    void *ptr;
    char data[1];
} metaInfo;

#define ALIGNMENT 8
#define MetaSize sizeof(metaInfo)
#define ALIGN8(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

#endif

