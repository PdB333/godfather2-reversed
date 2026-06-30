//FUNC_NAME: MemoryManager::resolvePointer
int __fastcall MemoryManager::resolvePointer(int handle)
{
    // Get thread-local storage base (FS segment)
    int* tlsBase = *(int**)(*(int*)(__readfsdword(0x2c)) + 8);
    int offset = *(int*)(handle + 0x10); // +0x10: offset field

    // Check if any of the four pointer fields at +0x38..+0x44 are non-null
    if ( (*(int*)(handle + 0x38) != 0 || *(int*)(handle + 0x3c) != 0 ||
          *(int*)(handle + 0x40) != 0 || *(int*)(handle + 0x44) != 0) )
    {
        // Attempt to resolve via external function (likely a lookup/validation)
        int result = FUN_0051c4d0(*(int*)(handle + 4), handle + 0x38);
        if (result != 0)
            return result;
    }

    // Fallback: compute address from TLS base + 0x50 + offset
    return (int)(tlsBase + 0x50 + offset);
}