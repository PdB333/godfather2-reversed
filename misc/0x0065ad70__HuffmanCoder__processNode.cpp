// FUNC_NAME: HuffmanCoder::processNode
// Address: 0x0065ad70
// Recursive Huffman tree builder/encoder. For internal nodes (nodeIndex >= 0), writes a 0 bit for the left child
// and a 1 bit for the right child into the bitstream, while recursing. For leaf nodes (nodeIndex < 0), stores the
// current depth and a 4-byte value from the bitstream into the global leaf data table.
// This function constructs a Huffman tree representation in the bitstream and populates leaf entries.

extern uint8_t* gInternalNodes; // DAT_01223354 – internal node table, 8 bytes per node: +4 = left child (int16), +6 = right child (int16)
extern uint8_t* gLeafData;      // DAT_01223360 – leaf data table, 12 bytes per entry: +4 = depth (uint8), +8 = value (uint32)

bool refillBitStream(BitStream* stream); // FUN_0064b7c0 – refill/reallocate bitstream buffer when full

struct BitStream {
    uint8_t* data;     // +0x0 (unused?) – actual pointer to byte buffer (obtained via *(void**)(stream+0xc))
    uint8_t* buffer;   // +0xc – pointer to current bit buffer
    int32_t  bitPos;   // +0x18 – current bit position within buffer
    int32_t  maxBits;  // +0x30 – total capacity in bits
};

void HuffmanCoder::processNode(BitStream* stream, int32_t nodeIndex, int32_t depth) {
    // Leaf node: store depth and a 4-byte value from the bitstream into the leaf table
    if (nodeIndex < 0) {
        int32_t leafOffset = (nodeIndex * 3 + 3) * -4; // Map negative index to positive offset in leafData
        uint8_t* leafEntry = gLeafData + leafOffset;

        // Read 4 bytes from the current position of the bitstream buffer
        *reinterpret_cast<uint32_t*>(leafEntry + 8) = *reinterpret_cast<uint32_t*>(*(uint32_t*)(&stream->buffer));

        // Store depth as a single byte at offset +4
        *reinterpret_cast<uint8_t*>(leafEntry + 4) = static_cast<uint8_t>(depth);
        return;
    }

    int32_t savedBitPos = stream->bitPos;

    // --- Left child: clear a bit (write '0') ---
    // Check if we have room, refill if necessary; skip if refill fails
    bool leftAvailable = (stream->bitPos + 1 <= stream->maxBits) || refillBitStream(stream);
    if (leftAvailable) {
        uint32_t byteIndex = stream->bitPos >> 3;
        uint32_t shift     = stream->bitPos & 7;
        stream->buffer[byteIndex] &= ~(1 << shift);  // Clear the bit (0)
        stream->bitPos++;

        // Recurse with left child from internal node table
        int16_t leftChild = *reinterpret_cast<int16_t*>(gInternalNodes + nodeIndex * 8 + 4);
        processNode(stream, leftChild, depth + 1);

        stream->bitPos = savedBitPos; // Restore position for right branch
    }

    // --- Right child: set a bit (write '1') ---
    bool rightAvailable = (stream->bitPos + 1 <= stream->maxBits) || refillBitStream(stream);
    if (rightAvailable) {
        uint32_t byteIndex = stream->bitPos >> 3;
        uint32_t shift     = stream->bitPos & 7;
        stream->buffer[byteIndex] |= 1 << shift;   // Set the bit (1)
        stream->bitPos++;

        // Recurse with right child from internal node table
        int16_t rightChild = *reinterpret_cast<int16_t*>(gInternalNodes + nodeIndex * 8 + 6);
        processNode(stream, rightChild, depth + 1);

        stream->bitPos = savedBitPos; // Final restore
    }
}