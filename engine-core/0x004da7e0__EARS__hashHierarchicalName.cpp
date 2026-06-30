// FUNC_NAME: EARS::hashHierarchicalName
void __thiscall EARS::hashHierarchicalName(char *inputBuffer, uint *outputHash)
{
    bool bNullTerm;
    char nextChar;
    int sizeField;
    uint tempVar;
    uint hashLow;
    uint hashHigh;
    uint *pBufByte;
    uint childOutput[4]; // local_1c, local_18, local_14, local_10, local_c but we use array
    uint hashTemp;
    char localBuf[8]; // written to local_18 and local_14 as uints

    // Terminal node: if first byte is 0x01, return fixed magic numbers
    if (*inputBuffer == '\x01') {
        outputHash[0] = 0xbadbadba;
        outputHash[1] = 0xbeefbeef;
        outputHash[2] = 0xeac15a55;
        outputHash[3] = 0x91100911;
        return;
    }

    // Extract initial hash seeds from input +0x0C and +0x10
    hashLow = *(uint *)(inputBuffer + 0x0C); // +0x0C
    hashHigh = hashLow << 0x1C | *(uint *)(inputBuffer + 0x10); // +0x10

    // Read up to 8 bytes from inputBuffer+1, null-terminated string portion
    char *pSrc = inputBuffer + 1;
    bNullTerm = false;
    pBufByte = (uint *)&localBuf[0];
    int count = 8;
    do {
        nextChar = *pSrc;
        if (nextChar == '\0') {
            bNullTerm = true;
            nextChar = 'X'; // pad with 'X'
        }
        else if (bNullTerm) {
            nextChar = 'X'; // continue padding after null
        }
        else {
            pSrc = pSrc + 1; // advance only if not null and not padded
        }
        *(char *)pBufByte = nextChar;
        pBufByte = (uint *)((int)pBufByte + 1);
        count = count - 1;
    } while (count != 0);

    // sizeField: default 0x58 (decimal 88), or next byte after the 8-char block if no null encountered
    sizeField = 0x58;
    if (!bNullTerm) {
        sizeField = (int)*pSrc; // read next byte as integer
    }

    // Update hashLow with sizeField and shift
    hashLow = (hashLow >> 4) | (sizeField << 0x18);

    // If there is a child node (inputBuffer+0x14 != 0), recursively hash it
    if (*(int *)(inputBuffer + 0x14) != 0) {
        hashHierarchicalName((char *)&childOutput[0]); // recursive call, uses &local_10 as input? Actually call with &local_10, but our childOutput[0] is that address

        // Use first uint of child's output (childOutput[0] corresponds to local_10) to update hashLow
        hashTemp = childOutput[0]; // local_10
        pBufByte = &hashTemp;
        uint uVar4 = hashLow;
        do {
            uVar4 = uVar4 * 0x1003f + (uint)(byte)*pBufByte;
            pBufByte = (uint *)((int)pBufByte + 1);
        } while (pBufByte < (uint *)&localBuf[0]); // process 4 bytes of child's first output

        hashLow = hashLow ^ (uVar4 ^ hashLow) & 0xffffff;

        // Use fourth uint of child's output (childOutput[3] corresponds to local_c) to update hashHigh
        hashTemp = childOutput[3]; // local_c
        pBufByte = &hashTemp;
        do {
            hashHigh = hashHigh * 0x1003f + (uint)(byte)*pBufByte;
            pBufByte = (uint *)((int)pBufByte + 1);
        } while (pBufByte < (uint *)&localBuf[0]); // process 4 bytes
    }

    // Store final results
    outputHash[0] = hashLow;
    outputHash[1] = hashHigh;
    outputHash[2] = *(uint *)&localBuf[0]; // first 4 bytes of buffer
    outputHash[3] = *(uint *)&localBuf[4]; // next 4 bytes of buffer
    return;
}