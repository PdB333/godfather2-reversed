// FUNC_NAME: ObjectRefHolder::release

void __fastcall ObjectRefHolder::release(int thisPtr)
{
    // Check if the pointer at offset +0x8 is non-null
    int* ptr = *(int**)(thisPtr + 8);
    if (ptr != nullptr)
    {
        // Call destructor or release function on the pointed object (likely a sub-object or resource)
        FUN_009c8f10(ptr);
    }
    // Reset the integer at offset +0xc to 0 (or zero out some flag/reference count)
    *(int*)(thisPtr + 0xc) = 0;
}