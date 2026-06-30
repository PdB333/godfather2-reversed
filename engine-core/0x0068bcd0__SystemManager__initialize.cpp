// FUNC_NAME: SystemManager::initialize
void SystemManager::initialize(bool doExtraInit)
{
    // Global system manager pointer at 0x01206880, offset +0x14 holds a pointer to the vtable pointer slot
    int* vtablePtrSlot = reinterpret_cast<int*>(DAT_01206880 + 0x14);

    // Write the vtable address into the slot pointed to by that pointer
    *reinterpret_cast<void**>(*vtablePtrSlot) = &PTR_LAB_00e50204;

    // Advance the vtable pointer by 4 bytes (likely to account for base-to-derived offset)
    *vtablePtrSlot += 4;

    if (doExtraInit)
    {
        // Build a small config string from globals
        char configBuffer[9];
        *reinterpret_cast<uint32_t*>(&configBuffer[0]) = DAT_0120eca8;
        *reinterpret_cast<uint32_t*>(&configBuffer[4]) = 0;
        configBuffer[8] = 0;

        // Parse the config string (0 = default mode)
        FUN_00408a00(configBuffer, 0);
    }

    // Initialize subsystems
    FUN_0040cd00(0);

    // Finalize initialization
    FUN_00485d50();
}