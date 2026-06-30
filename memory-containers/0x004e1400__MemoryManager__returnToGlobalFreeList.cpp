// FUNC_NAME: MemoryManager::returnToGlobalFreeList

#include <cstdint>

// Global memory pool base address (offset 0x14 points to free list stack pointer)
extern uint32_t DAT_01206880;

// Static sentinel value used as a tag in free list entries
extern void* PTR_LAB_01123be8;

// __readfsdword intrinsic for retrieving Thread Local Storage pointer
uint32_t __readfsdword(uint32_t offset);

void __fastcall MemoryManager::returnToGlobalFreeList(uint32_t unusedECX, int* param)
{
    // param is a pointer to a 2-int structure; param[0] is the block offset/index
    if (param[0] != 0) {
        // Get pointer to the per-thread data block from TLS
        uint32_t tlsArray = __readfsdword(0x2c);
        int* threadData = *(int**)(tlsArray + 8);
        int nodePtr = (int)threadData + param[0]; // offset into per-thread pool

        // Check if the node has a next free pointer at +0x14
        int nextFree = *(int*)(nodePtr + 0x14);
        if (nextFree != 0) {
            // Push the nextFree pointer onto the global free stack
            int* globalStack = (int*)(DAT_01206880 + 0x14); // pointer to stack head
            *(void**)*globalStack = &PTR_LAB_01123be8; // write sentinel tag
            *globalStack += 4;                           // advance head
            *(int*)*globalStack = nextFree;               // store data
            *globalStack += 4;                           // advance head

            // Clear the node's next and previous links (+0x14, +0x18)
            *(int*)(nodePtr + 0x14) = 0;
            *(int*)(nodePtr + 0x18) = 0;
        }

        // Push the original offset (param[0]) onto the global free stack
        int* globalStack = (int*)(DAT_01206880 + 0x14);
        *(void**)*globalStack = &PTR_LAB_01123be8;
        *globalStack += 4;
        *(int*)*globalStack = param[0];
        *globalStack += 4;

        // Clear the caller's block descriptor
        param[0] = 0;
        param[1] = 0;
    }
}