// FUNC_NAME: AllocateArrayElements
void __thiscall AllocateArrayElements(int elementCount, int* allocator, int* buffer) {
    // FUN_00641940 - likely begin memory tracking or lock
    BeginMemoryTracking();

    if (elementCount < 0) {
        // FUN_00633920 - assertion/error reporting
        ErrorAssert(*allocator, "bad integer in %s", allocator[4]);
    }

    int baseAlloc = *allocator;  // base pointer or heap handle
    uint allocSize = elementCount * 4; // element size is 4 bytes (int)

    if (allocSize != 0) {
        if (allocSize > 0xfffffffc) { // overflow check for size_t
            ErrorAssert(baseAlloc, "memory allocation error: block too big");
        }

        // Global function pointer for allocation (DAT_012059dc)
        int* memory = (int*)globalAllocFunc(0, allocSize);
        if (memory != 0) {
            if (baseAlloc != 0) {
                // Update allocation counter in allocator structure at offset +0x10 and +0x24
                int* counterPtr = (int*)(*(int*)(baseAlloc + 0x10) + 0x24);
                *counterPtr += allocSize; // increment total allocated bytes
            }
            goto storeResult;
        }

        if (baseAlloc != 0) {
            // FUN_00635a80 - garbage collection / retry allocation
            GarbageCollect();
            return; // likely continues? but original code returns after call, so we return
        }
    }

    memory = 0; // fallback if allocSize == 0 or allocation failed

storeResult:
    // Store results into buffer structure
    buffer[0x14 / 4] = (int)memory;  // offset +0x14: pointer to allocated memory
    buffer[0x30 / 4] = elementCount; // offset +0x30: element count

    // FUN_00641990 - end memory tracking
    EndMemoryTracking(elementCount);
}