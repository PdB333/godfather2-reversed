// FUNC_NAME: CameraManager::handleStateChangeMessage
// Function address: 0x0093cb00
// Role: Processes state messages for camera system, managing sniper mode and suppression flags.

void __thiscall CameraManager::handleStateChangeMessage(int* messageData) {
    int messageId = *messageData;
    uint flags = *(uint*)(this + 0x0C); // Camera state flags

    // Check for SNIPER_MODE_ENABLE message
    if (messageId == DAT_01130450 && ((flags >> 0x12 & 1) == 0)) {
        flags |= 0x40000; // set bit 18
        *(uint*)(this + 0x0C) = flags;
        FUN_0093c210(); // handleSniperModeEnable
        return;
    }

    // Check for SNIPER_MODE_DISABLE message
    if (messageId == DAT_011303b0 && ((flags >> 0x12 & 1) != 0)) {
        flags &= 0xfffbffff; // clear bit 18
        *(uint*)(this + 0x0C) = flags;
        FUN_0093a2f0(); // handleSniperModeDisable
        return;
    }

    // Check for SUPPRESS_ALL_EXCEPT_SNIPER_VIEW message
    if (messageId == DAT_01130240 && ((flags >> 0x13 & 1) == 0)) {
        flags |= 0x80000; // set bit 19
        *(uint*)(this + 0x0C) = flags;
        FUN_005a04a0("SuppressAllExceptSniperView", 0, &DAT_00d8a64c, 0); // debug command
        FUN_0093dac0(); // enterSniperView
        return;
    }

    // Check for UNSUPPRESS_ALL message
    if (messageId == DAT_01130348 && ((flags >> 0x13 & 1) != 0)) {
        flags &= 0xfff7ffff; // clear bit 19
        *(uint*)(this + 0x0C) = flags;
        FUN_005a04a0("UnSuppressAll", 0, &DAT_00d8a64c, 0); // debug command
        FUN_0093de90(); // exitSniperView
        return;
    }

    // Check for some other message that sets bit 21 (0x200000)
    if (messageId == DAT_011301d0) {
        flags |= 0x200000; // set bit 21
        *(uint*)(this + 0x0C) = flags;
        return;
    }

    // Check for clear bit 21 message
    if (messageId == DAT_01130498) {
        flags &= 0xffdfffff; // clear bit 21
        *(uint*)(this + 0x0C) = flags;
        return;
    }

    // Remaining two message types (DAT_0112a5a4 and DAT_01130248)
    if (messageId == DAT_0112a5a4) {
        // Check if the entity ID matches one stored at this+0xEC
        int entityId = *(int*)(*(int*)(messageData[1] + 4) + 0x38); // +0x38 offset for entityId in some struct
        if (entityId != *(int*)(this + 0xEC)) {
            return;
        }
    } else if (messageId != DAT_01130248) {
        return; // unknown message, ignore
    }

    // For these two messages, if bit 12 is set, clear some state
    if ((*(uint*)(this + 0x0C) >> 0xC & 1) != 0) {
        *(int*)(this + 0x120) = 0; // clear some pointer or value
    }
}