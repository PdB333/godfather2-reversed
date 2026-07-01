// FUNC_NAME: EventManager::setEventFlag
void __thiscall EventManager::setEventFlag( int bitIndex )
{
    // Bitmask array starts at this+0x8e0
    // Each uint stores 32 flags
    uint bitMask = 1 << (bitIndex & 0x1f);
    uint wordIndex = bitIndex >> 5;
    uint* wordPtr = (uint*)((char*)this + 0x8e0 + wordIndex * 4);
    
    // If the flag is being set for the first time, notify via callback
    if ((*wordPtr & bitMask) == 0)
    {
        // this+0x58 points to a helper object with a vtable
        // vtable entry at index 0x28 is a function taking an int parameter (0x20 = EVENT_FLAG_SET)
        void** helperObj = *(void***)((char*)this + 0x58);
        void (*notifyFunc)(int) = (void (*)(int))helperObj[0x28 / 4];
        notifyFunc(0x20);
    }
    
    // Set the flag
    *wordPtr |= bitMask;
}