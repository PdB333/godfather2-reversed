// FUNC_NAME: AudioFraction::encodeFromRational
// Function address: 0x00675010
// Converts a rational number (numerator, denominator<<6) into a compact fixed-point representation
// output structure (at EDI, size 18 bytes?):
//   +0x00: short den (normalized denominator)
//   +0x02: short shiftCount (trailing zeros of numerator after normalization)
//   +0x04: uint num (numerator after normalization)
//   +0x08: int numHalf (numerator>>1)
//   +0x0C: uint sampleRateOrSomething (from FUN_00676090)
//   +0x10: short flags (2 initially, then condition)
void AudioFraction::encodeFromRational(short *outBuffer, uint numerator, int denominatorShifted) // denominatorShifted = denominator << 6
{
    uint normNum = numerator;
    int normDen = denominatorShifted;
    uint combined;
    short shiftCount;
    uint tempNum;

    // Normalization: remove common factor of 2 from (normNum | normDen)
    combined = normNum & 1;
    while (combined == 0) {
        combined = ((normNum | normDen) >> 1) & 1;
        normDen >>= 1;
        normNum >>= 1;
    }

    // Default flags
    outBuffer[8] = 2; // unknown field

    // Get some external value (maybe sample rate from audio manager)
    uint externalVal = FUN_00676090();
    *(uint *)(outBuffer + 6) = externalVal; // offset 0x0C

    // If denominator after normalization fits in 15 bits (i.e., < 0x8000)
    if (normDen + 0x7fff < 0xffff) // same as normDen <= 0x7fff
    {
        shiftCount = 0;
        *outBuffer = (short)normDen; // store denominator

        // Count trailing zeros of the original normalized numerator
        tempNum = normNum;
        while ((tempNum & 1) == 0) {
            shiftCount++;
            tempNum = (int)normNum >> ((byte)shiftCount & 0x1f);
        }
        outBuffer[1] = shiftCount; // store shift count

        // Store numerator and numerator>>1
        *(uint *)(outBuffer + 2) = normNum; // offset 0x04
        *(int *)(outBuffer + 4) = (int)normNum >> 1; // offset 0x08

        // Set flags: 1 if after removing trailing zeros the numerator is not 1, else 0
        outBuffer[8] = (ushort)(((int)normNum >> ((byte)shiftCount & 0x1f)) != 1);
    }
}