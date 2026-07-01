// FUNC_NAME: CountActiveMissionsForPlayer
int CountActiveMissionsForPlayer(void) {
    // +0x16c: pointer to mission container (likely a list or array)
    // +0x1ef8: field identifying mission type (e.g., index or type ID)
    // +0x1f30: offset from game manager base to something (maybe player data)
    int targetPlayerId = *reinterpret_cast<int*>(0x0112b6fc);
    int count = 0;
    
    int* gameManager = *reinterpret_cast<int**>(0x012233a0);
    int playerBase = 0;
    if (gameManager != nullptr && *reinterpret_cast<int*>(gameManager + 1) != 0) {
        playerBase = *reinterpret_cast<int*>(gameManager + 1) - 0x1f30;
    }
    
    int* missionManager = *reinterpret_cast<int**>(0x0112ebb4);
    if (missionManager != nullptr && playerBase != 0) {
        int* missionContainer = *reinterpret_cast<int**>(missionManager + 0x16c / 4);
        int missionType = *reinterpret_cast<int*>(playerBase + 0x1ef8);
        
        // Initialize an iterator over missionContainer filtered by missionType
        int iteratorData[3]; // local_10 (function pointers) + local_c/local_8 (state)
        FUN_004bab20(&iteratorData, missionContainer, missionType);
        
        // iteratorData[0] -> get current element
        // iteratorData[2] -> advance
        // local_c and local_8 are the termination condition fields (current/end)
        int* current = reinterpret_cast<int*>(&iteratorData[0]); // actually first element is function pointer, but code uses it as (*code)()
        // The decompiler shows local_c and local_8 as separate locals; they are part of the iterator state.
        // We assume the iterator struct has begin/end values in local_c and local_8.
        while (iteratorData[1] != 0 || iteratorData[2] != 0) { // local_c and local_8 are in indices 1 and 2? Not exactly, but for clarity we use a while loop.
            int* missionObj = reinterpret_cast<int*>((*(code*)iteratorData[0])()); // call get current
            if (missionObj[2] == targetPlayerId && missionObj[5] == missionType &&
                (missionObj[3] > 0 || missionObj[4] == missionObj[5])) {
                count++;
            }
            (*(code*)iteratorData[2])(); // advance
        }
    }
    return count;
}