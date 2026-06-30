// FUNC_NAME: TNL::Checksum::calculateHash
// Function at 0x004da7e0
// This is a recursive hash function used for synchronizing networked objects (ghost validation).
// The input structure (this) has the layout:
//   +0x00: type byte (0x01 = null/identity, else data)
//   +0x01: name string (at most 11 bytes, but only first 9 used)
//   +0x0C: seed1 (uint32)
//   +0x10: seed2 (uint32)
//   +0x14: child pointer (another such structure, or NULL)
// Output is 4 uint32 hash values written to outHash.

void __thiscall TNL::Checksum::calculateHash(char* objectData, uint* outHash)
{
    bool stringTruncated;
    char ch;
    int ninthChar;
    uint seed1;
    uint seed2;
    uint* puVar6;
    uint runningHash;
    uint hash2;
    char* pName;
    bool bPad;
    uint combinedSeg[2]; // local_1c and local_18 overlap: actual bytes used are from &local_1c to &local_18 inclusive?
    // Layout: local_1c (uint), local_18 (uint), local_14 (uint), local_10 (uint), local_c (uint)
    // We treat them as 5 uints but the algorithm uses byte loops.

    // Check for null/identity object
    if (*objectData == 0x01) {
        outHash[0] = 0xBADBADBA;
        outHash[1] = 0xBEEFBEEF;
        outHash[2] = 0xEAC15A55;
        outHash[3] = 0x91100911;
        return;
    }

    seed1 = *(uint*)(objectData + 0x0C);
    hash2 = (seed1 << 0x1C) | *(uint*)(objectData + 0x10);
    pName = objectData + 1;
    bPad = false;
    // Read first 8 bytes of name, padding with 'X' for nulls or shorter strings
    for (int i = 0; i < 8; i++) {
        ch = *pName;
        if (ch == '\0') {
            bPad = true;
            ch = 'X';
        } else if (bPad) {
            ch = 'X';
        } else {
            pName++;
        }
        combinedSeg[0] = (combinedSeg[0] & 0xFFFFFF00) | (unsigned char)ch; // pseudo: writing byte to lower 8 bits? Decompiler writes char* puVar6
        // Actually puVar6 = &local_18, increment bytewise. So we store ch into byte array starting at local_18.
        // For reconstruction, we'll use a byte array.
    }
    // Get 9th character (or 'X' if truncated)
    if (!bPad) {
        ninthChar = *pName;
    } else {
        ninthChar = 'X'; // 0x58
    }
    // Combine seed1 >>4 with the 9th character as high byte
    seed1 = (seed1 >> 4) | (ninthChar << 0x18);

    // If there is a child object, hash it recursively and mix
    if (*(int*)(objectData + 0x14) != 0) {
        // Recursively hash the child; the resulting 4 uints are stored in local_c..local_18
        // Decompiled shows FUN_004da7e0(&local_10) but that's incorrect; we need to pass the child pointer.
        // Based on the assembly, it's more likely:
        TNL::Checksum::calculateHash(*(char**)(objectData + 0x14), &combinedSeg[1]); // or &local_10 ?
        // For reconstruction, we assume the child hash output is placed into local_10 and local_c, etc.
        // Then we mix child hash into seed1 and hash2 using the padded 8-byte name buffer.
        uint temp = seed1;
        uint* bytePtr = (uint*)&combinedSeg[0]; // start at local_1c (which contains the first 8 bytes? Actually need to track exactly)
        do {
            temp = temp * 0x1003F + (byte)*bytePtr; // using each byte from the 8-byte buffer?
            bytePtr = (uint*)((int)bytePtr + 1);
        } while (bytePtr < (uint*)&combinedSeg[1]); // until local_18
        seed1 = seed1 ^ ((temp ^ seed1) & 0xFFFFFF); // mask bottom 24 bits? Actually xor with mask
        // Then similar for hash2 using different segment
        temp = hash2;
        bytePtr = (uint*)&combinedSeg[2]; // starting at local_14? Decompiler uses local_c
        do {
            temp = temp * 0x1003F + (byte)*bytePtr;
            bytePtr = (uint*)((int)bytePtr + 1);
        } while (bytePtr < (uint*)&combinedSeg[0]); // until local_18
        // The actual mixing is unclear; we approximate.
    }

    outHash[0] = seed1;
    outHash[1] = hash2;
    outHash[2] = combinedSeg[0]; // local_18
    outHash[3] = combinedSeg[2]; // local_14
}