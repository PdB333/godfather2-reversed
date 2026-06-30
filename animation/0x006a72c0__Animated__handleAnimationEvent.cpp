// FUNC_NAME: Animated::handleAnimationEvent
void __thiscall Animated::handleAnimationEvent(int this, int *eventPtr) {
    char cVar1;
    int result;
    int localAnimationIndex;

    localAnimationIndex = this;
    if (*eventPtr == *(int *)(this + 0x14)) {
        // Check if any of the four slot pointers are non-null
        if (((((*(int *)(this + 0x24) != 0) ||
               (*(int *)(this + 0x28) != 0)) ||
              (*(int *)(this + 0x2c) != 0)) ||
             (*(int *)(this + 0x30) != 0)) &&
            ((*(int *)(this + 0x34) == 0 || (*(int *)(this + 0x34) == 0x48)))) {
            // Clear low byte of event ID to get animation group (??)
            eventPtr = (int *)((uint)eventPtr & 0xffffff00);
            result = FUN_00448100(this + 0x24, &eventPtr); // Look up animation by group
            if (result != 0) {
                localAnimationIndex = 0;
                // Check if animation with hash 0x2e5f1298 exists
                cVar1 = FUN_006a4e80(result, 0x2e5f1298, &localAnimationIndex);
                if (cVar1 != '\0') {
                    // Play that animation
                    FUN_006a4e40(localAnimationIndex);
                }
            }
        }
        // Transition to next state if current state is non-zero and not "idle" (0x48)
        eventPtr = (int *)(this + 0x34);
        if ((*(int *)(this + 0x34) != 0) && (*(int *)(this + 0x34) != 0x48)) {
            FUN_006a55a0();
            return;
        }
    }
    else if (*eventPtr == *(int *)(this + 0x1c)) {
        // Alternative event match
        eventPtr = (int *)(this + 0x34);
        if ((*(int *)(this + 0x34) != 0) && (*(int *)(this + 0x34) != 0x48)) {
            FUN_006a55f0();
            return;
        }
    }
    return;
}