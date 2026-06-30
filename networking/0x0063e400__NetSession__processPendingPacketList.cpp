// FUNC_NAME: NetSession::processPendingPacketList

void NetSession::processPendingPacketList(void)
{
    // Remove the first item from the pending packet linked list (head at this+0x14)
    PacketNode* pNode = *(PacketNode**)(this + 0x14);
    *(int*)(this + 0x14) = *(int*)pNode; // Move head to next node

    // Process the packet (likely handles sequence, ack, etc.)
    FUN_0063df30();

    // If the node has a flag at offset 0xC (might indicate reliable or ack required)
    if (pNode->flags != 0) {
        // Build a packet command (shifted address + type 0x21) and send via buffer at this+0xC+8
        FUN_006438e0(pNode->address << 0x18 | 0x21, *(void**)(*(int*)(this + 0xC) + 8));
    }

    // Reset sliding window state: current send window base = next expected ack, etc.
    *(int*)(this + 0x24) = *(int*)(this + 0x34);
    *(int*)(this + 0x1C) = *(int*)(this + 0x18);

    // Finalize processing (e.g., update timers or retransmission)
    FUN_00642880();
}