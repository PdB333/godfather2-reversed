// FUNC_NAME: EffectManager::processSlot
void EffectManager::processSlot(int blendFactor, int slotIndex, uint32_t* outParam1, uint32_t* outParam2)
{
    // Read the current slot selector stored at this+0x61
    uint8_t selector = *(uint8_t*)(this + 0x61);
    // Choose one of two 48-byte blocks based on parity of (selector - slotIndex)
    uint8_t* slotBase = (uint8_t*)this + ((selector - slotIndex) & 1) * 0x30;

    // Call the internal function that processes this slot.
    // It returns two pointers in registers ECX and EDX (simulated via struct)
    Registers reg = processSlotInternal(slotBase, blendFactor);
    uint32_t* src = (uint32_t*)reg.ecx;  // source data from ECX
    uint32_t* dst = (uint32_t*)reg.edx;  // destination data from EDX

    // Copy 4 dwords from src+0x10 to dst+0x30
    dst[0x30 / 4] = src[0x10 / 4];   // +0x30
    dst[0x34 / 4] = src[0x14 / 4];   // +0x34
    dst[0x38 / 4] = src[0x18 / 4];   // +0x38
    dst[0x3c / 4] = src[0x1c / 4];   // +0x3c

    // Override the last dword with a global constant
    dst[0x3c / 4] = gDefaultValue;   // DAT_00e2b1a4

    // Set output parameters from src+0x24 and src+0x20 (order swapped)
    *outParam1 = src[0x24 / 4];   // param_4 gets src+0x24
    *outParam2 = src[0x20 / 4];   // param_5 gets src+0x20
}