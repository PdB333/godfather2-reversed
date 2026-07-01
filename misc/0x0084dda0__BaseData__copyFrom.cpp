// FUNC_NAME: BaseData::copyFrom
// Address: 0x0084dda0
// Copies a data block from source to destination, resolving two internal pointers.
void __thiscall BaseData::copyFrom(uint32_t* thisPtr, BaseData* src)
{
    int resolvedIndex;
    uint32_t* resolvedPtr;

    // Resolve first pointer: if src->field4 is 0 or 0x48, resolve to 0; else add 0x10
    resolvedIndex = *(int*)(src + 1); // +4 bytes
    if (resolvedIndex == 0 || resolvedIndex == 0x48) {
        resolvedIndex = 0;
    } else {
        resolvedIndex = resolvedIndex + 0x10;
    }
    resolvedPtr = (uint32_t*)GetDataPointer(resolvedIndex); // FUN_004a8ec0
    thisPtr[0] = resolvedPtr[0];
    thisPtr[1] = resolvedPtr[1];

    // Resolve second pointer: from src->field12 (offset 0xc)
    resolvedIndex = *(int*)(src + 3); // +0xc
    if (resolvedIndex == 0 || resolvedIndex == 0x48) {
        resolvedIndex = 0;
    } else {
        resolvedIndex = resolvedIndex + 0x10;
    }
    resolvedPtr = (uint32_t*)GetDataPointer(resolvedIndex);
    thisPtr[2] = resolvedPtr[0];
    thisPtr[3] = resolvedPtr[1];

    // Copy remaining fields directly from src to this
    // +0x14 (8 bytes)
    *(uint64_t*)(thisPtr + 4) = *(uint64_t*)(src + 5);  // offset 0x14 = 5*4 = 20 bytes
    // +0x1c (4 bytes)
    thisPtr[6] = *(uint32_t*)(src + 7);                 // offset 0x1c = 7*4 = 28 bytes
    // +0x20 (8 bytes)
    *(uint64_t*)(thisPtr + 7) = *(uint64_t*)(src + 8);  // offset 0x20 = 8*4 = 32 bytes
    // +0x28 (4 bytes)
    thisPtr[9] = *(uint32_t*)(src + 10);                // offset 0x28 = 10*4 = 40
    // +0x2c (4 bytes)
    thisPtr[10] = *(uint32_t*)(src + 11);               // offset 0x2c = 11*4 = 44
    // +0x30 (4 bytes)
    thisPtr[11] = *(uint32_t*)(src + 12);               // offset 0x30 = 12*4 = 48
    // +0x34 (4 bytes)
    thisPtr[12] = *(uint32_t*)(src + 13);               // offset 0x34 = 13*4 = 52
    // +0x38 (4 bytes)
    thisPtr[13] = *(uint32_t*)(src + 14);               // offset 0x38 = 14*4 = 56
    // +0x3c (4 bytes)
    thisPtr[14] = *(uint32_t*)(src + 15);               // offset 0x3c = 15*4 = 60
    // +0x40 (4 bytes)
    thisPtr[15] = *(uint32_t*)(src + 16);               // offset 0x40 = 16*4 = 64
    // +0x44 (4 bytes)
    thisPtr[16] = *(uint32_t*)(src + 17);               // offset 0x44 = 17*4 = 68
}