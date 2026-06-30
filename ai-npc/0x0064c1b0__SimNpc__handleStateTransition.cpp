// FUNC_NAME: SimNpc::handleStateTransition
// This function likely handles a state transition or resource release for an NPC or sentient object.
// It compares a computed float value with a member float at +0x8 (possibly a threshold or timer).
// The global constants DAT_00e2b1a4 and DAT_00e44680 are likely masks or parameters.
// The callees are assumed to be release/free helpers.

void SimNpc::handleStateTransition(uint param3, uint param2) {
    // param3 is likely an index or ID; param2 may be a pointer to another object.
    // this+0x8 is a float (threshold or timer value)
    float memberVal = *(float*)((int)this + 8);

    // Compute condition: globalConstant - globalConstant / (param3 & 0xFF) <= (memberVal & mask)
    // This is likely a comparison to determine if a state should change.
    uint condition = (DAT_00e2b1a4 - DAT_00e2b1a4 / (float)(param3 & 0xFF)) <=
                     (float)(*(uint*)((int)this + 8) & DAT_00e44680);

    // FUN_0064bb50 appears to return some status based on condition.
    uint status = FUN_0064bb50(condition);

    if ((char)status == 0) {
        // If low byte is zero, release param3 and param2, then free param2.
        FUN_0064be30(param3);
        FUN_00b9a9fa(param2);
        FUN_0064be30(param2);
        return;
    }

    // Otherwise, extract the high byte of status.
    uint highByte = (status >> 8) & 0xFF;

    if (memberVal <= 0.0f && memberVal != 0.0f) {
        // If memberVal is negative (or zero? Actually <=0 and !=0 means negative)
        // Then call FUN_0064bb50 with highByte OR'd with 1.
        FUN_0064bb50((highByte << 8) | 1);
        return;
    }

    // Otherwise call FUN_0064bb50 with highByte shifted left (low byte zero).
    FUN_0064bb50(highByte << 8);
}