// FUNC_NAME: IsEqualGUID
bool __cdecl IsEqualGUID(const GUID& guid1, const GUID& guid2)
{
    // Compare two GUIDs by comparing their Data1, Data2, Data3, and Data4 fields
    // GUID structure:
    //   +0x00: unsigned long  Data1 (4 bytes)
    //   +0x04: unsigned short Data2 (2 bytes)
    //   +0x06: unsigned short Data3 (2 bytes)
    //   +0x08: unsigned char  Data4[8] (8 bytes)
    // Total: 16 bytes

    const byte* p1 = reinterpret_cast<const byte*>(&guid1);
    const byte* p2 = reinterpret_cast<const byte*>(&guid2);
    uint remaining = 0x10; // 16 bytes to compare

    // Compare 4 bytes at a time (as ints) for efficiency
    do {
        if (*(const int*)p1 != *(const int*)p2)
            goto byteCompare;
        remaining -= 4;
        p2 += 4;
        p1 += 4;
    } while (3 < remaining);

    // If we compared all 16 bytes as ints and they matched, GUIDs are equal
    if (remaining == 0) {
        return true;
    }

byteCompare:
    // Compare remaining bytes individually
    int diff = (uint)*p1 - (uint)*p2;
    if (diff == 0) {
        if (remaining == 1) return true;
        diff = (uint)p1[1] - (uint)p2[1];
        if (diff == 0) {
            if (remaining == 2) return true;
            diff = (uint)p1[2] - (uint)p2[2];
            if (diff == 0) {
                if (remaining == 3) return true;
                diff = (uint)p1[3] - (uint)p2[3];
                if (diff == 0) return true;
            }
        }
    }
    return diff > 0;
}