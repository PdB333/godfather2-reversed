// FUNC_NAME: GhostConnection::calcPacketSize

int __thiscall GhostConnection::calcPacketSize(uint groupId)
{
    int *maskTable;
    uint selectedMask;
    int objectCount;
    int *entryPtr;
    int *objectPtr;
    int i;
    int totalSize;

    // Find the bitmask associated with this group ID from the mask table at this+0x20
    maskTable = *(int **)(this + 0x20);
    selectedMask = 0;
    do {
        if ((groupId == (uint)*maskTable) || (*maskTable == 0)) {
            selectedMask = maskTable[1];
        }
        maskTable += 2;
    } while (selectedMask == 0);

    // Begin profiling scope? (unknown function call)
    local_14 = DAT_0120e924;
    local_10 = 0;
    local_c = 0;
    FUN_00408a00(&local_14, 0);

    objectCount = *(int *)(this + 0x14);               // Number of ghost entries
    totalSize = 4;                                     // Base packet header size

    if (objectCount != 0) {
        // Ghost entry array starts at offset 0x18 of the object list structure pointed by this+0x10
        entryPtr = (int *)(*(int *)(this + 0x10) + 0x18);
        for (i = 0; i < objectCount; i++) {
            objectPtr = (int *)*entryPtr;              // NetObject pointer

            // Check if object's bitmask matches AND (object is active OR we always include)
            if ((objectPtr[2] & selectedMask) != 0x0 &&
                ((*(byte *)(objectPtr + 1) & 1) != 0x0 || (*(byte *)(this + 0x1c) & 1) != 0x0)) {
                // Size of object data + 39 bytes overhead, aligned to 4 bytes
                totalSize += (*objectPtr + 0x27U) & 0xfffffffc;
            }
            entryPtr += 7;                             // Each ghost entry is 28 bytes (7 ints)
        }
    }

    return totalSize;
}