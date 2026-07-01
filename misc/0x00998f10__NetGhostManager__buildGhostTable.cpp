// FUNC_NAME: NetGhostManager::buildGhostTable
void __thiscall NetGhostManager::buildGhostTable(NetGhostManager* this, GhostList* newList)
{
    // +0x4c: flags (bit 2 = pending destruction)
    if ((this->flags & 4) == 0) {
        // Release previous ghost list if present
        if (this->ghostList != 0) {
            releaseGhostList(this->ghostList); // FUN_00997d90
        }
        this->ghostList = newList; // +0x1c
        // Increment reference count on new list
        if (*(short*)(newList + 4) != 0) {
            *(short*)(newList + 6) = *(short*)(newList + 6) + 1;
        }
        // Allocate ghost table (size 0x44, tag 0x2f)
        TlsGetValue(allocatorTlsIndex); // DAT_01139810
        int ghostTable = allocateMemory(0x44, 0x2f); // FUN_00aa2680
        *(unsigned short*)(ghostTable + 4) = 0x44; // store size
        GhostTableHandler* handler = getGhostTableHandler(); // FUN_009fd960
        this->ghostTable = handler; // +0x20
        // Process each ghost in the list
        int ghostCount = *(int*)(newList + 0xc); // +0xc: number of ghosts
        for (int i = 0; i < ghostCount; i++) {
            // Get ghost object from array at +0x8
            int ghostObj = *(int*)(*(int*)(newList + 8) + i * 4);
            // Call virtual function at vtable+0x18 (getGhostID)
            int ghostID = (*(**(int**)(*(int**)ghostObj + 0x18)))(); // method index 6
            registerGhostID(ghostID); // FUN_009fd840
            updateGhostTable(ghostTable); // FUN_009f01a0
        }
        // Now process ghost references
        int refCount = *(int*)(newList + 0x18); // +0x18: number of references
        for (int j = 0; j < refCount; j++) {
            int ghostRef = *(int*)(*(int*)(newList + 0x14) + j * 4); // array at +0x14
            int sourceGhost = *(int*)(ghostRef + 0x14); // +0x14: source ghost pointer
            int targetGhost = *(int*)(ghostRef + 0x18); // +0x18: target ghost pointer
            // Find source index in main list
            int srcIdx = -1;
            if (ghostCount > 0) {
                int* ghostPtrs = *(int**)(newList + 0x8);
                for (int k = 0; k < ghostCount; k++) {
                    if (ghostPtrs[k] == sourceGhost) {
                        srcIdx = k;
                        break;
                    }
                }
            }
            // Find target index in main list
            int dstIdx = -1;
            if (ghostCount > 0) {
                int* ghostPtrs = *(int**)(newList + 0x8);
                for (int k = 0; k < ghostCount; k++) {
                    if (ghostPtrs[k] == targetGhost) {
                        dstIdx = k;
                        break;
                    }
                }
            }
            // If both ghosts are valid and found in the list
            if ((sourceGhost != 0) && (targetGhost != 0) && (srcIdx >= 0) && (dstIdx >= 0)) {
                // Get ghost link from table using indices
                int tableArray = *(int*)(this->ghostTable + 8); // +0x8: array of indices per ghost
                int link = getGhostLink(*(int*)(tableArray + srcIdx * 4),
                                        *(int*)(tableArray + dstIdx * 4), 1); // FUN_009f9930
                releaseGhostLink((GhostLink*)link); // FUN_009fd8c0
            }
        }
        finalizeGhostTable(); // FUN_00998730
    }
}