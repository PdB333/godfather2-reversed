// FUNC_NAME: StreamManager::setActiveSlot
// Function address: 0x008dd250
// Sets the active slot in the stream manager's linked list and handles state transitions.
// Offsets:
//   +0x184: m_state (int) - current state (2, 3, or other)
//   +0x194: m_listHead (int*) - pointer to head of linked list (pointer-to-node)
//   +0x198: m_prevLinkBackup (int) - backup of the previous node's prevLink field
//   Node at +0x48 within slot object: contains next pointer at +0x0? and prevLink at +0x4.
void __thiscall StreamManager::setActiveSlot(int this, int slotPtr)
{
    int *headPointer;  // Pointer to the list head field at this+0x194
    int nodePtr;       // Pointer to the actual node (inside the slot object, offset 0x48)

    headPointer = (int *)(this + 0x194);

    // If slotPtr is zero, keep nodePtr as zero; otherwise offset by 0x48 to get the node.
    if (slotPtr == 0) {
        nodePtr = 0;
    } else {
        nodePtr = slotPtr + 0x48;
    }

    // Replace the list head if the new node differs from the current one.
    if (*headPointer != nodePtr) {
        // If the current head is non-null, remove it from the list.
        if (*headPointer != 0) {
            unlinkOldHead(headPointer);
        }
        // Set the new head.
        *headPointer = nodePtr;
        if (nodePtr != 0) {
            // Backup the new node's prevLink (at +0x4) into this+0x198.
            *(int *)(this + 0x198) = *(int *)(nodePtr + 4);
            // Update the new node's prevLink to point back to the headPointer field.
            *(int **)(nodePtr + 4) = headPointer;
        }
    }

    // State-dependent behavior.
    if (*(int *)(this + 0x184) == 2) {
        handleState2();
    } else if (*(int *)(this + 0x184) == 3) {
        handleState3();
    } else {
        handleStateOther();
    }
    return;
}