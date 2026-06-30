// FUNC_NAME: GameStateManager::updateState
uint GameStateManager::updateState(Object* obj) // 0x006fcc30
{
    // Check for null and type ID
    if (obj == nullptr)
        return in_EAX & 0xffffff00; // preserve upper bytes, likely error mask

    if (*(int*)(obj + 4) != 9)
        return in_EAX & 0xffffff00; // not the expected type

    // Perform cleanup/reinit on the object
    resetObject(obj);   // FUN_005709e0
    initObject(obj);    // FUN_00570860

    int index = 0;
    int* iterPtr = (int*)(g_stateManager + 0x88); // array of IDs at +0x88

    // Search for matching ID among 3 entries (0,1,2)
    while (*iterPtr != **(int**)(obj + 0x30)) // double deref to get ID from obj
    {
        index++;
        iterPtr += 0x16; // advance by 0x58 bytes (0x16 * 4)
        if (index > 2)
        {
            uint result = processUpdate(obj); // FUN_004a83d0
            return result;
        }
    }

    if (index == -1) // no match found (shouldn't happen here)
        goto fallback;

    // Point to the actual state entry at +0x78 + index*0x58
    int* stateEntry = (int*)(index * 0x58 + 0x78 + (int)g_stateManager);

    lockCriticalSection(&g_csState); // FUN_00ab4db0

    int currentState = *stateEntry;
    if (currentState == 2) // IDLE -> PREPARE
    {
        *stateEntry = 6; // transition to state 6
        stateEntry[1] = 0;
        goto callTransition;
    }
    else if (currentState == 3 || currentState == 4)
    {
        handleStateTransition(); // FUN_006fcb60
    }

    if (*stateEntry == 6 || *stateEntry == 5)
    {
callTransition:
        transitionToState(); // FUN_006fbd30
    }

    unlockCriticalSection(&g_csState); // FUN_00ab4e70

fallback:
    uint result = processUpdate(obj); // FUN_004a83d0
    return result;
}