// FUN_NAME: DebugIndicatorSystem::updateStatus(StatusState*)
// Address: 0x0096c1d0
// Role: Updates a debug status indicator (line drawing, state machine) for a debug overlay system.
// It checks flags, acquires a state object, draws a line based on state type, logs status, and updates state.

void __thiscall DebugIndicatorSystem::updateStatus(StatusState* state) {
    // state is a pointer to a status object; get the internal pointer at +0x100 (e.g., color or offset)
    void* internalPtr = state != nullptr ? reinterpret_cast<char*>(state) + 0x100 : nullptr;
    int type;

    if (state == nullptr) {
        return;
    }

    // Check bit 8 of flags at this+0x6f4 (enable bit)
    if ((*(reinterpret_cast<uint32_t*>(this) + 0x6f4 / 4) >> 8 & 1) == 0) {
        return;
    }

    // Acquire/lock the state object (FUN_00968e40 likely an addref or lock)
    if (!acquireState(&state, internalPtr)) {
        return;
    }

    type = state->type; // +0x4
    switch (type) {
        case 0:
        case 1: {
            // Retrieve position from state+0xf0 and state+0xf4 (two floats)
            float posX = state->someX; // +0xf0
            float posY = state->someY; // +0xf4
            // Draw a line from these coords using this+100 (0x64) as a parameter (maybe color or start point)
            debugDrawLine(&g_debugContext, &posX, *internalPtr, *(uint32_t*)(this + 0x64), 10000);
            // Release/lock (FUN_00968e40 may be a pair with acquire; here we set type to 2? Actually case0/1 paths set uVar3=2)
            // uVar3 is set to 2, later stored.
            newType = 2;
            break;
        }
        case 2: {
            float posX = state->someX; // +0xf0
            float posY = state->someY; // +0xf4
            debugDrawLine(&g_debugContext, &posX, *internalPtr, *(uint32_t*)(this + 0x60), 10000);
            newType = 0;
            break;
        }
        case 3:
            // Some other handling
            handleStateThree(state);
            break;
        default:
            goto default_label;
    }

    // Store the new type and compute a cumulative counter
    this->indicatorType = newType; // +0x108
    this->statusCounter = *(int*)(this + 0xd4) + *(int*)(this + 0xc4); // +0x10c

    // Log status change
    debugLog("SetStatus", 0, &DAT_00d8cdec, 0);

    // Release the internal reference at state+0x100
    releaseState(&state, internalPtr);

    // Update state's type
    state->type = newType; // +0x4

default_label:
    return;
}