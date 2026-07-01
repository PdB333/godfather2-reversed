// FUNC_NAME: SimManager_updateAllObjectLists
void SimManager_updateAllObjectLists(uint32_t deltaTime) // param_1 is likely delta time
{
    // Get global SimManager instance (base at 0x0112e2dc)
    // The SimManager structure contains at +0x04: pointer to array of linked list heads (ObjectList*)
    // At +0x08: an index or pointer to the end sentinel value (iVar2)
    SimManager* simMgr = *(SimManager**)0x0112e2dc;

    // Start with the first linked list head from the array
    ObjectList** slotArray = *(ObjectList***)((uint8_t*)simMgr + 0x04);
    ObjectList* head = *slotArray; // first list head
    ObjectList** currentSlotPtr = slotArray;

    // If first head is null, scan forward to find first non-null list head
    if (head == nullptr) {
        currentSlotPtr = slotArray + 1; // start scanning from next slot
        head = *currentSlotPtr;
        while (head == nullptr) {
            currentSlotPtr++;
            head = *currentSlotPtr;
        }
    }

    // Get the sentinel value that marks the end of all lists
    // Stored at offset +0x08 from the SimManager
    uint32_t slotCount = *(uint32_t*)((uint8_t*)simMgr + 0x08);
    ObjectList* endSentinel = slotArray[slotCount]; // either a null or a special sentinel

    // Iterate over all objects in all non-empty linked lists
    while (head != endSentinel) {
        // Process each object in the current list
        processObjectWithDelta(head, deltaTime); // FUN_0088fbb0

        // Move to next node in linked list (next pointer at +0x08 offset within ObjectList)
        head = head->next; // *(int*)(head + 8)

        // If we reached a null next, advance to the next non-null list head
        while (head == nullptr) {
            currentSlotPtr++; // advance to next slot
            head = *currentSlotPtr;
            // Note: the original code reassigns piVar1 = piVar4+1 and piVar4++ which is essentially this advancement
        }
    }
}