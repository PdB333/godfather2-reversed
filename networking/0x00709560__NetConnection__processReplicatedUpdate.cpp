// FUNC_NAME: NetConnection::processReplicatedUpdate

// Address: 0x00709560
// Role: Processes a bitstream packet for ghost replication / update.
// Reads ghost object IDs from the bitstream and dispatches virtual calls.
// Also handles another message type (likely an event or action).
// The 'this' pointer points to a base class subobject at offset 0x58 within the full NetConnection object.
// Bitstream structure at param3 has offsets:
// +0x0c: pointer to byte array of bits
// +0x18: current read bit index
// +0x1c: flag (set to 1 when end of stream reached)
// +0x2c: total number of bits in stream

struct BitStream {
    // +0x00-0x08 unknown, but decompiled uses +0x0c, +0x18, +0x1c, +0x2c
    int field_0x00;
    int field_0x04;
    int field_0x08;
    unsigned char* bits;    // +0x0c
    int field_0x10;
    int field_0x14;
    unsigned int readIndex; // +0x18
    unsigned char endFlag;  // +0x1c (0 or 1)
    int field_0x20;
    int field_0x24;
    int field_0x28;
    unsigned int totalBits; // +0x2c
};

void __thiscall NetConnection::processReplicatedUpdate(uint this, int param2, BitStream* stream) {
    byte bitByte;
    uint bitIndex;
    int objectId;
    int local_8[2];
    void* obj;

    // Initialize the bitstream? param2 might be a size or offset.
    FUN_00472830(param2, stream);

    // First ghost update loop
    bitIndex = stream->readIndex;
    if (stream->totalBits < bitIndex) {
        stream->endFlag = 1;
    } else {
        bitByte = stream->bits[bitIndex >> 3]; // get byte containing current bit
        stream->readIndex++;
        // Check the bit at position (bitIndex & 7)
        if ((bitByte & (1 << (bitIndex & 7))) != 0) {
            // Read an object ID from the bitstream (ghost ID)
            objectId = FUN_004a9cd0(stream, this + 0x254);
            // Find object by ID
            obj = FUN_004461c0(this + 0x254, 0);
            if (obj != 0) {
                // Call virtual function at vtable offset 8 on the object
                // vtable pointer is at *(int*)(this - 0x58) because this is a base subobject at offset 0x58
                (**(code**)(*(int*)(this - 0x58) + 8))(obj);
            }
        }
    }

    // Second part: process another type of message
    bitIndex = stream->readIndex;
    if (stream->totalBits < bitIndex) {
        stream->endFlag = 1;
        return;
    }
    bitByte = stream->bits[bitIndex >> 3];
    stream->readIndex++;
    if ((bitByte & (1 << (bitIndex & 7))) != 0) {
        // Reset bitstream to beginning for reading an integer
        FUN_004a8ec0(0);
        FUN_004a9360(stream, local_8); // Read a 32-bit value into local_8[0] (likely an event ID)
        int readFlag = FUN_004a8f00(); // Read another flag (maybe indicates type)
        if (readFlag == 0) {
            // Check if the read value is not a specific sentinel (0xFE16702F)
            if ((local_8[0] != -0x1e98fd1) &&
                ((*(int*)(this + 0x1bc) == 0) || (*(int*)(this + 0x1bc) == 0x48))) {
                // Send or queue a packet (maybe reliable)
                FUN_004547e0(-(uint)(this != 0x58) & this, local_8, 0);
            }
        } else {
            // Other type: if connection state allows, handle the object/event further
            if ((*(int*)(this + 0x1bc) == 0) || (*(int*)(this + 0x1bc) == 0x48)) {
                FUN_007084b0(readFlag);
                return;
            }
        }
    }
}