// FUNC_NAME: NetConnection::buildPacket

// Reconstructed from Ghidra decompile at 0x0065a5e0
// This function builds a packet structure in the provided buffer, copying header data
// and computing a checksum. The packet type is determined by the connection's state.

#include <cstring>

// Forward declarations of external helper functions
void copyPacketHeader(void* source, int size, int flag, void* dest);
void computePacketChecksum(uint64_t* field1, void* field2, void* buffer);

class NetConnection {
    // Fields: offset +0x0c: pointer to some header data
    // offset +0x10: packet type flag (compared to 0x20)
};

// Packet structure layout (size at least 0x274 bytes)
struct Packet {
    void* vtable;             // +0x00
    int field_0x04;           // +0x04 (set to 0)
    int field_0x08;           // +0x08 (set to 0)
    uint64_t first64;         // +0x0C (copy from later field)
    uint64_t second64;        // +0x14 (copy from later field)
    uint64_t headerFirst64;   // +0x1C (from source header)
    uint64_t headerSecond64;  // +0x24 (from source header)
    uint8_t data[0x204];      // +0x6C (copied from temporary buffer)
    int someField;            // +0x270 (set to 0)
};

// External vtable pointer (likely for Packet base class)
extern void* g_PacketVTable;

Packet* __thiscall NetConnection::buildPacket( void* sourceHeaderData, Packet* outPacket ) {
    // Large temporary buffer on stack (1063 dwords = 4252 bytes)
    unsigned int tmpBuffer[1063]; // local_10a0
    uint64_t local64a = 0;        // local_10b0
    uint64_t local64b = 0;        // local_10a8

    // Initialize output packet fields
    outPacket->field_0x04 = 0;
    outPacket->field_0x08 = 0;
    outPacket->vtable = &g_PacketVTable;

    // Check if packet type is 0x20 (data packet?)
    if ( *(int*)((char*)this + 0x10) == 0x20 ) {
        // Copy 16 bytes from source header into temporary buffer
        copyPacketHeader( *(void**)((char*)this + 0x0C), 0x10, 0, tmpBuffer );

        // Read two 64-bit values from the same source (offset 0x10 and 0x18)
        uint8_t* src = (uint8_t*) *(void**)((char*)this + 0x0C);
        outPacket->headerFirst64  = *(uint64_t*)(src + 0x10);
        outPacket->headerSecond64 = *(uint64_t*)(src + 0x18);
    } else {
        // For non-data packets, use default zero values
        copyPacketHeader( &local64a, 0x10, 0, tmpBuffer );
        outPacket->headerFirst64  = local64a;
        outPacket->headerSecond64 = local64b;
    }

    // Copy 0x81 dwords (0x204 bytes) from temporary buffer to packet data area
    // starting at offset +0x6C (0x1b * 4)
    unsigned int* srcBuf = tmpBuffer;
    unsigned int* dstBuf = (unsigned int*)((uint8_t*)outPacket + 0x6C);
    for ( int i = 0x81; i != 0; i-- ) {
        *dstBuf = *srcBuf;
        srcBuf++;
        dstBuf++;
    }

    // Copy the two header 64-bit values to their earlier positions
    outPacket->first64  = outPacket->headerFirst64;
    outPacket->second64 = outPacket->headerSecond64;

    // Compute checksum (or transform) between first64, data area, and buffer
    computePacketChecksum( &outPacket->first64, (uint8_t*)outPacket + 0x5C, tmpBuffer );

    // Set the final field to 0
    outPacket->someField = 0;

    return outPacket;
}