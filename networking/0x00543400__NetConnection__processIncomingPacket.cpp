// FUNC_NAME: NetConnection::processIncomingPacket
#include <cstdint>

// The Godfather 2 - EARS Engine
// Function at 0x00543400: NetConnection::processIncomingPacket
// Processes an incoming packet, performs validation, decoding, and optional acknowledgment.

// External helper from same module (0x00542f80)
extern bool validatePacket(void* packetData, uint32_t sequenceNumber);

// Vtable offsets for this class (derived from NetInterface/NetConnection)
// +0x1F8: decodePacket (decodes raw data into internal format, returns 0 on success)
// +0x1E4: connectionIsReady (returns 0 if data transfer is blocked, non-zero if ready)
// +0x20C: sendAcknowledgment (confirms receipt of packet)
// +0x1EC: storeSequenceNumber (saves the decoded sequence number for ordering)
// +0x210: signalPacketProcessed (notifies upper layers about the received packet)

int __thiscall NetConnection::processIncomingPacket(void* packetData, uint32_t packetSize, uint32_t sequenceNumber)
{
    bool isValid;
    int decodeResult;
    int readyResult;
    uint32_t decodedInfo;  // local_8 - output from decodePacket

    decodedInfo = 0;
    
    // Step 1: Validate the packet integrity (e.g., checksum, flags)
    isValid = validatePacket(packetData, sequenceNumber);
    if (!isValid) {
        return 0;
    }
    
    // Step 2: Decode the packet into internal representation
    // Virtual call via vtable+0x1F8
    decodeResult = (*(this->vtable[0x1F8/4]))(packetData, &decodedInfo);
    if (decodeResult != 0) {
        // Decoding failed – drop the packet
        return 0;
    }
    
    // Step 3: If a "send acknowledgment" flag is set (unaff_retaddr in decompiler),
    // check whether the connection is ready to send back.
    // Note: unaff_retaddr is likely a hidden parameter (e.g., a byte flag from the packet header)
    // For reconstruction, we treat it as a local variable that should be set during decode.
    // The decompiler artifact "unaff_retaddr" is used here; we assume it's part of the output
    // from decodePacket or a field in this. For clarity, we name it "sendAckFlag".
    bool sendAckFlag = (decodedInfo & 0xFF) != 0;  // Assume decodedInfo holds flag in LSB
    
    if (sendAckFlag) {
        // Virtual call via vtable+0x1E4: returns 0 if connection is not ready for data
        readyResult = (*(this->vtable[0x1E4/4]))();
        if (readyResult != 0) {
            // Connection is busy – drop the packet and don't acknowledge
            return 0;
        }
        // Send acknowledgment for this packet
        // Virtual call via vtable+0x20C
        (*(this->vtable[0x20C/4]))(packetData);
    }
    
    // Step 4: Store the sequence number for ordering (virtual call via vtable+0x1EC)
    (*(this->vtable[0x1EC/4]))(sequenceNumber, packetSize);
    
    // Step 5: Signal that the packet has been processed (virtual call via vtable+0x210)
    (*(this->vtable[0x210/4]))(packetData, packetSize);
    
    return 1;  // Success
}