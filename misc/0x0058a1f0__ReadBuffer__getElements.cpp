// FUNC_NAME: ReadBuffer::getElements
// Function at 0x0058a1f0 - copies 12-byte elements from a buffer into an output array.
// The buffer maintains a read pointer (offset +0x48) and a read index (offset +0x4c).
// param_1: startIndex to skip to
// param_2: output array of 12-byte elements (undefined4[3])
// param_3: pointer to the ReadBuffer object
// Note: ESI (unaff_ESI) holds the total number of elements available in the buffer (not shown in the prototype)
void __fastcall ReadBuffer::getElements(int startIndex, undefined4 *output, ReadBuffer *buf)
{
    int currentIndex;
    undefined4 *readPtr;
    undefined4 *elementPtr;
    undefined4 v1, v2, v3;

    // Advance read pointer to the element with index >= startIndex
    currentIndex = buf->readIndex;          // +0x4c
    while (currentIndex < startIndex) {
        buf->readPtr += 3;                  // +0x48: each element is 3 * 4 = 12 bytes
        buf->readIndex = currentIndex + 1;  // increment index
        currentIndex = buf->readIndex;      // reload
    }

    // Copy elements until the read index reaches the total count (in ESI)
    currentIndex = buf->readIndex;          // reload after possible skip
    while (currentIndex < esi) {            // ESI holds total element count
        elementPtr = buf->readPtr;          // +0x48
        v1 = elementPtr[0];         // first word of element
        v2 = elementPtr[1];         // second word
        v3 = elementPtr[2];         // third word

        buf->readIndex = currentIndex + 1;  // advance index
        buf->readPtr = elementPtr + 3;      // advance pointer by 12 bytes

        output[0] = v1;
        output[1] = v2;
        output[2] = v3;

        currentIndex = buf->readIndex;      // reload for next iteration
        output += 3;                        // advance output pointer (assumed)
    }
}

// Example struct definition (offsets based on decompilation):
// struct ReadBuffer {
//     char unknown[0x48];
//     undefined4* readPtr;   // +0x48
//     int readIndex;         // +0x4c
//     // other members...
// };