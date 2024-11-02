#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define POOL_SIZE 1024  // Define the memory pool size

// Define the memory block structure for memory pool management
typedef struct Block {
    size_t size;          // Size of the block
    bool isFree;          // Status: free or allocated
    struct Block* next;   // Next block in the list
} Block;

char memoryPool[POOL_SIZE];  // The memory pool
Block* freeList = NULL;      // Head of the free list

// Initialize memory pool as a single large free block
void initializeMemoryPool() {
    freeList = (Block*) memoryPool;
    freeList->size = POOL_SIZE - sizeof(Block);  // Allocate size minus header
    freeList->isFree = true;
    freeList->next = NULL;
}

// Best-fit allocation: find the smallest block that fits requested size
void* bestFitAlloc(size_t size) {
    Block* bestFit = NULL;
    Block* bestFitPrev = NULL;
    Block* prev = NULL;
    Block* curr = freeList;

    while (curr != NULL) {
        if (curr->isFree && curr->size >= size) {
            if (!bestFit || curr->size < bestFit->size) {
                bestFit = curr;
                bestFitPrev = prev;
            }
        }
        prev = curr;
        curr = curr->next;
    }

    if (!bestFit) {
        return NULL;  // No suitable block found
    }

    if (bestFit->size > size + sizeof(Block)) {  // Split block if too large
        Block* newBlock = (Block*)((char*)bestFit + sizeof(Block) + size);
        newBlock->size = bestFit->size - size - sizeof(Block);
        newBlock->isFree = true;
        newBlock->next = bestFit->next;

        bestFit->size = size;
        bestFit->next = newBlock;
    }

    bestFit->isFree = false;
    return (char*)bestFit + sizeof(Block);
}

// Free a block and merge adjacent free blocks if necessary
void bestFitFree(void* ptr) {
    if (!ptr) return;

    Block* block = (Block*)((char*)ptr - sizeof(Block));
    block->isFree = true;

    // Merge adjacent free blocks
    Block* curr = freeList;
    while (curr != NULL) {
        if (curr->isFree && curr->next && curr->next->isFree) {
            curr->size += curr->next->size + sizeof(Block);
            curr->next = curr->next->next;
        }
        curr = curr->next;
    }
}

// Define the Heap structure
typedef struct {
    int* data;       // Pointer to heap elements
    int size;        // Current number of elements in the heap
    int capacity;    // Maximum capacity of the heap
} Heap;

// Initialize a new heap using best-fit allocation
Heap* createHeap(int capacity) {
    Heap* heap = (Heap*) bestFitAlloc(sizeof(Heap));
    if (!heap) return NULL;

    heap->data = (int*) bestFitAlloc(capacity * sizeof(int));
    if (!heap->data) {
        bestFitFree(heap);  // Free heap struct if allocation fails
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Helper functions for heap operations
int parent(int i) { return (i - 1) / 2; }
int leftChild(int i) { return 2 * i + 1; }
int rightChild(int i) { return 2 * i + 2; }

// Insert an element into the heap
void heapInsert(Heap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap is full\n");
        return;
    }

    heap->data[heap->size] = value;
    int i = heap->size;
    heap->size++;

    // Heapify up
    while (i != 0 && heap->data[parent(i)] > heap->data[i]) {
        int temp = heap->data[i];
        heap->data[i] = heap->data[parent(i)];
        heap->data[parent(i)] = temp;
        i = parent(i);
    }
}

// Extract the minimum element from the heap
int heapExtractMin(Heap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return -1;
    }
    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }

    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    int i = 0;

    // Heapify down
    while (1) {
        int left = leftChild(i);
        int right = rightChild(i);
        int smallest = i;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }

        int temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;
        i = smallest;
    }
    return root;
}

// Main function for testing
int main() {
    initializeMemoryPool();

    int capacity = 10;
    Heap* heap = createHeap(capacity);
    if (!heap) {
        printf("Failed to allocate memory for heap\n");
        return 1;
    }

    // Insert elements into the heap
    heapInsert(heap, 20);
    heapInsert(heap, 5);
    heapInsert(heap, 15);

    // Extract elements from the heap
    printf("Min element: %d\n", heapExtractMin(heap));
    printf("Min element: %d\n", heapExtractMin(heap));

    // Free memory used by the heap
    bestFitFree(heap->data);
    bestFitFree(heap);

    return 0;
}
