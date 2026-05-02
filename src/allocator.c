// Responsible for the logic. Initialize memory pool, find suitable block, split block, coalesce block
//
// Conceptually...
// init()
// allocate(size)
// deallocate(ptr)
// find_block(size)
// split_block(block, size)
// coalesce()

#include "../include/allocator.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// =====================
// Global state (simple for Phase 1)
// =====================
static void* memory_pool = NULL;
static size_t pool_size = 0;
static block_t* free_list_head = NULL;

void init_allocator(size_t size)
{
    // Allocate big memory pool
    // For phase 1, use malloc or static buffer approach

    memory_pool = malloc(size);

    if(memory_pool == NULL)
    {
        printf( "No available memory.");
        return;
    }

    pool_size = size;

    //Create initial single large block of memory
    free_list_head = (block_t*)memory_pool;

    free_list_head->size = size - sizeof(block_t); //Size is set to size, skipping the header
    free_list_head->next = NULL;                   //Not pointing to anything yet
    free_list_head->free = 1;                      //1 will mark it as free, 0 as not free
}

block_t* find_block(size_t size)
{
    //For now, first fit. We are checking if a block is free, and if size is large enough

    for(block_t* curr = free_list_head; curr != NULL; curr = curr->next)
    {
        if(curr->free == 1 && curr->size >= size)
        {
            return curr;
        }
    }
    return NULL;
}

void* allocate(size_t size)
{
    block_t* available = find_block(size);

    if(available == NULL)
    {
        printf("No available blocks");
        return available;
    }
    available->free = 0;

    return (block_t*)available + 1;
}

void deallocate(void *ptr)
{
    block_t* passed_block = (block_t*)ptr - 1;
    passed_block->free = 1;
}
