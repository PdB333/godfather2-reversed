// FUNC_NAME: BitStream::readCompressedString
// Address: 0x0065ae90
// This function decompresses a string from a bitstream using a Huffman tree or raw bytes.
// The bitstream is stored in the object's buffer, with bit position, size, and error flag.
// Two global tables are used for Huffman decoding: g_treeNodes and g_symbolData.

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

// Global Huffman decompression tables (initialized by FUN_0065a940)
extern uint8  g_huffmanInitialized;   // DAT_0120588e
extern uint16 g_treeNodes[];          // DAT_01223354 - each node is two shorts (left/right, offset 4 and 6)
extern uint8  g_leafSymbols[];        // DAT_01223360 - symbols indexed by negative node value

// Helper function to read a specified number of bits from the bitstream (see FUN_0064b9e0)
extern uint32 readBits(BitStream* this, uint32 bitCount, void* output); // returns 0 on failure

class BitStream {
public:
    // Offsets in 'this':
    // +0x00-0x0B: unknown/vtable
    // +0x0C: uint8* mBuffer -> pointer to data
    // +0x18: uint32 mBitPos -> current bit position
    // +0x2C: uint32 mBitCount -> total bits available
    // +0x1C: uint8  mOverflow -> overflow flag

    uint8*  mBuffer;   // +0x0C
    uint32  mBitPos;   // +0x18
    uint32  mBitCount;  // +0x2C
    uint8   mOverflow;  // +0x1C

    // Method: readCompressedString(char* outBuffer)
    // Reads a compressed or raw null-terminated string from the bitstream.
    // Returns 1 on success, 0 on failure (overflow).
    int32 readCompressedString(char* outBuffer)
    {
        // Initialize Huffman tables if not done
        if (g_huffmanInitialized == 0) {
            FUN_0065a940(); // builds g_treeNodes and g_leafSymbols
        }

        uint32 currentBitPos = this->mBitPos;
        if (currentBitPos >= this->mBitCount) {
            // Overflow: mark error
            this->mOverflow = 1;
            return 1;
        }

        // Read one bit to decide compression mode
        uint8* bytePtr = this->mBuffer + (currentBitPos >> 3);
        uint8 bitMask = 1 << (currentBitPos & 7);
        this->mBitPos = currentBitPos + 1;

        if ((*bytePtr & bitMask) != 0) {
            // Compressed mode: decode Huffman symbols
            uint32 count;
            uint32 rawCount = 0;
            // Read 8 bits to get number of symbols to decode
            readBits(8, &rawCount);
            count = rawCount & 0xFF;
            if (count != 0) {
                // Use bitIndex as output position
                uint32 outIndex = 0;
                do {
                    int32 nodeIndex = 0; // start at root
                    do {
                        // Read one more bit
                        currentBitPos = this->mBitPos;
                        if (currentBitPos >= this->mBitCount) {
                            this->mOverflow = 1;
                            goto leaf;
                        }
                        bytePtr = this->mBuffer + (currentBitPos >> 3);
                        bitMask = 1 << (currentBitPos & 7);
                        this->mBitPos = currentBitPos + 1;

                        uint16 branchValue;
                        if ((*bytePtr & bitMask) != 0) {
                            // Go to right child (offset +6)
                            branchValue = g_treeNodes[nodeIndex * 4 + 3]; // +6 from base
                        } else {
                            // Go to left child (offset +4)
                            branchValue = g_treeNodes[nodeIndex * 4 + 2]; // +4 from base
                        }
                        nodeIndex = (int32)branchValue;
                    } while (nodeIndex >= 0);
leaf:
                    // When nodeIndex is negative, it encodes the symbol index
                    // Symbol is at g_leafSymbols[ -12*nodeIndex - 7 ]
                    uint8 symbol = g_leafSymbols[-12 * nodeIndex - 7];
                    outBuffer[outIndex] = symbol;
                    outIndex++;
                } while (outIndex < count);
            }
            // Null-terminate
            outBuffer[count] = 0;
        } else {
            // Raw mode: read length and then raw bytes
            uint32 length;
            readBits(8, &length);
            uint32 rawSize = length & 0xFF;
            readBits(rawSize * 8, outBuffer);
            outBuffer[rawSize] = 0;
        }
        return 1;
    }
};