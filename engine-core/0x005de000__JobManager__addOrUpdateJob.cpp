// FUNC_NAME: JobManager::addOrUpdateJob
// Address: 0x005de000
// Role: Searches for an existing job with matching type/subtype, updates its value; otherwise allocates a new job node from a global free list and appends to the manager's array.

#include <cstdint>

// Assumed memory pool structure (global)
struct JobPool {
    // +0x00-0x33: other fields
    // +0x34: flags (byte)
    // +0x40: some allocation limit?
    // +0x44: free list head (pointer to next free node)
    int field_0x40;
    uint8_t field_0x34; // LSB indicates availability
    // ... padding?
    JobNode* freeListHead; // +0x44
};

// Job node structure (20 words = 0x50 bytes? Actually offsets up to 0x19 * 4 = 0x64)
struct JobNode {
    // +0x00-0x0F: magic numbers for debugging (0x00-0x1C)
    uint32_t magic[4]; // 0x00, 0x04, 0x08, 0x0C
    // +0x10-0x13: vtable? Or next pointer?
    // +0x14: type (compared with dataPtr+0x0c)
    // +0x18: subtype (compared with dataPtr+0x08)
    // +0x1C: some value (from dataPtr+0x10)
    // +0x20: current state (from dataPtr+0x14)
    // +0x24: previous state (same as current)
    // +0x28-0x3F: other fields
    uint32_t field_0x10; // assumed next pointer for free list
    uint32_t type;       // +0x14
    uint32_t subtype;    // +0x18
    uint32_t field_0x1C; // +0x1C
    uint32_t currentValue; // +0x20
    uint32_t previousValue; // +0x24
    // ... rest
};

// Manager class that holds a dynamic array of JobNode pointers
struct JobManager {
    // +0x270: pointer to array of JobNode* pointers
    // +0x274: number of elements in array
    // +0x278: capacity of array
    JobNode** jobArray;  // +0x270
    uint32_t jobCount;   // +0x274
    uint32_t jobCapacity; // +0x278
};

// External functions (callees)
extern JobNode* __cdecl allocateJobNode(); // FUN_004de190
extern void __thiscall jobNodeConstructor(JobNode* node); // FUN_005dd030
extern void __thiscall growArray(JobManager* manager, int newCapacity); // FUN_005e1c00

extern JobPool g_jobPool; // DAT_01223508

// Main function
uint32_t __thiscall JobManager::addOrUpdateJob(JobManager* thisPtr, void* dataPtr)
{
    uint32_t index = 0;
    int tempVar = g_jobPool.field_0x40; // unused? Actually used later

    if (thisPtr->jobCount != 0) {
        JobNode** currentPtr = thisPtr->jobArray;
        do {
            JobNode* node = *currentPtr;
            if (node != nullptr &&
                node->subtype == *(uint32_t*)((uint8_t*)dataPtr + 0x0c) &&
                node->type == *(uint32_t*)((uint8_t*)dataPtr + 0x08)) {
                // Found existing job; update its values
                node->currentValue = *(uint32_t*)((uint8_t*)dataPtr + 0x14);
                node->previousValue = *(uint32_t*)((uint8_t*)dataPtr + 0x14);
                return (index << 8) | 1; // success with index
            }
            index++;
            currentPtr++;
        } while (index < thisPtr->jobCount);
    }

    // No match found; need to allocate a new node
    // Check if free list is empty and allocation is allowed
    if (g_jobPool.freeListHead == nullptr &&
        (g_jobPool.field_0x40 == 0 || ((g_jobPool.field_0x34 & 1) == 0))) {
        allocateJobNode(); // expands the pool
    }

    JobNode* newNode = g_jobPool.freeListHead;
    if (newNode != nullptr) {
        // Remove from free list
        g_jobPool.freeListHead = (JobNode*)newNode->field_0x10; // next pointer at +0x10
        // Update pool statistics (likely count)
        // g_jobPool.field_0x20++; g_jobPool.field_0x1c--; // offsets from global
        // Those offsets are +0x20 and +0x1c from global base
        *(int*)((uint8_t*)&g_jobPool + 0x20) += 1;
        *(int*)((uint8_t*)&g_jobPool + 0x1c) -= 1;

        // Set debugging magic numbers
        newNode->magic[0] = 0xbadbadba;
        newNode->magic[1] = 0xbeefbeef;
        newNode->magic[2] = 0xeac15a55;
        newNode->magic[3] = 0x91100911;

        // Call constructor to initialize vtable etc.
        jobNodeConstructor(newNode);

        // Copy data from dataPtr
        newNode->field_0x1C = *(uint32_t*)((uint8_t*)dataPtr + 0x04);
        newNode->type = *(uint32_t*)((uint8_t*)dataPtr + 0x08);
        newNode->subtype = *(uint32_t*)((uint8_t*)dataPtr + 0x0c);
        newNode->field_0x10 = *(uint32_t*)((uint8_t*)dataPtr + 0x10);
        newNode->currentValue = *(uint32_t*)((uint8_t*)dataPtr + 0x14);
        newNode->previousValue = *(uint32_t*)((uint8_t*)dataPtr + 0x14);

        // Check if array needs to grow
        if (thisPtr->jobCount < 0x14) {
            if (thisPtr->jobCount == thisPtr->jobCapacity) {
                int newCapacity;
                if (thisPtr->jobCapacity == 0) {
                    newCapacity = 1;
                } else {
                    newCapacity = thisPtr->jobCapacity * 2;
                }
                growArray(thisPtr, newCapacity);
            }
            // Append to array
            JobNode** writeSlot = thisPtr->jobArray + thisPtr->jobCount;
            thisPtr->jobCount++;
            *writeSlot = newNode;
            return (thisPtr->jobCount << 8) | 1; // success with new count
        }
    }

    // Failed to allocate or array full
    return index & 0xffffff00; // low byte cleared
}