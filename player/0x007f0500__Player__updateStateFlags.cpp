// FUNC_NAME: Player::updateStateFlags
void __fastcall Player::updateStateFlags(int thisPtr)
{
    char desiredState = *(char *)(thisPtr + 0x5e1); // +0x5e1: m_desiredState
    char currentState = *(char *)(thisPtr + 0x5e0); // +0x5e0: m_currentState

    // Check if state change is pending and enough time has passed (cooldown > 2 frames)
    if (currentState != desiredState && (uint)(g_frameCounter - *(int *)(thisPtr + 0x5e8)) > 2)
    {
        *(char *)(thisPtr + 0x5e0) = desiredState; // Apply new state
        if (desiredState == 1)
        {
            // Activate components when state becomes 1
            // Each component is a pointer to an object; call its second virtual function (index 1)
            (**(code **)(*(int *)(thisPtr + 0x2c) + 4))(); // +0x2c: m_component1
            (**(code **)(*(int *)(thisPtr + 0x48) + 4))(); // +0x48: m_component2
            (**(code **)(*(int *)(thisPtr + 0x64) + 4))(); // +0x64: m_component3 (offset 100 decimal)
            (**(code **)(*(int *)(thisPtr + 0x80) + 4))(); // +0x80: m_component4
        }
        *(int *)(thisPtr + 0x5e8) = g_frameCounter; // +0x5e8: m_lastStateChangeTime
    }

    // Second pair of state flags (no action on change, just debounce)
    char anotherDesired = *(char *)(thisPtr + 0x5e3); // +0x5e3: m_anotherDesiredState
    char anotherCurrent = *(char *)(thisPtr + 0x5e2); // +0x5e2: m_anotherCurrentState
    if (anotherCurrent != anotherDesired && (uint)(g_frameCounter - *(int *)(thisPtr + 0x5ec)) > 2)
    {
        *(char *)(thisPtr + 0x5e2) = anotherDesired;
        *(int *)(thisPtr + 0x5ec) = g_frameCounter; // +0x5ec: m_lastAnotherChangeTime
    }
}