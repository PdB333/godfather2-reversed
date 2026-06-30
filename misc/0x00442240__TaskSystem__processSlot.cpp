// FUNC_NAME: TaskSystem::processSlot
// Address: 0x00442240
// Role: Processes tasks associated with a reference-counted slot. Increments slot refcount,
// executes virtual callback on each unprocessed task node, decrements refcount, and if zero,
// removes completed task nodes, freeing them via the global memory allocator.

#include <cstdint>

// Forward declarations
struct TaskNode;
struct MemoryAllocator;
struct Deleter;

// Global memory allocator base address (0x01223428 + 0x1c -> MemoryAllocator*)
extern uint8_t* gMemoryManagerBase;

// Struct representing a single slot in the task array (size 0x14 = 20 bytes)
struct TaskSlot {
    int32_t field_0x00;        // unknown
    int32_t field_0x04;        // unknown
    void*   context;           // +0x08: context pointer passed to callback
    int32_t refCount;          // +0x0C: reference count
    TaskNode* headNode;        // +0x10: linked list of TaskNode
    int32_t field_0x14;        // unknown (padding?)
};

// Node in the slot's linked list (8 bytes each)
struct TaskNode {
    void*   object;            // +0x00: pointer to an object (vtable pointer)
    uint32_t flagsAndNext;     // +0x04: lower bit = done flag, upper bits = next pointer (aligned)
    // Use flag bit 0: 1 = task completed, 0 = pending
    // Next pointer: flagsAndNext & ~1
};

// Memory allocator structure (points to a pool allocator)
struct MemoryAllocator {
    void*   poolStart;         // +0x00
    uint32_t poolSize;         // +0x04 (or possibly end offset)
    void*   freeListHead;      // +0x08
    int32_t freeCount;         // +0x0C (incremented on free)
    // ... other fields
    Deleter* deleter;          // +0x1C: if non-null, used for out-of-pool nodes
};

// Deleter object with vtable
struct Deleter {
    void** vtable;             // vtable pointer
    // virtual void free(void* ptr) at vtable+8 (index 2)
};

void TaskSystem::processSlot(int32_t slotIndex) {
    // Get the slot array from this+0x24
    TaskSlot* slotArray = *(TaskSlot**)(reinterpret_cast<char*>(this) + 0x24);
    TaskSlot& currentSlot = slotArray[slotIndex];

    // Increment reference count
    currentSlot.refCount++;

    // Iterate over the linked list of task nodes
    TaskNode* currentNode = currentSlot.headNode;
    while (currentNode != nullptr) {
        // Check if not already processed (bit 0 clear)
        if ((currentNode->flagsAndNext & 1) == 0) {
            // Call virtual function at vtable offset 4 (second virtual method) on the node's object
            // Parameters: slotIndex, context from slot
            // Returns bool (non-zero = true)
            bool taskCompleted = reinterpret_cast<bool (**)(int32_t, void*)>(
                *reinterpret_cast<void**>(currentNode->object)
            )[1](slotIndex, currentSlot.context);   // [1] -> offset 4

            if (taskCompleted) {
                currentNode->flagsAndNext |= 1;   // Mark as done
            }
        }
        // Move to next node (mask off flag bit)
        currentNode = reinterpret_cast<TaskNode*>(currentNode->flagsAndNext & ~1);
    }

    // Decrement reference count
    currentSlot.refCount--;

    // If ref count became zero, clean up completed nodes
    if (currentSlot.refCount == 0) {
        // Get memory allocator from global
        MemoryAllocator* allocator = *reinterpret_cast<MemoryAllocator**>(
            gMemoryManagerBase + 0x1C
        );

        TaskNode* previousNode = nullptr;
        TaskNode* currentNode = currentSlot.headNode;
        TaskNode* nextNode;

        while (currentNode != nullptr) {
            nextNode = reinterpret_cast<TaskNode*>(currentNode->flagsAndNext & ~1);

            if ((currentNode->flagsAndNext & 1) != 0) {
                // Remove from linked list
                if (previousNode == nullptr) {
                    currentSlot.headNode = nextNode;
                } else {
                    // Update previous node's next pointer, preserving its flag bit
                    previousNode->flagsAndNext = 
                        (previousNode->flagsAndNext & 1) | reinterpret_cast<uintptr_t>(nextNode);
                }

                // Free the node
                // Check if node falls within the pool's address range
                bool inPool = (allocator->poolStart != nullptr &&
                               currentNode >= allocator->poolStart &&
                               currentNode < reinterpret_cast<TaskNode*>(
                                   reinterpret_cast<char*>(allocator->poolStart) + allocator->poolSize
                               ));

                // If no deleter is set OR node is within the memory pool, add to free list
                if (allocator->deleter == nullptr || inPool) {
                    // Add to free list
                    currentNode->object = allocator->freeListHead;   // store old head
                    allocator->freeCount++;
                    allocator->freeListHead = currentNode;
                } else {
                    // Out-of-pool: call deleter's free virtual function (vtable+8)
                    reinterpret_cast<void (**)(void*)>(allocator->deleter->vtable)[2](currentNode);
                }

                // Note: previousNode remains unchanged because we removed the current node
            } else {
                // Node not completed, keep it
                previousNode = currentNode;
            }

            currentNode = nextNode;
        }
    }
}