// FUNC_NAME: MemoryManager::allocateArray
// Address: 0x0043fc60
// Role: Allocate array memory with overflow detection and zero-size handling

void* MemoryManager::allocateArray(unsigned int elementCount)
{
    if (elementCount == 0)
    {
        // Zero-size allocation: delegate to internal allocator (likely returns null or throws)
        return (void*)internalMemAlloc(0);
    }

    // Overflow check: ensures elementCount does not exceed maximum size (0xFFFFFFFF) for a single allocation.
    // The calculation (0xFFFFFFFF / elementCount) yields zero only if elementCount > 0xFFFFFFFF.
    if ( (int)( (unsigned long long)0xFFFFFFFF / (unsigned long long)elementCount ) == 0 )
    {
        // Overflow detected: prepare exception info and invoke the global new handler chain
        unsigned int overflowMarker = 0;
        void** exceptionInfo = &s_exceptionTable;     // points to static exception data at 0x00e31050
        if (g_newHandlerFunc != nullptr)
            g_newHandlerFunc(exceptionInfo);         // call custom new handler (DAT_0113d3a0)
        (*(void (*)())exceptionInfo[2])();            // invoke the terminate function
        std::_Throw((exception*)&overflowMarker);   // compiler-generated throw
    }

    // Perform the actual allocation
    return (void*)internalMemAlloc(elementCount);
}