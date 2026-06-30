// FUN_0054cec0: ObjectAllocator::constructWithFlag
int __thiscall ObjectAllocator::constructWithFlag(void* thisObj, byte allocFlag)
{
    // Global memory system initialization (likely singleton)
    callGlobalInit(); // FUN_009f0cb0

    if (allocFlag & 1)
    {
        // Retrieve thread-local storage (allocation context? pool handle?)
        TlsGetValue(DAT_01139810);

        // Call internal alloc/construct with size 0x31 (49 bytes)
        // +0x4: likely a size or type identifier (short)
        initializeMemory(thisObj, *(short*)((int)thisObj + 4), 0x31); // FUN_00aa26e0
    }

    // Return the constructed object (this pointer)
    return (int)thisObj;
}