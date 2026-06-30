// FUNC_NAME: Player::shutdown
// Function at 0x005f0420 - Called during Player destruction/shutdown.
// This method safely releases owned subsystems and then calls a global cleanup function.
// Offsets relative to 'this' (Player*):
// +0x0C : m_pInputManager (or similar subsystem pointer 1)
// +0x14 : m_pSpecialAbility (or similar subsystem pointer 2)

void __thiscall Player::shutdown() {
    // Check if required subsystems exist and if a global manager interface is available.
    if ( *(int*)(this + 0x0C) != 0 &&          // m_pInputManager
         *(int*)(this + 0x14) != 0 &&          // m_pSpecialAbility
         *(int*)(*(int*)DAT_01223518 + 4) != 0 ) // g_pGameManager->m_pReleaseInterface
    {
        // Call virtual Release() on the first subsystem (vtable offset 4).
        // Typically used to decrement reference count or trigger cleanup.
        (**(code**)(**(int**)(DAT_01223518 + 4) + 4))(*(int*)(this + 0x0C), 0);
    }

    // Global shutdown/cleanup routine (likely engine-level).
    FUN_009c8eb0();
}