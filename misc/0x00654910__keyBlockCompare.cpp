// FUNC_NAME: keyBlockCompare
uint __fastcall keyBlockCompare(byte* key1, byte* key2)
{
    bool bGreater;
    uint remainingBytes;
    int diff;

    remainingBytes = 8;
    do {
        // Compare 4-byte chunks
        if (*(int*)key1 != *(int*)key2) {
            goto byteCompare;
        }
        remainingBytes -= 4;
        key2 += 4;
        key1 += 4;
    } while (3 < remainingBytes);

    // All 8 bytes matched
    bGreater = false;
    goto done;

byteCompare:
    // Compare remaining bytes (starting from first mismatched chunk)
    diff = (uint)*key1 - (uint)*key2;
    if (diff == 0) {
        if (remainingBytes == 1) goto equal;
        diff = (uint)key1[1] - (uint)key2[1];
        if (diff == 0) {
            if (remainingBytes == 2) goto equal;
            diff = (uint)key1[2] - (uint)key2[2];
            if (diff == 0) {
                if (remainingBytes == 3) goto equal;
                diff = (uint)key1[3] - (uint)key2[3];
                if (diff == 0) goto equal;
            }
        }
    }
    bGreater = true;
    if (diff < 1) {
        return 0xffffff00; // key1 < key2
    }
done:
    return (uint)!bGreater; // 0 if key1 > key2, 1 if equal
equal:
    bGreater = false;
    goto done;
}