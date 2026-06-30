// FUNC_NAME: MemoryPool::freeAllNodes
// Address: 0x0065b9d0
// Role: Iterates through a linked list of allocated nodes, checks for a signature match, marks the buffer if condition holds, then moves each node to the global free list. Also handles static initialization guard and counter.

// Node structure: offset 0 = next, 4 = buffer pointer, 8 = size (compared to first int of buffer)
struct PoolNode {
    PoolNode* next;           // +0x00
    void*     buffer;          // +0x04
    int       size;            // +0x08 (maybe type/size tag)
};

// Global variables (likely static members of MemoryPool or global pool data)
extern uint   gPoolInitFlag;   // _DAT_01223ba4 – bit0 indicates initialized
extern int    gNumActiveNodes; // _DAT_01223b98 – active node count
extern PoolNode* gFreeListHead; // DAT_01223ba0 – head of free list

extern void MemoryPool_initialize(); // FUN_0065ba80
extern void atexit(void (*func)(void)); // standard atexit

void __thiscall MemoryPool::freeAllNodes(void* this) {
    // this points to the head of a list to free (first pointer is next)
    PoolNode* nodeList = *(PoolNode**)this; // dereference this to get list head
    while (nodeList != nullptr) {
        PoolNode* currentNode = nodeList;
        nodeList = currentNode->next; // advance before moving node

        // Check if the buffer's first int matches the size field (maybe a signature)
        if (currentNode->size == *(int*)(currentNode->buffer)) {
            // Mark buffer at offset 5 as "freed" or "available"
            ((char*)currentNode->buffer)[5] = 1;
        }

        // Static initialization guard (only once)
        if ((gPoolInitFlag & 1) == 0) {
            gPoolInitFlag |= 1;
            MemoryPool_initialize();
            atexit((void (*)(void))0x00d51450); // cleanup routine at exit
        }

        // Decrement active node count
        gNumActiveNodes--;

        // Return node to global free list
        currentNode->next = gFreeListHead;
        gFreeListHead = currentNode;
    }
}