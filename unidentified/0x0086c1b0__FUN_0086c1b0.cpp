// FUNC_NAME: SomeClass::checkStateFlag
bool __thiscall SomeClass::checkStateFlag(SomeClass* this) {
    // Read flags at offset +0xC8 (200)
    ushort flags = *(ushort*)((uintptr_t)this + 0xC8);
    // Shift right by 6 to bring bit 6 to bit 0
    ushort shifted = flags >> 6;
    // bVar1 = ~(byte)shifted & 1  -> 1 if bit 6 is 0, else 0
    bool result = (~(byte)shifted & 1) != 0;

    if (!result) {
        // Bit 6 is set (result == 0)
        // Read pointer at +0x50
        void* subObjPtr = *(void**)((uintptr_t)this + 0x50);
        if (subObjPtr != nullptr) {
            // Subtract 0x48 to get base of parent structure
            uintptr_t base = (uintptr_t)subObjPtr - 0x48;
            // Read flags at +0xC88 in parent
            uint parentFlags = *(uint*)(base + 0xC88);
            // Check if original bit 6 is 0 (shifted & 1 == 0) – always false here
            if ((shifted & 1) == 0) {
                // Check bit 0x15 (21) or bit 0xB (11) in parentFlags
                if (((parentFlags >> 0x15) & 1) != 0 || ((parentFlags >> 0xB) & 1) != 0) {
                    result = true;
                }
            }
        }
    }
    return result;
}