// FUNC_NAME: KeyDecoder::decodeStringToBytes

void KeyDecoder::decodeStringToBytes(const char* inputString, uint8_t* outputBuffer) {
    // External lookup tables
    extern const uint8_t g_substitutionTable[256];   // At 0x010c2330
    extern const uint8_t g_base40ValueTable[256];    // At 0x010c2331 (used with offset +0xff)

    // Clear output buffer (16 bytes = 4 dwords)
    *(uint32_t*)(outputBuffer + 0) = 0;
    *(uint32_t*)(outputBuffer + 4) = 0;
    *(uint32_t*)(outputBuffer + 8) = 0;
    *(uint32_t*)(outputBuffer + 12) = 0;

    if (inputString == nullptr) {
        return;
    }

    // Map input characters through substitution table into local buffer (max 23 bytes)
    uint8_t mappedBuffer[24] = {0};      // local_18
    size_t mappedLength = 0;             // _Size

    for (; mappedLength < 23; mappedLength++) {
        uint8_t inputChar = inputString[mappedLength];
        uint8_t mappedChar = g_substitutionTable[inputChar];
        if (mappedChar == 0) {
            break;
        }
        mappedBuffer[mappedLength] = mappedChar;
    }

    // Decode based on length of mapped data
    if (mappedLength < 17) {
        // Short string: copy mapped bytes directly
        if (mappedLength > 0) {
            memcpy(outputBuffer, mappedBuffer, mappedLength);
        }
    } else {
        // Long string (17-23 characters): partially convert base-40 representation
        
        // Number of trailing bytes to copy directly
        size_t copyLength = 0x2F - 2 * mappedLength;   // _Size_00 (0x2F = 47)
        size_t bytesCopied = 0;                         // sVar1

        if (copyLength > 0) {
            memcpy(outputBuffer, mappedBuffer + (mappedLength - copyLength), copyLength);
            bytesCopied = copyLength;
        }

        // Decode the first base-40 ternary digit (bytes[0])
        outputBuffer[bytesCopied] = g_base40ValueTable[mappedBuffer[0]] - 0x80;

        // Decode the remaining triplets (3 base-40 digits -> 2 bytes)
        size_t outputIndex = bytesCopied + 1;       // iVar2
        uint8_t* srcPtr = mappedBuffer + 1;         // pbVar3

        while (outputIndex < 16) {
            uint16_t value = g_base40ValueTable[srcPtr[0]]
                           + g_base40ValueTable[srcPtr[1]] * 0x28
                           + g_base40ValueTable[srcPtr[2]] * 0x640;

            outputBuffer[outputIndex] = (uint8_t)(value & 0xFF);
            outputBuffer[outputIndex + 1] = (uint8_t)(value >> 8);

            outputIndex += 2;
            srcPtr += 3;
        }
    }
}