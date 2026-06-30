// FUNC_NAME: BehaviorComponent::executeAction

void __thiscall BehaviorComponent::executeAction(int thisPtr, int arg)
{
    BehaviorData* behaviorObj;
    float scaleX;
    float scaleY;

    // Flag at +0x98: is this behavior active?
    if (*(bool*)(thisPtr + 0x98) != false) {
        behaviorObj = *(BehaviorData**)(thisPtr + 0x24);  // +0x24: pointer to behavior data structure
        switch (*(uint8_t*)(behaviorObj + 0x10)) {        // +0x10: action type byte
        case 0:
            // Idle / stand action
            FUN_004eec40();                                // e.g., playIdleAnimation
            return;
        case 1:
            // Talk / speech action
            FUN_0040aee0(*(int*)(behaviorObj + 0x4c));     // e.g., startDialog
            return;
        case 2:
            // Move to position action
            FUN_005149c0(arg, 
                         thisPtr + 0x30,                   // +0x30: start position (maybe vec3)
                         thisPtr + 0x40,                   // +0x40: target position
                         thisPtr + 0x60,                   // +0x60: some vector
                         *(int*)(thisPtr + 0x3c),         // +0x3c: speed?
                         *(int*)(thisPtr + 0x4c));         // +0x4c: animation flag?
            return;
        case 4:
            // Use / interact action
            FUN_005172c0(arg,
                         *(int*)(thisPtr + 0x88),          // +0x88: interaction target
                         *(int*)(behaviorObj + 0x40),      // +0x40: duration?
                         *(int*)(thisPtr + 0x84),          // +0x84: animation ID
                         *(int*)(thisPtr + 0x8c),          // +0x8c: effect attachment
                         thisPtr + 0x70,                   // +0x70: offset / position
                         *(int*)(behaviorObj + 0x44),      // +0x44: ?
                         *(int*)(behaviorObj + 0x48),      // +0x48: ?
                         *(int*)(behaviorObj + 0x14));     // +0x14: action data ID?
            return;
        case 5:
            // Die / death action
            FUN_004ef1d0(1);                               // param 1 = immediate? or force?
            return;
        case 6:
            // Play animation action
            FUN_004e69c0(thisPtr + 0x30);                  // +0x30: animation data?
            return;
        case 7:
            // Wait / pause action
            if (*(int*)(thisPtr + 0x28) != 0) {           // +0x28: wait condition flag
                FUN_004e6b30();                            // e.g., handle wait
                return;
            }
            break;
        case 8:
            // Show / hide item action
            FUN_004e44c0(*(int*)(thisPtr + 0x58),         // +0x58: item ID?
                         *(int*)(thisPtr + 0x54));         // +0x54: visible flag?
            return;
        case 10:
            // Attach object action
            FUN_004e4400(*(int*)(thisPtr + 0x54),         // +0x54: object?
                         *(int*)(thisPtr + 0x58));         // +0x58: bone?
            return;
        case 11:
            // Scale / grow action (or size change)
            scaleX = *(float*)(behaviorObj + 0x40);
            if (scaleX == 0.0f) {
                scaleX = DEFAULT_SCALE;                    // Address 0x00e2b04c, likely 1.0f
            }
            scaleY = *(float*)(behaviorObj + 0x44);
            if (scaleY == 0.0f) {
                scaleY = DEFAULT_SCALE;
            }
            FUN_0052e450(thisPtr + 0x80,                  // +0x80: scale target (e.g., transform)
                         *(int*)(thisPtr + 0x28),         // +0x28: actor handle?
                         scaleX,
                         scaleY);
            return;
        case 13:
            // Unlock / open action
            FUN_004e4550();                                // e.g., unlockDoor
            return;
        case 14:
            // Spawn particle / effect action
            FUN_004e4690(*(int*)(thisPtr + 0x84),         // +0x84: effect type
                         *(int*)(thisPtr + 0x8c));         // +0x8c: position/offset
            return;
        case 15:
            // Play sound action
            FUN_004e4860(thisPtr + 0x30,                  // +0x30: sound channel?
                         *(int*)(thisPtr + 0x84),         // +0x84: sound ID
                         *(int*)(thisPtr + 0x8c));         // +0x8c: pitch/volume?
            return;
        case 16:
            // Cancel / abort action
            FUN_004e4930();                                // e.g., abortCurrentAction
            // Fall through (no return)
        }
    }
    return;
}