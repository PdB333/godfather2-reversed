// FUNC_NAME: GhostManager::removeGhostByUID
bool GhostManager::removeGhostByUID(int* pUid) {
    // Compute hash from 4 UID components (djb2-style, multiplier 0x21 = 33)
    int hash = ((pUid[0] * 0x21 + pUid[1]) * 0x21 + pUid[2]) * 0x21 + pUid[3];
    int* pGhostObj = hashTableLookup(hash); // FUN_004059b0: finds ghost object by hash
    if (pGhostObj != nullptr) {
        // Debug log: format string and ghost pointer
        struct DebugLogEntry {
            char* formatStr; // +0x00
            char unknown;    // +0x04 (local_c = 0)
            int ghostPtr;    // +0x08 (local_10)
        } entry;
        entry.formatStr = gDebugFormatString; // DAT_0120e94c
        entry.unknown = 0;
        entry.ghostPtr = (int)pGhostObj;
        debugLogPrint(&entry, 0); // FUN_00408a00

        int* pGhostState = getGhostState((int)pGhostObj); // FUN_004025a0: retrieve state block
        if (pGhostState != nullptr) {
            // Clear the "pending destroy" flag (bit 8) at offset +0x50
            *(uint*)((char*)pGhostState + 0x50) &= ~0x100;
        }
        return true;
    }
    return false;
}