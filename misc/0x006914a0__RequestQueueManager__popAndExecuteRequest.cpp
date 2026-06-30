// FUNC_NAME: RequestQueueManager::popAndExecuteRequest
// Address: 0x006914a0
// This function appears to be part of a request queue management system.
// It pops a request object from a global stack and executes its virtual process function.
// The function checks a global state (m_currentState) and processes if conditions are met.

void __thiscall RequestQueueManager::popAndExecuteRequest(int param_2) {
    int* pvtable;
    
    // Check global state at offset 0x564 (likely m_currentState) from the game manager singleton (DAT_012233b4)
    // If state is not 0x12 (18) and the request stack index is valid and has an entry...
    if ((*(char*)(pGameManager + 0x564) != '\x12') && (s_requestStackIndex != -1) &&
        (s_requestStack[s_requestStackIndex] != 0)) {
        // If param_2 (possibly a priority or count) is less than 15 and state is still not 0x12
        if ((param_2 < 0xf) && (*(char*)(pGameManager + 0x564) != '\x12')) {
            // Call a helper function with the current state byte and then update something
            getRequestObject(*(char*)(pGameManager + 0x564));
            updateAudioState();  // FUN_004958a0
        }
        // If stack index is valid, pop the top request
        if (s_requestStackIndex != -1) {
            undefined4 requestObj = s_requestStack[s_requestStackIndex];
            s_requestStackIndex = s_requestStackIndex - 1;
        }
        // Get the vtable pointer from the request object (by calling getRequestObject again with state)
        pvtable = (int*)getRequestObject(*(undefined1*)(pGameManager + 0x564));
        // Call the third virtual method (offset 8) on the popped request object
        (**(code**)(*pvtable + 8))(requestObj);
    }
}