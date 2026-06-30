// FUN_004aae10: GameContext::setThreadLocalSlotValue

void __thiscall GameContext::setThreadLocalSlotValue(int this, int value)
{
    // Windows x86: FS:[0x2C] holds the pointer to the Thread Local Storage (TLS) array.
    // Index 2 (offset 8) contains a pointer to a global game context structure.
    int* tlsArray = *reinterpret_cast<int**>(__readfsdword(0x2C)); // TLS array
    int* globalContext = reinterpret_cast<int*>(tlsArray[2]);        // context pointer

    // Destination = globalContext + 0x78 + this->offsetAt0x18
    // +0x18 likely stores an index or sub-offset within the context.
    int destOffset = 0x78 + *reinterpret_cast<int*>(this + 0x18);
    int* dest = reinterpret_cast<int*>(reinterpret_cast<char*>(globalContext) + destOffset);

    *dest = value;
}