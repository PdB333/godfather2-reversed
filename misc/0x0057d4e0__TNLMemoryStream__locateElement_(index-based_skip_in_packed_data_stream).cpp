// FUNC_NAME: TNLMemoryStream::locateElement (index-based skip in packed data stream)
// Address: 0x0057d4e0
// Purpose: Advances a stream pointer to the element at the given index within a packed binary structure.
//          The stream uses a variable-length token format with type encoded in low nibble of first byte.
//          Type 5 indicates a block of multiple tokens; other types are fixed-size or variable-size tokens.
//          The function uses two global lookup tables (kTokenSizeMultiplier and kTokenSizeAddend) to compute token sizes.

#include <cstdint>

// Static lookup tables for computing token sizes based on type (low nibble).
// These are located in the binary at 0x00e2be68 and 0x00e2be30.
static const int32_t kTokenSizeMultiplier[16] = {
    // filled from binary (values unknown, but derived from DAT_00e2be68)
    // Since specific values are not visible in the decompilation, we assume they exist.
    0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0  // Placeholder
};
static const int32_t kTokenSizeAddend[16] = {
    // filled from binary (from DAT_00e2be30)
    5, 8, 11, 14, 2, 0, 8, 8, 0, 0, 0, 0, 2, 2, 0, 0 // Placeholder (approximate from switch)
};

// Helper function called for type 4 tokens (performs two separate operations).
void FUN_0057d370(); // Unimplemented in this snapshot: possibly reads additional data or validates.

// Main function: locates and advances to the element at 'targetIndex' within the stream.
// Parameters:
//   pStreamPtr - pointer to the current position pointer (modified upon return)
//   targetIndex - the zero-based index of the element to locate
void __thiscall TNLMemoryStream::locateElement(int32_t targetIndex, uint8_t** pStreamPtr) {
    uint8_t* stream = *pStreamPtr;
    uint8_t headerByte = *stream;
    uint8_t type = headerByte & 0xF;

    if (type != 5) {
        // Simple token: advance by fixed or variable size based on type.
        switch (type) {
            case 0: // 5-byte token
                *pStreamPtr = stream + 5;
                return;
            case 1: // 8-byte token
                *pStreamPtr = stream + 8;
                return;
            case 2: // 11-byte token
                *pStreamPtr = stream + 11;
                return;
            case 3: // 14-byte token
                *pStreamPtr = stream + 14;
                return;
            case 4: { // Variable-size token (count*4 + 2) preceded by two helper calls
                uint8_t count = stream[1];
                FUN_0057d370();
                FUN_0057d370();
                // Count is derived from low nibble of header byte and second byte.
                uint32_t totalSize = ((count << 4) | (headerByte >> 4)) * 4 + 2;
                *pStreamPtr = stream + totalSize;
                return;
            }
            case 6: // Variable-size token: size = (count*16 + highNibble) + 8
                *pStreamPtr = stream + ((stream[1] << 4) | (headerByte >> 4)) + 8;
                return;
            case 7: // Variable-size token: size = (count*16 + highNibble) * 2 + 8
                *pStreamPtr = stream + (((stream[1] << 4) | (headerByte >> 4)) * 2) + 8;
                return;
            case 0xC: // 2-byte token (just advance by 2)
                *pStreamPtr = stream + 2;
                return;
            case 0xD: // Also 2-byte token (immediate return after advance)
                *pStreamPtr = stream + 2;
                return;
            default:
                // Unknown type; just advance by 2 (fallback)
                *pStreamPtr = stream + 2;
                return;
        }
    }

    // Type 5: block containing multiple elements.
    uint32_t numElements = (stream[1] << 4) | (headerByte >> 4);
    stream += 2; // Skip the two header bytes

    if (numElements == 0) {
        *pStreamPtr = stream;
        return;
    }

    // Find the element that contains targetIndex.
    while (true) {
        uint8_t* elementHeader = stream;
        uint8_t elementType = elementHeader[0] & 0xF;
        uint32_t elementCount = (elementHeader[1] << 4) | (elementHeader[0] >> 4);
        numElements--;

        if (targetIndex < (int32_t)(elementCount - 1)) {
            break; // target is inside this element (sub-index)
        }

        targetIndex -= (elementCount - 1); // Skip whole element
        // Advance past this element using token size formula
        stream = elementHeader + kTokenSizeMultiplier[elementType] * elementCount + kTokenSizeAddend[elementType];
        if ((int32_t)numElements <= 0) {
            *pStreamPtr = stream;
            return;
        }
    }

    // Now we are at the start of the element that contains the target.
    // Compute offset within the element based on its type.
    uint8_t* elementStart = stream;
    uint8_t elementType = *elementStart & 0xF;
    uint8_t* elementData;

    switch (elementType) {
        case 0:
            elementData = elementStart + 5;
            break;
        case 1:
            elementData = elementStart + 8;
            break;
        case 2:
            elementData = elementStart + 11;
            break;
        case 3:
            elementData = elementStart + 14;
            break;
        case 4: {
            uint32_t count = (elementStart[1] << 4) | (*elementStart >> 4);
            FUN_0057d370();
            FUN_0057d370();
            elementData = elementStart + 2 + count * 4;
            break;
        }
        case 6:
            elementData = elementStart + (elementStart[1] << 4 | (*elementStart >> 4)) + 8;
            break;
        case 7:
            elementData = elementStart + ((elementStart[1] << 4 | (*elementStart >> 4)) * 2) + 8;
            break;
        case 0xD: // Same as 0xC but no extra offset
        default:
            elementData = elementStart + 2;
            break;
    }

    stream = elementData;
    // Skip remaining elements (if any) to reach the exact target position.
    while ((int32_t)numElements > 0) {
        uint8_t* nextHeader = stream;
        uint8_t nextType = *nextHeader & 0xF;
        uint32_t nextCount = (nextHeader[1] << 4) | (*nextHeader >> 4);
        stream = nextHeader + kTokenSizeMultiplier[nextType] * nextCount + kTokenSizeAddend[nextType];
        numElements--;
    }

    *pStreamPtr = stream;
}