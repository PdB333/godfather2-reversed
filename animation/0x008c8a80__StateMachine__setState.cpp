// FUNC_NAME: StateMachine::setState
void __thiscall StateMachine::setState(int thisPtr, int newState)
{
    // +0x18: pointer to physics/character body (e.g., havok character proxy)
    int* bodyPtr = *(int**)(thisPtr + 0x18);
    if (bodyPtr != 0) {
        int* physicsBody = (int*)FUN_006b0ee0((int)bodyPtr);
        if (physicsBody != 0) {
            // +0xFC: some flag indicating physics is active
            if (*(int*)(physicsBody + 0xfc) != 0) {
                FUN_006bebd0(*(int*)(thisPtr + 8));
                FUN_006bebf0(*(int*)(thisPtr + 8));
            }
            FUN_006b3c40(*(int*)(thisPtr + 8));
            FUN_006b3c60(*(int*)(thisPtr + 8));
        }
        *(int**)(thisPtr + 0x18) = 0;
        FUN_00790d30(0);
        // +0x10: pointer to state-specific data (e.g., player state info)
        int* stateData = *(int**)(thisPtr + 0x10);
        if (stateData != 0) {
            // +0x58: flag indicating whether to use enter or exit handler
            if (*(int*)(stateData + 0x58) == 0) {
                FUN_008feb40();
            } else {
                FUN_008febb0();
            }
        }
    }

    int oldState = *(int*)(thisPtr + 4); // +0x4: current state
    if (oldState != newState) {
        float* timerField = (float*)(thisPtr + 0x14); // +0x14: state timer or multiplier
        if (newState == 6) {
            // +0x0C: pointer to a data block, +0x17C: a speed/factor value
            float factor = *(float*)(*(int*)(thisPtr + 0x0C) + 0x17C);
            if (factor > 0.0f) {
                *timerField = factor * (*timerField);
            }
        } else {
            *timerField = 0.0f;
        }
        FUN_008c83b0(oldState, newState, 0); // notify state transition
        *(int*)(thisPtr + 4) = newState;
    }
    return;
}