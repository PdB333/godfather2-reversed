// FUNC_NAME: ThreadSafeObject::synchronizedExecute
void __fastcall ThreadSafeObject::synchronizedExecute(int thisPtr)
{
    CRITICAL_SECTION* pCS = *(CRITICAL_SECTION**)(thisPtr + 0x4e8); // offset of critical section pointer
    if (pCS != nullptr)
    {
        EnterCriticalSection(pCS);
        // Increment a custom use count stored in the DebugInfo field (crude lock counter)
        // Ghidra decompiles as: pCS[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&(pCS[1].DebugInfo)->Type + 1);
        // This actually increments the value at pCS->DebugInfo by the size of the 'Type' field.
        // It's likely a reinterpreted InterlockedIncrement.
        InterlockedIncrement((volatile LONG*)&pCS->DebugInfo);
    }

    // Call the actual work method
    FUN_00646ea0(thisPtr);

    if (pCS != nullptr)
    {
        // Decrement the custom counter
        InterlockedDecrement((volatile LONG*)&pCS->DebugInfo);
        LeaveCriticalSection(pCS);
    }
}