// FUNC_NAME: PacketNode::setFrom
void __thiscall PacketNode::setFrom(int this, int other) {
    int *listPtr;
    int target;

    // Get the global list head manager (likely a singleton for packet lists)
    target = GetGlobalListHead();
    if (target != 0) {
        target = target + -0x58; // Adjust to reach base of list structure? (offset -0x58)
    }
    listPtr = (int *)(this + 4); // Pointer to first list entry (prev/next?) at +4
    if (target != 0) {
        target = target + 0x48; // Offset to the actual list head node (0x48)
    }
    if (*listPtr != target) {
        if (*listPtr != 0) {
            RemoveListEntry(listPtr); // Detach from previous list
        }
        *listPtr = target; // Attach to new list
        if (target != 0) {
            *(int *)(this + 8) = *(int *)(target + 4); // Set this->next to head->next
            *(int **)(target + 4) = listPtr; // head->next = this (via pointer to pointer)
        }
    }

    // Repeat second list pointer at +0xC
    target = GetGlobalListHead();
    if (target != 0) {
        target = target + -0x58;
    }
    listPtr = (int *)(this + 0xc);
    if (target != 0) {
        target = target + 0x48;
    }
    if (*listPtr != target) {
        if (*listPtr != 0) {
            RemoveListEntry(listPtr);
        }
        *listPtr = target;
        if (target != 0) {
            *(int *)(this + 0x10) = *(int *)(target + 4);
            *(int **)(target + 4) = listPtr;
        }
    }

    // Copy the core data block (0x30 bytes) from 'other' starting at offset 0x10
    // This includes fields like ID, flags, payload pointers, etc.
    *(long long *)(this + 0x14) = *(long long *)(other + 0x10);
    *(int *)(this + 0x1c) = *(int *)(other + 0x18);
    *(long long *)(this + 0x20) = *(long long *)(other + 0x1c);
    *(int *)(this + 0x28) = *(int *)(other + 0x24);
    *(int *)(this + 0x2c) = *(int *)(other + 0x28);
    *(int *)(this + 0x30) = *(int *)(other + 0x2c);
    *(int *)(this + 0x34) = *(int *)(other + 0x30);
    *(int *)(this + 0x38) = *(int *)(other + 0x34);
    *(int *)(this + 0x3c) = *(int *)(other + 0x38);
    *(int *)(this + 0x40) = *(int *)(other + 0x3c);
    *(int *)(this + 0x44) = *(int *)(other + 0x40);
}