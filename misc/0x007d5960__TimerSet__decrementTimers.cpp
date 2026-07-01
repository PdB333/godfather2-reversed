// FUNC_NAME: TimerSet::decrementTimers

void __thiscall TimerSet::decrementTimers(float deltaTime) {
    // this + 0x74: pointer to timer data array
    // Timer block starts at + 0x38 from that pointer, contains 2 groups of 4 floats (timers)
    float* timerBlock = *(float**)(this + 0x74) + 0x0E; // +0x38 / sizeof(float) = 0x0E floats offset
    int groupCount = 2;
    do {
        // First timer in group (offset -1 from block start? Actually pfVar1 starts at +0x38, so pfVar1[-1] = +0x34)
        if (timerBlock[-1] > 0.0f) {
            timerBlock[-1] = max(timerBlock[-1] - deltaTime, 0.0f);
        }
        // Second timer
        if (timerBlock[0] > 0.0f) {
            timerBlock[0] = max(timerBlock[0] - deltaTime, 0.0f);
        }
        // Third timer
        if (timerBlock[1] > 0.0f) {
            timerBlock[1] = max(timerBlock[1] - deltaTime, 0.0f);
        }
        // Fourth timer
        if (timerBlock[2] > 0.0f) {
            timerBlock[2] = max(timerBlock[2] - deltaTime, 0.0f);
        }
        timerBlock += 4; // Advance to next group of 4 timers
        groupCount--;
    } while (groupCount != 0);
}