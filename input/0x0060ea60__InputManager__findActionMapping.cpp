// FUNC_NAME: InputManager::findActionMapping
int __cdecl InputManager_findActionMapping(outActionData* outData, int* outFlags, int* ioSlotId, int* outType, char inputChar)
{
    int elemIdx;          // uVar3
    int *elemIter;         // piVar1
    int foundEntry;        // iVar2
    void *listData;        // puVar5
    void *destData;        // puVar6
    int listHandle;        // local_14
    int listCount;         // local_10
    int listDummy;         // local_c

    *outFlags = 0;
    elemIdx = 0;
    listHandle = 0;
    listCount = 0;
    listDummy = 0;          // unused/reserved

    if (g_inputDeviceCount != 0) {
        // Iterate over all input device slots (each slot 0x10 bytes)
        int slotBase = 0;
        do {
            // Check if slot's device pointer (at offset g_deviceOffset) is null
            if (*(int*)(slotBase + (uint)g_deviceOffset) == 0) {
                // Build a local list of all empty slots? Actually adds an entry for this slot
                InputManager_addEmptySlotToList(&listHandle, slotBase + g_deviceOffset + 4);
                elemIdx = 0;
                *ioSlotId = 1;                     // Assume player slot 1
                *outType = 0x54;                   // Some action type constant

                // If the list has entries, search for a specific mapping
                if (listCount != 0) {
                    // Point to first element's data (element size 0x14c bytes)
                    elemIter = (int*)(listHandle + 8);
                    do {
                        // Each element: field0 at +0, field1 at +4, field2 at +8
                        if ((elemIter[-1] == *ioSlotId) && (*elemIter == 0x50) && ((char)elemIter[1] == inputChar)) {
                            // Found matching binding, copy data to output structure
                            int base = elemIdx * 0x14c + listHandle;
                            outData->field0 = *(int*)(base + 0);
                            outData->field1 = *(int*)(base + 4);
                            outData->field2 = *(int*)(base + 8);
                            outData->field3 = *(char*)(base + 0xC);

                            // Bulk copy 0x4c dwords (0x130 bytes) starting at offset 0x10
                            destData = &outData->field4;
                            for (int i = 0; i < 0x4C; i++) {
                                ((int*)destData)[i] = *(int*)(base + 0x10 + i*4);
                            }

                            // Copy remaining 0xC bytes? Actually call a dedicated copy for offset 0x140 area
                            InputManager_copyActionTail(&outData->tailData, base + 0x140);
                            InputManager_freeList(&listHandle);
                            return 1;
                        }
                        elemIdx++;
                        elemIter += 0x53;         // 0x53 ints = 0x14c bytes per element
                    } while (elemIdx < listCount);
                }
                InputManager_freeList(&listHandle);
                return 0;
            }
            elemIdx++;
            slotBase += 0x10;
        } while (elemIdx < g_inputDeviceCount);
    }

    InputManager_freeList(&listHandle);
    return 0;
}