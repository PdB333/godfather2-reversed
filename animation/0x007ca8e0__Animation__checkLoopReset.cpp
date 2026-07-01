//FUNC_NAME: Animation::checkLoopReset
bool __thiscall Animation::checkLoopReset(float currentTime) {
    int state = *(int *)(this + 8);          // +0x8: animation state (0=stopped, 3=playing, 4=looping?)
    bool result = false;

    // Condition 1: Reset if state is 0 or 4, or if loopCounter2 > 5, and loopCounter1 > 3
    if (((state == 4 || state == 0) || (*(int *)(this + 0x1c) > 5)) &&
        (*(uint *)(this + 0x10) > 3)) {
        result = true;
        *(uint *)(this + 0x10) = 0;   // +0x10: loopCounter1
        *(int *)(this + 0x1c) = 0;    // +0x1c: loopCounter2
        *(int *)(this + 0x18) = 0;    // +0x18: timer
    }

    // Condition 2: Reset if state is 3, or if flag is false and (time threshold exceeded or loopCounter1 > 3)
    if ((state == 3) ||
        ((*(char *)(this + 0xc) == 0) &&   // +0xc: flag (e.g., isPaused)
         ((g_timeThreshold < currentTime || (*(uint *)(this + 0x10) > 3))))) {
        result = true;
        *(uint *)(this + 0x10) = 0;
        *(int *)(this + 0x1c) = 0;
        *(int *)(this + 0x18) = 0;
    }

    return result;
}