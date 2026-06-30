// FUNC_NAME: GameManager::constructor
void __thiscall GameManager::constructor(void) {
    // Global singleton pointer stored at DAT_01223504
    s_globalManager = this;

    // Set vtable pointer at offset +0x00
    this->vtable = &PTR_LAB_00e3f6d4;

    // Initialize field at offset +0x14 (dword) to 0
    *(int32_t*)((uintptr_t)this + 0x14) = 0;

    // Set byte at offset +0x1C to 4 (likely enum or flag)
    *(uint8_t*)((uintptr_t)this + 0x1C) = 4;

    // Set byte at offset +0x1D to 0
    *(uint8_t*)((uintptr_t)this + 0x1D) = 0;

    // Clear 4 dwords starting at offset +0x04 and 4 bytes starting at offset +0x18
    for (int i = 0; i < 4; i++) {
        *(int32_t*)((uintptr_t)this + 0x04 + i * 4) = 0;  // +0x04, +0x08, +0x0C, +0x10
        *(uint8_t*)((uintptr_t)this + 0x18 + i) = 0;      // +0x18, +0x19, +0x1A, +0x1B
    }
}