// FUNC_NAME: ThreadData::popAndPushCallback

#include <cstdint>

// Global queue structures (static pointers to per-thread callback stacks)
extern int* DAT_01206880; // main thread callback queue
extern int* DAT_012068e8; // worker thread callback queue

// External function pointer for the callback
extern void (*PTR_LAB_01124c0c)();

// Size of a free-list node block within the thread data structure
const int NODE_BLOCK_SIZE = 0x98;

struct ThreadData {
    // Free-list head pointer for thread index 0 (likely main thread) at offset +0x04
    int head0;
    // Padding to align next head at NODE_BLOCK_SIZE offset?
    // Nodes are stored contiguously in this block; each node contains:
    // +0x00: next index/pointer (int)
    // +0x08: saved callback data (uint64)  [offset +0x22 relative to head0?]
    // +0x10: more data? (uint64)           [offset +0x24 relative to head0?]
    // But the exact layout is inferred from decompiled offsets.

    // Free-list head pointer for thread index !=0 (worker thread) at offset +0x04+0x98
    int head1;
};

void ThreadData::popAndPushCallback()
{
    // Get thread-local index from the process's TLS
    int** tlsBase = (int**)__readfsdword(0x2C); // TEB -> TLS array
    int* tlsData = *tlsBase;
    int threadIndex = *(int*)(tlsData + 0x34); // 0 for main thread, non-zero for worker

    // Select which free-list head to use based on thread index
    int* headPtr = (int*)((uint)(threadIndex != 0) * NODE_BLOCK_SIZE + 0x04 + (int)this);

    // Pop the first node from the free list: set head to the next node
    headPtr[0] = headPtr[1]; // headPtr[1] is the next pointer of the current head

    // If the new head is valid (positive address), shift data from the new head to the old node
    if (headPtr[1] > 0) {
        // Copy 8 bytes from offset +0x88 (headPtr+0x22) to +0x08 (headPtr+2)
        *(uint64_t*)(headPtr + 2) = *(uint64_t*)(headPtr + 0x22);
        // Copy 8 bytes from offset +0x90 (headPtr+0x24) to +0x10 (headPtr+4)
        *(uint64_t*)(headPtr + 4) = *(uint64_t*)(headPtr + 0x24);
    }

    // Mark popped node as end of list (no next node)
    headPtr[1] = -1;

    // Select global callback queue based on thread type
    int* globalQueue = (threadIndex != 0) ? &DAT_012068e8 : &DAT_01206880;

    // Push callback entry onto the global queue (stack behavior)
    // The queue stores a pointer to a function and a boolean flag.
    int** stackPtr = (int**)(globalQueue + 0x14); // points to current stack top
    **stackPtr = (int)&PTR_LAB_01124c0c;          // write function pointer
    *stackPtr += 1;                               // advance stack
    **stackPtr = (threadIndex != 0);              // write boolean (1 = worker, 0 = main)
    *stackPtr += 1;                               // advance stack
}