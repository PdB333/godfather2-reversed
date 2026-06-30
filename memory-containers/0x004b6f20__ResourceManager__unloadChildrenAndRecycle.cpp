// FUNC_NAME: ResourceManager::unloadChildrenAndRecycle

void __thiscall ResourceManager::unloadChildrenAndRecycle(int thisPtr, int *resourceKey)
{
    int *arrayBase;
    int *slotPtr;
    int *tempPtr;
    int *(*getManagerFunc)();
    int *manager;
    undefined4 someValue;
    char *checkString;
    int matchingCount;
    uint slot;
    int *node;
    int *prevNode;

    // Check if the resource key matches the expected type ID
    if (DAT_012069c4 != *resourceKey) {
        return;
    }

    // Check if the "locked" flag (bit 1 of offset 0x1C) is clear
    if ((*(byte *)(thisPtr + 0x1C) & 2) != 0) {
        return;
    }

    matchingCount = 0;
    slot = 0;
    arrayBase = *(int **)(thisPtr + 0xC);
    if (arrayBase == 0) {
        goto SKIP_CHILDREN;
    }

    do {
        // Read pointer to child object at offset 0x40 + slot * 0x70
        slotPtr = *(int **)((int)arrayBase + 0x40 + slot * 0x70);
        if (slotPtr == 0) {
            // No object in this slot – check if there is an actual object (same pointer)
            // and if its type byte equals 6 (likely a specific resource type)
            tempPtr = *(int **)((int)arrayBase + 0x40 + slot * 0x70);
            if (tempPtr != 0 && *(char *)(tempPtr + 0xD8) == 6) {
                matchingCount++;
            }
        } else {
            // Object exists – check if its string ID matches the given resourceKey
            getManagerFunc = *(int *(*)(void))(*(int *)DAT_0113dfc8 + 0x14);
            manager = (int *)getManagerFunc();
            someValue = (**(code **)(*manager + 0x10))(slotPtr);
            checkString = (char *)FUN_00ab06f0(resourceKey, someValue);
            if (*checkString != '\0') {
                // String did not match – treat this as a candidate for removal
                tempPtr = *(int **)((int)arrayBase + 0x40 + slot * 0x70);
                if (tempPtr != 0 && *(char *)(tempPtr + 0xD8) == 6) {
                    matchingCount++;
                }
            }
        }
        slot++;
    } while (slot < *(uint *)(thisPtr + 0x10));

    // If any matching children were found, notify parent by calling cleanup at (this - 0xC)
    if (matchingCount != 0) {
        FUN_004b6820(thisPtr - 0xC, 0);
    }

SKIP_CHILDREN:
    // If the "free flag" at offset 0x14 is non-zero, insert this object into a global free list (likely a pool)
    if (*(int *)(thisPtr + 0x14) != 0) {
        prevNode = *(int **)(thisPtr - 4);
        FUN_004a6a80(0);
        node = prevNode;
        if (DAT_0120548c != 0) {
            *(int *)(DAT_0120548c + 0x90) = node;
            node = DAT_01205488;
        }
        DAT_01205488 = node;
        *(int *)(node + 0x8C) = DAT_0120548c;
        *(int *)(node + 0x90) = 0;
        DAT_0120548c = node;
    }
    return;
}