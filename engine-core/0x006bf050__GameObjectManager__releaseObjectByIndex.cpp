// FUNC_NAME: GameObjectManager::releaseObjectByIndex
int __thiscall GameObjectManager::releaseObjectByIndex(int thisObj, int* slotInfo)
{
    int objectIndex;
    int objectPtr;
    int* globalManager;

    objectIndex = slotInfo[1]; // +0x04 slot index
    // Access object pointer from table: base pointer at slotInfo[0] with offset -4 (header?) + index*4
    objectPtr = *(int*)(slotInfo[0] - 4 + objectIndex * 4);
    globalManager = (int*)getGlobalManager(); // FUN_00791300

    if (globalManager == (int*)0) {
        // No global manager: check object flags for pending release
        if ((*(uint*)(objectPtr + 0x5c) & 0x60000) != 0) {
            *(uint*)(objectPtr + 0x5c) |= 0x40000000; // Mark as queued for deletion
            return 0;
        }
    } else {
        // Global manager exists
        if (((uint)globalManager[0x7d6] >> 0x19 & 1) == 0) {
            // Manager not in a safe state: call virtual trigger
            (*(code**)(*globalManager + 0x288))(2, 0, 0);
            return 0;
        }
        // Initialize manager component at offset 0x3c (0xf * 4)
        initializeManagerComponent(globalManager + 0xf); // FUN_004088c0
    }

    // If object exists, destroy and notify
    if (objectPtr != 0) {
        destroyObjectByIndex(objectIndex - 1); // FUN_006be9f0
        notifyObjectReleased(thisObj);          // FUN_00791350
        recycleObjectPool();                   // FUN_006bec10
    }
    return objectPtr;
}