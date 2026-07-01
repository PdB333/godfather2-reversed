// FUNC_NAME: TargetingManager::setActiveTarget
void __thiscall TargetingManager::setActiveTarget(int thisPtr, int targetId, char force) {
    uint entryCount = *(uint *)(thisPtr + 0x198);
    
    // Check if global targeting is enabled, and either forced or target changed
    if (*(char *)(g_targetingEnabled + 0x48) != '\0' &&
        ((force != '\0') || (*(int *)(thisPtr + 0x1a0) != targetId)) &&
        (*(char *)(thisPtr + 0x18) != '\0')) {
        
        // Search for targetId in allowed target list
        uint i = 0;
        bool found = false;
        if (entryCount != 0) {
            // Each list entry has format: struct { int unused; int targetId; } (8 bytes per entry)
            int *listEntry = (int *)(*(int *)(thisPtr + 0x194) + 4); // point to first targetId
            while (i < entryCount) {
                if (*listEntry == targetId) {
                    found = true;
                    break;
                }
                i++;
                listEntry += 2; // move to next entry (skip unused + targetId)
            }
        }
        
        uint flags = *(uint *)(thisPtr + 0x11c);
        bool targetLocked = (flags >> 0x17) & 1; // bit 23
        
        if (entryCount == 0) {
            // No list – allow any target
            if (targetLocked) {
                disableTargetLock();   // FUN_00949850
                *(uint *)(thisPtr + 0x11c) = flags & 0xFF7FFFFF; // clear bit 23
                *(int *)(thisPtr + 0x1a0) = targetId;
                return;
            }
        } else {
            // Has a list – only allow if target is in list
            if (found) {
                if (!targetLocked) {
                    enableTargetLock(); // FUN_00949800
                    *(uint *)(thisPtr + 0x11c) = flags | 0x800000; // set bit 23
                }
                *(int *)(thisPtr + 0x1a0) = targetId;
            }
        }
    }
}