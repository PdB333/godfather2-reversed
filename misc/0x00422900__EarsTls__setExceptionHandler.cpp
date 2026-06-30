// FUNC_NAME: EarsTls::setExceptionHandler
void __fastcall EarsTls::setExceptionHandler(unsigned int functionPtr) // param_1 is a function pointer or context
{
    // Get TLS structure pointer from FS:[0x2c] (thread-local storage slot)
    int* tlsBase = *(int**)(__readfsdword(0x2c)); // dereference TLS slot
    // Store the provided function pointer at offset +0x24 in the TLS structure
    *(unsigned int*)(tlsBase + 0x24) = functionPtr;

    // Check if the flag at offset +0x34 is zero (first time setup?)
    if (*(int*)(tlsBase + 0x34) == 0)
    {
        // Global pointer table at DAT_01206880 + 0x14 (list of exception handlers)
        int* globalListPtr = (int*)(DAT_01206880 + 0x14);
        // Write the address of a global vtable/function table (PTR_LAB_0110b640) into the list
        *(int**)globalListPtr = &PTR_LAB_0110b640;
        // Advance pointer by 4 (to next slot)
        *globalListPtr += 4;
        // Write the provided function pointer into the list
        *(unsigned int*)*globalListPtr = functionPtr;
        // Advance pointer by 4 again
        *globalListPtr += 4;
    }
}