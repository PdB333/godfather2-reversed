// FUNC_NAME: SomeManager::processActiveControllers
void __fastcall SomeManager::processActiveControllers(void)
{
    char bAnyProcessed;
    byte bFlag2, bFlag3;
    int nodePtr;
    int local_40, local_3c, local_38, local_34, local_30, local_2c, local_28, local_24, local_20, local_1c, local_18, local_14, local_10, local_c, local_8, local_4;

    if (*(int *)(this + 0x9c) == 0) { // +0x9c: pointer to a settings/manager object
        ensureInitialized();
    }
    preUpdate();           // FUN_006bacb0
    updateTimers();        // FUN_006bba40

    // Check if the manager is valid and conditions are met
    if ((*(int *)(this + 0x9c) != 0) && 
        (nodePtr = checkCondition1(), nodePtr != 0) &&
        (bAnyProcessed = checkCondition2(), bAnyProcessed != 0)) {
        
        // Check if bit 3 of flags is set (0x08)
        if ((*(uint *)(this + 0x84) >> 3 & 1) != 0) { // +0x84: flags
            nodePtr = *(int *)(*(int *)(this + 0x9c) + 0xfc); // get some sub-object
            if (nodePtr == 0) goto LABEL_CLEANUP;
            // Check if the sub-object's children have specific type IDs
            if (((*(int *)(nodePtr + 0x14) == 0) || 
                 (*(int *)(*(int *)(nodePtr + 0x14) + 0x54) == 0x637b907)) ||
                ((*(int *)(nodePtr + 0x18) == 0) || 
                 (*(int *)(*(int *)(nodePtr + 0x18) + 0x54) == 0x637b907)))
                goto LABEL_CLEANUP;
        }

        nodePtr = *(int *)(this + 0x9c);
        // If bit 0 of flags is set and timestamp condition
        if ((nodePtr != 0) && ((*(byte *)(this + 0x84) & 1) != 0) &&
            (*(uint *)(this + 0x98) < *(uint *)(nodePtr + 0xac))) {
            *(uint *)(this + 0x98) = *(uint *)(nodePtr + 0xac); // copy timestamp
        }

        local_38 = nodePtr + 0xa8;  // some offset for pointer?
        local_3c = this;            // this pointer
        local_34 = getSomeObject(); // FUN_006ba3c0
        local_24 = nodePtr + 0x84;
        local_20 = 0xffffffff;
        local_c = 0xffffffff;
        local_40 = *(int *)(this + 0x60); // linked list head node
        local_10 = nodePtr + 0x9c;
        local_30 = 0;
        local_2c = 0;
        local_1c = 0;
        local_18 = 0;
        local_8 = 0;
        local_4 = 0;
        bAnyProcessed = 1;
        local_28 = this;
        local_14 = this;

        // Process each node in the linked list until none left or nothing processed
        while ((local_40 != 0) && (bAnyProcessed != 0)) {
            bAnyProcessed = 0;
            // Bit 0: process type A
            if ((*(byte *)(this + 0x84) & 1) != 0) {
                bAnyProcessed = processListNode(&local_40); // FUN_006bbde0
            }
            // Bit 1: process type B
            if ((*(uint *)(this + 0x84) >> 1 & 1) != 0) {
                bFlag2 = processListNode(&local_40);
                bAnyProcessed = bAnyProcessed | bFlag2;
            }
            // Bit 2: process type C
            if ((*(uint *)(this + 0x84) >> 2 & 1) != 0) {
                bFlag3 = processListNode(&local_40);
                bAnyProcessed = bAnyProcessed | bFlag3;
            }
        }
        // Accumulate processed count
        *(int *)(this + 0x94) += local_2c; // +0x94: count of processed items
    }

LABEL_CLEANUP:
    postUpdate(); // FUN_006badb0
    return;
}