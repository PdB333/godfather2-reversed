// FUNC_NAME: GhostConnection::processGhostStateMachine
void GhostConnection::processGhostStateMachine(void)
{
    int *statePtr; // unaff_EDI - pointer to state machine context (ghost state, index, param)
    int *connection; // in_EAX - pointer to GhostConnection object
    int result;
    
    statePtr = /* set by caller */;
    connection = /* set by caller */;
    
    switch (*statePtr) {
    case 5: // GhostState_5
        *statePtr = 0xB; // GhostState_11
        return;
        
    case 6: // GhostState_6
        // Build a ghost update packet with command 4 and ghost index shifted left 15
        result = buildGhostPacket(statePtr[1] << 0xF | 4, *(undefined4 *)(connection[3] + 8));
        *statePtr = 10; // GhostState_10
        statePtr[1] = result;
        return;
        
    case 7: // GhostState_7
        // Build a ghost update packet with command 5 and ghost index shifted left 6
        result = buildGhostPacket(statePtr[1] << 6 | 5, *(undefined4 *)(connection[3] + 8));
        *statePtr = 10; // GhostState_10
        statePtr[1] = result;
        return;
        
    case 8: // GhostState_8
        // Decrement update counter if ghost parameters are within valid range
        if ((connection[0xD] <= statePtr[2]) && (statePtr[2] < 0xFA)) {
            connection[9] = connection[9] - 1; // +0x24: updateCount
        }
        if ((connection[0xD] <= statePtr[1]) && (statePtr[1] < 0xFA)) {
            connection[9] = connection[9] - 1; // +0x24: updateCount
        }
        // Schedule a ghost update with type 6
        result = scheduleGhostUpdate(6, statePtr[1], statePtr[2]);
        *statePtr = 10; // GhostState_10
        statePtr[1] = result;
        return;
        
    case 0xC: // GhostState_12
        if (*statePtr == 0xC) { // redundant check
            uint32_t *ghostFlags = *(uint32_t **)(*connection + 0xC); // +0x0C: ghostFlags array
            // Set bit 7 and clear bit 6 in the ghost flags for this index
            ghostFlags[statePtr[1]] = (ghostFlags[statePtr[1]] & 0xFFFF80BF) | 0x80;
            *statePtr = 0xB; // GhostState_11
            // Extract a byte from offset 3 of the same flags entry (likely a sub-state)
            statePtr[1] = (int)*(char *)((int)ghostFlags + 3 + statePtr[1] * 4);
        }
        return;
    }
    return;
}