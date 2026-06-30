// FUNC_NAME: PlayerManager::PlayerManager

void __thiscall PlayerManager::PlayerManager(void)
// Constructor at 0x005e7180, initializes singleton PlayerManager
{
    // Store global singleton pointer (g_playerManager = this)
    *(PlayerManager**)0x01223504 = this;

    // Set vtable pointer
    *(void**)this = (void*)0x00e3f6d4; // vtable for PlayerManager

    // Offset 0x14: unknown integer (initialized to 0)
    *(int*)((uintptr_t)this + 0x14) = 0;

    // Offset 0x1C: byte set to 4 (likely maxPlayerCount or similar)
    *(uint8_t*)((uintptr_t)this + 0x1C) = 4;

    // Offset 0x1D: byte initialized to 0
    *(uint8_t*)((uintptr_t)this + 0x1D) = 0;

    // Zero out two arrays of 4 elements each:
    // - int32 array at offset 0x04 (size 16 bytes)
    // - byte array at offset 0x18 (size 4 bytes)
    for (int i = 0; i < 4; i++)
    {
        *(uint32_t*)((uintptr_t)this + 0x04 + i * 4) = 0;
        *(uint8_t*)((uintptr_t)this + 0x18 + i) = 0;
    }
}