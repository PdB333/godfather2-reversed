// FUNC_NAME: StateMachine::advanceTimer
int StateMachine::advanceTimer(StateData* timerData) {
    // timerData: [state, timer, _, startTime, endTime] at offsets +0, +4, +8, +0xC, +0x10
    // this (ESI) has fields at +0x28 (some speed/rate) and +0x34 (some max timer bound)

    // Check if startTime equals endTime (meaning the timer range is zero)
    if (timerData->startTime == timerData->endTime) {
        FUN_00642b00(); // likely internal state update
        goto LAB_00643004;
    }

    FUN_00642b00();

    if (timerData->state == 11) { // 0xB = kStateExit or kStateIdle
        if (timerData->startTime == timerData->endTime)
            goto LAB_00643004;
        if (this->field_0x34 <= timerData->timer) {
            FUN_00642d90(timerData->timer); // clamp or notify timer overflow
            goto LAB_00643004;
        }
    }

    FUN_00642ec0(); // finalize timer processing

LAB_00643004:
    if (timerData->state == 1) { // kStateEnterTransition
        if (this->field_0x28 + 250 < 512) { // 0xFA + 0x28, threshold check
            int newTimer = FUN_00642a90(); // compute new timer from rate
            timerData->timer = newTimer;
            timerData->state = 4; // transition to kStateActive
            return newTimer + 250; // return adjusted timer value
        }
    } else if (timerData->state == 4 && timerData->timer + 250 < 512) {
        return timerData->timer + 250;
    }

    // Fallback: re-evaluate state 11
    FUN_00642b00();
    if (timerData->state == 11) {
        int t = timerData->timer;
        if (timerData->startTime == timerData->endTime)
            return t;
        if (this->field_0x34 <= t) {
            FUN_00642d90(t);
            return timerData->timer;
        }
    }

    FUN_00642ec0();
    return timerData->timer;
}