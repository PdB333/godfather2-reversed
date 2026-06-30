// FUNC_NAME: hashBuffer (0x004db320) - Simple hash function using multiplier 0x1003f, likely used for packet/serialization hashing in EARS networking layer.
int hashBuffer(byte* data, int length)
{
    int hash = 0;
    if ((data != (byte*)0x0) && (data + length, data < data + length)) {
        do {
            byte currentByte = *data;
            data = data + 1;
            hash = hash * 0x1003f + (unsigned int)currentByte;
        } while (data < data + length); // note: end pointer computed each iteration but condition uses original end pointer? In assembly it's a comparison before loop entry.
        // Actually the decompiler shows a single end pointer computed once: pbVar3 = data + length, then compare data < pbVar3 each iteration.
    }
    return hash;
}