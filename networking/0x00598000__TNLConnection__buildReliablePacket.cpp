// FUNC_NAME: TNLConnection::buildReliablePacket
// Function at 0x00598000
// Builds a reliable packet header by allocating a buffer from the global packet manager
// and writing key fields: flags, type, and sequence number.
// Returns the size of the packet header (8 bytes).

int TNLConnection::buildReliablePacket()
{
    // Global packet manager singleton (e.g., TNL::PacketManager)
    // The vtable pointer at *DAT_01205590 provides methods at offsets
    PacketManager* pktMgr = *gPacketManager; // DAT_01205590

    // Packet header fields to be written
    uint packetFlags = 0x700;       // +0x04: flags (reliable, sequenced, etc.)
    uint packetType  = 2;           // +0x05: packet type identifier (e.g., RELIABLE)

    // Step 1: Allocate a new packet buffer from the manager
    // Virtual function at offset 0x10 (likely allocatePacket)
    pktMgr->allocatePacket();

    // Step 2: Write the header fields into the allocated buffer
    // Each call writes sizeof(uint) bytes from the given pointer
    // The third argument (count=1) indicates a single value write

    // Write flags at this + 4
    pktMgr->writeField(this + 4, &packetFlags, 1);

    // Write type at this + 5
    pktMgr->writeField(this + 5, &packetType, 1);

    // Write sequence number (stored at this + 2) into this + 6
    // This copies the connection's current send sequence counter
    pktMgr->writeField(this + 6, &this[2], 1);  // iStack_24 = this + 2

    // Return the base header size (8 bytes)
    return 8;
}