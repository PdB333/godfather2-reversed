// FUNC_NAME: ObjectManager::processExpiredObjects
void ObjectManager::processExpiredObjects(void)
{
    ushort *bitFieldPtr;
    int numItems;
    int objIndex;
    int subObjIndex;
    ushort bitMask;
    int subCount;
    int subLimit;
    uint subLoop;
    int itemOffset;

    // TLS check: ensure game object is initialized (using FS segment offset 0x2c)
    if (*(int *)(**(int **)(__readfsdword(0x2c) + 0x34) != 0)) {
        // Main processing only if global flag is set
        if (g_expireProcessingEnabled != '\0') {
            bitMask = g_currentBitMask; // 16-bit mask
            objIndex = 0;

            // Iterate over all object slots (max 0x3000/0x60 = 128 slots)
            do {
                int *objPtr = (int *)(g_objectManagerBase + 0x40 + objIndex);
                if (*(int *)(g_objectManagerBase + 0x40 + objIndex) != 0) {
                    int base = g_objectManagerBase;

                    // Process sub-objects if flag set and count > 0
                    if ((g_processSubObjects != '\0') && (subLimit = *(uint *)(base + 0x4c + objIndex), subLimit != 0)) {
                        subObjIndex = 0;
                        subLoop = 0;
                        do {
                            int subObjBase = *(int *)(base + 0x48 + objIndex) + subObjIndex;
                            if (*(char *)(subObjBase + 0x24) != '\0') {
                                *(char *)(subObjBase + 0x24) = '\0';
                                FUN_0049fad0(*(int *)(subObjBase + 0x40), 0);
                                base = g_objectManagerBase;
                            }
                            subLoop++;
                            subObjIndex += 0x50;
                        } while (subLoop < subLimit);
                    }

                    // Check main object expiration flag
                    if (*(char *)(base + 0x24 + objIndex) != '\0') {
                        int objId = *objPtr;
                        *(char *)(base + 0x24 + objIndex) = '\0';

                        int globalObj = *(int *)(g_globalManager + 4);
                        int count1 = *(int *)(globalObj + 0x1268);
                        if (count1 > 0) {
                            int offset1 = 0;
                            int idx = 0;
                            do {
                                if (*(int *)(offset1 + 0x1c + *(int *)(globalObj + 0x1240)) == objId) {
                                    bitFieldPtr = (ushort *)(*(int *)(globalObj + 0x123c) + idx * 2);
                                    *bitFieldPtr = *bitFieldPtr | bitMask;
                                }
                                idx++;
                                offset1 += 0x20;
                            } while (idx < count1);
                        }

                        int count2 = *(int *)(globalObj + 0x1fa8);
                        if (count2 > 0) {
                            int offset2 = 0;
                            int idx = 0;
                            do {
                                if (*(int *)(offset2 + 0x1c + *(int *)(globalObj + 0x1f80)) == objId) {
                                    bitFieldPtr = (ushort *)(*(int *)(globalObj + 0x1f7c) + idx * 2);
                                    *bitFieldPtr = *bitFieldPtr | bitMask;
                                }
                                idx++;
                                offset2 += 0x20;
                            } while (idx < count2);
                        }

                        if (g_expireCallback != (FuncPtr)0x0) {
                            g_expireCallback(objId, 0);
                            bitMask = g_currentBitMask;
                        }
                    }
                }
                objIndex += 0x60; // Next slot
            } while (objIndex < 0x3000);

            g_expireProcessingActive = 0;
            FUN_004299f0(); // Post-processing cleanup
        }
        return;
    }

    // Fallback: initialize global singleton vtable (if not yet ready)
    int *vtablePtr = (int *)(g_untrackedVar + 0x14);
    **(int **)(g_untrackedVar + 0x14) = &VTABLE_0110b784;
    *vtablePtr = *vtablePtr + 4;
    return;
}