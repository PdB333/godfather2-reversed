// FUNC_NAME: GodfatherGameManager::frameUpdate
// Function address: 0x0080b580
// Per-frame update for the main game manager. Handles pause/menu state flags,
// activates the manager handle, calls a virtual update method, and updates subsystems.

void __fastcall GodfatherGameManager::frameUpdate(int *this)
{
    uint32_t flags = (uint32_t)this[0x6E5]; // offset 0x1B94: bitfield of state flags

    // Bit 12 indicates a menu/pause overlay is active
    if ((flags >> 0xC) & 1)
    {
        // Decode sub-state: bits 8-11 define specific menu type
        if ((flags >> 8) & 1)
        {
            setMenuPause(0); // FUN_0080ad10(0) - disable pause for this menu
        }
        else if ((flags >> 9) & 1)
        {
            setMenuPause(1); // FUN_0080ad10(1) - enable pause
        }
        else if ((flags >> 0xA) & 1)
        {
            setSubmenuOption(1); // FUN_0080a520(1) - set option for submenu
        }
        else if ((flags >> 0xB) & 1)
        {
            setSubmenuOption(0); // FUN_0080a520(0) - clear option
        }
    }

    // Retrieve manager handle from global singleton (+0x60)
    void *managerHandle = *(void **)(DAT_01223480 + 0x60);
    setManagerActive(managerHandle, 1); // FUN_00805ed0(managerHandle, 1)

    // Virtual call: vtable offset 0x2F8 (index 190)
    if ((**(code **)(*this + 0x2F8))() != 0)
    {
        // Virtual method returned true, re-activate manager
        setManagerActive(managerHandle, 1);
    }

    // Update core subsystems
    updateAudioSystem();       // FUN_007f85f0
    updatePhysicsSystem();     // FUN_007fe8b0
    updateAnimationSystem();   // FUN_007fea20
    updateRenderingSystem();   // FUN_007feb90

    // Check another flag: this[0x23A] (offset 0x8E8) bit 14
    if ((((uint32_t)this[0x23A] >> 0xE) & 1) && DAT_0112a53c != 0)
    {
        char buffer[20];
        serializeGameState(buffer); // FUN_00826510(buffer) - saves/transmits state
    }

    // Remaining subsystem updates
    updateNetworkSystem();     // FUN_007fecd0
    updateUISystem();          // FUN_007fedc0
    updateGameplaySystem();    // FUN_007fee80
}