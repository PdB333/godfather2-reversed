// FUNC_NAME: NetConnection::processAcknowledge
// Function address: 0x0063eb30
// Role: Processes an acknowledgment from a received packet, updates bitfield and sequence numbers.

// Assumed class from TNL (Torque Network Library)
// Contains packet window management with 32-slot windows, each slot has a 64-bit mask.

// Forward declarations of called functions
void FUN_00642ec0(void); // Possibly sendFailedAck or handleMissingPacket
void FUN_006438e0(uint param1, uint param2); // Possibly sendRawPacket or queuePacket

// Structure representing the acknowledgment info from a packet (passed in EDI)
struct PacketAckInfo {
    int type;            // +0x00: Packet type (0, 0xC, or other)
    int slotIndex;       // +0x04: Index into the packet window's bitfield array
    int pad1[2];         // +0x08, +0x0C
    int* sequencePtr;    // +0x14: Pointer to a sequence number (e.g., outgoing sequence)
    int pad2;            // +0x18
    int slot;            // +0x1C: Slot number (0-based or 1-based?)
    int needsAck;        // +0x20: Non-zero if an ACK should be sent back
};

// This function processes the acknowledgment and updates the connection state.
// It is called when a received packet indicates it has acknowledged our previous packets.
// The 'this' pointer is in EAX, packet info in EDI (__thiscall? Actually __fastcall with ECX=this, EDX=packet? Ghidra shows in_EAX and unaff_EDI)
void __thiscall NetConnection::processAcknowledge(int* thisPtr, PacketAckInfo* ackInfo)
{
    uint* pBitfieldEntry;
    uint combinedFlags;
    int sequenceNumber;
    uint dataPtr;

    // Only proceed if the packet indicates an ACK is needed
    if (ackInfo->needsAck != 0) {
        if (ackInfo->type == 0xC) {
            // Type 0xC: Standard ACK
            // Get the bitfield entry for this slot index
            // *thisPtr is a pointer to a base address of bitfield array
            // +0x0C from that base gives the array data
            pBitfieldEntry = (uint*)(*thisPtr + 0xC) + ackInfo->slotIndex;
            // Clear bits 6-11 in the bitfield (mask out the ack flags for this slot)
            *pBitfieldEntry = *pBitfieldEntry & 0xFFFF803F;
            // Prepare data for the acknowledgment packet
            dataPtr = *(uint*)(thisPtr[3] + 8); // Probably a timestamp or sequence buffer base
            // Combine slot, sequence number, and ack flag
            combinedFlags = (ackInfo->slot * 0x40) - 0x40U   // Slot offset in bits (0x40 = 64 bits per slot)
                          | (*(int*)(ackInfo->sequencePtr + 4) << 0x18) // Sequence number in upper 8 bits? Actually shift by 0x18 (24) puts it in byte 3
                          | 0x20; // Set bit 5 indicating ack type
        } else {
            // Non-standard type (type != 0 and type != 0xC)
            if (ackInfo->type != 0) {
                // Unknown type, call error/fail handler
                FUN_00642ec0();
            }
            // For type 0 or after fail, construct a nack or different flag
            dataPtr = *(uint*)(thisPtr[3] + 8);
            combinedFlags = (ackInfo->slot * 0x40) - 0x21U
                          | (*(int*)(ackInfo->sequencePtr + 4) << 0x18)
                          | 0x1F; // Set lower 5 bits (31) for nack?
        }
        // Send the acknowledgment packet (or queue it)
        FUN_006438e0(combinedFlags, dataPtr);

        // Update the next expected sequence number
        // ackInfo->sequencePtr + 4 contains the sequence we are acknowledging
        // Increment and store in the connection's field at +0x24 (thisPtr[9])
        thisPtr[9] = *(int*)(ackInfo->sequencePtr + 4) + 1;
    }
}