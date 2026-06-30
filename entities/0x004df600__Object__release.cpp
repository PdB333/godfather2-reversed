// FUNC_NAME: Object::release
void __fastcall Object::release(int* thisPtr) // __thiscall, this in ecx
{
    // Dereference first member as pointer to internal data block
    int* pData = (int*)*thisPtr;
    if (pData)
    {
        // Set bit 21 (0x200000) in flags at offset +0xC
        pData[3] |= 0x200000; // +0xC: flags

        // Call external cleanup/notification function
        FUN_0051d6b0();

        // If there is a callback pointer at offset +0x8
        if (pData[2]) // +0x8: callback pointer (pointer to pointer)
        {
            // Nullify the target pointer
            *(int*)pData[2] = 0;
            // Nullify the callback pointer itself
            pData[2] = 0;
        }
    }
}