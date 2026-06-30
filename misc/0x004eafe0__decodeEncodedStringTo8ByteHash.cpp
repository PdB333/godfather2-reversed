// FUNC_NAME: decodeEncodedStringTo8ByteHash
// Function at 0x004eafe0: Converts an encoded input string (up to 11 bytes) into an 8-byte hash/output.
// Uses two static lookup tables: sFilterTable (256 entries, zero entry terminates input) and sDecodeTable (signed byte table for arithmetic).
// The output buffer is zeroed at start, then filled according to two cases (short input <9 vs long input >=9).
void __fastcall decodeEncodedStringTo8ByteHash(void* output, const void* input)
{
    byte* tempBuffer; // local_c (12 bytes)
    int processedBytes; // _Size
    int tailLen; // _Size_00
    int writePos; // iVar2
    byte* src; // pbVar3
    int value; // iVar4
    byte* outBytes; // unaff_EDI

    // Zero out first 8 bytes of output (two 32-bit words)
    *(uint32_t*)output = 0;
    *(uint32_t*)((byte*)output + 4) = 0;

    if (input == nullptr) return;

    // Stage 1: filter input through sFilterTable, building tempBuffer (max 11 bytes)
    processedBytes = 0;
    tempBuffer = new byte[12]; // actually local on stack
    // In the original code, tempBuffer is a local array, not allocated
    // We'll just use a local array

    do {
        byte inputByte = ((const byte*)input)[processedBytes];
        if (sFilterTable[inputByte] == 0) break;
        tempBuffer[processedBytes] = sFilterTable[inputByte];
        processedBytes++;
    } while (processedBytes < 11);

    // Decision based on length
    if (processedBytes < 9) {
        // Short string: simply copy tempBuffer output
        if (processedBytes > 0) {
            memcpy(output, tempBuffer, processedBytes);
        }
    } else {
        // Long string (9-11 bytes): encode into 8 bytes using a more complex scheme
        tailLen = 23 - 2 * processedBytes; // original: _Size * -2 + 0x17

        // Copy tail from tempBuffer
        if (tailLen > 0) {
            memcpy(output, &tempBuffer[processedBytes - tailLen], tailLen);
        }

        // Write a single derived byte at position tailLen
        ((char*)output)[tailLen] = sDecodeTable[tempBuffer[0] + 0xff] - 0x80;

        writePos = tailLen + 1;

        // Process remaining triplets of tempBuffer[1..] to produce 2-byte groups
        if (writePos < 8) {
            src = &tempBuffer[1];
            do {
                // Combine three table lookups: a + b*0x28 + c*0x640
                value = (byte)sDecodeTable[src[0] + 0xff] +
                        (byte)sDecodeTable[src[1] + 0xff] * 0x28 +
                        (byte)sDecodeTable[src[2] + 0xff] * 0x640;
                ((char*)output)[writePos] = (char)value;
                ((char*)output)[writePos + 1] = (char)(value >> 8);
                writePos += 2;
                src += 3;
            } while (writePos < 8);
        }
    }
}