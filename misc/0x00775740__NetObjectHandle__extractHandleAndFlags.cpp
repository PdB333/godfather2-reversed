// FUNC_NAME: NetObjectHandle::extractHandleAndFlags
uint extractObjectHandleAndFlags(void* obj, uint initialEax) // initialEax holds value from caller's EAX (high 24 bits used)
{
    uint result = initialEax & 0xffffff00; // preserve upper 24 bits of initial value
    void* subObj = *(void**)((char*)obj + 0x5c); // +0x5c: pointer to sub-object (e.g., NetObject)
    if (subObj != nullptr && subObj != (void*)0x48) // 0x48 is a sentinel (maybe null handle)
    {
        // subObj is non-null and not sentinel
        uint high24 = ((uint)subObj - 0x48) >> 8; // compute object index from pointer (adjust by 0x48 base)
        uint lowByte = (*(uint8*)((char*)subObj + 0xd4) & 0x79) != 0 ? 1 : 0; // test flags at +0xd4 (bits 0,3,4,5,6)
        return (high24 << 8) | lowByte; // combine into 32-bit handle
    }
    else
    {
        // Fallback: use global flag at address 0x11c (likely a global state indicator)
        extern uint8 g_globalFlag; // placeholder for global byte at 0x11c
        result = (g_globalFlag & 0x79) != 0;
    }
    return result;
}