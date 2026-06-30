// FUNC_NAME: ActionOptions::isActionAvailable
// Function address: 0x00741ff0
// Role: Checks availability of a given action type (10, 11, 12) based on internal state and global conditions.
// Likely part of the action system controlling what actions the player or AI can perform.

uint __thiscall ActionOptions::isActionAvailable(int this, undefined4 param_2, undefined4 param_3, int actionType, undefined4 param_5)
{
    byte bVar1;
    char cVar2;
    uint uVar3;

    bVar1 = 0;
    if (actionType == 10) {
        // Check bit 0 of flags at offset +0x60
        if ((*(byte *)(this + 0x60) & 1) != 0) {
            // Check if bit 10 of value at (this+0x50)->+0x8e4 is clear
            if ((*(uint *)(*(int *)(this + 0x50) + 0x8e4) >> 10 & 1) == 0) {
                bVar1 = 1;  // Action allowed
            }
            else if (*(int *)(this + 0x48) == 0) {
                // If property at +0x48 is zero, use random/skill check
                bVar1 = FUN_0045f120(); // Possibly random success check
            }
            else {
                // Otherwise, also use random/skill check
                bVar1 = FUN_0045f120();
            }
        }
        // Check global game state (maybe paused or in cutscene?)
        cVar2 = FUN_007f8f10();
        uVar3 = 1;
        if (cVar2 == '\0') {
            uVar3 = (uint)bVar1;
        }
        return uVar3;
    }
    if (actionType != 0xb) {
        if (actionType != 0xc) {
            // Fallback to generic handler
            uVar3 = FUN_004ac640(param_2, param_3, actionType, param_5);
            return uVar3;
        }
        // Case 12: return bit 1 of value at (this+0x5c)->+0x4c
        return *(uint *)(*(int *)(this + 0x5c) + 0x4c) >> 1 & 1;
    }
    // Case 11: compare global float with this+0x30
    if (_DAT_00d5780c < *(float *)(this + 0x30)) {
        return 1;
    }
    return 0;
}