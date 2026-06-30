// FUNC_NAME: ArrayAllocator::allocateIntBuffer
// Address: 0x00641af0
// Role: Allocates an int buffer of given count, updates memory tracking and output struct

void ArrayAllocator::allocateIntBuffer(int newCount, MemoryContext* allocContext, OutputStruct* outStruct)
{
    // Initialize allocation state (e.g., check for pending errors)
    initAlloc();

    // Validate count: must be non-negative
    if (newCount < 0)
    {
        reportError(allocContext->currentSize, "bad integer in %s", allocContext->nameString); // allocContext->nameString is at +0x10
    }

    int currentSize = allocContext->currentSize; // +0x00
    uint sizeToAlloc = newCount * 4;
    void* buffer = nullptr;

    if (sizeToAlloc != 0)
    {
        if (sizeToAlloc > 0xFFFFFFFC) // Max allocation check (block too big)
        {
            reportError(currentSize, "memory allocation error: block too big");
        }

        // Call the custom allocator (DAT_012059dc) with hint=0 and size
        buffer = allocFunc(0, sizeToAlloc);
        if (buffer != nullptr)
        {
            if (currentSize != 0)
            {
                // Update memory usage counter: allocContext->usageTracker at +0x10->+0x24
                int* usageTracker = (int*)(*(int*)((char*)allocContext + 0x10) + 0x24);
                *usageTracker += sizeToAlloc;
            }
        }
        else
        {
            if (currentSize != 0)
            {
                handleAllocFailure();
                return;
            }
        }
    }

    // Store results in output struct at known offsets
    outStruct->bufferPtr = (int*)buffer; // +0x0C
    outStruct->count = newCount;         // +0x2C

    // Finalize allocation (e.g., set flags, update metadata)
    finalizeAlloc(newCount);
}