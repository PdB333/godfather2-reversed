// FUNC_NAME: radixSortByUpperWord
void radixSortByUpperWord(uint count, uint* inputBuffer, uint* tempBuffer)
{
    // Two histogram arrays of 256 shorts each (512 bytes total)
    // They are global buffers in the original (DAT_01223580 and DAT_01223780)
    static short firstPassHistogram[256];
    static short secondPassHistogram[256];

    // Zero out both histograms (256 shorts each = 0x200 bytes)
    for (int i = 0; i < 0x80; i++) {
        ((uint*)firstPassHistogram)[i] = 0;
        ((uint*)secondPassHistogram)[i] = 0;
    }

    if (count != 0) {
        // First pass: count occurrences of byte at offset 2 (third byte) and byte at offset 3 (fourth byte)
        // from each 4-byte record. This captures the upper 16 bits (high word) of the integer.
        uint* recordPtr = inputBuffer;
        for (uint i = 0; i < count; i++) {
            byte* bytes = (byte*)(recordPtr + i); // each record is 4 bytes
            byte lowKey = bytes[2]; // offset 2 – secondary key (higher byte in little-endian)
            byte highKey = bytes[3]; // offset 3 – primary key (MSB)
            firstPassHistogram[lowKey]++;
            secondPassHistogram[highKey]++;
        }
    }

    // Convert histograms to prefix sums (starting indices for stable sort)
    short sumLow = 1;
    short sumHigh = 1;
    for (uint i = 0; i < 256; i++) {
        short lowCount = firstPassHistogram[i];
        firstPassHistogram[i] = sumLow - 1;
        sumLow += lowCount;

        short highCount = secondPassHistogram[i];
        secondPassHistogram[i] = sumHigh - 1;
        sumHigh += highCount;
    }

    // First pass (by low key): copy records from inputBuffer to tempBuffer
    if (count != 0) {
        for (uint i = 0; i < count; i++) {
            byte* srcBytes = (byte*)(inputBuffer + i);
            byte key = srcBytes[2];
            uint destIndex = firstPassHistogram[key];
            firstPassHistogram[key] = destIndex + 1;
            tempBuffer[destIndex] = inputBuffer[i];
        }
    }

    // Second pass (by high key): copy records from tempBuffer back to inputBuffer
    if (count != 0) {
        for (uint i = 0; i < count; i++) {
            byte* srcBytes = (byte*)(tempBuffer + i);
            byte key = srcBytes[3];
            uint destIndex = secondPassHistogram[key];
            secondPassHistogram[key] = destIndex + 1;
            inputBuffer[destIndex] = tempBuffer[i];
        }
    }

    // Flush cache lines for both histograms (likely to ensure coherence after modification)
    // Each cache line is 64 bytes (0x40), total of 512 bytes / 64 = 8 lines
    for (uint offset = 0; offset < 0x200; offset += 0x40) {
        clflush((char*)firstPassHistogram + offset);
        clflush((char*)secondPassHistogram + offset);
    }
}