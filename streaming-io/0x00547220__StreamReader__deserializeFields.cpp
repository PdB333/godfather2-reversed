// FUNC_NAME: StreamReader::deserializeFields
// Address: 0x00547220
// Role: Deserializes a set of fields from a bitstream or raw pointer list into a target structure.
// The function reads tagged values (field IDs 0-9) and writes them to specified offsets in the output.
// The source is either a compact bitstream (with an optional bitmask) or a list of (tag, value) pairs.
// Parameter hash (0xe9613cc5) likely identifies the field layout class.

#include <cstdint>

// Constants
static const float kTwoPower32 = 4294967296.0f; // Used for unsigned-to-float conversion

// Forward declaration of unknown internal function (likely iterator advancement)
void FUN_0043b140(); // Unknown purpose

// Helper struct representing the iterator state during deserialization
struct FieldIterator {
    bool   isBitStream;   // cStack_64: 0 = raw pointer list, 1 = bitstream
    int    bitMaskPtr;    // iStack_60: base of bitmask array (only for bitstream)
    uint32_t* dataArray;  // puStack_5c: pointer to data elements (only for bitstream)
    uint32_t currentIdx;  // uStack_58: current index in bitstream or list
    uint32_t totalCount;  // uStack_54: total number of elements (only bitstream)
    uint16_t tmpIdx;      // uStack_4c: temporary short index
    uint32_t copiedData;  // uStack_48: copy of the current data element
    void*    currentTag;  // puStack_50: current tag/value pointer (or null)
};

// Stream reader object with virtual methods at vtable offsets 0x220 and 0x228
class StreamReader {
public:
    virtual int getReadCount() = 0;      // vtable +0x220
    virtual int getZeroParam() = 0;      // vtable +0x228 (returns 0 in this context)
};

// Deserialization function
void FUN_00547220(uint32_t fieldSetHash, void* targetData, StreamReader* streamReader) {
    // Call virtual method: e.g., get total element count or start reading
    streamReader->getReadCount();

    // Perform hash-based validation / class identification (0xe9613cc5)
    // This call is likely a map lookup or type check
    // FUN_0043aff0(fieldSetHash, 0xe9613cc5);  // placeholder call, omitted for clarity but kept conceptually

    // Initialize the iterator from stack variables (simplified)
    FieldIterator iter;
    // The iterator state is built from stack locals; we simulate the while loop logic.
    void* currentListPtr = nullptr; // ppuVar8, initial value from ppuStack_8

    // While there are more fields to read
    while (true) {
        bool done;
        if (!iter.isBitStream) {
            // Raw pointer list mode: check if current pointer is null
            done = (currentListPtr == nullptr);
        } else {
            // Bitstream mode: check if index reached total count
            done = (iter.currentIdx == iter.totalCount);
        }
        if (done) break;

        // Determine the current element pointer (ppuVar3)
        void* elementPtr = nullptr; // ppuVar3
        if (!iter.isBitStream) {
            elementPtr = currentListPtr;
        } else {
            elementPtr = &iter.currentTag; // actually points to the stack variable holding the tag
        }

        // Get the field tag (puVar2). The tag is either a 16-bit value at elementPtr+6 or a pointer at elementPtr+4
        uint32_t tag;
        if (!iter.isBitStream && *(short*)((char*)elementPtr + 6) == 0x25e3) {
            // Special case: tag is stored as 16-bit at offset 2 from elementPtr (but the code does *(ushort*)(ppuVar3+1) -> offset 4)
            // Actually the decompiler may have mis-sized the pointer arithmetic. Let's replicate faithfully.
            tag = (uint32_t)(*(uint16_t*)((char*)elementPtr + sizeof(void*) + 2)); // offset 6? We'll keep as is.
        } else {
            // Normal case: tag is the second pointer in the element
            tag = (uint32_t)(*((void**)elementPtr + 1));
        }

        // Interpret the tag as a field ID (values 0..9)
        switch (tag) {
        case 0: // field at targetData + 0x08
            *((void**)((char*)targetData + 0x08)) = *((void**)elementPtr + 2);
            break;
        case 1: // field at targetData + 0x0c
            *((void**)((char*)targetData + 0x0c)) = *((void**)elementPtr + 2);
            break;
        case 2: // field at targetData + 0x14
            *((void**)((char*)targetData + 0x14)) = *((void**)elementPtr + 2);
            break;
        case 3: // field at targetData + 0x10
            *((void**)((char*)targetData + 0x10)) = *((void**)elementPtr + 2);
            break;
        case 4: // field at targetData+0x1c -> pointer to int; write value to *pointer
            **(int**)((char*)targetData + 0x1c) = (int)(*((void**)elementPtr + 2));
            break;
        case 5: // write to pointer[4]
            *((int*)(*(int*)((char*)targetData + 0x1c) + 4)) = (int)(*((void**)elementPtr + 2));
            break;
        case 6: // write to pointer[8]
            *((int*)(*(int*)((char*)targetData + 0x1c) + 8)) = (int)(*((void**)elementPtr + 2));
            break;
        case 7: // write to pointer[12]
            *((int*)(*(int*)((char*)targetData + 0x1c) + 12)) = (int)(*((void**)elementPtr + 2));
            break;
        case 8: // field at targetData + 0x18
            *((void**)((char*)targetData + 0x18)) = *((void**)elementPtr + 2);
            break;
        case 9: // Special: compute interpolation weights for a float array at targetData+0x28
        {
            float* weightArray = *(float**)((char*)targetData + 0x28);
            void* valuePtr = *((void**)elementPtr + 2);
            // Get two counts from the stream reader
            int count2 = streamReader->getReadCount();          // vtable+0x220
            int count1 = streamReader->getZeroParam();          // vtable+0x228 (always returns 0 ?)
            // Convert unsigned to float with proper range handling
            float fCount1 = (float)(int)count1;
            if (count1 < 0) {
                fCount1 = fCount1 + kTwoPower32;
            }
            uint8_t i;
            for (i = 0; i < (uint8_t)count1; i++) {
                // First part: 1.0 - value / fCount1? Actually (1.0 - (float)valuePtr) / fCount1
                weightArray[i] = (1.0f - (float)(uintptr_t)valuePtr) / fCount1;
            }
            // Remaining entries
            float fDiff = (float)(int)(count2 - count1);
            if ((int)(count2 - count1) < 0) {
                fDiff = fDiff + kTwoPower32;
            }
            for (; i < (uint32_t)count2; i++) {
                weightArray[i] = (float)(uintptr_t)valuePtr / fDiff;
            }
            break;
        }
        default:
            // Unrecognized tag; ignore
            break;
        }

        // Advance to next element
        if (!iter.isBitStream) {
            // Raw pointer list: advance by adding the offset stored at the current pointer
            if ((int)iter.currentIdx < 0) {
                // Negative offset? (unusual)
                currentListPtr = (void*)((char*)currentListPtr + (int)(*(int*)currentListPtr));
                FUN_0043b140(); // unknown function call
            } else if ((int)iter.currentIdx < (int)(iter.totalCount - 1)) {
                iter.currentIdx++;
                currentListPtr = (void*)((char*)currentListPtr + (int)(*(int*)currentListPtr));
                // Actually the code sets ppuVar8 twice; we replicate the increment
                // The original had: ppuStack_8 = (void**)((char*)ppuVar8 + *(int*)ppuVar8);
                // So we advance similarly.
            } else {
                // Reached end of list; set to sentinel (DAT_01163cf8)
                currentListPtr = (void*)0x01163cf8; // This is a static sentinel address
            }
        } else {
            // Bitstream mode: increment index
            iter.currentIdx++;
            if (iter.currentIdx != iter.totalCount) {
                iter.tmpIdx = (uint16_t)iter.currentIdx;
                // Check bitmask at position currentIdx/8, bit (currentIdx&7)
                uint8_t* bitmask = (uint8_t*)iter.bitMaskPtr;
                bool bitSet = (bitmask[iter.currentIdx >> 3] & (1 << (iter.currentIdx & 7))) != 0;
                if (!bitSet) {
                    // Bit not set: element is present, copy from data array
                    iter.currentTag = iter.dataArray;
                    iter.copiedData = *iter.dataArray;
                    iter.dataArray++;
                } else {
                    // Bit set: element is absent (tag = null)
                    iter.currentTag = nullptr;
                    iter.copiedData = 0;
                }
            }
        }
    }
}