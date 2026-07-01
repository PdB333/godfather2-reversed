// FUNC_NAME: InputManager::initializeControllerSlots
void __fastcall InputManager::initializeControllerSlots(int this)
{
    // Call base initialization (likely clears or resets internal state)
    FUN_005c1740();

    // Initialize 16 controller slots (0x44 bytes each) starting at offset +0x54
    // Each call to FUN_005c0460 sets up a slot with a specific configuration
    // The DAT_* addresses are likely static configuration data for each slot
    FUN_005c0460(&DAT_00d856e0, this + 0x54, 0, 0, 1);   // Slot 0
    FUN_005c0460(&DAT_00d86e88, this + 0x58, 0, 0, 1);   // Slot 1
    FUN_005c0460(&DAT_00d86e80, this + 0x5c, 0, 0, 1);   // Slot 2
    FUN_005c0460(&DAT_00d86e78, this + 0x60, 0, 0, 1);   // Slot 3
    FUN_005c0460(&DAT_00d86e70, this + 100, 0, 0, 1);    // Slot 4 (offset 0x64)
    FUN_005c0460(&DAT_00d86e68, this + 0x68, 0, 0, 1);   // Slot 5
    FUN_005c0460(&DAT_00d86e60, this + 0x6c, 0, 0, 1);   // Slot 6
    FUN_005c0460(&DAT_00d86e58, this + 0x70, 0, 0, 1);   // Slot 7
    FUN_005c0460(&DAT_00d86e50, this + 0x74, 0, 0, 1);   // Slot 8
    FUN_005c0460(&DAT_00d86e48, this + 0x78, 0, 0, 1);   // Slot 9
    FUN_005c0460(&DAT_00d86e40, this + 0x7c, 0, 0, 1);   // Slot 10
    FUN_005c0460(&DAT_00d86e38, this + 0x80, 0, 0, 1);   // Slot 11
    FUN_005c0460(&DAT_00d86e30, this + 0x84, 0, 0, 1);   // Slot 12
    FUN_005c0460(&DAT_00d86e28, this + 0x88, 0, 0, 1);   // Slot 13
    FUN_005c0460(&DAT_00d86e20, this + 0x8c, 0, 0, 1);   // Slot 14
    FUN_005c0460(&DAT_00d86e18, this + 0x90, 0, 0, 1);   // Slot 15
    FUN_005c0460(&DAT_00d86e10, this + 0x94, 0, 0, 1);   // Slot 16
    FUN_005c0460(&DAT_00d86e08, this + 0x98, 0, 0, 1);   // Slot 17 (extra?)
    return;
}