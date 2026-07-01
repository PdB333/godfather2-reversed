// FUNC_NAME: GameManager::update
void __fastcall GameManager::update(int *this)
{
    // Call virtual update method at vtable+0xB8 (likely main update)
    (**(code (__thiscall **)(int *))(*this + 0xb8))();

    // Check if bit 10 of member at offset 0x7c is not set (pause flag)
    // and global flag (g_bEnableSubsystems) is nonzero
    if ((((uint)this[0x1f] >> 10 & 1) == 0) && (DAT_01223484 != 0))
    {
        // Update input/controller subsystems (argument 0 indicates which slot or none)
        FUN_008a2d40(0);
        FUN_008a4ae0(0);
    }
}