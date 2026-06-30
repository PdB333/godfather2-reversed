// FUNC_NAME: ReorderBuffer::reverseSegments
class ReorderBuffer {
public:
    // +0x36: number of segment pairs
    // +0x3c: array of start indices (short)
    // +0x40: array of end indices (short)
    // +0x44: first 16-bit array
    // +0x48: second 16-bit array
    // +0x4c: array of bytes
    void __thiscall reverseSegments() {
        short count = *(short*)((uint8_t*)this + 0x36);
        if (count <= 0) return;

        short* rangeStarts = *(short**)((uint8_t*)this + 0x3c);
        short* rangeEnds   = *(short**)((uint8_t*)this + 0x40);
        uint16_t* arrayA = *(uint16_t**)((uint8_t*)this + 0x44);
        uint16_t* arrayB = *(uint16_t**)((uint8_t*)this + 0x48);
        uint8_t* arrayC  = *(uint8_t**)((uint8_t*)this + 0x4c);

        for (short i = 0; i < count; ++i) {
            short start = rangeStarts[i];
            short end   = rangeEnds[i];
            // Reverse the segment from start+1 to end (inclusive)
            uint swapCount = ((uint)(end - start)) / 2;
            if (swapCount > 0) {
                short left = start;
                short right = end;
                do {
                    left++;
                    uint16_t tmpA = arrayA[left];
                    uint16_t tmpB = arrayB[left];
                    uint8_t tmpC  = arrayC[left];

                    arrayA[left] = arrayA[right];
                    arrayB[left] = arrayB[right];
                    arrayC[left] = arrayC[right];

                    arrayA[right] = tmpA;
                    arrayB[right] = tmpB;
                    arrayC[right] = tmpC;

                    right--;
                    swapCount--;
                } while (swapCount != 0);
            }
        }
    }
};