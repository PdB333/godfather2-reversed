// FUNC_NAME: NetBuffer::initialize
void __thiscall NetBuffer::initialize(void *this, int param)
{
    // Base initialization (likely increment reference count or similar)
    FUN_00587d00(this, this);

    // Attempt to get a valid handle from the manager
    int handle = FUN_00587da0(this);
    if (handle >= 0)
    {
        // Success: retrieve a preallocated buffer
        int buffer = FUN_00579870();
        // Store param (unused in this path)
        int storedParam = param;
        FUN_00579450(this, buffer);
        return;
    }
    else
    {
        // Failure: allocate a local temporary buffer
        FUN_00579870(); // discard result
        // Store param (unused)
        int storedParam = param;
        char localBuffer[12]; // 12-byte temporary buffer
        FUN_00579450(this, localBuffer);
        // Mark that we are using a local buffer (flag at offset 0x2f0)
        *(int *)((char *)this + 0x2f0) = 0;
        return;
    }
}