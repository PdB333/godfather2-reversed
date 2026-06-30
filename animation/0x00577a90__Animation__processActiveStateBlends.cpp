// FUNC_NAME: Animation::processActiveStateBlends
void Animation::processActiveStateBlends()
{
    // Check if there is an active entity or target (offset +0xb8)
    if (m_pActiveEntity == nullptr) {
        return;
    }

    // Retrieve pointer to state machine / animation set (offset +0x70)
    StateMachine* pStateMachine = m_pStateMachine;

    // Current state index stored as short (offset +0x76)
    short currentState = m_currentStateIndex;

    // Validate state machine and current state
    bool bValid = (pStateMachine != nullptr) &&
                  (pStateMachine->stateCount >= 1) &&
                  (pStateMachine->statesList != nullptr) &&
                  (currentState >= 0) &&
                  (currentState < pStateMachine->stateCount);

    StateData* pStateData = nullptr;
    if (bValid) {
        // Each state occupies 0x18 bytes
        pStateData = (StateData*)((uint8_t*)pStateMachine->statesList + currentState * 0x18);
    }

    if (pStateData == nullptr) {
        return;
    }

    // Number of blend elements for this state (offset +0x08 within state data)
    int blendCount = pStateData->blendCount;

    // Array of blend flags (offset +0xb4 on this)
    int8_t* pBlendArray = m_pBlendArray;

    for (int i = 0; i < blendCount; ++i) {
        // A value of -1 indicates an inactive blend slot
        if (pBlendArray[i] != -1) {
            // Invoke handler for active blend element (address 0x424470)
            FUN_00424470(); // placeholder: processBlendElement()
        }
    }
}