// FUNC_NAME: ComponentArrayManager::calculateOffsets
void __fastcall ComponentArrayManager::calculateOffsets(void)
{
    uint currentOffset = *(uint *)(this + 0x98); // buffer base address
    if ((currentOffset & 0xf) != 0) {
        currentOffset = (currentOffset & 0xfffffff0) + 0x10; // align to 16 bytes
    }

    // Group 1: small arrays (short counts)
    short count1 = *(short *)(this + 0x10); // +0x10: numTypeA
    if (count1 == 0) {
        *(undefined4 *)(this + 0xd0) = 0; // +0xd0: ptrTypeA
    } else {
        int tempVar = count1 - 1;
        *(uint *)(this + 0xd0) = currentOffset;
        // size = 8 + ( (count1-1) / 32 ) * 8   i.e., 8 bytes per 32 elements
        currentOffset = currentOffset + 8 + ((int)(tempVar + (tempVar >> 0x1f & 0x1fU)) >> 5) * 8;
    }

    short count2 = *(short *)(this + 0x2e); // +0x2e: numTypeB
    if (count2 == 0) {
        *(undefined4 *)(this + 0xcc) = 0; // +0xcc: ptrTypeB
    } else {
        int tempVar = count2 - 1;
        *(uint *)(this + 0xcc) = currentOffset;
        currentOffset = currentOffset + 8 + ((int)(tempVar + (tempVar >> 0x1f & 0x1fU)) >> 5) * 8;
    }

    short count3 = *(short *)(this + 0x74); // +0x74: numTypeC
    if (count3 == 0) {
        *(undefined4 *)(this + 0xd8) = 0; // +0xd8: ptrTypeC
    } else {
        int tempVar = count3 - 1;
        *(uint *)(this + 0xd8) = currentOffset;
        currentOffset = currentOffset + 8 + ((int)(tempVar + (tempVar >> 0x1f & 0x1fU)) >> 5) * 8;
    }

    short count4 = *(short *)(this + 0x76); // +0x76: numTypeD
    if (count4 == 0) {
        *(undefined4 *)(this + 0xd4) = 0; // +0xd4: ptrTypeD
    } else {
        int tempVar = count4 - 1;
        *(uint *)(this + 0xd4) = currentOffset;
        currentOffset = currentOffset + 8 + ((int)(tempVar + (tempVar >> 0x1f & 0x1fU)) >> 5) * 8;
    }

    short count5 = *(short *)(this + 0x8a); // +0x8a: numTypeE
    if (count5 == 0) {
        *(undefined4 *)(this + 0xe8) = 0; // +0xe8: ptrTypeE
    } else {
        int tempVar = count5 - 1;
        *(uint *)(this + 0xe8) = currentOffset;
        currentOffset = currentOffset + 8 + ((int)(tempVar + (tempVar >> 0x1f & 0x1fU)) >> 5) * 8;
    }

    // After small arrays, process a block of combined size
    int tempVar2 = currentOffset + *(int *)(this + 0x7c); // +0x7c: some size offset
    int count6 = *(int *)(this + 0x38); // +0x38: numLargeArrayA
    if (count6 == 0) {
        *(undefined4 *)(this + 0xb0) = 0; // +0xb0: ptrLargeArrayA
    } else {
        *(int *)(this + 0xb0) = tempVar2;
        tempVar2 = tempVar2 + *(int *)(this + 0x38);
    }

    int count7 = *(int *)(this + 0x34); // +0x34: numLargeArrayB
    if (count7 == 0) {
        *(undefined4 *)(this + 0xa8) = 0; // +0xa8: ptrLargeArrayB
    } else {
        *(int *)(this + 0xa8) = tempVar2;
        tempVar2 = tempVar2 + *(int *)(this + 0x34);
    }

    int count8 = *(int *)(this + 0x5c); // +0x5c: numLargeArrayC
    if (count8 == 0) {
        *(undefined4 *)(this + 0xa4) = 0; // +0xa4: ptrLargeArrayC
    } else {
        *(int *)(this + 0xa4) = tempVar2;
        tempVar2 = tempVar2 + *(int *)(this + 0x5c);
    }

    // +0xa0: ptrLargeArrayD (always set)
    *(int *)(this + 0xa0) = tempVar2;
    int tempVar3 = tempVar2 + *(int *)(this + 0x30); // +0x30: numLargeArrayD (?), might be extra size

    int count9 = *(int *)(this + 0x4); // +0x4: numLargeArrayE
    if (count9 == 0) {
        *(undefined4 *)(this + 0xac) = 0; // +0xac: ptrLargeArrayE
    } else {
        *(uint *)(this + 0xac) = tempVar3;
        tempVar3 = tempVar3 + *(int *)(this + 0x4);
    }

    int count10 = *(int *)(this + 0x40); // +0x40: numLargeArrayF
    if (count10 == 0) {
        *(undefined4 *)(this + 0xb4) = 0; // +0xb4: ptrLargeArrayF
    } else {
        *(uint *)(this + 0xb4) = tempVar3;
        tempVar3 = tempVar3 + *(int *)(this + 0x40);
    }

    int count11 = *(int *)(this + 0x68); // +0x68: numLargeArrayG
    if (count11 == 0) {
        *(undefined4 *)(this + 0xbc) = 0; // +0xbc: ptrLargeArrayG
    } else {
        *(uint *)(this + 0xbc) = tempVar3;
        tempVar3 = tempVar3 + *(int *)(this + 0x68);
    }

    int count12 = *(int *)(this + 0x6c); // +0x6c: numLargeArrayH
    if (count12 == 0) {
        *(undefined4 *)(this + 0xc0) = 0; // +0xc0: ptrLargeArrayH
    } else {
        *(uint *)(this + 0xc0) = tempVar3;
        tempVar3 = tempVar3 + *(int *)(this + 0x6c);
    }

    int count13 = *(int *)(this + 0x44); // +0x44: numLargeArrayI
    if (count13 == 0) {
        *(undefined4 *)(this + 0xb8) = 0; // +0xb8: ptrLargeArrayI
    } else {
        *(uint *)(this + 0xb8) = tempVar3;
        tempVar3 = tempVar3 + *(int *)(this + 0x44);
    }

    int count14 = *(int *)(this + 0x60); // +0x60: numLargeArrayJ
    if (count14 == 0) {
        *(undefined4 *)(this + 0xc4) = 0; // +0xc4: ptrLargeArrayJ
    } else {
        *(uint *)(this + 0xc4) = tempVar3;
        tempVar3 = tempVar3 + *(int *)(this + 0x60);
    }

    int count15 = *(int *)(this + 100); // 100 = 0x64: numLargeArrayK
    if (count15 == 0) {
        *(undefined4 *)(this + 200) = 0; // 200 = 0xc8: ptrLargeArrayK
    } else {
        *(uint *)(this + 200) = tempVar3;
        tempVar3 = tempVar3 + *(int *)(this + 100);
    }

    // Smaller array with element size 16
    short count16 = *(short *)(this + 0x8e); // +0x8e: numTypeF
    if (count16 == 0) {
        *(undefined4 *)(this + 0xe0) = 0; // +0xe0: ptrTypeF
    } else {
        *(uint *)(this + 0xe0) = tempVar3;
        tempVar3 = tempVar3 + *(short *)(this + 0x8e) * 0x10; // each element 16 bytes
    }

    // Last pointer: null if count17 == 0, else current offset (without advancing)
    short count17 = *(short *)(this + 0x8c); // +0x8c: numTypeG
    *(uint *)(this + 0xe4) = -(uint)(count17 != 0) & tempVar3;
    return;
}