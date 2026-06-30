// FUNC_NAME: SimObjectManager::resetAllObjects
void SimObjectManager::resetAllObjects(void)
{
    SimObjectNode** nodeArray = nullptr; // array of pointers to nodes
    int nodeCount = 0;
    SimObjectNode* currentNode = g_objectListHead; // DAT_01205a28

    // First pass: collect all nodes into a dynamic array
    if (g_objectListHead != nullptr) {
        uint arrayCapacity = 1;
        int collected = 0;
        do {
            if ((uint)collected < arrayCapacity) {
                // Grow array (round up to multiple of 16)
                arrayCapacity = ((arrayCapacity - (arrayCapacity & 0xf)) + 0x10);
                SimObjectNode** newArray = (SimObjectNode**)malloc(arrayCapacity * 4);
                if (collected != 0) {
                    SimObjectNode** src = newArray;
                    int remaining = collected;
                    do {
                        if (src != nullptr) {
                            *src = *(SimObjectNode**)((int)nodeArray - (int)newArray + (int)src);
                        }
                        src++;
                        remaining--;
                    } while (remaining != 0);
                }
                free(nodeArray);
                nodeArray = newArray;
            }
            arrayCapacity++;
            if (nodeArray + collected != nullptr) {
                nodeArray[collected] = currentNode;
            }
            currentNode = currentNode->next; // +0x10
            collected++;
        } while (currentNode != nullptr);
        nodeCount = collected;
    }

    // Second pass: process each node and its slot entries
    while (currentNode = g_objectListHead, currentNode != nullptr) {
        uint generationId = currentNode->generationId; // +0x14
        g_objectListHead = currentNode->next; // +0x10
        currentNode->next = nullptr; // +0x10
        currentNode->prev = nullptr; // +0xc
        currentNode->generationId = 0; // +0x14

        if (generationId != 0) {
            // Iterate through slot entries linked from node
            SlotEntry* slotEntry = currentNode->slotListHead; // +0x1c
            while (slotEntry != nullptr) {
                SlotEntry* nextSlot = slotEntry->next; // +0xc
                if (slotEntry->flags == 0) { // +0x4
                    SlotManager* parentMgr = slotEntry->parentManager; // +0x14
                    slotEntry->flags = generationId; // +0x4
                    // Move slot entry to the end of the used slot array
                    int currentSlotCount = parentMgr->usedSlotCount; // +0x200
                    if (slotEntry->slotIndex != currentSlotCount) { // +0x2c
                        // Swap with the entry at currentSlotCount
                        SlotEntry* entryAtCount = parentMgr->slotArray[currentSlotCount]; // +0x1fc
                        entryAtCount->slotIndex = slotEntry->slotIndex; // +0x2c
                        parentMgr->slotArray[slotEntry->slotIndex] = entryAtCount;
                        parentMgr->slotArray[currentSlotCount] = slotEntry;
                        slotEntry->slotIndex = currentSlotCount;
                    }
                    parentMgr->usedSlotCount = currentSlotCount + 1; // +0x200
                } else {
                    slotEntry->flags |= generationId; // +0x4
                }
                slotEntry = nextSlot;
            }
        }
    }

    g_objectListHead = nullptr; // DAT_01205a28
    free(nodeArray);
    return;
}