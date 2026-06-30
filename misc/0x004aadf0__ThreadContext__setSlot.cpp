// FUNC_NAME: ThreadContext::setSlot
void __thiscall ThreadContext::setSlot(uint32_t thisPtr, uint32_t value)
{
    // Slot offset stored at this+0x18
    uint32_t slotOffset = *(uint32_t*)(thisPtr + 0x18);

    uint32_t tlsArray;
    __asm {
        mov eax, dword ptr fs:[0x2c]
        mov tlsArray, eax
    }

    // First TLS slot holds a pointer to per-thread data
    uint32_t perThreadData = *(uint32_t*)tlsArray;
    // Offset +8 yields slot array base
    uint32_t slotBase = *(uint32_t*)(perThreadData + 8);
    // Slot array begins at slotBase + 0x74
    uint32_t* target = (uint32_t*)((uint8_t*)slotBase + 0x74 + slotOffset);
    *target = value;
}