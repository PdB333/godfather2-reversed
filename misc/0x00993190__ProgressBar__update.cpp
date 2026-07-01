// FUNC_NAME: ProgressBar::update
void __thiscall ProgressBar::update(int this) {
    float fVar1;
    float local_10;
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;

    // +0x50: timerCount (remaining time in arbitrary units)
    if (*(int *)(this + 0x50) != 0) {
        // Timer still running: decrement and update bar
        *(int *)(this + 0x50) = *(int *)(this + 0x50) + -1;
        FUN_005a04a0("SetBar", 0, &DAT_00d921ec, 0);
        fVar1 = (float)*(int *)(this + 0x50);
        // Negative adjustment (likely for float conversion, constant is 0.0f)
        if (*(int *)(this + 0x50) < 0) {
            fVar1 = fVar1 + *(float*)&DAT_00e44578;
        }
        // Compute bar value: progress = timer * scale1 * scale2 + baseOffset
        local_10 = fVar1 * *(float*)&DAT_00e576b8 * *(float*)&DAT_00d58cbc + *(float*)&DAT_00d92140;
        fVar1 = *(float*)&DAT_00d9213c;
        // Clamp between min and max bar value
        if ((local_10 < *(float*)&DAT_00d9213c) || (fVar1 = *(float*)&DAT_00d92140, *(float*)&DAT_00d92140 < local_10)) {
            local_10 = fVar1;
        }
        // Set bar visual progress (float)
        FUN_0090cec0(local_10);
        // Set bar color/state
        local_c = *(undefined4*)&DAT_011304d8;
        local_8 = 0;
        local_4 = 0;
        FUN_00408a00(&local_c, 0);
        return;
    }
    // Timer expired: trigger flash effect
    FUN_005a04a0("FlashBar", 0, &DAT_00d921ec, 0);
    local_c = *(undefined4*)&DAT_011302c0;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0);
    return;
}