// FUNC_NAME: SlotManager::freeSlot
void __fastcall SlotManager::freeSlot(void* unused, int slotIndex) {
    // slotIndex is passed in EAX register (in_EAX), max 16 slots
    if (slotIndex >= 16) return;

    // Slot data starts at this+0x14, each slot is 0x18 bytes
    Slot* slot = reinterpret_cast<Slot*>(reinterpret_cast<char*>(this) + 0x14 + slotIndex * 0x18);
    if (slot == nullptr) return;

    // Clear all flags except bit 2 (0x4) at offset +8
    slot->flags = slot->flags & 4;

    // Get linked list head at slot+0xC (pool of items attached to this slot)
    Node* node = reinterpret_cast<Node*>(slot->listHead);
    slot->listHead = nullptr;

    // Move all nodes from the slot's list to the global free list at this+0x2D8
    while (node != nullptr) {
        Node* next = reinterpret_cast<Node*>(node->next);
        node->next = reinterpret_cast<Node*>(this->freeListHead);
        this->freeListHead = node;
        node = next;
    }

    // Notify system that slot was freed (two bytes at this+0x195, +0x196)
    FUN_00410b40(slotIndex, *(byte*)(reinterpret_cast<char*>(this) + 0x195),
                 *(byte*)(reinterpret_cast<char*>(this) + 0x196));
}