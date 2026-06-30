// FUNC_NAME: MemoryPool::isAddressInBound
// Function at 0x00514300: Checks if a given address is within the memory
// pool's contiguous block. Uses thread-local storage (FS:[0x2c]) to retrieve
// the base of a global memory region. Return 1 if address is inside, 0 otherwise.
// Parameters: eax = address to check, edi = this (MemoryPool object).
// The pool layout: +0x00 = blockCount, +0x04 = elementSize (0x2a0), +0x10 = something?
bool __fastcall MemoryPool::isAddressInBound(uint addressToCheck)
{
    uint blockCount = *(uint*)this;                 // +0x00
    if (blockCount <= addressToCheck)
    {
        int baseAddr = 0;
        if (blockCount != 0)
        {
            // Get TLS pointer (FS:[0x2c]) -> global memory region base + 8
            baseAddr = *(int*)(**(int**)(__readfsdword(0x2c)) + 8) + blockCount;
        }
        int regionEnd = *(int*)(this + 4) * 0x2a0 + baseAddr;  // +0x04: elementSize
        if (regionEnd != 0 &&
            addressToCheck < (uint)(regionEnd - *(int*)(**(int**)(__readfsdword(0x2c)) + 8)))
        {
            return 1;
        }
    }
    return 0;
}