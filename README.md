# 📦 Custom Malloc Implementation in C

Welcome to the **Custom Malloc Implementation** project! This implementation provides a simplified version of `malloc`, handling dynamic memory allocation at runtime. It's a great way to understand how memory management works at a lower level and can be used to explore concepts like block splitting, heap extension, and memory fragmentation.

## ✨ Features
- **Dynamic Memory Allocation**: Allocate memory blocks based on your needs.
- **Memory Splitting**: Split blocks if the requested size is smaller than an existing free block.
- **Heap Extension**: Dynamically extend the heap when no suitable block is found.

## ⚙️ How It Works

### 🧠 Memory Block Structure

Each block of memory is described using the `metaInfo` struct, which stores:
- **Size**: The size of the block.
- **Free**: A flag indicating whether the block is free (1) or allocated (0).
- **Next**: A pointer to the next block.
- **Prev**: A pointer to the previous block (doubly linked list).
- **Ptr**: Points to the start of the usable memory (after metadata).
- **Data**: The actual memory allocated for the user.

```c
typedef struct metaInfo {
    size_t size;
    int free;
    struct metaInfo* next;
    struct metaInfo* prev;
    void* ptr;
    char data[1]; // Flexible array member
} metaInfo;

#define MetaSize sizeof(metaInfo)
#define ALIGN8(x) (((((x)-1) >> 3) << 3) + 8) // Align size to 8 bytes
