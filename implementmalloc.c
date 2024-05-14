typedef unsigned long size_t;

#define NULL ((void *) 0)

// free_block takes up 8 bytes of memory
// ulong = 4 bytes
// void* = 4 bytes
typedef struct chunk {
    unsigned long addr;
    size_t size;
    chunk *next_chunk;
} chunk;

#define MAX_HEAP_SIZE 1024 // let's say we have 1024 bytes of heap space
#define HEAP_START 0x10000000 // our heap starts at 0x10000000

chunk* free_list = {HEAP_START, MAX_HEAP_SIZE, NULL};

void* self_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }
    // add 8 bytes to the size to store the size of the block, and of the next block
    // TODO: hacky implementation - check alignment of allocation

    chunk *current = free_list;
    while (current != NULL) {
        if (current->size - sizeof(chunk) >= size) {
            // allocate size + sizeof(chunk) bytes
            // create new chunk with reduced size and new address shifted by size+sizeof(chunk)
            // {addr, size, next_chunk} = {result, size, NULL} // what we set next_chunk to doesn't matter (overwritten when freeing)
            unsigned long result = current->addr;
            chunk *new_chunk = {result, size, NULL};
            
            * ((chunk *) result) = *new_chunk; // copy the chunk to the new memory address
            result += sizeof(chunk); // move the result pointer to the start of the allocated memory

            // edit free list block
            unsigned long new_addr = current->addr + size + sizeof(chunk);
            current->size -= size + sizeof(chunk);
            current->addr = new_addr;

            return (void *) result;
        }
        else {
            // check next block for a fit instead
            current = current->next_chunk;            
        }
    }

    return -1; // no memory available
}

void self_free(void *memory) {
    // add the block to the free list, as long as we're not freeing up a null address
    if (memory != NULL) {
        chunk *memchunk = (chunk *) (((chunk*) memory) - 1);
        memchunk->next_chunk = free_list;
        free_list = memchunk;
    }
    
    // merge adjacent free blocks
    chunk *current = free_list;
    while (current != NULL) {
        if (current->next_chunk != NULL) {
            if (current->addr + current->size == current->next_chunk->addr) {
                // merge the two blocks
                current->size += current->next_chunk->size;
                current->next_chunk = current->next_chunk->next_chunk;
            }
            else {
                current = current->next_chunk;
            }
        }
        else {
            break;
        }
    }
}