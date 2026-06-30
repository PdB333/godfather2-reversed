// FUNC_NAME: RunLengthDecoder::skipEncodedElements
// Address: 0x0057dc70
// Role: Decodes a variable-length compressed stream of elements. Each element has a type (low nibble) and a span (high nibble+next byte). The function skips 'targetIndex' elements and advances the data pointer to the start of the element at that index (or to the end if out of bounds).

// External data tables used for per-type size calculations (from .data at 0x00e2be68, 0x00e2be30)
extern const int g_sizeMultiplier[16]; // DAT_00e2be68
extern const int g_sizeOffset[16];    // DAT_00e2be30

void __fastcall skipEncodedElements(void* unused, int targetIndex, int** dataPtr)
{
    byte bLowNibble;
    byte bHighNibble;
    uint count;
    uint spanLen;
    byte* pbCurr;
    byte* pbTmp;
    uint elementType;

    pbCurr = (byte*)*dataPtr;
    bLowNibble = *pbCurr & 0xf;

    if (bLowNibble == 5) {
        // Run of multiple elements: read total count (12-bit value from high nibble of first byte + second byte)
        count = ((uint)pbCurr[1] << 4) | ((uint)(*pbCurr >> 4));
        pbCurr += 2;

        if (count != 0) {
            do {
                // Each element header: 2 bytes, low nibble = type, high nibble+next byte = span length
                spanLen = ((uint)pbCurr[1] << 4) | ((uint)(*pbCurr >> 4));
                count--;
                elementType = *pbCurr & 0xf;
                // Check if the requested index falls within this element's span (0-based)
                if (targetIndex <= (int)(spanLen - 1)) {
                    // Found: compute pointer to start of this element's data
                    pbTmp = pbCurr + 2;
                    switch (elementType) {
                    case 0: // 5 bytes total (data after 2-byte header = 3 bytes? Actually header+3 = 5)
                        pbTmp = pbCurr + 5;
                        break;
                    case 1: // 8 bytes total
                        pbTmp = pbCurr + 8;
                        break;
                    case 2: // 11 bytes total
                        pbTmp = pbCurr + 0xb;
                        break;
                    case 3: // 14 bytes total
                        pbTmp = pbCurr + 0xe;
                        break;
                    case 4: // Variable length: 2-byte header + spanLen * 4 bytes (calls sub-decoder)
                        FUN_0057d370(); // sub-decoder (not reconstructed)
                        pbTmp = pbTmp + spanLen * 4; // pbTmp starts at pbCurr+2, adds spanLen*4 -> total = 2+spanLen*4
                        break;
                    case 6: // 8 bytes + spanLen bytes
                        pbTmp = pbCurr + spanLen + 8;
                        break;
                    case 7: // 8 bytes + spanLen*2 bytes
                        pbTmp = pbCurr + spanLen * 2 + 8;
                        break;
                    case 0xd: // 2 bytes only (header)
                        // pbTmp stays at pbCurr+2
                        break;
                    // Other types default to no change (pbTmp remains pbCurr+2)
                    }
                    // Skip all remaining elements in this run to advance past them
                    while (0 < (int)count) {
                        elementType = *pbTmp & 0xf;
                        spanLen = ((uint)pbTmp[1] << 4) | ((uint)(*pbTmp >> 4));
                        // Advance by the size of the element (using lookup tables)
                        pbTmp = pbTmp + spanLen * g_sizeMultiplier[elementType] + g_sizeOffset[elementType];
                        count--;
                    }
                    *dataPtr = (int)pbTmp;
                    return;
                }
                // Index not in this element: subtract the number of entries consumed and move to next element
                targetIndex -= (spanLen - 1);
                // Move to next element header using per-type size calculation
                pbCurr = pbCurr + spanLen * g_sizeMultiplier[elementType] + g_sizeOffset[elementType];
            } while (0 < (int)count);
            // Reached end of run without finding the index
            *dataPtr = (int)pbCurr;
            return;
        }
    }
    else {
        // Single element
        switch (bLowNibble) {
        case 0:
            *dataPtr = (int)(pbCurr + 5);
            return;
        case 1:
            *dataPtr = (int)(pbCurr + 8);
            return;
        case 2:
            *dataPtr = (int)(pbCurr + 0xb);
            return;
        case 3:
            *dataPtr = (int)(pbCurr + 0xe);
            return;
        case 4:
            bHighNibble = pbCurr[1];
            FUN_0057d370(); // sub-decoder
            *dataPtr = (int)(pbCurr + ((uint)bHighNibble << 4 | (uint)(*pbCurr >> 4)) * 4 + 2);
            return;
        case 6:
            *dataPtr = (int)(pbCurr + ((uint)pbCurr[1] << 4 | (uint)(*pbCurr >> 4)) + 8);
            return;
        case 7:
            *dataPtr = (int)(pbCurr + ((uint)pbCurr[1] << 4 | (uint)(*pbCurr >> 4)) * 2 + 8);
            return;
        case 0xc:
            pbCurr += 2;
            break; // fall through to default advancement
        case 0xd:
            *dataPtr = (int)(pbCurr + 2);
            return;
        }
    }
    *dataPtr = (int)pbCurr;
    return;
}