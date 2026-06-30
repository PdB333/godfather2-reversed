// FUNC_NAME: SerializableObject::readFields

#include <cstdint>

// Bit stream parser for EARS serialization (hash 0xdf0a26e8)
// Reads tagged fields from a packed data stream into an object.
// The stream can be sequential or tree-based (bit flags indicate mode).
// Tags 0-10 correspond to offsets in the object.
class SerializableObject {
public:
    // Offset 0x00: vtable or base class pointer
    // +0x08: pointer to first data field
    void* field08;
    // +0x0c: pointer
    void* field0c;
    // +0x10: pointer
    void* field10;
    // +0x14: pointer
    void* field14;
    // +0x18: pointer
    void* field18;
    // +0x1c: pointer
    void* field1c;
    // +0x20: pointer
    void* field20;
    // +0x24: unsigned flag/byte
    uint32_t flag24;
    // +0x28: unsigned flag/byte
    uint32_t flag28;
    // +0x2c: unsigned flag/byte
    uint32_t flag2c;
    // +0x30: unsigned flag/byte
    uint32_t flag30;

    void readFields(uint32_t streamHandle);
};

// External helper: initialize bit stream reader
void BitStreamInit(uint32_t stream, uint32_t hash); // FUN_0043aff0
// External helper: advance in tree-based stream
void BitStreamAdvance(); // FUN_0043b140
// Null terminator for tree mode
extern uint32_t* NullTerminator; // DAT_01163cf8

void SerializableObject::readFields(uint32_t streamHandle) {
    // Initialize bit stream with given hash (identifies format)
    BitStreamInit(streamHandle, 0xdf0a26e8);

    // Local state for stream parsing
    bool isTreeMode;          // local_64: 0 = sequential, 1 = tree
    uint8_t* bitBase;         // local_60: base of bit array for tree
    uint32_t* bitCursor;      // local_5c: current pointer in sequential bit stream
    uint32_t readIndex;       // local_58: current index in bit stream
    uint32_t bitCount;        // local_54: total number of bits/elements
    uint32_t* currentNode;    // local_50: current tree node
    uint32_t nodeHeader;      // local_48: header at node
    uint32_t* tagNodePtr;     // local_8: pointer used for tag extraction

    // Initialization from bit stream (not fully shown, but sets local variables)
    isTreeMode = (/* from stream */ false);
    if (isTreeMode) {
        // tree mode: bit array at bitBase, bitCount = number of bits
    } else {
        // sequential mode: current node starts at stream data
        currentNode = (uint32_t*)streamHandle;
    }

    while (true) {
        bool done;
        if (!isTreeMode) {
            done = (*tagNodePtr == 0); // null terminator check
        } else {
            done = (readIndex == bitCount);
        }
        if (done) break;

        // Get tag value from current node
        uint32_t tag;
        if (isTreeMode) {
            // In tree mode, get tag from nodeHeader (offset 6 of node)
            if (*(int16_t*)((uint8_t*)tagNodePtr + 6) == 0x25e3) {
                // tag is in low 16 bits of node[1]
                tag = (uint32_t)*(uint16_t*)(tagNodePtr + 1);
            } else {
                // otherwise tag is node[1] directly
                tag = (uint32_t)tagNodePtr[1];
            }
        } else {
            // Sequential mode: tag from node[1]
            tag = (uint32_t)currentNode[1];
        }

        // Apply tag: write to the appropriate field of this object
        uint8_t* fieldBase = (uint8_t*)this; // base offset

        // Helper to get the source value based on mode
        uint32_t* sourcePtr;
        if (isTreeMode) {
            sourcePtr = tagNodePtr; // actually uses tagNodePtr offset by 2 words?
        } else {
            sourcePtr = currentNode; // uses currentNode+2 as source
        }
        // The actual source is at offset 8 bytes from the node pointer (ppuVar2 + 2)
        uint32_t sourceValue = *(uint32_t*)((uint8_t*)sourcePtr + 8);

        switch (tag) {
            case 0: { // byte flag at +0x24
                *(uint32_t*)(fieldBase + 0x24) = (uint32_t)(*(uint8_t*)&sourceValue);
                break;
            }
            case 1: { // pointer at +0x08
                *(void**)(fieldBase + 0x08) = (void*)sourceValue;
                break;
            }
            case 2: { // pointer at +0x0c
                *(void**)(fieldBase + 0x0c) = (void*)sourceValue;
                break;
            }
            case 3: { // byte flag at +0x2c
                *(uint32_t*)(fieldBase + 0x2c) = (uint32_t)(*(uint8_t*)&sourceValue);
                break;
            }
            case 4: { // pointer at +0x1c
                *(void**)(fieldBase + 0x1c) = (void*)sourceValue;
                break;
            }
            case 5: { // byte flag at +0x30
                *(uint32_t*)(fieldBase + 0x30) = (uint32_t)(*(uint8_t*)&sourceValue);
                break;
            }
            case 6: { // pointer at +0x20
                *(void**)(fieldBase + 0x20) = (void*)sourceValue;
                break;
            }
            case 7: { // byte flag at +0x28
                *(uint32_t*)(fieldBase + 0x28) = (uint32_t)(*(uint8_t*)&sourceValue);
                break;
            }
            case 8: { // pointer at +0x10
                *(void**)(fieldBase + 0x10) = (void*)sourceValue;
                break;
            }
            case 9: { // pointer at +0x14
                *(void**)(fieldBase + 0x14) = (void*)sourceValue;
                break;
            }
            case 10: { // pointer at +0x18
                *(void**)(fieldBase + 0x18) = (void*)sourceValue;
                break;
            }
            default:
                break;
        }

        // Advance stream position
        if (!isTreeMode) {
            // Sequential mode: follow pointer chains or linear
            if ((int)readIndex < 0) {
                // Tree inside sequential: follow pointer
                tagNodePtr = (uint32_t*)((uint8_t*)tagNodePtr + (intptr_t)*tagNodePtr);
                BitStreamAdvance();
                readIndex = /* reload */ 0; // local_58 updated
            } else if ((int)readIndex < (int)(bitCount - 1)) {
                // Move to next sequential node
                tagNodePtr = (uint32_t*)((uint8_t*)tagNodePtr + (intptr_t)*tagNodePtr);
                readIndex++;
            } else {
                // End of sequential data: set to null terminator
                tagNodePtr = NullTerminator;
                // local_8 set to NullTerminator twice (dead store)
                tagNodePtr = NullTerminator;
            }
        } else {
            // Tree mode: advance bit index
            readIndex++;
            if (readIndex != bitCount) {
                // Read next bit from the bit array
                uint32_t byteIndex = readIndex >> 3;
                uint32_t bitMask = 1 << (readIndex & 7);
                if (bitBase[byteIndex] & bitMask) {
                    // Bit set: node is present, read next structure
                    currentNode = bitCursor;
                    nodeHeader = *bitCursor;
                    bitCursor++;
                } else {
                    // Bit clear: node absent
                    currentNode = nullptr;
                    nodeHeader = 0;
                }
            }
        }
    }
    return;
}