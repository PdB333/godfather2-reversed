// FUNC_NAME: BitStream::readObjectUpdate
// Function address: 0x00653800
// Role: Reads a compressed object update from a bitstream, interpreting a two-bit header to determine update type.
// If the first bit is 0: no update (returns).
// If the first bit is 1 and second bit is 0: reads four 32-bit values (transform data) into output struct.
// If both bits are 1: sets a "delta" flag on output and returns without reading transform data.

class BitStream {
public:
    // Reads a 32-bit unsigned integer from the bitstream (FUN_00652840)
    uint32_t readUInt32();

    // Aligns the bit stream to the next byte boundary (FUN_006538d0)
    void alignToByte();

    // Reads an object update into the given output structure
    // param outStruct: pointer to output structure with fields at offsets:
    //   +0xb8: uint32_t flagsField (bit 3 = delta flag)
    //   +0xe4: float transformComp0
    //   +0xe8: float transformComp1
    //   +0xec: float transformComp2
    //   +0xf0: float transformComp3
    void readObjectUpdate(void* outStruct) {
        // Bitstream internal state offsets:
        // +0x0c: uint8_t* bitData
        // +0x18: uint32_t currentBitIndex
        // +0x2c: uint32_t totalBits
        // +0x1c: uint8_t endFlag (set to 1 when stream exhausted)

        uint8_t* bitData = *(uint8_t**)((uint8_t*)this + 0x0c);
        uint32_t& currentBitIndex = *(uint32_t*)((uint8_t*)this + 0x18);
        uint32_t totalBits = *(uint32_t*)((uint8_t*)this + 0x2c);
        uint8_t& endFlag = *(uint8_t*)((uint8_t*)this + 0x1c);

        // Check if there are any bits left
        if (currentBitIndex >= totalBits) {
            endFlag = 1;
            return;
        }

        // Read first bit
        uint8_t byteVal = bitData[currentBitIndex >> 3];
        uint8_t bitMask = (uint8_t)(1 << (currentBitIndex & 7));
        bool firstBit = (byteVal & bitMask) != 0;

        if (!firstBit) {
            // No update for this object
            return;
        }

        uint32_t nextBitIndex = currentBitIndex + 1;

        // Need more bits? Check if we have room for the second bit
        if (totalBits < nextBitIndex) {
            endFlag = 1;
            return;
        }

        // Read second bit
        byteVal = bitData[nextBitIndex >> 3];
        bitMask = (uint8_t)(1 << (nextBitIndex & 7));
        bool secondBit = (byteVal & bitMask) != 0;

        // Advance past both bits
        currentBitIndex += 2;

        if (secondBit) {
            // Both bits set: indicates delta/reuse previous data
            *(uint32_t*)((uint8_t*)outStruct + 0xb8) |= 8;  // set delta flag (bit 3)
            return;
        }

        // First bit only: read full transform (four 32-bit values)
        uint32_t comp0 = readUInt32();
        uint32_t comp1 = readUInt32();
        uint32_t comp2 = readUInt32();
        uint32_t comp3 = readUInt32();

        // Store in output struct (order reversed in memory relative to reads)
        *(uint32_t*)((uint8_t*)outStruct + 0xf0) = comp0;
        *(uint32_t*)((uint8_t*)outStruct + 0xec) = comp1;
        *(uint32_t*)((uint8_t*)outStruct + 0xe8) = comp2;
        *(uint32_t*)((uint8_t*)outStruct + 0xe4) = comp3;

        // Align bitstream to byte boundary
        alignToByte();
    }
};