// FUNC_NAME: SomeManager::processListEntries
// Address: 0x00785d60
// Role: Iterates a linked list starting from *(param2+0x88), calling processListNode() for each entry.
//       The number of iterations is determined by this->count (offset +0x1a3c).
//       Each call advances the pointer to the next node via the process function.
void __thiscall SomeManager::processListEntries(SomeManager* this, /* ListContainer* */ SomeContainer* listContainer) {
    // Read the head pointer from the container at offset +0x88
    ListNode* currentNode = *reinterpret_cast<ListNode**>(reinterpret_cast<uint8_t*>(listContainer) + 0x88);
    // Number of entries to process, stored in this object at offset +0x1a3c
    uint32_t entryCount = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x1a3c);

    for (uint32_t i = 0; i < entryCount; i++) {
        // Call function that processes the node and likely updates the pointer to the next node
        processListNode(&currentNode);
    }
}