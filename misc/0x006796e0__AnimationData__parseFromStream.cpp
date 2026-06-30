// FUNC_NAME: AnimationData::parseFromStream
int* __thiscall AnimationData::parseFromStream(int* stream, byte* dataLen) {
    // param_1: stream structure with fields: buffer (offset 0), pos (offset 4), size (offset 12)
    // param_2: length of the data in bytes? Used as version or count.
    // Returns a newly allocated AnimationData (through internal allocator)
    byte* pbVar1;
    byte* pbVar2;
    int* piVar3;
    byte bVar5, bVar6;
    ushort uVar23;
    int iVar14, iVar15, iVar24;
    undefined *puVar16;
    uint *puVar22;
    short sVar20 = 0;
    byte local_34;
    byte bStack_33;
    byte local_20, local_1f, local_16, local_15;
    undefined local_c, local_b, local_a, local_9, local_8, local_7, local_3, local_2;
    undefined1 local_2c[12]; // Actually 43 bytes? but declared as 12 short?
    int local_48, local_44;
    ushort local_3c;
    undefined4 local_38;

    int dataLength = (int)dataLen;
    piVar3 = stream;
    // Allocate result structure
    int* result = (int*)FUN_00673070(); // allocation wrapper
    result[0x3e] = 0;   // offset 0xF8
    result[0xc] = 0;    // offset 0x30
    result[0x48] = 0;   // offset 0x120
    *result = in_EAX;   // this pointer? Actually the vtable or self
    *(short*)(result + 5) = (short)dataLength; // offset 0x14 (result+5 = 20 bytes) - store length
    *(byte*)((int)result + 0xad) = 0; // offset 0xAD
    *(byte*)(result + 0x2b) = 0;      // offset 0xAC? Actually result+0x2b = offset 0xAC
    result[1] = (int)piVar3; // store stream pointer

    iVar14 = piVar3[3]; // stream->size or end offset
    undefined4* header = (undefined4*)(*piVar3 + iVar14); // stream->buffer + stream->pos
    piVar3[1] = iVar14; // stream->pos = iVar14 (actually it was already set?)
    // Actually the stream advances: piVar3[1] = iVar14 + 10; after reading
    uVar8 = *header;
    uVar9 = header[1];
    uVar23 = *(ushort*)(header + 2);
    local_38._0_1_ = (char)uVar8;
    piVar3[1] = iVar14 + 10;

    // Check magic "PFR" with version
    if (local_38._0_1_ != 'P' || 
        (local_38._1_1_ = (char)((uint)uVar8 >> 8), local_38._1_1_ != 'F') || 
        (local_38._2_1_ = (char)((uint)uVar8 >> 0x10), local_38._2_1_ != 'R'))
        goto LAB_0067a3eb;

    local_34 = (byte)uVar9;
    local_38._3_1_ = (char)((uint)uVar8 >> 0x18);
    *(ushort*)((int)result + 0xa2) = (uVar23 << 8) + (uVar23 >> 8); // big-endian swap? Actually multiply and shift - simplified: byte-swap
    bStack_33 = (byte)((uint)uVar9 >> 8);
    *(ushort*)(result + 0x29) = (local_34 << 8) + bStack_33; // offset 0xA4? Actually result+0x29 = 0xA4
    *(char*)(result + 2) = local_38._3_1_ - '0'; // convert version ASCII to integer

    piVar3[1] = piVar3[3]; // reset pos? Actually just read advance
    _memcpy(local_2c, (void*)(*piVar3 + piVar3[3]), 0x2b); // copy 43 bytes of header info
    *(byte*)((int)result + 0x36) = local_2; // offset 0x36
    result[0xb] = CONCAT21(CONCAT11(local_9, local_8), local_7); // some bytes
    result[0xc] = CONCAT21(CONCAT11(local_c, local_b), local_a); // offset 0x30? Actually result[0xc] = offset 0x30

    iVar14 = (local_20 << 8) + local_1f + piVar3[3]; // read two bytes and add current pos
    iVar24 = *piVar3;
    piVar3[1] = iVar14 + 2;
    undefined byte0 = *(byte*)(iVar14 + iVar24);
    undefined byte1 = *(byte*)(iVar14 + 1 + iVar24);
    iVar14 = dataLength * 5 + 2 + iVar14 + 2;
    piVar3[1] = iVar14;
    local_38._0_1_ = (char)*(short*)(iVar14 + iVar24);
    local_38._1_1_ = (char)(*(short*)(iVar14 + iVar24) >> 8);
    uint someVal = CONCAT21(CONCAT11((char)local_38, local_38._1_1_), *(byte*)(iVar14 + 2 + iVar24));
    result[4] = (byte0 << 8) + byte1; // offset 0x10

    iVar14 = piVar3[3] + someVal;
    piVar3[1] = iVar14;
    // Read three 24-bit values (stored as 24-bit signed? Actually stored as 3 bytes, sign-extended)
    uVar7 = *(short*)(*piVar3 + iVar14);
    uVar10 = *(byte*)(*piVar3 + iVar14 + 2);
    local_38._0_1_ = (char)uVar7;
    piVar3[1] = iVar14 + 3;
    local_38._1_1_ = (char)(uVar7 >> 8);
    result[0x2c] = (CONCAT21(CONCAT11((char)local_38, local_38._1_1_), uVar10)) << 8; // sign-extend? Actually left shift 8

    // Repeat for next three
    iVar14 = piVar3[1];
    uVar7 = *(short*)(*piVar3 + iVar14);
    uVar10 = *(byte*)(*piVar3 + iVar14 + 2);
    piVar3[1] = iVar14 + 3;
    result[0x2d] = (int)(CONCAT21(CONCAT11((char)uVar7, (char)(uVar7>>8)), uVar10)) << 8;

    iVar14 = piVar3[1];
    uVar7 = *(short*)(*piVar3 + iVar14);
    uVar10 = *(byte*)(*piVar3 + iVar14 + 2);
    piVar3[1] = iVar14 + 3;
    result[0x2e] = (int)(CONCAT21(CONCAT11((char)uVar7, (char)(uVar7>>8)), uVar10)) << 8;

    iVar14 = piVar3[1];
    uVar7 = *(short*)(*piVar3 + iVar14);
    uVar10 = *(byte*)(*piVar3 + iVar14 + 2);
    piVar3[1] = iVar14 + 3;
    int val = (int)CONCAT21(CONCAT11((char)uVar7, (char)(uVar7>>8)), uVar10);
    result[0x2f] = val * 0x100;
    if (val < 0) result[0x2f] = val * -0x100; // sign fix

    // Compute absolute values for clamping
    int abs1 = result[0x2c];
    if (abs1 < 0) abs1 = -abs1;
    int abs2 = result[0x2d];
    if (abs2 < 0) abs2 = -abs2;
    if (abs2 < abs1) {
        dataLen = (byte*)(abs1);
        if (result[0x2c] < 0) dataLen = (byte*)-abs1;
    } else {
        dataLen = (byte*)abs2;
        if (result[0x2d] < 0) dataLen = (byte*)-abs2;
    }

    // Replace with random-ish values from FUN_00676090
    result[0x2c] = FUN_00676090();
    result[0x2d] = FUN_00676090();
    result[0x2e] = FUN_00676090();
    result[0x2f] = FUN_00676090();

    iVar15 = *piVar3;
    iVar14 = piVar3[3] + 0xc + someVal;
    piVar3[1] = iVar14;
    bVar5 = *(byte*)(iVar14 + iVar15);
    iVar24 = iVar14 + 1;
    piVar3[1] = iVar24;
    if ((bVar5 & 4) == 0) {
        if ((bVar5 & 0x10) != 0) {
            if ((bVar5 & 0x20) == 0) {
                uVar23 = (ushort)*(byte*)(iVar24 + iVar15);
                piVar3[1] = iVar14 + 2;
            } else {
                piVar3[1] = iVar14 + 3;
                uVar23 = CONCAT11(*(byte*)(iVar24 + iVar15), *(byte*)(iVar14 + 2 + iVar15));
            }
        }
    } else {
        if ((bVar5 & 8) == 0) {
            uVar23 = (ushort)*(byte*)(iVar24 + iVar15);
            piVar3[1] = iVar14 + 2;
        } else {
            piVar3[1] = iVar14 + 3;
            uVar23 = CONCAT11(*(byte*)(iVar24 + iVar15), *(byte*)(iVar14 + 2 + iVar15));
        }
        *(ushort*)(result + 0x28) = uVar23; // offset 0xA0? Actually result+0x28 = 0xA0
    LAB_00679a9a:
        uVar23 = (ushort)param_1; // param_1 is int*? confused.
    }
    *(ushort*)((int)result + 0xa6) = uVar23; // offset 0xA6
    *(byte*)(result + 0x2b) = 0; // offset 0xAC
    *(byte*)((int)result + 0xad) = 0; // offset 0xAD

    iVar14 = piVar3[1];
    iVar15 = *piVar3;
    piVar3[1] = iVar14 + 2;
    uVar10 = *(byte*)(iVar14 + 4 + iVar15);
    uint length = CONCAT11(*(byte*)(iVar14 + iVar15), *(byte*)(iVar14 + 1 + iVar15));
    uVar7 = *(short*)(iVar14 + 2 + iVar15);
    local_38 = CONCAT22(CONCAT11(local_38._3_1_, uVar10), uVar7);
    piVar3[1] = iVar14 + 5;
    if (CONCAT12(local_3, (local_16 << 8) + local_15) > 0xFFFF) {
        length += (uint)*(byte*)(iVar14 + 5 + iVar15) * 0x10000;
        piVar3[1] = iVar14 + 6;
    }
    iVar14 = (int)CONCAT21(CONCAT11((char)local_38, (char)(uVar7>>8)), uVar10) + piVar3[3];
    piVar3[1] = iVar14;
    byte* dataPtr;
    if (length == 0)
        dataPtr = 0;
    else {
        dataPtr = (byte*)(iVar15 + iVar14);
        piVar3[1] = iVar14 + length;
    }
    // Read 16-bit big-endian fields from dataPtr
    *(ushort*)((int)result + 0x16) = (dataPtr[0] << 8) + dataPtr[1]; // offset 0x16
    *(ushort*)(result + 6) = (dataPtr[2] << 8) + dataPtr[3];         // offset 0x18? Actually result+6 = 0x18
    *(ushort*)((int)result + 0x1a) = (dataPtr[4] << 8) + dataPtr[5]; // offset 0x1A

    // Determine a flag based on version and frame count
    if (*(char*)(result + 2) < 2 || *(ushort*)(result + 6) > 0xFF)
        *(byte*)((int)result + 0x35) = 0;
    else
        *(byte*)((int)result + 0x35) = 1;

    // Initialize more fields
    int val2 = FUN_00676090();
    result[10] = val2;   // offset 0x28? Actually result[10] = 0x28
    result[0x32] = val2; // offset 0xC8
    result[0x33] = 0;
    result[0x34] = 0;
    result[0x35] = val2;
    result[0x36] = 0;
    result[0x37] = 0;
    FUN_0067bbb0(); // some initialization
    result[0x43] = (uint)*(ushort*)((int)result + 0x1a); // offset 0x10C
    *(ushort*)(result + 0x26) = (dataPtr[6] << 8) + dataPtr[7]; // offset 0x98
    *(ushort*)((int)result + 0x9a) = (dataPtr[8] << 8) + dataPtr[9]; // offset 0x9A
    *(ushort*)(result + 0x27) = (dataPtr[10] << 8) + dataPtr[11]; // offset 0x9C
    *(ushort*)((int)result + 0x9e) = (dataPtr[12] << 8) + dataPtr[13]; // offset 0x9E
    bVar5 = dataPtr[14];
    byte* currentPtr = dataPtr + 15;
    // Set flag from bit0
    *(byte*)(result + 7) = bVar5 & 1;
    if ((bVar5 & 4) == 0) {
        bVar6 = *currentPtr;
        currentPtr = dataPtr + 17;
        sVar20 = (bVar6 << 8) + dataPtr[16];
    }
    result[0x4a] = 0;  // offset 0x128
    *(short*)(result + 0xe) = 0; // offset 0x38? Actually result+0xe = 0x38

    // Loop for packed data (bones? joints?)
    if (bVar5 < 0) {
        bVar5 = *currentPtr;
        currentPtr++;
        for (uint count = (uint)bVar5; count != 0; count--) {
            bVar5 = *currentPtr;
            byte* nextPtr = currentPtr + 2;
            if (currentPtr[1] == 2) {
                // Type 2: allocate string
                int len = 0;
                bVar6 = *nextPtr;
                while (bVar6 != 0) { len++; bVar6 = nextPtr[len]; }
                int* alloc = (int*)FUN_00673070();
                result[0x3e] = (int)alloc;
                if (alloc != 0)
                    FUN_00675f60(len + 1); // copy string
            } else if (currentPtr[1] == 3) {
                // Type 3: read quaternion? values
                bVar6 = *nextPtr;
                uint countX = bVar6 >> 4;
                uint countY = bVar6 & 0xF;
                currentPtr = currentPtr + 3;
                result[0x5f] = countX;
                result[0x60] = countY;
                if (countX != 0) {
                    for (int i = 0; i < (int)countX; i++) {
                        bVar6 = *currentPtr;
                        byte* bPtr1 = currentPtr + 1;
                        currentPtr += 2;
                        result[i + 0x6d] = (uint)CONCAT11(bVar6, *bPtr1);
                        // Fixed-point adjustment
                        uint temp = result[0x3a];
                        int mult = 1;
                        if ((int)temp < 0) { mult = -1; temp = -temp; }
                        int randVal = FUN_00676010();
                        result[i + 0x6d] = (randVal + (temp >> 16) * mult + result[0x3c]) >> 16;
                    }
                }
                if (0 < (int)countY) {
                    currentPtr--;
                    for (int i = 0; i < (int)countY; i++) {
                        byte* bPtr1 = currentPtr + 1;
                        byte* bPtr2 = currentPtr + 2;
                        currentPtr += 2;
                        result[i + 0x61] = (uint)CONCAT11(*bPtr1, *bPtr2);
                        uint temp = result[0x39];
                        int mult = 1;
                        if ((int)temp < 0) { mult = -1; temp = -temp; }
                        int randVal = FUN_00676010();
                        result[i + 0x61] = (randVal + (temp >> 16) * mult + result[0x3d]) >> 16;
                    }
                }
            }
            local_3c = (ushort)bVar5;
            currentPtr = nextPtr + local_3c; // advance by size field
        }
    }

    // Read data block
    uint blockSize = CONCAT21(CONCAT11(*currentPtr, currentPtr[1]), currentPtr[2]);
    result[9] = blockSize; // offset 0x24? Actually result[9] = 0x24
    if (blockSize == 0) {
        result[8] = 0;
    } else {
        byte* mem = (byte*)FUN_00673070();
        int size = result[9];
        result[8] = (int)mem;
        if (0 < size) {
            int offset = 3 - (int)mem;
            do {
                *mem = mem[(int)(currentPtr + offset)];
                mem++;
                size--;
            } while (size != 0);
        }
    }

    // Read more counts
    local_48 = (short)(ushort)currentPtr[result[9] + 3];
    currentPtr += result[9] + 4;
    result[0x59] = local_48; // offset 0x164
    if (local_48 != 0) {
        uint* dest = (uint*)(result + 0x4b); // offset 0x12C
        do {
            bVar5 = *currentPtr;
            byte* next = currentPtr + 1;
            currentPtr += 2;
            uint val = CONCAT11(bVar5, *next);
            *dest = val;
            uint temp = result[0x39];
            int mult1 = 1;
            if ((int)temp < 0) { mult1 = -1; temp = -temp; }
            uint temp2 = result[0x3b];
            uint signedVal = val * 0x10000;
            int mult2 = 1;
            if ((int)signedVal < 0) {
                signedVal = val * -0x10000;
                mult2 = -1;
                if ((int)temp2 < 0) { mult2 = 1; temp2 = -temp2; }
            } else {
                mult2 = 1;
                if ((int)temp2 < 0) { mult2 = -1; temp2 = -temp2; }
            }
            *dest = (((signedVal >> 16) * (temp2 & 0xFFFF) + (signedVal >> 16) * (temp2 >> 16) * 0x10000) * mult2 + result[0x3d] + (temp >> 16) * mult1) >> 16;
            dest++;
            local_48--;
        } while (local_48 != 0);
    }

    // Read more individual values
    uint uVar17 = (uint)*currentPtr;
    uint uVar13 = result[0x39];
    result[0x5a] = uVar17; // offset 0x168
    // Similar fixed-point adjustment
    uint uVar18 = uVar17 * 0x10000;
    int iVar14 = 1;
    if ((int)uVar13 < 0) { iVar14 = -1; uVar13 = -uVar13; }
    uint uVar19 = result[0x3b];
    if ((int)uVar18 < 0) {
        uVar18 = uVar17 * -0x10000;
        dataLen = (byte*)0xFFFFFFFF;
        if ((int)uVar19 < 0) { dataLen = (byte*)0x1; uVar19 = -uVar19; }
    } else {
        dataLen = (byte*)0x1;
        if ((int)uVar19 < 0) { dataLen = (byte*)0xFFFFFFFF; uVar19 = -uVar19; }
    }
    result[0x5a] = (((uVar18 >> 16) * (uVar19 & 0xFFFF) + (uVar18 >> 16) * (uVar19 >> 16) * 0x10000) * (int)dataLen + (uVar13 >> 16) * iVar14 + result[0x3d]) >> 16;

    // Second value
    uVar18 = (uint)currentPtr[1];
    uVar13 = uVar18 * 0x10000;
    result[0x5b] = uVar18;
    iVar14 = 1;
    if ((int)uVar17 < 0) { iVar14 = -1; uVar17 = -uVar17; }
    uVar19 = result[0x3b];
    if ((int)uVar13 < 0) {
        uVar13 = uVar18 * -0x10000;
        dataLen = (byte*)0xFFFFFFFF;
        if ((int)uVar19 < 0) { dataLen = (byte*)0x1; uVar19 = -uVar19; }
    } else {
        dataLen = (byte*)0x1;
        if ((int)uVar19 < 0) { dataLen = (byte*)0xFFFFFFFF; uVar19 = -uVar19; }
    }
    result[0x5c] = (*(ushort*)(result + 6) * 0x1CB + 0x8000) >> 16;
    result[0x5b] = (((uVar13 >> 16) * (uVar19 >> 16) * 0x10000 + (uVar13 >> 16) * (uVar19 & 0xFFFF)) * (int)dataLen + (uVar17 >> 16) * iVar14 + result[0x3d]) >> 16;

    // Third value (16-bit)
    iVar14 = (uint)currentPtr[2] * 0x100 + (uint)currentPtr[3];
    uVar13 = result[0x38];
    result[0x5d] = iVar14;
    uVar17 = iVar14 * 0x10000;
    if ((int)uVar17 < 0) {
        uVar17 = iVar14 * -0x10000;
        dataLen = (byte*)0xFFFFFFFF;
        if ((int)uVar13 < 0) { dataLen = (byte*)0x1; uVar13 = -uVar13; }
    } else {
        dataLen = (byte*)0x1;
        if ((int)uVar13 < 0) { dataLen = (byte*)0xFFFFFFFF; uVar13 = -uVar13; }
    }
    uVar18 = result[0x3a];
    iVar14 = 1;
    if ((int)uVar18 < 0) { iVar14 = -1; uVar18 = -uVar18; }
    result[0x5d] = ((uVar18 >> 16) * iVar14 + result[0x3c] + ((uVar17 >> 16) * (uVar13 >> 16) * 0x10000 + (uVar17 >> 16) * (uVar13 & 0xFFFF)) * (int)dataLen) >> 16;

    // Fourth value (16-bit)
    uVar13 = result[0x39];
    uVar17 = CONCAT11(currentPtr[4], currentPtr[5]);
    result[0x5e] = uVar17;
    uVar18 = uVar17 * 0x10000;
    iVar14 = 1;
    if ((int)uVar13 < 0) { iVar14 = -1; uVar13 = -uVar13; }
    uVar19 = result[0x3b];
    if ((int)uVar18 < 0) {
        uVar18 = uVar17 * -0x10000;
        dataLen = (byte*)0xFFFFFFFF;
        if ((int)uVar19 < 0) { dataLen = (byte*)0x1; uVar19 = -uVar19; }
    } else {
        dataLen = (byte*)0x1;
        if ((int)uVar19 < 0) { dataLen = (byte*)0xFFFFFFFF; uVar19 = -uVar19; }
    }
    int iVar15 = ((uVar18 >> 16) * (uVar19 >> 16) * 0x10000 + (uVar18 >> 16) * (uVar19 & 0xFFFF)) * (int)dataLen;
    currentPtr += 8;
    result[0x5e] = (iVar15 + result[0x3d] + (uVar13 >> 16) * iVar14) >> 16;

    // Read two more bytes
    *(ushort*)(result + 0x42) = (currentPtr[-2] << 8) + currentPtr[-1];

    // Call another parser
    FUN_0067a530(&currentPtr, local_38, sVar20);

    // Process array of structures
    local_48 = 0;
    if (*(short*)(result + 0xe) != 0) {
        for (int i = 0; i < (int)(uint)*(ushort*)(result + 0xe); i++) {
            local_44 = 0;
            if (0 < *(int*)((byte*)i * 12 + result[0xf] + 4)) {
                int base = (byte*)i * 12 + result[0xf] + 8;
                for (int j = 0; j < *(int*)((byte*)i * 12 + result[0xf] + 4); j++) {
                    int dummy = 0;
                    uint val = FUN_0067bb50(&dummy);
                    result[0x7b] = val & 0xFF;
                    *(short*)(*(int*)base + j * 12) = (short)dummy;
                    local_44++;
                }
            }
        }
    }

    FUN_0067a920();

    // Cleanup if needed
    int ptr8 = result[8];
    int self = *result;
    if (ptr8 != 0) {
        *(undefined4*)(*(int*)(self + 0xc) + *(int*)(ptr8 - 8) * 4) = 0;
        piVar3 = (int*)(self + 4);
        (*piVar3)--;
        // Deallocate memory
        (*DAT_01206694)(ptr8 - 0x10);
    }

LAB_0067a3eb:
    *(byte*)((int)result + 0xad) = 1;
    return result;
}