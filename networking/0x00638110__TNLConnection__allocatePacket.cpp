// FUNC_NAME: TNLConnection::allocatePacket

// Allocate a packet buffer from the connection's packet pool.
// The packet type parameter determines the allocation size: (type * 8) + 0x10 bytes.
// The allocated buffer is prepended to a singly-linked list owned by the manager (+0x10).
// Packet header layout (0x10 bytes):
//   +0x00: next pointer (previous head of list)
//   +0x04: flags byte (set to 6)
//   +0x05: flags byte (set to 0)
//   +0x06: flags byte (set to 1)
//   +0x07: packet type byte (from argument)
//   +0x08: payload data (size depends on type)

void TNLConnection::allocatePacket(int packetType)
{
    uint allocSize = packetType * 8 + 0x10;
    PacketHeader* newPacket = nullptr;

    if (allocSize == 0) {
        // Intentionally fall through – will write to null (likely unreachable)
    }
    else if (allocSize < 0xfffffffd) {
        // Allocate from global heap (DAT_012059dc is a custom malloc)
        newPacket = (PacketHeader*)malloc(0, allocSize);
        if (newPacket == nullptr) {
            if (this != nullptr) {
                // Out‑of‑memory handler (FUN_00635a80)
                handleAllocFailure();
                return;
            }
            // If this is null, fall through (newPacket remains null)
        }
    }
    else {
        // Overflow or invalid size (FUN_00633920)
        allocErrorHandler();
    }

    if (this != nullptr) {
        // Update total allocated size in the packet manager (offset +0x24)
        PacketManager* mgr = *(PacketManager**)((char*)this + 0x10);
        mgr->totalAllocated += allocSize;
    }

    PacketManager* mgr = *(PacketManager**)((char*)this + 0x10);
    // Insert at head of linked list (mgr->packetHead at +0x0c)
    newPacket->next = mgr->packetHead;
    mgr->packetHead = newPacket;

    // Initialize packet header
    newPacket->type = packetType;              // byte at +0x07
    newPacket->flags[1] = 0;                   // byte at +0x05
    newPacket->flags[0] = 6;                   // byte at +0x04
    newPacket->flags[2] = 1;                   // byte at +0x06
    return;
}