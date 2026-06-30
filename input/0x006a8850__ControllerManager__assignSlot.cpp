// FUNC_NAME: ControllerManager::assignSlot
void __thiscall ControllerManager::assignSlot(int this, SlotNode* pSlotNodeA, SlotNode* pSlotNodeB)
{
    SlotData* pDataA;
    byte flagsA;
    int idA;
    int idB;
    bool bSameTarget;
    bool bDataAChanged;
    int iVar8;
    int iVar9;
    byte newSlotIndex;
    int iVar3;
    int iVar4;
    byte flagsB;
    SlotNode** ppCurrentNode;

    // Check if this manager is enabled (offset +0x10)
    if (*(char*)(this + 0x10) == 0) {
        return;
    }

    idA = pSlotNodeA->id; // +0x00
    bSameTarget = false;

    // Check if both slots point to the same target (same ID and same data pointer)
    if ((idA == pSlotNodeB->id) && ((idA == 0) || (pSlotNodeA->data == pSlotNodeB->data))) {
        bSameTarget = true;
    }

    iVar9 = 0;
    bDataAChanged = false;
    iVar8 = 0;

    if (!bSameTarget) {
        iVar8 = idA;
        if (idA != 0) {
            pDataA = pSlotNodeA->data; // +0x08
            // Clear bit 3 (0x08) of data flags (offset +0x21) - mark as not pending
            *(byte*)(pDataA + 0x21) &= 0xF7;
            bDataAChanged = true;
        }
    }

    // Reset slot index in this manager (offset +0x20)
    *(byte*)(this + 0x20) = 0;

    idB = pSlotNodeB->id;
    if (idB == 0) {
        // If target slot is empty, detach old data if it was changed
        if (bDataAChanged) {
            // Clear bit 1 (0x02) of data flags - mark as inactive
            *(byte*)(iVar9 + 0x21) &= 0xFD;
            // Detach slot A (ID, data, attach=1, detach=0, unknown)
            attachSlot(iVar8, iVar9, 1, 0, 0);
        }
    }
    else {
        pDataB = pSlotNodeB->data; // +0x08
        flagsB = *(byte*)(pDataB + 0x21);
        // Set bit 3 (0x08) - mark as pending
        *(byte*)(pDataB + 0x21) = flagsB | 8;

        if (((flagsB & 2) == 0) || bSameTarget) {
            // If not already active, or same target, allocate slot index if needed
            if ((flagsB & 0x10) == 0) {
                newSlotIndex = allocateSlotIndex(); // FUN_006a8020
                *(byte*)(pDataB + 0x21) |= 0x10; // Set bit 4 - mark as allocated
                *(byte*)(pDataB + 0x20) = newSlotIndex;
            }
            // Set bit 1 (0x02) - mark as active
            *(byte*)(pDataB + 0x21) |= 2;

            if (bDataAChanged) {
                // Detach old slot A
                attachSlot(iVar8, iVar9, 1, 0, 0);
            }
            // Attach new slot B (ID, data, attach=0, detach=1, unknown)
            attachSlot(idB, pDataB, 0, 1, 0);
        }
        // Copy slot index from data to this manager
        *(byte*)(this + 0x20) = *(byte*)(pDataB + 0x20);
    }

    // Update the linked list of slot nodes in this manager
    ppCurrentNode = (SlotNode**)(this + 0x14);
    if (ppCurrentNode != pSlotNodeB) {
        idB = pSlotNodeB->id;
        if (*ppCurrentNode != idB) {
            if (*ppCurrentNode != 0) {
                freeSlotNode(ppCurrentNode); // FUN_004daf90
            }
            *ppCurrentNode = idB;
            *(int*)(this + 0x18) = *(int*)(idB + 4); // Copy next pointer
            *(int**)(idB + 4) = ppCurrentNode; // Insert into list
        }
    }
    // Store the data pointer from the target slot
    *(SlotData**)(this + 0x1C) = pSlotNodeB->data;
}