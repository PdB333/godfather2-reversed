// FUNC_NAME: Entity::updateState
void __fastcall Entity::updateState(int thisPtr)
{
    int field4;                // +0x4
    int field8;                // +0x8
    char isPaused;             // result of global check
    int tempVar;
    undefined4 local68[3];     // temporary vector?
    undefined local50[12];     // unknown
    undefined4 local44;        // zeroed
    undefined4 local34;        // zeroed
    float local30, local2c, local28; // after call, likely velocity or delta
    undefined4 local24;        // zeroed
    undefined4 local14;        // initialized from global _DAT_00d5780c

    field4 = *(int *)(thisPtr + 4);
    isPaused = FUN_00481640(); // 0x00481640: global pause check?
    if (isPaused != 0) {
        FUN_00799230(); // 0x00799230: possible update skip or sound pause
        return;
    }

    field8 = *(int *)(thisPtr + 8);
    if ((field8 != 0) && (field8 != 0x48)) { // 0x48 = 72, maybe state flag
        // If state is active and not a specific state (e.g., 0x48 = dead/disabled)
        if (field8 != 0) { // redundant, but kept as per decompiler
            tempVar = FUN_00471610(); // 0x00471610: some object function?
            FUN_00799270(tempVar + 0x30); // 0x00799270: set position?
        } else {
            tempVar = FUN_00471610();
            FUN_00799270(tempVar + 0x30);
        }
        return;
    }

    // Default path: state is 0 or 0x48 (inactive/dormant)
    local44 = 0;
    local34 = 0;
    local24 = 0;
    local14 = _DAT_00d5780c; // global initializer

    // Build something using array at DAT_00002494 indexed by field4
    FUN_00425060(&local68, *(undefined4 *)(&DAT_00002494 + field4)); // 0x00425060: copy/math?
    FUN_0056b8a0(local64, local68, local60, local50); // 0x0056b8a0: transform?

    tempVar = FUN_00471610(); // 0x00471610: repeated call
    // Compute new position using global scale factor
    local5c = local30 * DAT_00d6ee48 + *(float *)(tempVar + 0x30);
    local58 = local2c * DAT_00d6ee48 + *(float *)(tempVar + 0x34);
    local54 = local28 * DAT_00d6ee48 + *(float *)(tempVar + 0x38);

    FUN_00799270(&local5c); // 0x00799270: set position or update
    return;
}