// FUNC_NAME: ContentLoader::parseFromBuffer
void __thiscall ContentLoader::parseFromBuffer(void) {
    int* pRefCounted1;
    int* pRefCounted2;
    int* pTemp;
    undefined4* pRefCounted3;
    int sizeInBytes;
    uint roundedSize;
    undefined** pVtableTmp; // +0x00 vtable pointer
    undefined4 bufferStart1; // start of temporary buffer
    undefined4 bufferStart2;
    undefined4 bufferStart3;
    int field_0x10_copy; // copy of this->+0x10
    uint bufferSizeBytes; // total size of buffer in bytes
    uint bufferLength; // string length
    char nullByte; // zero terminator check
    char flag2;
    int someSize; // offset 0x28
    int someOtherSize;
    undefined4 unk_local_108;
    char bufferEnd; // end of local buffer

    // Read fields from this
    field_0x10_copy = *(int*)(this + 0x10);
    bufferStart3 = *(undefined4*)(this + 0x0C);
    someSize = field_0x10_copy * 8; // multiply by 8
    bufferStart1 = 0;
    bufferStart2 = 0;
    bufferSizeBytes = 0;
    pVtableTmp = &PTR_LAB_00e42d70; // pointer to a static vtable
    bufferLength = 0;
    nullByte = '\0';
    flag2 = 0;
    bufferEnd = 0;
    unk_local_108 = 0;
    someOtherSize = someSize;

    // First allocation: 0x18 bytes for a ref-counted object
    pRefCounted3 = (undefined4*)FUN_009c8e50(0x18); // operator new
    if (pRefCounted3 == (undefined4*)0x0) {
        pRefCounted3 = (undefined4*)0x0;
    } else {
        pRefCounted3[1] = 0; // ref count?
        pRefCounted3[2] = 0;
        *pRefCounted3 = &PTR_LAB_00e42d64; // vtable
        pRefCounted3[4] = 0;
        pRefCounted3[3] = 0;
        *(undefined1*)(pRefCounted3 + 5) = 1; // set some byte
    }

    // Release previous this->+0x1c object
    pRefCounted2 = *(int**)(this + 0x1C);
    if (pRefCounted2 != (int*)0x0) {
        pTemp = pRefCounted2 + 2;
        *pTemp = *pTemp - 1; // decrement ref count
        if (*pTemp == 0) {
            (**(code**)(*pRefCounted2 + 8))(); // call destructor
        }
    }
    *(undefined4**)(this + 0x1C) = pRefCounted3;
    if (pRefCounted3 != (undefined4*)0x0) {
        pRefCounted3[2] = pRefCounted3[2] + 1; // increment ref count
    }

    // Initialize the temporary string buffer from some source
    FUN_0064bc00(&bufferSizeBytes); // likely fills buffer with data

    // Second allocation: 0x24 bytes
    sizeInBytes = FUN_009c8e50(0x24);
    if (sizeInBytes == 0) {
        sizeInBytes = 0;
    } else {
        sizeInBytes = FUN_00654840(&bufferSizeBytes); // constructs object from buffer
    }

    // Release previous this->+0x18 object
    pRefCounted2 = *(int**)(this + 0x18);
    if (pRefCounted2 != (int*)0x0) {
        pTemp = pRefCounted2 + 2;
        *pTemp = *pTemp - 1;
        if (*pTemp == 0) {
            (**(code**)(*pRefCounted2 + 8))();
        }
    }
    *(int*)(this + 0x18) = sizeInBytes;
    if (sizeInBytes != 0) {
        *(int*)(sizeInBytes + 8) = *(int*)(sizeInBytes + 8) + 1; // increment ref count
    }

    // Third allocation: another 0x18 byte object
    pRefCounted3 = (undefined4*)FUN_009c8e50(0x18);
    if (pRefCounted3 == (undefined4*)0x0) {
        pRefCounted3 = (undefined4*)0x0;
    } else {
        pRefCounted3[1] = 0;
        pRefCounted3[2] = 0;
        *pRefCounted3 = &PTR_LAB_00e42d64;
        pRefCounted3[4] = 0;
        pRefCounted3[3] = 0;
        *(undefined1*)(pRefCounted3 + 5) = 1;
    }

    // Release previous this->+0x20 object
    pRefCounted2 = *(int**)(this + 0x20);
    if (pRefCounted2 != (int*)0x0) {
        pTemp = pRefCounted2 + 2;
        *pTemp = *pTemp - 1;
        if (*pTemp == 0) {
            (**(code**)(*pRefCounted2 + 8))();
        }
    }
    *(undefined4**)(this + 0x20) = pRefCounted3;
    if (pRefCounted3 != (undefined4*)0x0) {
        pRefCounted3[2] = pRefCounted3[2] + 1;
    }

    // Round up buffer length to multiple of 8, then store shifted
    roundedSize = bufferLength + 7;
    bufferLength = roundedSize & 0xFFFFFFF8;
    *(uint*)(this + 0x28) = roundedSize >> 3; // store number of 8-byte chunks

    // Finalize parsing
    FUN_0064bc00(&bufferSizeBytes); // possibly cleanup temp buffer

    // Set a flag if conditions met:
    // - nullByte is zero (no error)
    // - original size matches rounded size
    // - an internal flag in the object at +0x18 is non-zero
    if ((nullByte == '\0') && (*(uint*)(this + 0x10) == ((bufferLength + 7) >> 3)) &&
        (*(char*)(*(int*)(this + 0x18) + 0x20) != '\0')) {
        *(undefined1*)(this + 0x24) = 1; // set flag at offset 0x24
    }

    FUN_0064b440(); // final cleanup call (likely returns void)
    return;
}