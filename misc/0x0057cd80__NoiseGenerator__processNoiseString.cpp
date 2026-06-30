// FUNC_NAME: NoiseGenerator::processNoiseString
undefined4 __thiscall NoiseGenerator::processNoiseString(
    NoiseGenerator* this,
    char* inputString,
    char flag,
    int* outCount,
    int* outBuffer,
    int stringLen)
{
    char* endPtr;
    int randomValue;
    float randomFloat;
    float tempFloat;
    int stepSize;
    int* bufferPtr;
    int* ptr1;
    int* ptr2;
    int* ptr3;
    int blockCount;
    float floatFromRandom;
    float extraOutST0;
    int* ptr4;
    int constantValue;

    // Calculate end pointer from string length (passed in EAX)
    endPtr = inputString + stringLen;

    // Get a random seed value (converted to float)
    randomValue = getRandomSeedValue();
    randomFloat = (float)randomValue;

    blockCount = 0;

    if (inputString != endPtr) {
        // Initialize floating point copy of random for use inside loop
        floatFromRandom = (float10)randomValue;

        // Set up buffer pointers (offsets into the output buffer)
        ptr3 = outBuffer + 0xc / 4;  // +0x0C
        ptr1 = outBuffer + 0x8 / 4;  // +0x08
        ptr2 = outBuffer + 0x4 / 4;  // +0x04
        int* ptr5 = outBuffer;       // base (unused directly)
        int* ptr6 = outBuffer + 0x20 / 4; // +0x20
        int* ptr7 = outBuffer + 0x24 / 4; // +0x24
        int* ptr8 = outBuffer + 0x28 / 4; // +0x28

        constantValue = DAT_00e2b1a4;  // Some constant, e.g., 0x3F800000 (1.0f) or 0x00000000

        do {
            if ((inputString == NULL) || (*inputString == '\x02')) {
                // Start of a block marker (0x02) or null string
                if (flag == '\0') {
                    // Mode 1: write 7 random floats + constant
                    this = NoiseGenerator::appendNoiseFloat(this, (float)floatFromRandom);
                    this = NoiseGenerator::appendNoiseFloat(this, randomFloat);
                    this = NoiseGenerator::appendNoiseFloat(this, randomFloat);
                    this = NoiseGenerator::appendNoiseFloat(this, randomFloat);
                    this = NoiseGenerator::appendNoiseFloat(this, randomFloat);
                    this = NoiseGenerator::appendNoiseFloat(this, randomFloat);
                    this = NoiseGenerator::appendNoiseFloat(this, randomFloat);

                    // Write constant at offset +0x1C
                    *(outBuffer + 0x1c / 4) = constantValue;

                    stepSize = 0x20;  // 32 bytes
                } else {
                    // Mode 2: write 6 random floats + 2 constants
                    NoiseGenerator::writeNoiseFloatToBuffer((float)floatFromRandom, ptr2);  // +0x04
                    NoiseGenerator::writeNoiseFloatToBuffer(randomFloat, ptr1);            // +0x08
                    NoiseGenerator::writeNoiseFloatToBuffer(randomFloat, ptr3);            // +0x0C
                    NoiseGenerator::writeNoiseFloatToBuffer(randomFloat, outBuffer + 0x20 / 4); // +0x20
                    NoiseGenerator::writeNoiseFloatToBuffer(randomFloat, outBuffer + 0x24 / 4); // +0x24
                    NoiseGenerator::writeNoiseFloatToBuffer(randomFloat, outBuffer + 0x28 / 4); // +0x28

                    // Write constants at +0x2C and +0x3C
                    *(outBuffer + 0x2c / 4) = constantValue;
                    *(outBuffer + 0x3c / 4) = constantValue;

                    stepSize = 0x40;  // 64 bytes
                }

                // Advance pointers by step size
                ptr1 = (int*)((char*)ptr1 + stepSize);
                ptr2 = (int*)((char*)ptr2 + stepSize);
                ptr3 = (int*)((char*)ptr3 + stepSize);
                outBuffer = (int*)((char*)outBuffer + stepSize);
                blockCount++;
            }
            else if (*inputString != '\0') {
                // For other non-null characters (e.g., data bytes), perform 7 skip operations
                this = NoiseGenerator::skipNoise(this);
                this = NoiseGenerator::skipNoise(this);
                this = NoiseGenerator::skipNoise(this);
                this = NoiseGenerator::skipNoise(this);
                this = NoiseGenerator::skipNoise(this);
                this = NoiseGenerator::skipNoise(this);
                this = NoiseGenerator::skipNoise(this);
                floatFromRandom = extraOutST0;  // Preserve whatever float result comes back
            }

            inputString++;
        } while (inputString != endPtr);

        // Write the number of blocks processed
        *outCount = blockCount;
        return this;
    }

    // Edge case: empty string
    *outCount = 0;
    return this;
}