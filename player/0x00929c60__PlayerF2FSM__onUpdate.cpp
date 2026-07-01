// FUNC_NAME: PlayerF2FSM::onUpdate
void __thiscall PlayerF2FSM::onUpdate(PlayerF2FSM* this)
{
    // Offset +0x50: byte flag indicating F2F should be hidden
    if (*(char*)((uintptr_t)this + 0x50) != 0)
    {
        *(char*)((uintptr_t)this + 0x50) = 0;
        // Issue hide command for First-to-Fight overlay
        console->execute("HideF2F", 0, nullptr, 0);  // FUN_005a04a0
        // Reset some vector or state (likely a 3-component struct)
        struct HideF2FData
        {
            int32_t constant;  // +0x00: DAT_01130358
            int32_t zero1;     // +0x04
            char   zero2;      // +0x08
        } data = { DAT_01130358, 0, 0 };
        resetHideState(&data, 0);  // FUN_00408a00
    }
    // Call virtual base update (vtable+0x2c)
    (*(void (__thiscall**)(PlayerF2FSM*))(*((uintptr_t*)this) + 0x2c))(this);
}