// FUNC_NAME: Connection::handleIncomingPacket
// Function address: 0x00622110
// Handles incoming packet processing, duplicate detection, and out-of-order buffering.
// Part of TNL (Torque Network Library) connection layer.

// Assumed class layout (offsets relative to this):
// +0x00: vtable
// +0x1C: pointer to pointer to current packet buffer slot (Packet**)
// +0x20: int m_connectionState (0 = disconnected/uninitialized)

// External functions (not reconstructed):
// FUN_00622c80 - storePacket(Connection*, undefined4* outData, bool isReliable, uint* sequencePtr)
// FUN_00b97aea - assert(condition) (debug assertion)
// FUN_006242f0 - advancePacketBuffer()
// FUN_00623fa0 - lockPacketBuffer(Connection*)
// FUN_006229f0 - checkBufferIntegrity() (returns bool)
// FUN_00622aa0 - getCurrentPacketData(Connection*, int* outPacket, uint* sequencePtr)

#include "stdint.h"

// Forward declare types (incomplete, for readability)
class Connection;
typedef uint32_t Packet; // Simplified; actual packet header has fields at known offsets
// Packet structure assumed:
// +0x00: next pointer or data start
// +0x08: possibly pointer to flags
// +0x0C: uint32_t sequenceNumber
// +0x08 -> +0x25: byte flag (e.g., duplicate/reliable flag)

undefined4* Connection::handleIncomingPacket(
    Connection* this,
    undefined4* outData,          // Output buffer for two dwords
    uint* sequencePtr,            // Pointer to sequence number of incoming packet
    Connection* sourceConnection, // Source connection for validation (0 or this)
    Packet* packet                // Pointer to incoming packet data
)
{
    char bVar1;
    undefined4* resultPtr;
    bool bVar2;
    int local_c; // packet index / temp
    Packet* currentPacket;

    // If connection is not active, store packet directly as reliable
    if (*(int*)(this + 0x20) == 0) {
        storePacket(this, outData, 1, sequencePtr);
        return outData;
    }

    // Get current packet from connection's buffer
    // *(int*)(this + 0x1C) is a pointer to a pointer to the current packet slot
    currentPacket = (Packet*)(**(int**)(this + 0x1C)); // Read two levels of indirection

    // Validate source connection (anti-aliasing check)
    if (sourceConnection == 0 || sourceConnection != this) {
        // Typically an assert: "Invalid source connection"
        debugAssert();
    }

    // Compare the incoming packet with the current packet in the buffer
    if (packet == currentPacket) {
        // Same packet: check sequence number
        if (*sequencePtr < *(uint32_t*)(packet + 0x0C)) {
            // Incoming sequence older than stored; discard (store as duplicate? flag 1 = already have it)
            storePacket(this, outData, 1, sequencePtr);
            return outData;
        }
        // Otherwise, sequence is newer or equal; fall through to use current packet data
    }
    else {
        // Different packet: re-assign currentPacket after potential buffer changes
        currentPacket = *(Packet**)(*(int*)(this + 0x1C));
        if (sourceConnection == 0 || sourceConnection != this) {
            debugAssert();
        }
        if (packet == currentPacket) {
            // Now matches after re-read? Check if new sequence is ahead
            if (*(uint32_t*)(*(int*)(*(int*)(this + 0x1C) + 8) + 0x0C) < *sequencePtr) {
                storePacket(this, outData, 0, sequencePtr);
                return outData;
            }
        }
        else {
            // Packet is distinct from current buffer slot
            bVar2 = *(uint32_t*)(packet + 0x0C) < *sequencePtr;
            if (*sequencePtr < *(uint32_t*)(packet + 0x0C)) {
                // Sequence is behind; advance/update buffer
                advancePacketBuffer();
                if (*(uint32_t*)(packet + 0x0C) < *sequencePtr) {
                    // After advance, still behind? Check flag at packet+8 -> +0x25
                    if (*(char*)(*(int*)(packet + 8) + 0x25) == '\0') {
                        storePacket(this, outData, 1, sequencePtr);
                        return outData;
                    }
                    storePacket(this, outData, 0, sequencePtr);
                    return outData;
                }
                bVar2 = *(uint32_t*)(packet + 0x0C) < *sequencePtr;
            }
            if (bVar2) {
                // Sequence is ahead: lock buffer, check integrity, and compare again
                currentPacket = *(Packet**)(*(int*)(this + 0x1C));
                local_c = (int)this;
                lockPacketBuffer(this);
                bVar1 = checkBufferIntegrity();
                if (bVar1 != '\0' || *sequencePtr < *(uint32_t*)(packet + 0x0C)) {
                    if (*(char*)(*(int*)(packet + 8) + 0x25) == '\0') {
                        storePacket(this, outData, 1, sequencePtr);
                        return outData;
                    }
                    storePacket(this, outData, 0, sequencePtr);
                    return outData;
                }
            }
        }
    }

    // If we reach here, packet is acceptable; retrieve data from current packet buffer
    resultPtr = (undefined4*)getCurrentPacketData(this, &local_c, sequencePtr);
    *outData = *resultPtr;
    outData[1] = resultPtr[1];
    return outData;
}