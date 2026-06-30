// FUNC_NAME: checkedArrayAlloc_40Byte
// Address: 0x00694330
// Custom array allocation function for objects of size 0x28 (40 bytes) with overflow checking.
// Inline comments document structure offsets and exception handling.
void* __cdecl checkedArrayAlloc_40Byte(unsigned int elementCount)
{
    // Handle zero element count – explicit set to 0 (redundant but preserved from original)
    if (elementCount == 0) {
        elementCount = 0;
    }
    else
    {
        // Overflow check: if (0xFFFFFFFF / elementCount) < 0x28, throw "bad array new length"
        if ((0xFFFFFFFF / elementCount) < 0x28)
        {
            // Setup exception structure for throwing std::bad_array_new_length
            void** exceptionData = &PTR_LAB_00e31050;     // +0x0: points to "bad array new length" string
            // exceptionData[1] is unknown (local_4 = 0)
            // exceptionData[2] is a function pointer for the throw mechanism

            // Call global exception handler if registered
            if (DAT_0113d3a0 != nullptr)
            {
                ((void(__cdecl*)(void***))DAT_0113d3a0)(&exceptionData);
            }

            // Invoke the throw function stored at exceptionData[2]
            ((void(__cdecl*)(void))exceptionData[2])();

            // Ultimate call to std::_Throw (custom EA exception handling)
            std::_Throw((exception*)&exceptionData);
        }
    }

    // Allocate memory: elementCount * 0x28 bytes
    return heapAllocate(elementCount * 0x28);  // FUN_009c8e50 renamed
}