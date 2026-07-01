// FUNC_NAME: GameTimer::GameTimer
undefined4 * __thiscall GameTimer::GameTimer(GameTimer *this, const GameTimerInput *inputData) {
    this->vtable = &PTR_FUN_00d6efa0; // VTable for GameTimer class

    // Copy input data (64-bit start time + 32-bit duration)
    // offset +0x04: startTime (uint64)
    this->startTime.low = inputData->startTime.low;
    this->startTime.high = inputData->startTime.high;
    // offset +0x0C: duration (uint32)
    this->duration = inputData->duration;
    // offset +0x10: reserved constant (likely sentinel or default)
    this->reserved16 = DAT_00d6ef9c;

    // Zero all timer state fields from +0x20 to +0x38 (7 uint32)
    // +0x20: elapsedTime? / +0x24: timeRemaining? / +0x28: loopCount? etc.
    this->field_20 = 0;
    this->field_24 = 0;
    this->field_28 = 0;
    this->field_2C = 0;
    this->field_30 = 0;
    this->field_34 = 0;
    this->field_38 = 0;

    // Duplicate start time and duration into a "working copy" region
    // offset +0x14: currentStartTime (uint64)
    this->currentStartTime.low = this->startTime.low;
    this->currentStartTime.high = this->startTime.high;
    // offset +0x1C: currentDuration (uint32)
    this->currentDuration = this->duration;

    // Adjust the high part of currentStartTime by a float offset (likely time scale or base)
    this->currentStartTime.high += DAT_00e445ac; // global float offset

    // Check if a global condition enables immediate start
    if (FUN_0078e110() != 0) {
        if (FUN_0078da20(1) != 0) {
            // Flag at +0x20 indicates the timer is active/running
            this->isActive = 1;
        }
    }

    return this;
}