// FUNC_NAME: CharacterAI::updateMovementAndAttack
void __thiscall CharacterAI::updateMovementAndAttack(int remainingActions, int targetHandle, unsigned int* outActionId) {
    int* pState;
    int delta;
    int steps;
    int prevSteps;
    unsigned int actionId;
    float timeStep;
    float factor;
    float floatVar1;
    float floatVar2;
    float floatVar3;
    float floatVar4;
    float floatVar5;
    float floatVar6;

    // Acquire a reference if not already held
    if ((this->m_resourceHandle == 0) && (*(int*)(*(int*)(this + 4) + 0x20) != 0)) {
        pState = *(int**)(*(int*)(this + 4) + 0x20);
        if (pState != 0) {
            pState[1] = pState[1] + 1; // Increment reference count
        }
        pState = (int*)FUN_00513f70(pState);
        if (pState != 0) {
            this->m_resourceHandle = pState[0x24 / 4];   // +0x24
            this->m_resourceHandle2 = pState[0x28 / 4]; // +0x28
        }
        if ((this->m_resourceHandle != 0) && (this->m_resourceHandle != 0)) {
            // Some global increment; using FS segment
            // *(int*)(*(int*)(__readfsdword(0x2c) + 8) + 0x30 + this->m_resourceHandle) += 1;
        }
    }

    timeStep = *(float*)(this->m_pEntityState + 0xac);
    floatVar1 = 0.0f;
    if (timeStep < 0.0f) {
        if ((*(uint8_t*)(this + 0x2c) & 0x10) != 0) {
            return;
        }
        timeStep = 0.0f;
    }

    // If entity has a specific flag, apply acceleration
    if ((*(uint32_t*)(this->m_pEntityState + 0x108) & 0x40000) != 0) {
        FUN_004e41b0(); // maybe get delta time?
        floatVar1 = (floatVar1 + *(float*)(this->m_pEntityState + 0xbc)) * timeStep;
        timeStep = floatVar1;
    }

    int entityStatePtr = this->m_pEntityState;
    FUN_004e41b0();
    float maxFactor = DAT_00e2b1a4; // likely 1.0f

    // Accumulate fractional movement
    floatVar4 = *(float*)(this + 0x40) + floatVar1 * (float)(int)*(int16_t*)(entityStatePtr + 0x126) + (float)(int)*(int16_t*)(entityStatePtr + 0x124);
    steps = (int)floatVar4;
    floatVar5 = (float)steps;
    floatVar1 = floatVar4 - floatVar5;
    *(float*)(this + 0x40) = floatVar1; // Store fractional part

    // Apply optional smoothing/damping
    if (((*(uint32_t*)(entityStatePtr + 0x10c) & 0x20000000) == 0) && (steps != 0)) {
        FUN_00534350(); // some check
        if (floatVar1 < maxFactor) {
            floatVar2 = floatVar1 * floatVar4;
            if (floatVar2 < maxFactor) {
                floatVar2 = maxFactor;
            }
            prevSteps = (int)floatVar2;
            timeStep = ((((float)prevSteps * DAT_00e448a4) / floatVar5) * (maxFactor - floatVar1) + maxFactor) * timeStep;
        }
    }

    // Distance-based damping
    if ((*(float*)(entityStatePtr + 0xc0) != 0.0f) && (*(float*)(this + 0x30) > 0.0f)) {
        // Calculate distance to target position
        int baseAddr = *(int*)(*(int*)(__readfsdword(0x2c) + 8) + 8);
        int idx = *(int*)(this + 0x10);
        floatVar5 = *(float*)(baseAddr + 0x88 + idx) - *(float*)(this + 0x88);
        floatVar4 = *(float*)(baseAddr + 0x84 + idx) - *(float*)(this + 0x84);
        floatVar1 = *(float*)(baseAddr + 0x80 + idx) - *(float*)(this + 0x80);
        float distance = sqrtf(floatVar5 * floatVar5 + floatVar4 * floatVar4 + floatVar1 * floatVar1);
        floatVar1 = (distance / *(float*)(this + 0x30)) * *(float*)(entityStatePtr + 0xc0);
        if (maxFactor < floatVar1) {
            floatVar1 = maxFactor;
        }
        timeStep = (maxFactor - floatVar1) * timeStep;
        steps = (int)((*(float*)(entityStatePtr + 0xc4) * floatVar1 + maxFactor) * (float)steps);
    }

    // Apply timeStep to accumulated time
    *(float*)(this + 0x3c) = timeStep + *(float*)(this + 0x3c);

    // Clamp steps by remaining action count
    delta = *(int16_t*)(entityStatePtr + 0x11a) - remainingActions;
    if (delta < steps) {
        steps = delta;
    }

    // Global cap
    if ((DAT_01194a94 != 0) && ((*(uint32_t*)(entityStatePtr + 0x10c) & 0x1000) == 0) &&
        (*(int*)(DAT_01194a94 + 0x2c) < steps)) {
        steps = *(int*)(DAT_01194a94 + 0x2c);
    }

    // Check if action can be triggered
    if ((steps != 0) &&
        (((*(int16_t*)(entityStatePtr + 0x118) < 0) || (*(int*)(this + 0x50) < (int)*(int16_t*)(entityStatePtr + 0x118))) &&
         ((*(uint32_t*)(this + 0x2c) & 0x800) == 0))) {
        actionId = FUN_0050cac0(steps, targetHandle);
        *outActionId = actionId;
    }
}