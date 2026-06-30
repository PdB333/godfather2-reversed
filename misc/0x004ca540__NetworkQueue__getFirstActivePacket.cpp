// FUNC_NAME: NetworkQueue::getFirstActivePacket
// Address: 0x004ca540
// Traverses a linked list of packets (next pointer at +0x8, active flag at +0x15)
// and returns the first packet with a non-zero active flag.
// The list is assumed to be non-empty and eventually contain an active packet.

struct PacketRecord {
    char gap_0x0[8];
    PacketRecord* next;          // +0x8
    char gap_0xc[9];
    char activeFlag;             // +0x15
};

void* NetworkQueue::getFirstActivePacket() {
    PacketRecord* node = *(PacketRecord**)((char*)this + 8);
    while (node->activeFlag == 0) {
        node = node->next;
    }
    return node;
}