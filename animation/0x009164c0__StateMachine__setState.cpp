// FUNC_NAME: StateMachine::setState
// Address: 0x009164c0
// Role: Sets the state machine to a new state (stateId) with data from a singleton frame data source.
// The function retrieves a 16-byte data block (likely a timestamp + vector/quaternion), adds a global time offset,
// processes it, then transitions the state machine to state 2 after clearing any previous state in range 1-4.

void __thiscall StateMachine::setState(uint stateId) {
    // +0x00: vtable pointer (implied)
    // +0x04: m_stateId (uint)
    // +0x08: m_state (int)

    // Get pointer to frame data from singleton (FUN_00950b20)
    FrameData* pFrameData = getFrameData();
    float time;
    uint data0, data2, data3;

    if (pFrameData == nullptr) {
        time = 0.0f;
        data0 = 0;
        data2 = 0;
        data3 = 0;
    } else {
        data0 = pFrameData->field0;      // +0x00
        time = pFrameData->field4;        // +0x04 (float)
        data2 = pFrameData->field8;       // +0x08
        data3 = g_globalData;             // _DAT_00d5780c
    }

    // Add global time offset (DAT_00d8bbc8)
    time += g_timeOffset;

    // Process the data block (FUN_0097a8d0) – likely normalizes or applies transform
    processFrameData(&data0);

    // Clear state if it was in the range 1-4 (e.g., transitioning from other active states)
    if (m_state >= 1 && m_state <= 4) {
        m_state = 0;
    }

    // Set new state ID and state to 2 (active/playing)
    m_stateId = stateId;
    m_state = 2;

    // Apply the new state (FUN_00978790) – e.g., start animation, activate camera
    applyState(stateId);
}