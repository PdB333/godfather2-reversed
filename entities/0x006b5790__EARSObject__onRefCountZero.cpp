// FUNC_NAME: EARSObject::onRefCountZero
// Address: 0x006b5790
// Role: Decrements reference count; if zero, releases all child objects indexed from childCount-1 down to 0.

void __thiscall EARSObject::onRefCountZero(void) // ecx = this
{
    // Offset +0x78: reference count (int)
    int* refCount = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x78);
    (*refCount)--;
    if (*refCount == 0)
    {
        // Offset +0xac: number of child objects (int)
        int childCount = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xac);
        // Iterate in reverse order to release children cleanly
        for (int i = childCount - 1; i >= 0; i--)
        {
            // FUN_006b56a0 releases the i-th child (likely a handle or index)
            releaseChild(i); // Actual name: releaseChild
        }
    }
}