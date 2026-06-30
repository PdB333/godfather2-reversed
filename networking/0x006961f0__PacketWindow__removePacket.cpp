// FUNC_NAME: PacketWindow::removePacket
// Address: 0x006961f0
// This function removes a packet node from a doubly linked list (packet window) and returns pointers to the node and its next.
// Struct PacketWindow: +0x04 = head pointer (PacketNode*), +0x08 = count (int)
// PacketNode: +0x00 = next, +0x04 = prev, +0x08 = sequenceNumber

void __thiscall PacketWindow::removePacket(PacketWindow* this, PacketNode** out, PacketNode* rangeStart, PacketNode* rangeEnd, PacketNode* targetStart, PacketNode* targetEnd)
{
    PacketNode* head;
    PacketNode* firstNode;
    int count;

    head = *(PacketNode**)(this + 4);
    firstNode = *head; // dereference head's next pointer to get the first real node

    // Validation: rangeStart must be non-null and equal to this (list root)
    if ((rangeStart == 0) || (rangeStart != (PacketNode*)this)) {
        assertionFailed(); // FUN_00b97aea
    }

    // If the node to remove is the first node after the head
    if (rangeEnd == firstNode) {
        firstNode = *(PacketNode**)(this + 4);
        if ((targetStart == 0) || (targetStart != (PacketNode*)this)) {
            assertionFailed();
        }
        if (targetEnd == firstNode) {
            // Remove the first node from the list
            unlinkNode(*(PacketNode**)( *(int*)(this + 4) + 4 )); // FUN_00695700(unlink the node after first)
            *(PacketNode**)(*(int*)(this + 4) + 4) = *(PacketNode**)(this + 4); // set first->next to head? (circular)
            *(int*)(this + 8) = 0; // reset count to zero
            // set prev pointer of first node to itself
            *(PacketNode*)*(PacketNode**)(this + 4) = *(PacketNode**)(this + 4);
            // set next of first node to itself
            *(PacketNode**)(*(int*)(this + 4) + 8) = *(int*)(this + 4);
            // get the original next pointer (now the head's next after removal)
            firstNode = **(PacketNode***)(this + 4);
            out[0] = (PacketNode*)this; // return list head
            out[1] = firstNode; // return the next pointer
            return;
        }
    }

    // Generic case: iterate through the list to find the range
    while (true) {
        if ((rangeStart == 0) || (rangeStart != targetStart)) {
            assertionFailed();
        }
        if (rangeEnd == targetEnd) break;
        advanceList(); // FUN_006941f0
        copyNodePair(local_8, rangeStart, rangeEnd); // FUN_00695ac0
    }
    out[0] = rangeStart;
    out[1] = rangeEnd;
    return;
}