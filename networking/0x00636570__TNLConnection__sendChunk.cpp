// FUNC_NAME: TNLConnection::sendChunk
#include <cstdint>

class TNLConnection {
public:
    // +0x0c: uint32_t currentHeader;   // first word of current packet in buffer
    // +0x14: int32_t writeOffset;      // offset from buffer base to current write position
    // +0x18: int32_t remainingSize;    // = packetSize - 8 + packetCount * 8
    // +0x1c: int32_t packetSize;       // base size of a single packet
    // +0x20: int32_t packetCount;      // number of packets per chunk
    // +0x28: int32_t bufferBase;       // start of the packet buffer
    // +0x2c: uint16_t maxPackets;      // maximum allowed packets (compared to 0x1000)
    // +0x2e: uint16_t sequenceNumber;  // sequence number for ordering
    // +0x31: uint8_t flags;            // misc flags
    // +0x54: void* currentPacket;      // temporarily stores the packet data pointer

private:
    int32_t validateSlot();          // FUN_00635ab0
    void copyPacketData();           // FUN_006382a0
    void advanceSequence();          // FUN_006359f0
    void flushBuffer();              // FUN_00635c10

public:
    int32_t sendChunk(void* packetData);
};

// Address: 0x00636570
int32_t TNLConnection::sendChunk(void* packetData) {
    // Save current state before building the packet chunk
    uint16_t savedSequence = this->sequenceNumber;       // +0x2e
    uint8_t savedFlags = this->flags;                    // +0x31
    int32_t savedWriteOffset = this->writeOffset;        // +0x14
    int32_t base = this->bufferBase;                     // +0x28
    void* savedPacket = this->currentPacket;             // +0x54

    this->currentPacket = packetData;                    // Store the packet data to process

    int32_t result = this->validateSlot();               // Check if there's room in the window
    if (result == 0) {
        // Failed – restore the packet pointer and return failure
        this->currentPacket = savedPacket;
        return 0;
    }

    // Build the packet chunk: copy data and update sequence
    this->copyPacketData();                              // Copy packet into buffer
    this->advanceSequence();                             // Increment sequence number

    // Restore the saved sequence/flags (they are only used temporarily)
    this->sequenceNumber = savedSequence;
    this->flags = savedFlags;

    // Update the write pointer: base + (oldWriteOffset - base) essentially
    uint32_t* newWritePtr = (uint32_t*)(base + (savedWriteOffset - base));
    this->writeOffset = (int32_t)newWritePtr;             // +0x14
    this->currentHeader = *newWritePtr;                    // +0x0c – read first word of packet

    // Recalculate remaining size: packetSize - 8 + packetCount * 8
    this->remainingSize = this->packetSize - 8 + this->packetCount * 8;  // +0x18

    // Check if the buffer is full beyond the maximum allowed packets
    if (this->maxPackets > 0x1000) {
        int32_t packetCount = ((int32_t)newWritePtr - base) / 0x18; // 24 bytes per packet
        if (packetCount + 1 < 0x1000) {
            this->flushBuffer();       // Send the accumulated chunk
            this->currentPacket = savedPacket;
            return result;
        }
    }

    this->currentPacket = savedPacket;
    return result;
}