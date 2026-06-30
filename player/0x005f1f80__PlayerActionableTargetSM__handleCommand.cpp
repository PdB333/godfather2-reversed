// FUNC_NAME: PlayerActionableTargetSM::handleCommand

// Reconstructed from Ghidra decompilation of 0x005f1f80
// Role: Process an action command for the player's actionable target state machine

int __thiscall PlayerActionableTargetSM::handleCommand(PlayerActionableTargetSM* thisPtr, Command* cmd) {
    bool bIsCrouch;   // bVar6
    bool bIsRun;      // bVar5
    float threshold = DAT_00e44598; // Global threshold for distance/speed

    if (cmd == nullptr) {
        return 0; // Invalid command
    }

    // Check current state (thisPtr->state at +0x68)
    int currentState = thisPtr->state;
    
    // Determine if crouching state (state 5) or (state 4 with certain flag)
    if (currentState == 5) {
        bIsCrouch = true;
    } else if (currentState == 4) {
        byte flags = *(byte*)(*(int*)(cmd->target + 4) + 8); // target flags
        bIsCrouch = (flags & 0x40) != 0;
    } else {
        bIsCrouch = false;
    }

    // Determine if running state (state 2) or (state 4 without that flag)
    if (currentState == 2) {
        bIsRun = true;
    } else if (currentState == 4) {
        byte flags = *(byte*)(*(int*)(cmd->target + 4) + 8); // target flags
        bIsRun = (flags & 0x40) == 0;
    } else {
        bIsRun = false;
    }

    float value = cmd->floatValue; // +0x8
    thisPtr->storedValue = value;  // +0x50

    if (bIsCrouch) {
        return 1; // Already in desired state
    }

    if (threshold >= value) {
        // Value below threshold, continue
        // Try to find a new target based on cmd and value
        if (thisPtr != nullptr || (thisPtr = CAST(PlayerActionableTargetSM*, FUN_005f1df0(cmd->target + 4, value)) != nullptr)) {
            // Set action bit for command flags
            byte actionFlags = cmd->byteFlags; // +0xf
            thisPtr->flagByte ^= (thisPtr->flagByte ^ ((cmd->packedInput >> 7) * 2)) & 0x2; // +0x7b
            FUN_005f2150(actionFlags); // Play animation or start action
            return 1;
        }
    }

    // If target has the "ignore" flag (0x20)
    byte targetFlags = *(byte*)(*(int*)(cmd->target + 4) + 8);
    if ((targetFlags & 0x20) != 0) {
        FUN_005e4cf0(); // Cancel current action
        return 1;
    }

    // If running state and not crouching, transition to a new state
    if (thisPtr != nullptr && bIsRun) {
        int oldState = thisPtr->state;
        FUN_005f2230(1); // Prepare state transition
        if (oldState != 4) {
            thisPtr->state = 3; // Set new state
            return 1;
        }
    }

    return 1; // Default success
}

// Assumed structure for Command (4 bytes aligned, size unknown)
struct Command {
    // +0x0 : unknown/unused in this function?
    // +0x4 : pointer to another structure (target) with byte flags at +0x8
    // +0x8 : floatValue (speed/distance)
    // +0xc : packedInput (ushort, bits for control)
    // +0xf : byteFlags (action type)
};