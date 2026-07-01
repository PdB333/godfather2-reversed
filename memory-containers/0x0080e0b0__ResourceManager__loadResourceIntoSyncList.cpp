// FUNC_NAME: ResourceManager::loadResourceIntoSyncList
bool __fastcall ResourceManager::loadResourceIntoSyncList(int this) {
    bool success = false;
    int state = getState(); // FUN_0080d3f0 - returns 1 or 2
    if (state == 1 || state == 2) {
        int gameManager = getGameManager(); // FUN_00471610 - returns global game manager
        // Extract transform/identifier from game manager (offset 0x30, 0x38)
        unsigned long long transform = *(unsigned long long *)(gameManager + 0x30);
        unsigned int extraData = *(unsigned int *)(gameManager + 0x38);
        
        if ((*(unsigned char *)(this + 0x94) & 1) == 0) {
            // Loading from handle (this+0x50)
            int handleResult = findAssetByHandle(*(unsigned int *)(this + 0x50), &transform, &transform, 1);
            if (handleResult == 0) {
                // Asset not found, clear current loaded node
                if (*(int *)(this + 0x60) != 0) {
                    safeDeleteNode((unsigned int *)(this + 0x60));
                    *(unsigned int *)(this + 0x60) = 0;
                }
                return true;
            }
            // Check error code in result
            if (*(int *)(handleResult + 0x24) == 0) {
                setError(0);
                return false;
            }
            setError(*(int *)(handleResult + 0x24) - 0x48);
            return false;
        } else {
            // Bit 0 set: load from existing node or by state
            int nodePtr = *(int *)(this + 0x58);
            int newPtr;
            if (state == 1) {
                newPtr = iRam000001d0; // Global reference? Possibly static default
                if (nodePtr != 0) {
                    newPtr = *(int *)(nodePtr + 0x188);
                }
            } else {
                if (nodePtr == 0) {
                    nodePtr = 0;
                } else {
                    nodePtr = nodePtr - 0x48;
                }
                newPtr = *(int *)(nodePtr + 0x1d4);
            }
            char result = loadAndInsertNode(state, &transform, newPtr, 0, &newPtr);
            success = (result == '\0');
            int *listHead = (int *)(this + 0x60);
            int finalPtr;
            if (newPtr == 0) {
                finalPtr = 0;
            } else {
                finalPtr = newPtr + 0x48; // Adjust for list node offset
            }
            if (*listHead != finalPtr) {
                if (*listHead != 0) {
                    safeDeleteNode(listHead);
                }
                *listHead = finalPtr;
                if (finalPtr != 0) {
                    *(unsigned int *)(this + 100) = *(unsigned int *)(finalPtr + 4);
                    *(int **)(finalPtr + 4) = listHead;
                }
            }
        }
    }
    return success;
}