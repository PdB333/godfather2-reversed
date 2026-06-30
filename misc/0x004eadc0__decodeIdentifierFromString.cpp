// FUNC_NAME: decodeIdentifierFromString
void decodeIdentifierFromString(void)
{
    // This function decodes a string representation (from the game data) into a 16-byte identifier (probably a hash/GUID).
    // Input: EAX = pointer to encoded string (null-terminated, up to 23 characters)
    // Output: ESI = pointer to 16-byte output buffer
    // Uses two global lookup tables: DAT_010c2330 (256 bytes) and s___________________________________010c2331 (some array of bytes).
    // The decoding logic appears to be a custom base conversion (likely base-??) for compact string IDs.

    int inputPtr;          // in_EAX
    int outputIdx;         // iVar2
    int count;             // iVar4
    int decodedLen;        // _Size
    int lastPartLen;       // _Size_00
    int copyOffset;        // sVar1
    char localBuf[24];     // local_18 (max 23 chars + null? Actually only used up to 0x17 bytes)
    extern const size_t DAT_010c2330[256]; // Mapping table: maps input char to decoded value (0 means invalid)
    extern const signed char s___________________________________010c2331[512]; // Lookup for further encoding

    // Clear output (16 bytes)
    *(int*)unaff_ESI = 0;
    ((int*)unaff_ESI)[1] = 0;
    ((int*)unaff_ESI)[2] = 0;
    ((int*)unaff_ESI)[3] = 0;

    if (inputPtr == 0) return;

    // Step 1: Decode input string into localBuf using DAT_010c2330 mapping (up to 23 chars)
    decodedLen = 0;
    do {
        size_t idx = *(unsigned char*)(inputPtr + decodedLen);
        if (DAT_010c2330[idx] == 0)
            break;
        localBuf[decodedLen] = (char)DAT_010c2330[idx];
        decodedLen++;
    } while (decodedLen < 0x17);

    if (decodedLen < 0x11) {
        // Short string: copy directly if non‑empty
        if (0 < decodedLen) {
            memcpy(unaff_ESI, localBuf, decodedLen);
        }
    } else {
        // Long string: decode more complexly
        lastPartLen = 0x2f - 2 * decodedLen; // e.g., for max 23 chars → 1
        copyOffset = 0;
        if (0 < lastPartLen) {
            // Copy the last part of localBuf into output
            memcpy(unaff_ESI, localBuf + (decodedLen - lastPartLen), lastPartLen);
            copyOffset = lastPartLen;
        }

        // Decode special first byte with offset
        *(unsigned char *)((int)unaff_ESI + copyOffset) =
            (unsigned char)(s___________________________________010c2331[(unsigned char)localBuf[0] + 0xff] - 0x80);

        outputIdx = copyOffset + 1;
        if (outputIdx < 0x10) {
            // Process triplets of localBuf (starting from index 1) into two‑byte chunks
            unsigned char *ptr = (unsigned char*)localBuf + 1;
            while (outputIdx < 0x10) {
                int val = s___________________________________010c2331[*ptr + 0xff] +
                          s___________________________________010c2331[ptr[1] + 0xff] * 0x28 +
                          s___________________________________010c2331[ptr[2] + 0xff] * 0x640;
                *(unsigned char *)((int)unaff_ESI + outputIdx) = (unsigned char)val;
                *(unsigned char *)((int)unaff_ESI + outputIdx + 1) = (unsigned char)(val >> 8);
                outputIdx += 2;
                ptr += 3;
            }
        }
    }
}