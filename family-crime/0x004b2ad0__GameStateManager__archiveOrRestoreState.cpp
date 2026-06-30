// FUNC_NAME: GameStateManager::archiveOrRestoreState
void GameStateManager::archiveOrRestoreState(uint32_t action) {
    char dirtyFlag;
    int32_t stateBuffSize;
    int32_t idx;
    uint32_t *srcPtr;
    uint32_t *dstPtr;
    uint32_t *stateBuffer;
    uint32_t localState[533]; // temporary stack buffer for state save/restore (533 * 4 = 2132 bytes)
    // Note: localState size matches the object's internal buffer at offset +0xB0 (533 uints)

    // Save the action parameter; it will be modified below
    // local_14 = action; (but not used later directly)
    
    // Get the singleton game state manager object
    GameStateManager *manager = getGameStateManager(); // FUN_004b2740()

    // Pointer to the internal state buffer at offset +0xB0
    stateBuffer = (uint32_t *)((uint8_t *)manager + 0xB0);

    // Copy 533 uints from local stack buffer into the manager's state buffer (overwrites current state)
    srcPtr = (uint32_t *)&localState; // &stack0x00000008 is the address of localState array (first element)
    dstPtr = stateBuffer;
    for (idx = 0x215; idx != 0; idx--) {
        *dstPtr = *srcPtr;
        srcPtr++;
        dstPtr++;
    }

    // Modify action: extract bit 0 from the first uint of the state buffer (shifted right by 2) and combine with action's high bits, then mask with 0xFFFFFF01
    // This effectively sets bit 0 of action to the value ((stateBuffer[0] >> 2) & 1), clearing bits 1-7
    action = (action & 0xFFFFFF00) | ((uint8_t)(*stateBuffer >> 2) & 0x01);

    // Compute a conditional pointer: address of manager + 0x6FC, but zero if the byte at that address is zero
    uint32_t maybeAddress = (uint32_t)((uint8_t *)manager + 0x6FC) & -(uint32_t)(*(uint8_t *)((uint8_t *)manager + 0x6FC) != '\0');

    // Set up stack variables that may be used by called functions (arguments or pseudo-arguments)
    uint32_t localVar1 = maybeAddress; // uStack_1c
    uint32_t localVar2 = action;       // uStack_18
    // uStack_20 = 0x4B2B34 is some static address, likely a debug string or handler pointer

    // Check if some condition is true (e.g., "is restore needed")
    dirtyFlag = isStateDirty(); // FUN_0061ee20(); probably checks a flag

    if (dirtyFlag != '\0') {
        // Copy back from manager's state buffer into local stack buffer
        srcPtr = stateBuffer;
        dstPtr = localState;
        for (idx = 0x215; idx != 0; idx--) {
            *dstPtr = *srcPtr;
            srcPtr++;
            dstPtr++;
        }
        // Perform the actual restore/apply operation using the local buffer
        restoreStateFromBuffer(); // FUN_004b2980()
    }

    // Clear the "archived" flag at offset +0x904
    *(uint8_t *)((uint8_t *)manager + 0x904) = 0;
    return;
}