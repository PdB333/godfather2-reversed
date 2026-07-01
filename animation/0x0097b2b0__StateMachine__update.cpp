// FUNC_NAME: StateMachine::update
int __fastcall StateMachine::update(int thisPtr)
{
    // +0x138: m_activeCount (number of active states or priority)
    if (*(int *)(thisPtr + 0x138) > 0) {
        return 1; // Already active, skip
    }

    // +0x150: m_timeout (timer threshold)
    if (*(int *)(thisPtr + 0x150) == 0) {
        *(int *)(thisPtr + 0x14c) = 0; // +0x14c: m_elapsedTime
        return 1;
    }

    // Get current time (likely milliseconds or game ticks)
    uint currentTime = getCurrentTime(); // FUN_00494d10
    if (currentTime < *(uint *)(thisPtr + 0x150)) {
        return 0; // Time not yet reached, return false
    }

    // +0x144: m_currentState, +0x13c: m_targetState
    if (*(int *)(thisPtr + 0x144) == *(int *)(thisPtr + 0x13c)) {
        // States match: handle idle/complete
        // +0x60: m_flags (bit 6 = 0x40)
        if ((*(uint *)(thisPtr + 0x60) >> 6 & 1) == 0) {
            // Schedule a callback (e.g., animation event) with label at 0x0097ab70
            scheduleCallback(thisPtr + 0x14, &LAB_0097ab70, 0); // FUN_005c0d50
        }

        // Check additional conditions (e.g., input, environment)
        bool cond1 = checkCondition1(); // FUN_00977390
        bool cond2 = checkCondition2(); // FUN_00977360
        if (cond1 || cond2) {
            executeAction(); // FUN_00979890
        }

        // Schedule next update callback (function at 0x00977610)
        scheduleCallback(thisPtr + 0x14, &FUN_00977610, 0); // FUN_005c0d50
        return 1;
    }

    // States differ: perform transition
    transitionToNextState(); // FUN_0097b230
    return 1;
}