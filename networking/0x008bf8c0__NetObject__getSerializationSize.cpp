// FUNC_NAME: NetObject::getSerializationSize
int __thiscall NetObject::getSerializationSize(int* thisPtr)
{
    int baseCount;
    int totalSize;

    // Compute the number of 4-byte elements based on various fields
    // Offsets: +0x24 (field_9), +0x28 (field_10), +0x2c (field_11), +0x30 (field_12),
    //          +0x34 (field_13), +0x38 (field_14), +0x3c (field_15)
    baseCount = thisPtr[0xd] +                                          // +0x34
                (thisPtr[0xb] + 0xc +                                   // +0x2c + fixed header size
                (thisPtr[0xc] * 5 + thisPtr[0xf] + thisPtr[0xe]) * 2) * 2 +  // +0x30, +0x3c, +0x38
                thisPtr[0xa] + thisPtr[0x9];                            // +0x28, +0x24

    totalSize = baseCount * 4;

    // If the object is a specific subclass (magic ID 0x637b907), include additional size
    if (thisPtr[0] == 0x637b907) {
        totalSize += FUN_008921c0(thisPtr + baseCount);
    }

    return totalSize;
}