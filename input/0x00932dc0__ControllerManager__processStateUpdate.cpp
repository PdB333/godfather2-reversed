// FUNC_NAME: ControllerManager::processStateUpdate
// Address: 0x00932dc0
// Reconstructed based on Ghidra decompilation of The Godfather 2 (EA EARS engine)

void ControllerManager::processStateUpdate() {
    // Global state pointers (offset comments from decompilation)
    uint8_t* pManager = reinterpret_cast<uint8_t*>(DAT_01129928);      // Manager object (e.g., ControllerManager)
    uint8_t* pInputDevice = reinterpret_cast<uint8_t*>(DAT_01129828);  // Input device object
    uint32_t& inputFlags = DAT_01130590;                               // Input flags bitfield
    int32_t& controllerState = DAT_00e5672c;                           // Controller state (e.g., 0x10, 0x11)
    uint8_t* pSomeOther = reinterpret_cast<uint8_t*>(DAT_01223484);    // Another object (e.g., Device component)

    // Check a boolean flag at offset +0xB4 in the manager
    if (pManager[0xB4] == 0) {
        // Check if device has some active state at +0x2C
        if (*reinterpret_cast<int32_t*>(pInputDevice + 0x2C) == 0) {
            // Clear bit 10 (0x400) of inputFlags
            inputFlags &= 0xFFFFFBFF;
            controllerState = 0x10; // e.g., disconnected or idle
        } else {
            // Retain bit 10 and set low nibble to 0x1
            controllerState = ((inputFlags >> 10) & 1) | 0x10;
        }
    } else {
        // Reset the flag
        pManager[0xB4] = 0;
        controllerState = 0x11; // e.g., connecting or active
    }

    // Handle a secondary object (e.g., timer or component)
    uint8_t* pObj = pSomeOther;
    if (pObj != nullptr) {
        // If any of the two fields (+0x28, +0x2C) are non-zero, nullify them
        int32_t field28 = *reinterpret_cast<int32_t*>(pObj + 0x28);
        int32_t field2C = *reinterpret_cast<int32_t*>(pObj + 0x2C);
        if (field28 != 0 || field2C != 0) {
            *reinterpret_cast<int32_t*>(pObj + 0x28) = 0;
            *reinterpret_cast<int32_t*>(pObj + 0x2C) = 0;
        }
    }

    // Reset a field in the manager at +0x60
    *reinterpret_cast<int32_t*>(pManager + 0x60) = 0;

    // If inputFlags bit 0 is not set, schedule a callback and set the bit
    if ((inputFlags & 1) == 0) {
        // FUN_005c0d50 is likely a timer/callback registration function
        // parameters: (context, callback address, optional delay or ID)
        FUN_005c0d50(pManager + 0x14, &LAB_00931e00, 0);
        inputFlags |= 1;
    }
}