// FUNC_NAME: AnimationController::update
void __thiscall AnimationController::update(void)
{
    int state;
    int count;
    int tempHandle; // local_c
    int tempValue;  // local_8
    int tempUnused; // local_4

    tempHandle = 0;
    tempValue = 0;
    tempUnused = 0;

    // Global update/reset call
    updateGlobalState();

    // Copy source values into the per-state count array
    this->m_counts[0] = this->m_sourceValue1; // +0x60 -> +0x78
    initTempHandle(&tempHandle); // FUN_009217e0
    this->m_counts[2] = this->m_sourceValue2; // +0x6c -> +0x80
    this->m_counts[1] = tempValue; // +0x7c = local_8

    state = this->m_state; // +0x58
    switch (state)
    {
    case 0:
        updateState0(); // FUN_00921320
        break;
    case 1:
        updateState1(); // FUN_009223c0
        break;
    case 2:
        updateState2(); // FUN_00921100
        break;
    }

    state = this->m_state;
    count = this->m_counts[state]; // +0x78 + state*4
    if (count < 1)
    {
        // No frames left – release effect handle if present
        if (this->m_pEffectHandle != 0) // +0xa4
        {
            releaseHandle((undefined4 *)&this->m_pEffectHandle); // FUN_004daf90
            this->m_pEffectHandle = 0;
        }
    }
    else
    {
        // Advance the loop counter modulo count
        this->m_loopCounter = (this->m_loopCounter + count) % count; // +0x74

        switch (state)
        {
        case 0:
            advanceState0(); // FUN_00921730
            break;
        case 1:
            advanceState1(); // FUN_009218e0
            break;
        case 2:
            advanceState2(); // FUN_00921680
            break;
        }
    }

    // Destroy temporary handle if it was allocated
    if (tempHandle != 0)
    {
        destroyHandle(tempHandle); // FUN_009c8f10
    }
}