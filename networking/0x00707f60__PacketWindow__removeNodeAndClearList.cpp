// FUNC_NAME: PacketWindow::removeNodeAndClearList
void __thiscall NetConnection::clearPacketWindowList(int this, int packetNode) {
    // this +0x2a0 is a pointer to a linked list head (m_packetWindowList)
    int* headPtr = (int*)(this + 0x2a0);
    if (*headPtr == 0) {
        return;
    }

    // The vtable pointer for the node type is stored on the stack (not used directly)
    void** vtableSlot = &PTR_FUN_00e31e2c; // vtable for PacketNode? (offset 0x0)

    // Determine the node associated with packetNode
    // packetNode is a pointer to a parent object; +0x48 is offset to the node's link field
    int* targetNode = (packetNode != 0) ? (int*)(packetNode + 0x48) : 0;

    int* savedNext = 0;
    if (targetNode != 0) {
        // Save the node's next pointer (at +0x4)
        savedNext = (int*)*(targetNode + 1);
        // Detach the node by making it point to itself (sentinel for removal)
        *(targetNode + 1) = (int)&targetNode;
    }

    // Save old head and clear the list
    int* savedHead = (int*)*headPtr;
    FUN_00408a00(&savedHead, 0); // likely a function to unlink or clear the list
    FUN_00408310(headPtr); // deallocate or finalize list structure
    *headPtr = 0;

    // Delete the removed node if present
    if (targetNode != 0) {
        FUN_004daf90(targetNode); // destructor / deallocation for the node
    }
}