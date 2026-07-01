// FUNC_NAME: GameManager::initialize
void __fastcall GameManager::initialize(GameManager* thisPtr)
{
    // Set up vtable pointers (primary +6 +7 +10)
    *thisPtr = &g_vtable_00d91dcc;                      // +0x00: vtable pointer
    thisPtr[6] = &g_struct_00d91dc8;                    // +0x18: offset 24
    thisPtr[7] = &g_struct_00d91db8;                    // +0x1c: offset 28
    sub_4086d0(&g_global_0112a5a4);                     // Initialize global structure
    sub_5c0a90();                                        // Subsystem init
    thisPtr[10] = &g_vtable2_00d91dac;                  // +0x28: offset 40
    sub_4de130();                                        // Engine init
    sub_4083d0();                                        // Subsystem init
    thisPtr[6] = &g_struct_00d91db4;                    // Update field +0x18
    g_globalFlag_01130040 = 0;                          // Clear initialization flag
    sub_5c0190();                                        // Final init step
}