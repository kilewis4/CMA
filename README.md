# **CMA(Custom Memory Allocator)**

A low-level implementation of dynamic memory allocation, recreating core functionality similar to malloc and free using a manually managed memory pool.

This project explores how memory is organized, allocated, and optimized at the systems level, with a focus on performance tradeoffs, fragmentation, and memory layout.

## **Key Features**
- Custom implementations of:
  - malloc(size_t size)
  - free(void* ptr)
- Manual memory management via:
  - sbrk() (Linux) or static buffer
- Linked-list-based block allocator
- First-fit allocation strategy(baseline)
- Block splitting to reduce internal fragmentation
- Coalescing of adjacent free blocks

## **Advanced Features**
- Bit-level metadata optimization(flags embedded in size field)
- Configurable memory alignment (e.g. 8-byte)
- Multiple allocation strategies
  - First-fit
  - Best-fit
- Debugging & instrumentation:
  - Memory layout visualization
  - Fragmentation metrics
  - Allocation tracking
- Optional thread safety using mutexes

## **Architecture Overview**
- Memory is managed as a linked list of blocks:

`[ Header | Data ][ Header | Data ][ Header | Data ]`

Each block contains:
- Size (with optional embedded flags)
- Allocation status
- Pointer to next block

## **Allocation Flow**
1. Traverse block list
2. Select a suitable free block (first-fit or best-fit)
3. Split block if oversized
4. Mark as allocated
5. Return pointer to usable memory

## **Free Flow**
1. Mark blocks as free
2. Coalesce adjacent free blocks
3. Reduce fragmentation over time

## **Debugging and Instrumentation**

- Memory layout dump (visual block inspection)
- Fragmentation tracking
- Allocation statistics (count, sizes, reuse)

## **Possible Features**
- Benchmarking against libc **malloc**
- Slab / pool allocators
- Lock-free allocator experiments
- Integration into a custom runtime
