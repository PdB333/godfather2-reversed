// FUNC_NAME: MemoryManager::allocateArray
void __thiscall MemoryManager::allocateArray(int count, int* manager, Array* outArray) 
{
    int* managerHeader;
    uint allocSize;
    int* data;
    int* statsPtr;

    MemoryManager::enterAllocationLock();

    if (count < 0) {
        // Error: invalid count (negative)
        err(manager[0], "bad integer in %s", manager[4]); // manager[4] is the allocator name string
    }

    managerHeader = manager[0]; // +0x00: pointer to memory manager internal block
    allocSize = count * 4; // Size in bytes for int array

    if (allocSize != 0) {
        if (allocSize > 0xfffffffc) {
            // Exceeded maximum allocation size
            err(managerHeader, "memory allocation error: block too big");
        }

        data = allocFunc(0, allocSize); // DAT_012059dc - custom allocator function
        if (data != 0) {
            // Allocation succeeded: update total allocated bytes counter
            if (managerHeader != 0) {
                statsPtr = (int*)(*(int*)(managerHeader + 0x10) + 0x24); // +0x10: stats struct, +0x24: totalAllocatedBytes
                *statsPtr = *statsPtr + allocSize;
            }
            goto storePtr;
        }

        // Allocation failed: attempt recovery
        if (managerHeader != 0) {
            MemoryManager::outOfMemoryHandler(); // FUN_00635a80 - possibly garbage collection
            return;
        }
    }

    data = 0;

storePtr:
    outArray->data = data;   // +0x0c: pointer to allocated array
    outArray->capacity = count; // +0x2c: element count (capacity)

    MemoryManager::registerAllocation(count); // FUN_00641990 - track allocation size
}