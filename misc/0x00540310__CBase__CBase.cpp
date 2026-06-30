// FUNC_NAME: CBase::CBase
int __thiscall CBase::CBase(int thisPtr, byte flag)
{
    // Call base class initializer (likely common initialization routine)
    BaseInit();

    // If flag bit 0 is set, perform thread-local memory pool deallocation
    if ((flag & 1) != 0)
    {
        // Retrieve TLS value for memory pool (global TLS index stored in DAT_01139810)
        TlsGetValue(DAT_01139810);
        // Deallocate memory with size stored at this+4 (object size) and tag 0x27
        DeallocatePool(thisPtr, *(unsigned short*)(thisPtr + 4), 0x27);
    }

    return thisPtr;
}