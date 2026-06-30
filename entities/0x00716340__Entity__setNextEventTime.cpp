// FUNC_NAME: Entity::setNextEventTime
void __thiscall Entity::setNextEventTime(int param_1, int param_2) {
    int iVar1;
    int iVar2;
    float fVar3;
    int local_8;

    // Store the base value (likely current game time or trigger time)
    *(int *)(param_1 + 0x328) = param_2; // m_eventBase

    // Clear the "ready" bit (bit 0) of flags
    *(uint *)(param_1 + 0x308) &= ~1u; // m_flags

    // Check if some condition allows random timing (e.g., random delay enabled)
    iVar1 = someAvailabilityCheck(); // FUN_00800a90
    if (iVar1 != 0) {
        // Get a random base delay
        fVar3 = getRandomFloat01(); // FUN_00701020
        local_8 = (int)(longlong)ROUND(fVar3 * g_baseDelayConst); // DAT_00d60d04

        iVar1 = local_8; // Save base delay
        iVar2 = _rand(); // Random integer

        // Get another random factor for scatter
        fVar3 = getSecondRandomFloat01(); // FUN_00701030
        // Calculate a random offset (scatter)
        local_8 = (int)(longlong)ROUND((float)iVar2 * g_scatterFactor * fVar3 * g_anotherFactor); // DAT_00e44590, _DAT_00d61ad8

        // Set next event time: base value + (base delay - scatter)
        *(int *)(param_1 + 0x32c) = (iVar1 - local_8) + param_2; // m_nextEventTime
    }

    // If the flag is not already set and the next event time is already passed (<= current game time)
    if (((*(byte *)(param_1 + 0x308) & 1) == 0) &&
        (*(uint *)(param_1 + 0x32c) <= g_currentGameTime)) { // DAT_01205224
        // Set the "ready" flag
        *(uint *)(param_1 + 0x308) |= 1u;
    }
    return;
}