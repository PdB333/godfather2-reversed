// FUNC_NAME: decodeCompressedBlock

extern int g_encodeTable1[16]; // +0x00 from 0x00e2c758
extern int g_encodeTable2[16]; // +0x00 from 0x00e2c720

void decodeCompressedBlock(int *dataPtr, int unused, int maxSize) {
    byte *src = (byte *)*dataPtr;
    byte header = *src;
    byte lowNibble = header & 0xf;
    byte highNibble = header >> 4;

    if (lowNibble == 5) {
        // Run-length encoded block
        int count = (src[1] << 4) | highNibble;
        int blockSize = *(unsigned short *)(src + 2);
        byte *blockEnd = (src + 2) + (blockSize - 2); // Actually points to end of block
        src += 4;

        if (count != 0) {
            do {
                int length = (src[1] << 4) | (src[0] >> 4);
                int type = src[0] & 0xf;
                int iVar1 = length - 1;

                if (maxSize <= iVar1) {
                    // Handle early exit based on type
                    switch (type) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 6:
                    case 7:
                    case 0xd:
                        *dataPtr = (int)blockEnd;
                        return;
                    case 4:
                        processError(); // FUN_00579a20
                        break;
                    default:
                        break;
                    }
                    *dataPtr = (int)blockEnd;
                    return;
                }

                if (maxSize > 0) {
                    maxSize -= iVar1;
                    // Advance src by table-based offset
                    src += g_encodeTable1[type] * length + g_encodeTable2[type];
                }
                count--;
            } while (count >= 0); // Actually while (0 < (int)count) but loop decrements first

            *dataPtr = (int)src;
            return;
        }
    } else {
        // Single-item types
        switch (lowNibble) {
        case 0:
            *dataPtr = (int)(src + 5);
            return;
        case 1:
            *dataPtr = (int)(src + 8);
            return;
        case 2:
            *dataPtr = (int)(src + 11);
            return;
        case 3:
            *dataPtr = (int)(src + 14);
            return;
        case 4: {
            byte bVal = src[1];
            processError(); // FUN_00579a20
            *dataPtr = (int)(src + ((bVal << 4) | highNibble) * 4 + 2);
            return;
        }
        case 6:
            *dataPtr = (int)(src + ((src[1] << 4) | highNibble) + 8);
            return;
        case 7:
            *dataPtr = (int)(src + ((src[1] << 4) | highNibble) * 2 + 8);
            return;
        case 0xc:
            src += 2;
            break;
        case 0xd:
            *dataPtr = (int)(src + 2);
            return;
        }
    }
    *dataPtr = (int)src;
}