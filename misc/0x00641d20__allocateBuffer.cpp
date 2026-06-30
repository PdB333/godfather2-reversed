// FUNC_NAME: allocateBuffer
void __thiscall allocateBuffer(int count, int* allocator, void* outputBuffer)
{
    int* basePtr;               // from *allocator
    unsigned int sizeBytes;     // count * 4
    int memoryPtr;              // allocated pointer
    // +0x00: base pointer for memory tracking
    // +0x04: string table entry?

    lock();                     // FUN_00641940 – probably enter critical section

    if (count < 0) {
        reportError(*allocator, "bad integer in %s", allocator[4]); // FUN_00633920
    }

    basePtr = (int*)*allocator;
    sizeBytes = count * 4;

    if (sizeBytes != 0) {
        if (sizeBytes > 0xfffffffc) {
            reportError(*allocator, "memory allocation error: block too big"); // FUN_00633920
        }

        memoryPtr = heapAlloc(0, sizeBytes); // (*DAT_012059dc)(0, uVar2) – global allocation function

        if (memoryPtr != 0) {
            if (basePtr != 0) {
                // Update total allocated counter in the memory tracker
                // basePtr points to a structure; offset +0x10 points to another structure
                // that holds a byte counter at offset +0x24
                *(int*)(*(int*)((int)basePtr + 0x10) + 0x24) += sizeBytes;
            }
            goto assignAndExit;
        }

        // Allocation failed
        if (basePtr != 0) {
            attemptGarbageCollection(); // FUN_00635a80 – try to free memory
            return; // early return, no unlock – probably fatal or throws
        }
    }

    memoryPtr = 0;

assignAndExit:
    // Store data and size into the buffer structure passed as outputBuffer
    *(int*)((int)outputBuffer + 0x14) = memoryPtr;   // +0x14: pointer to data
    *(int*)((int)outputBuffer + 0x30) = count;        // +0x30: element count

    unlock(count); // FUN_00641990 – probably leave critical section
    return;
}