// FUNC_NAME: setEntityWorldTransformAndRegisterForRendering
void setEntityTransformAndRegisterRender(uint entityId, undefined4* pTransform, float extraFloat) {
    // Global hash table for entity lookups (DAT_01223398)
    // Structure at DAT_01223398+8: pointer to hash table array
    // +4: base pointer of bucket pointers
    // +8: number of buckets
    uint* bucketBase = *(uint**)(*(int*)(*(int*)(DAT_01223398 + 8) + 4));
    uint bucketCount = *(uint*)(*(int*)(DAT_01223398 + 8) + 8);
    uint bucketIndex = entityId % bucketCount;
    uint* pNode = bucketBase + bucketIndex * 4; // each bucket is a linked list, first node pointer at bucketBase[bucketIndex]

    // Traverse linked list to find entity with matching ID
    for (pNode = (uint*)*pNode; pNode != nullptr; pNode = (uint*)pNode[2]) {
        if (*pNode == entityId) {
            break;
        }
    }

    uint entityPtr;
    if (pNode != nullptr && pNode + 1 != nullptr) {
        entityPtr = pNode[1]; // entity object pointer stored at offset 4 in node
    } else {
        entityPtr = 0;
    }

    // Copy 4 values from transform parameter to entity offsets
    // +0x30: world position / quaternion (x)
    // +0x34: second component
    // +0x38: third component
    // +0x3c: fourth component (scale or w)
    *(undefined4*)(entityPtr + 0x30) = pTransform[0];
    *(undefined4*)(entityPtr + 0x34) = pTransform[1];
    *(undefined4*)(entityPtr + 0x38) = pTransform[2];
    *(undefined4*)(entityPtr + 0x3c) = pTransform[3];
    // +0x84: additional float (e.g., alpha, time)
    *(float*)(entityPtr + 0x84) = extraFloat;

    // +0x90: entity state (e.g., 0=inactive, 4=removed?)
    int state = *(int*)(entityPtr + 0x90);
    if (state != 0 && state != 4) {
        bool isSpecial;
        int* slotCount;
        int* slotArray;
        int maxSlots;

        // Check if this is a special entity (e.g., skybox, sun)
        // g_specialFloat (DAT_00e2b05c) is a constant, likely -1.0f or 1.0f
        // +0x24: pointer to some group/type structure
        // group+0x14 bit 0x80 indicates a special flag
        if (extraFloat == g_specialFloat && (*(byte*)(*(int*)(entityPtr + 0x24) + 0x14) & 0x80) != 0) {
            isSpecial = true;
            slotCount = &g_specialSlotCount;   // DAT_0119474c
            slotArray = &g_specialSlotArray;   // DAT_01194754
        } else {
            isSpecial = false;
            slotCount = &g_normalSlotCount;    // DAT_01194750
            slotArray = &g_normalSlotArray;    // DAT_0119475c
        }

        // maxSlots: 1 for special, 4 for normal (bit trick)
        maxSlots = (-(uint)isSpecial & 0xfffffffd) + 4; // yields 1 for true, 4 for false

        int slotIndex = 0;
        bool full = (*slotCount == 0); // actually initial false if count>0, but loop will set if not found

        // Try to find an existing slot for the same group (type)
        if (*slotCount > 0) {
            do {
                if (isSpecial || slotArray[slotIndex * 2] == *(int*)(entityPtr + 0x24)) {
                    // Slot matches this entity's group; link it if not already in this slot
                    if (slotArray[slotIndex * 2 + 1] != entityPtr) {
                        *(int*)(entityPtr + 0x20) = slotArray[slotIndex * 2 + 1]; // previous head
                        slotArray[slotIndex * 2 + 1] = entityPtr; // new head
                    }
                    break;
                }
                slotIndex++;
            } while (slotIndex < *slotCount);
            full = (slotIndex == *slotCount);
        }

        // If no existing slot found and there is room, add a new slot
        if (full && slotIndex < maxSlots) {
            *(int*)(entityPtr + 0x20) = 0; // no next
            slotArray[slotIndex * 2 + 1] = entityPtr; // head
            slotArray[slotIndex * 2] = *(int*)(entityPtr + 0x24); // group pointer
            (*slotCount)++;
        }

        // If this is a normal entity (not special), update a global dirty flag
        if (!isSpecial) {
            byte flagByte = FUN_0049f820(); // get current flag byte
            flagByte |= (byte)(1 << (slotIndex & 0x1f)); // set bit for this slot index
            FUN_0049f960(&gCallbackFunction, &flagByte); // propagate dirty flag
        }
    }
}