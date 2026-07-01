// FUNC_NAME: NPC::setFocusTarget
void __thiscall NPC::setFocusTarget(int this, int newTarget) {
    // this + 0x1bc8: pointer to a pointer to the current target (double indirection, likely a handle/pointer-to-pointer)
    // this + 0x1bc4: target handle or identifier used in the attach function
    // Checking if the resolved current target differs from the new one
    if (**(int **)(this + 0x1bc8) != newTarget) {
        // If we already had a target, detach/clear it first
        if (*(int **)(this + 0x1bc8) != (int *)0x0) {
            // FUN_007f0740: internal attach/detach function; arguments: handle, newTarget, flags (0=detach?, 1=immediate?)
            FUN_007f0740(*(undefined4 *)(this + 0x1bc4), newTarget, 0, 1);
        }
        // Fetch current time/tick values for tracking
        // FUN_007ef4a0 likely returns current game time (float seconds)
        float currentTime = (float)FUN_007ef4a0();
        *(float *)(this + 0x724) = currentTime;
        // FUN_007ef4b0 likely returns a related timestamp (maybe delta or another clock)
        float anotherTime = (float)FUN_007ef4b0();
        *(float *)(this + 0x730) = anotherTime;
        // Update internal state after target change
        FUN_007f5690();
    }
}