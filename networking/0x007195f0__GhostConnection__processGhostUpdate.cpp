// FUNC_NAME: GhostConnection::processGhostUpdate
void __thiscall GhostConnection::processGhostUpdate(int ghostIndex, uint* outData) {
    int localGhostIndex = ghostIndex;
    acquireGhostLock(ghostIndex);  // Lock ghost for thread safety

    if (outData == 0) {
        findGhostData(&ghostIndex, localGhostIndex);
    } else {
        uint* foundData = (uint*)findGhostData(&ghostIndex, localGhostIndex);
        *outData = *foundData;
    }

    // Offset 0x330: pointer to an array of ghost object pointers
    int ghostArrayBase = *(int*)(this + 0x330);
    int indexFromArray = (ghostArrayBase == 0) ? 0 : ghostArrayBase - 0x48; // Subtract size of ghost header?

    if (localGhostIndex == indexFromArray) {
        onGhostIndexMatch();  // May trigger creation or state change
    }

    // Offset 0x18: pointer to a game manager or session
    if (*(int*)(this + 0x18) != 0) {
        int* pSimManager = (int*)getSimManager(DAT_01131018); // Global singleton
        if (pSimManager != 0) {
            int sessionId = (*(code**)(*pSimManager + 0x34))(); // Virtual call to getSession or similar
            if (sessionId != 0) {
                int sessionArrayBase = *(int*)(sessionId + 0xC);
                int sessionIndex = (sessionArrayBase == 0) ? 0 : sessionArrayBase - 0x48;
                if (sessionIndex == localGhostIndex) {
                    // Match on session's ghost index
                } else {
                    int altArrayBase = *(int*)(sessionId + 4);
                    int altIndex = (altArrayBase == 0) ? 0 : altArrayBase - 0x48;
                    if (altIndex == localGhostIndex) {
                        // Match on second array
                    } else {
                        return; // No match
                    }
                }
                notifyEvent(); // Final callback
            }
        }
    }
}