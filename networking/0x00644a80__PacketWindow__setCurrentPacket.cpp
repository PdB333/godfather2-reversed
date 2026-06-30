// FUNC_NAME: PacketWindow::setCurrentPacket
void __thiscall PacketWindow::setCurrentPacket(int param_2, bool param_3) {
    // +0x440: currentPacket (Node*)
    // +0x30:  listHead (sentinel node)
    // +0x3c:  listTail (last node in list)
    // +0x46c: flag (e.g., isWindowFull)
    // +0x468: computedEndPointer

    Node* oldCurrent = *(Node**)((int)this + 0x440);
    *(Node**)((int)this + 0x440) = (Node*)param_2;     // set new current packet

    // Initialize new node as a single-element circular list
    ((Node*)param_2)->prev = (Node*)param_2;             // +0x0c
    ((Node*)param_2)->next = ((Node*)param_2)->prev;     // +0x08 = +0x0c

    // If old current is a real node (not the sentinel head) and param_3 is true,
    // move it to the tail of the list.
    if (oldCurrent != (Node*)((int)this + 0x30) && param_3) {
        Node* oldTail = *(Node**)((int)this + 0x3c);     // +0x3c
        oldCurrent->next = (Node*)((int)this + 0x30);    // point to head sentinel
        oldCurrent->prev = oldTail;
        *(Node**)((int)this + 0x3c) = oldCurrent;        // new tail
        oldTail->next = oldCurrent;
    }

    // If the window is not full (flag at +0x46c == 0), compute an end pointer
    if (*(char*)((int)this + 0x46c) == '\0') {
        // node->field_at_4 is some size/offset; compute alignment then add node base
        uint sizeField = *(uint*)(param_2 + 4);           // +0x04
        uint alignedHalf = (sizeField >> 1) & 0x3ffffffc;
        *(uint*)((int)this + 0x468) = (uint)param_2 + alignedHalf;
    }
}