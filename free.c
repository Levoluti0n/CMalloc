#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
// #include "malloc.c"
#include "includes/malloc.h"
extern void* base;

metaInfo* merge_blocks(metaInfo* block)
{
    if (block->next && block->next->free)
    {
        block->size += MetaSize + block->next->size;
        block->next = block->next->next;
    }
    if (block->next)
    {
        block->next->prev = block;
    }
    return block;
}

metaInfo* get_block_addr(void *p)
{
    char *tmp = p;
    tmp = tmp - MetaSize; 
    p = tmp;
    return (p);
}

int is_addr_valid(void *p)
{
    if (base)
    {
        if (p > base && p < sbrk(0))
        {
            return (p == get_block_addr(p)->ptr);
        }
    }
    return 0;
}

void myFree(void *ptr)
{
    if (is_addr_valid(ptr))
    {
        metaInfo* block = get_block_addr(ptr);
        block->free = 1;
        if (block->prev && block->prev->free)
        {
            block = merge_blocks(block->prev);
        }

        if (block->next)
        {
            block = merge_blocks(block);
        }
        else
        {
            if (block->prev)
            {
                block->prev->next = NULL;
            }
            else
            {
                base = NULL;
            }
            brk(block);
        }
    }
}