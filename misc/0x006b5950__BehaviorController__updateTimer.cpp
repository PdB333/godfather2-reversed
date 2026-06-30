// FUNC_NAME: BehaviorController::updateTimer
void __thiscall BehaviorController::updateTimer(int this) {
    float fVar1;

    // Check conditions: no active state at +0x16c and +0xfc, bit 29 of flags at +0x34 is clear,
    // and either pointer at +0x74 or +0x6c is non-null.
    if ((*(int *)(this + 0x16c) == 0) &&
        (*(int *)(this + 0xfc) == 0) &&
        ((*(uint *)(this + 0x34) >> 0x1d & 1) == 0) &&
        (*(int *)(this + 0x74) != 0 || *(int *)(this + 0x6c) != 0)) {

        // Increment timer at +0x7c by global delta time (DAT_012067e8)
        fVar1 = *(float *)(this + 0x7c) + DAT_012067e8;
        *(float *)(this + 0x7c) = fVar1;

        // If timer exceeds threshold at +0x80 and is not exactly equal
        if (*(float *)(this + 0x80) <= fVar1 && fVar1 != *(float *)(this + 0x80)) {
            // Reset timer
            *(float *)(this + 0x7c) = 0.0f;

            // If pointer at +0x74 is non-null, trigger a specific action
            if (*(int *)(this + 0x74) != 0) {
                FUN_006b3b10(1);
                FUN_006b4da0();
                return;
            }

            // Otherwise, check counters at +0x68, +0x58, +0x60, +0x5c
            if ((*(int *)(this + 0x68) == *(int *)(this + 0x58)) &&
                (*(uint *)(this + 0x60) <= *(uint *)(this + 0x5c))) {
                FUN_006b3b40(1);
                FUN_008c7890(*(int *)(this + 0x40), 1);
            }
        }
    }
}