// FUNC_NAME: Animated::setAnimState
void __thiscall Animated::setAnimState(int this, int newState, char skipEvent) // param_3 = bool skipEvent?
{
    int oldState; // iVar3, iVar1 reused
    int iVar2;
    float duration;
    // +0x16c: current animation state
    // +0x170: state duration (float)
    // +0x34: flags (bit 0x120000 = frozen? bit 0x1 = active?)
    // +0x40: owner pointer (e.g., Entity)
    // +0xd4: event handler pointer
    // +0x100: some override pointer
    // +0x38: animation data pointer

    oldState = *(int *)(this + 0x16c);
    // Check if the entity is not frozen/inactive and has an owner that is valid
    if ((((*(uint *)(this + 0x34) & 0x120000) == 0) && ((*(byte *)(this + 0x34) & 1) == 0)) &&
        (*(int *)(this + 0x40) != 0)) {
        iVar2 = getOwnerComponent(*(int *)(this + 0x40)); // FUN_008c74d0
        if ((iVar2 == 0) || ((~(byte)(*(uint *)(iVar2 + 0x84) >> 5) & 1) == 0)) goto condition_met;
    }
    else {
condition_met:
        oldState = 1; // Mark that a condition forced a state?
    }

    int currentState = *(int *)(this + 0x16c);
    if (currentState != newState) {
        *(int *)(this + 0x16c) = newState;
        duration = (float)getStateDuration(newState); // FUN_006b20f0 returns 10-byte real
        *(float *)(this + 0x170) = duration;
        if (newState == 0) {
            // Stop animation: clear flags (0x120000 bits) and call stop handlers
            *(uint *)(this + 0x34) = *(uint *)(this + 0x34) & 0xfff5ffff; // Clear 0xA0000 bits
            stopAnimation(); // FUN_006b24d0
            *(uint *)(this + 0x34) = *(uint *)(this + 0x34) & 0xffbfffff; // Clear 0x400000 bit
            clearAnimationOverrides(*(undefined4 *)(this + 0x38)); // FUN_008b7b70
            // Copy override from global manager if exists
            if (*(int *)(DAT_0112a668 + 0x18) != 0) {
                *(undefined4 *)(this + 0x100) = *(undefined4 *)(*(int *)(DAT_0112a668 + 0x18) + 0xc0);
            }
        }
        else if (currentState == 0) {
            // Start animation from stopped
            startAnimation(); // FUN_006b2540
        }
        updateAnimation(); // FUN_006b2f70
    }

    // Re-evaluate condition after state change
    iVar2 = *(int *)(this + 0x16c);
    if ((((*(uint *)(this + 0x34) & 0x120000) == 0) && ((*(byte *)(this + 0x34) & 1) == 0)) &&
        (*(int *)(this + 0x40) != 0)) {
        int comp = getOwnerComponent(*(int *)(this + 0x40)); // FUN_008c74d0
        if ((comp != 0) && ((~(byte)(*(uint *)(comp + 0x84) >> 5) & 1) != 0)) goto afterCheck;
    }
    iVar2 = 1;
afterCheck:
    if ((iVar2 != oldState) && (skipEvent == '\0')) {
        // Build event for state change notification
        void *eventData[3]; // local_10, local_c, local_8, local_4
        eventData[1] = (void *)(&staticStateChangeTable); // &PTR_LAB_00d5e234
        eventData[2] = (void *)this;
        eventData[0] = (void *)oldState; // iVar3
        // Note: local_4 = iVar1, but it's not in array? Actually decompiled has local_10, local_c, local_8, local_4
        // We'll adjust: eventData[3] = (void*)iVar2; but decompiled shows local_4 is iVar1

        if (*(int *)(this + 0xd4) != 0) {
            sendEventToHandler(DAT_0112a600, *(int *)(this + 0xd4) + 0x3c, &eventData, 0); // FUN_00408bb0
        }
        processEvents(&DAT_0112a600, 0); // FUN_00408a00, local_1c = DAT_0112a600, local_14 = 0
        // Check global flag array for newState
        if (*(char *)(iVar2 * 0x10 + 0xe50d11) != '\0') {
            callGlobalFunction(); // FUN_008c7330
        }
    }
    return;
}