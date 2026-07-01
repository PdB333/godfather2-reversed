// FUNC_NAME: Sentient::isAliveAndHasTarget
// Address: 0x00819260
// Checks if the sentient is alive (state != dead, state != 0) and has a target pointer.
int __thiscall Sentient::isAliveAndHasTarget(int thisPtr) {
    // +0x7C: current state (e.g., kState_Dead = 0x48)
    // +0x84: current target entity pointer (non-null means has target)
    int state = *(int *)(thisPtr + 0x7C);
    int target = *(int *)(thisPtr + 0x84);
    if (state != 0 && state != 0x48 && target != 0) {
        return 1;
    }
    return 0;
}