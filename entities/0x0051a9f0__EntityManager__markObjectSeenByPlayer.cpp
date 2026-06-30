// FUNC_NAME: EntityManager::markObjectSeenByPlayer
void EntityManager::markObjectSeenByPlayer(void)
{
    int iVar1;
    int this; // unaff_ESI - implied this pointer
    undefined8 contextId;

    contextId = getCurrentContextId(); // returns 64-bit ID (e.g., player simulation ID)

    // Iterate through linked list of objects starting from global head DAT_01205514
    for (iVar1 = gEntityListHead; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x14)) {
        // Check if this context (this==0 means global) matches object's owner (offset +0x10)
        if (((this == 0) || (this == *(int *)(iVar1 + 0x10))) &&
            // Check if object's 64-bit ID matches contextId (offsets +0x70 and +0x74)
            (*(int *)(iVar1 + 0x70) == (int)contextId) &&
            (*(int *)(iVar1 + 0x74) == (int)((ulonglong)contextId >> 0x20))) {
            // If the "notified" flag (0x20000) is not set, set it and call callback
            if ((*(uint *)(iVar1 + 0xc) & 0x20000) == 0) {
                *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 0x20000;
                onObjectSeen(); // FUN_0051b120
            }
            // Clear the "processed" flag (0x40000) after notification
            *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffbffff; // ~0x40000
        }
    }
    return;
}