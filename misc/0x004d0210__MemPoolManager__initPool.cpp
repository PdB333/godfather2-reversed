// FUNC_NAME: MemPoolManager::initPool
void MemPoolManager::initPool(int poolIndex, int largeBlockCount, int mediumBlockOffset, int smallBlockCount, uint eaxFlags) {
    // eaxFlags contains page index in high bits (>>17)
    uint pageIndex = eaxFlags >> 0x11;
    // Calculate base size for the large block allocation
    uint allocSize = pageIndex * 0x20008 + 0xb498; // base offset + page-related adjustment
    uint combinedSize = allocSize + poolIndex * 8; // include pool index scaling
    
    // Get the global allocator vtable (likely from a singleton)
    void** allocatorVtable = (void**)FUN_009c8f80(); // returns pointer to allocator interface
    
    // Allocate the pool memory
    MemAllocParams params;
    params.field0 = 2;  // some flags
    params.field4 = 0x800; // alignment or size?
    int baseAllocation = (**(int(__stdcall*)(uint, MemAllocParams*))*allocatorVtable)(combinedSize, &params);
    
    // Get the pool manager singleton (likely contains free lists, slots, etc.)
    MemPoolManager* manager;
    if (pageIndex * 0x20008 + baseAllocation == 0) {
        manager = nullptr;
    } else {
        manager = (MemPoolManager*)FUN_004d00d0(); // returns singleton manager
    }
    
    // Initialize large block circular queue (protected by critical section)
    if (largeBlockCount != 0) {
        // Each large block is 0x20000 bytes
        uint* largeBlockEntry = (uint*)(baseAllocation + pageIndex * 0x20000);
        int remainingLargeBlocks = largeBlockCount;
        uint currentLargeBlock = baseAllocation;
        do {
            uint* entryPtr;
            if (largeBlockEntry == nullptr) {
                entryPtr = nullptr;
            } else {
                largeBlockEntry[0] = 0; // next pointer
                largeBlockEntry[1] = currentLargeBlock; // block address
                entryPtr = largeBlockEntry;
            }
            EnterCriticalSection((LPCRITICAL_SECTION)((byte*)manager + 0x28));
            int queueSize = *(int*)((byte*)manager + 0x24); // current count
            int capacity = *(int*)((byte*)manager + 0x1c);  // max capacity
            if (queueSize < capacity) {
                int slotIndex = *(int*)((byte*)manager + 0x20) + queueSize; // base index + offset
                *(int*)((byte*)manager + 0x24) = queueSize + 1;
                if (capacity <= slotIndex) {
                    slotIndex = slotIndex - capacity; // circular wrap
                }
                // Store entry in slot array (manager+0x18 is buffer pointer)
                *(uint**)(*(int*)((byte*)manager + 0x18) + slotIndex * 4) = entryPtr;
            }
            LeaveCriticalSection((LPCRITICAL_SECTION)((byte*)manager + 0x28));
            currentLargeBlock += 0x20000;
            largeBlockEntry += 2; // each entry is 8 bytes (2 uint32)
            remainingLargeBlocks--;
        } while (remainingLargeBlocks != 0);
    }
    
    // Initialize medium-sized object free list (0x80 objects of size 0x168)
    uint mediumBlockStart = baseAllocation + mediumBlockOffset;
    int mediumCount = 0x80;
    do {
        void* mediumObject;
        if (mediumBlockStart == 0) {
            mediumObject = nullptr;
        } else {
            mediumObject = (void*)FUN_004d1630(); // presumably allocates fixed size or returns sub-block?
        }
        // Link into singly linked free list (manager+0x60 = head, manager+0x5c = tail)
        *(uint*)mediumObject = 0; // next pointer
        *(uint*)((byte*)mediumObject + 4) = *(uint*)((byte*)manager + 0x60); // link to previous head
        if (*(void**)((byte*)manager + 0x60) == nullptr) {
            *(void**)((byte*)manager + 0x5c) = mediumObject; // tail
        } else {
            *(void**)*(void**)((byte*)manager + 0x60) = mediumObject; // previous head's next = new object
        }
        mediumBlockStart += 0x168; // size of medium object
        mediumCount--;
        *(void**)((byte*)manager + 0x60) = mediumObject; // new head
    } while (mediumCount != 0);
    
    // Initialize small-sized object free list (8-byte objects)
    if (smallBlockCount != 0) {
        uint* smallBlockEntry = (uint*)(baseAllocation + allocSize); // note: allocSize was pageIndex*0x20008+0xb498
        do {
            uint* entryPtr;
            if (smallBlockEntry == nullptr) {
                entryPtr = nullptr;
            } else {
                smallBlockEntry[0] = 0;
                smallBlockEntry[1] = 0;
                entryPtr = smallBlockEntry;
            }
            // Link into free list (manager+0x10 = head, manager+0x14 = tail)
            *entryPtr = *(uint*)((byte*)manager + 0x10); // next pointer
            if (*(int*)((byte*)manager + 0x10) == 0) {
                *(void**)((byte*)manager + 0x14) = entryPtr; // tail
            }
            smallBlockEntry += 2; // each entry is 8 bytes
            smallBlockCount--;
            *(void**)((byte*)manager + 0x10) = entryPtr; // new head
        } while (smallBlockCount != 0);
    }
    
    // Store base allocation address in manager
    *(int*)((byte*)manager + 8) = baseAllocation;
}

// Memory pool manager structure (hypothetical layout)
struct MemPoolManager {
    int baseAllocation;   // +0x08
    void* smallFreeHead;  // +0x10
    void* smallFreeTail;  // +0x14
    void* slotBuffer;     // +0x18
    int slotCapacity;     // +0x1c
    int slotBase;         // +0x20
    int slotCount;        // +0x24
    CRITICAL_SECTION cs;  // +0x28
    // ... (0x5c, 0x60 offsets)
    void* mediumFreeTail; // +0x5c
    void* mediumFreeHead; // +0x60
};

// Helper struct for allocation parameters
struct MemAllocParams {
    int field0;   // 2
    int field4;   // 0x800
};