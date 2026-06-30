// FUNC_NAME: huffmanDecodeStream
// Function at 0x0057d3a0: Decodes a variable-length encoded stream using a Huffman-like table.
// Advances the pointer in param_1 past the decoded data.
// Tables at 0x00e2be68 and 0x00e2be30 are 16-element arrays of int offsets.
// Used by TNL or EARS networking layer for packet decompression.

extern int gDecodeTableOffset[16];   // +0x00e2be68, base offset per symbol
extern int gDecodeTableLength[16];   // +0x00e2be30, length per symbol

void huffmanDecodeStream(unsigned int **param_1) {
    unsigned char *pbCurrent = (unsigned char *)*param_1;
    unsigned char bHeader = *pbCurrent;
    int iType = bHeader & 0x0F;          // low nibble: symbol type
    int iCount = (bHeader >> 4);         // high nibble: number of symbols or encoded length
    unsigned int uEncoded = (unsigned int)*(pbCurrent + 1) << 4 | (unsigned int)(bHeader >> 4);
    unsigned int uRemaining;

    if (iType != 5) {
        // Simple single-symbol decode: offset = uEncoded * tableOffset + tableLength
        *param_1 = (unsigned int *)(pbCurrent + gDecodeTableOffset[iType] * uEncoded + gDecodeTableLength[iType]);
        return;
    }

    // Type 5: multi-level decode (Huffman tree traversal)
    int iBlocks = (int)uEncoded >> 2;    // number of full blocks (each block processes 4 symbols?)
    uRemaining = (bHeader >> 4) & 3;     // remaining count after blocks (0-3)
    pbCurrent += 2;                      // skip header bytes

    if (iBlocks != 0) {
        do {
            // Process one block of 4 symbols? The inner loop iterates 4 times per block.
            unsigned char b1 = *pbCurrent;
            int t1 = b1 & 0x0F;
            int off1 = ((unsigned int)*(pbCurrent + 1) << 4 | (unsigned int)(b1 >> 4)) * gDecodeTableOffset[t1] + gDecodeTableLength[t1];
            unsigned char b2 = pbCurrent[off1];
            int t2 = b2 & 0x0F;
            int off2 = ((unsigned int)pbCurrent[off1 + 1] << 4 | (unsigned int)(b2 >> 4)) * gDecodeTableOffset[t2] + gDecodeTableLength[t2];
            int offSum = off2 + off1;
            unsigned char b3 = pbCurrent[offSum];
            int t3 = b3 & 0x0F;
            int off3 = ((unsigned int)pbCurrent[offSum + 1] << 4 | (unsigned int)(b3 >> 4)) * gDecodeTableOffset[t3] + gDecodeTableLength[t3];
            int offSum2 = off3 + offSum;
            unsigned char b4 = pbCurrent[offSum2];
            int t4 = b4 & 0x0F;
            int off4 = ((unsigned int)pbCurrent[offSum2 + 1] << 4 | (unsigned int)(b4 >> 4)) * gDecodeTableOffset[t4] + gDecodeTableLength[t4];
            iBlocks--;
            pbCurrent += off4 + offSum2;
        } while (0 < iBlocks);
    }

    if ((bHeader >> 4 & 3) != 0) {
        do {
            unsigned char b = *pbCurrent;
            int t = b & 0x0F;
            uRemaining--;
            pbCurrent += ((unsigned int)*(pbCurrent + 1) << 4 | (unsigned int)(b >> 4)) * gDecodeTableOffset[t] + gDecodeTableLength[t];
        } while (0 < (int)uRemaining);
    }

    *param_1 = (unsigned int *)pbCurrent;
    return;
}