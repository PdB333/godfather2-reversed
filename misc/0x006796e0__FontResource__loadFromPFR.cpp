// FUNC_NAME: FontResource::loadFromPFR
struct ReadContext {
    uint8_t* buffer;       // +0x00
    int currentOffset;     // +0x04
    int pad;               // +0x08
    int size;              // +0x0c
};

// Allocator functions (internal)
int* allocFontResource();
int* allocMem();
void freeMem(int* ptr);
int  getRandomSeed16();
int  mathFixedPoint(int value, int scale);
void processPalette(uint8_t** dataPtr, int flags, short unknown);
void finalizeFont();

int* FontResource::loadFromPFR(ReadContext* ctx, uint8_t* fontData) {
    int versionShort;
    int* fontResource;
    int* piVar3;
    uint8_t* pbVar21;
    uint8_t* pbVar25;
    int iVar14;
    int iVar15;
    int uVar13;
    int uVar17;
    int uVar18;
    int uVar19;
    short sVar20;
    uint8_t bVar5;
    uint8_t bVar6;
    uint8_t* pbVar1;
    uint8_t* pbVar2;
    uint16_t uVar23;
    int* piVar11;
    int local_44;
    int local_48;
    uint16_t local_3c;
    uint32_t local_38;
    uint8_t local_34;
    uint8_t bStack_33;
    uint8_t local_2c[12]; // copied from data
    uint8_t local_20;
    uint8_t local_1f;
    uint8_t local_16;
    uint8_t local_15;
    // ... more locals

    iVar15 = (int)fontData;
    piVar3 = ctx;
    // Allocate font resource structure
    piVar11 = allocFontResource();
    piVar11[0x3e] = 0;
    piVar11[0xc] = 0;
    piVar11[0x48] = 0;
    *piVar11 = someID; // from EAX (likely passed via register)
    *(short*)(piVar11 + 5) = (short)iVar15; // store data pointer as version?
    *(uint8_t*)((int)piVar11 + 0xad) = 0;
    *(uint8_t*)(piVar11 + 0x2b) = 0;
    piVar11[1] = (int)piVar3;

    // Read from current position
    iVar14 = piVar3[3]; // size
    int* puVar12 = (int*)(*piVar3 + iVar14);
    piVar3[1] = iVar14;
    uint32_t magic = *puVar12;
    uint32_t magic2 = puVar12[1];
    uint16_t swapped = *(uint16_t*)(puVar12 + 2);
    local_38 = (uint8_t)magic;
    piVar3[1] = iVar14 + 10;

    // Check for 'PFR' magic
    if (((uint8_t)local_38 != 'P') ||
        ((uint8_t)(magic >> 8) != 'F') ||
        ((uint8_t)(magic >> 16) != 'R'))
        goto cleanup;

    // Read version and other fields
    local_34 = (uint8_t)magic2;
    uint8_t versionDigit = (uint8_t)(magic >> 24);
    *(uint16_t*)((int)piVar11 + 0xa2) = (swapped << 8) | (swapped >> 8);
    bStack_33 = (uint8_t)(magic2 >> 8);
    *(uint16_t*)(piVar11 + 0x29) = (local_34 << 8) | (bStack_33);
    *(uint8_t*)(piVar11 + 2) = versionDigit - 0x30; // version as integer

    // Copy initial data
    piVar3[1] = piVar3[3];
    memcpy(local_2c, (void*)(*piVar3 + piVar3[3]), 0x2b);
    *(uint8_t*)((int)piVar11 + 0x36) = local_2c[2];
    piVar11[0xb] = (local_2c[9] << 16) | (local_2c[8] << 8) | local_2c[7];
    piVar11[0xc] = (local_2c[12] << 16) | (local_2c[11] << 8) | local_2c[10];

    // Read variable-length fields
    iVar14 = (local_20 << 8 | local_1f) + piVar3[3];
    int iVar24 = *piVar3;
    piVar3[1] = iVar14 + 2;
    uint8_t uVar10 = *(uint8_t*)(iVar14 + 1 + iVar24);
    uint8_t uVar4 = *(uint8_t*)(iVar14 + iVar24);
    iVar14 = iVar15 * 5 + 2 + iVar14 + 2;
    piVar3[1] = iVar14;
    local_38 = *(uint16_t*)(iVar14 + iVar24);
    uVar13 = (local_38 & 0xff) | ((local_38 >> 8) << 8) | (*(uint8_t*)(iVar14 + 2 + iVar24) << 16);
    piVar11[4] = (uVar4 << 8) | uVar10;

    // Read 24-bit fields
    iVar14 = piVar3[3] + uVar13;
    piVar3[1] = iVar14;
    uint16_t val16 = *(uint16_t*)(*piVar3 + iVar14);
    uint8_t val8 = *(uint8_t*)((uint16_t*)(*piVar3 + iVar14) + 1);
    local_38 = (uint8_t)val16;
    piVar3[1] = iVar14 + 3;
    piVar11[0x2c] = ((val16 & 0xff) | ((val16 >> 8) << 8) | (val8 << 16)) << 8;

    iVar14 = piVar3[1];
    val16 = *(uint16_t*)(*piVar3 + iVar14);
    val8 = *(uint8_t*)(*piVar3 + iVar14 + 2);
    piVar3[1] = iVar14 + 3;
    piVar11[0x2d] = ((val16 & 0xff) | ((val16 >> 8) << 8) | (val8 << 16)) << 8;

    iVar14 = piVar3[1];
    val16 = *(uint16_t*)(*piVar3 + iVar14);
    val8 = *(uint8_t*)(*piVar3 + iVar14 + 2);
    piVar3[1] = iVar14 + 3;
    piVar11[0x2e] = ((val16 & 0xff) | ((val16 >> 8) << 8) | (val8 << 16)) << 8;

    iVar14 = piVar3[1];
    val16 = *(uint16_t*)(*piVar3 + iVar14);
    val8 = *(uint8_t*)(*piVar3 + iVar14 + 2);
    piVar3[1] = iVar14 + 3;
    iVar15 = ((val16 & 0xff) | ((val16 >> 8) << 8) | (val8 << 16));
    int iVar15Abs = iVar15 * 0x100;
    if (iVar15 < 0) iVar15Abs = -iVar15 * 0x100;
    piVar11[0x2f] = iVar15Abs;

    // Compute min absolute value
    int val2c = piVar11[0x2c];
    int val2d = piVar11[0x2d];
    int abs2c = (val2c < 0) ? -val2c : val2c;
    int abs2d = (val2d < 0) ? -val2d : val2d;
    // (original logic was using param_2 as byte ptr for min)
    // Skipping dead assignment

    // Load random seeds
    iVar14 = getRandomSeed16();
    piVar11[0x2c] = iVar14;
    iVar14 = getRandomSeed16();
    piVar11[0x2d] = iVar14;
    iVar14 = getRandomSeed16();
    piVar11[0x2e] = iVar14;
    iVar14 = getRandomSeed16();
    piVar11[0x2f] = iVar14;

    // Read glyph count flags
    iVar15 = *piVar3;
    iVar14 = piVar3[3] + 0xc + uVar13;
    piVar3[1] = iVar14;
    bVar5 = *(uint8_t*)(iVar14 + iVar15);
    iVar24 = iVar14 + 1;
    piVar3[1] = iVar24;
    if ((bVar5 & 4) == 0) {
        if ((bVar5 & 0x10) == 0) {
            // no count
        } else if ((bVar5 & 0x20) == 0) {
            uVar23 = *(uint8_t*)(iVar24 + iVar15);
            piVar3[1] = iVar14 + 2;
        } else {
            piVar3[1] = iVar14 + 3;
            uVar23 = (*(uint8_t*)(iVar24 + iVar15) << 8) | *(uint8_t*)(iVar14 + 2 + iVar15);
        }
    } else {
        if ((bVar5 & 8) == 0) {
            uVar23 = *(uint8_t*)(iVar24 + iVar15);
            piVar3[1] = iVar14 + 2;
        } else {
            piVar3[1] = iVar14 + 3;
            uVar23 = (*(uint8_t*)(iVar24 + iVar15) << 8) | *(uint8_t*)(iVar14 + 2 + iVar15);
        }
        *(uint16_t*)(piVar11 + 0x28) = uVar23;
    }
    *(uint16_t*)((int)piVar11 + 0xa6) = uVar23;
    *(uint8_t*)(piVar11 + 0x2b) = 0;
    *(uint8_t*)((int)piVar11 + 0xad) = 0;

    // Read glyph data header
    iVar14 = piVar3[1];
    iVar15 = *piVar3;
    piVar3[1] = iVar14 + 2;
    uint8_t c0 = *(uint8_t*)(iVar14 + iVar15);
    uint8_t c1 = *(uint8_t*)(iVar14 + 1 + iVar15);
    uint16_t w = *(uint16_t*)(iVar14 + 2 + iVar15);
    uint8_t c4 = *(uint8_t*)(iVar14 + 4 + iVar15);
    local_38 = (c4 << 24) | (w << 8) | (c1 << 0) | (c0 << 16); // messy
    piVar3[1] = iVar14 + 5;
    if (0xffff < (local_16 << 8 | local_15)) {
        uVar13 += *(uint8_t*)(iVar14 + 5 + iVar15) * 0x10000;
        piVar3[1] = iVar14 + 6;
    }
    iVar14 = ((local_38 & 0xff) | ((local_38 >> 8) & 0xff00) | ((local_38 >> 16) & 0xff)) + piVar3[3];
    piVar3[1] = iVar14;

    if (uVar13 == 0) {
        pbVar21 = nullptr;
    } else {
        pbVar21 = (uint8_t*)(iVar15 + iVar14);
        piVar3[1] = iVar14 + uVar13;
    }

    // Read glyph metrics (big-endian)
    *(uint16_t*)((int)piVar11 + 0x16) = (pbVar21[0] << 8) | pbVar21[1];
    *(uint16_t*)(piVar11 + 6) = (pbVar21[2] << 8) | pbVar21[3];
    *(uint16_t*)((int)piVar11 + 0x1a) = (pbVar21[4] << 8) | pbVar21[5];

    // Determine if compressed (version < 2 or width > 0xff)
    if (*(uint8_t*)(piVar11 + 2) >= 2 && *(uint16_t*)(piVar11 + 6) <= 0xff) {
        *(uint8_t*)((int)piVar11 + 0x35) = 1;
    } else {
        *(uint8_t*)((int)piVar11 + 0x35) = 0;
    }

    // Allocate and initialize other buffers
    iVar14 = getRandomSeed16();
    piVar11[10] = iVar14;
    piVar11[0x32] = iVar14;
    piVar11[0x33] = 0;
    piVar11[0x34] = 0;
    piVar11[0x35] = iVar14;
    piVar11[0x36] = 0;
    piVar11[0x37] = 0;
    FUN_0067bbb0(); // unknown initialization
    piVar11[0x43] = *(uint16_t*)((int)piVar11 + 0x1a);

    // More big-endian reads
    *(uint16_t*)(piVar11 + 0x26) = (pbVar21[6] << 8) | pbVar21[7];
    *(uint16_t*)((int)piVar11 + 0x9a) = (pbVar21[8] << 8) | pbVar21[9];
    *(uint16_t*)(piVar11 + 0x27) = (pbVar21[10] << 8) | pbVar21[11];
    *(uint16_t*)((int)piVar11 + 0x9e) = (pbVar21[12] << 8) | pbVar21[13];

    bVar5 = pbVar21[14];
    pbVar25 = pbVar21 + 15;
    local_38 = (bVar5 << 24) | ((uint32_t)local_38 & 0xffffff); // mask
    *(uint8_t*)(piVar11 + 7) = bVar5 & 1; // flags

    if ((bVar5 & 4) == 0) {
        bVar6 = *pbVar25;
        pbVar25 = pbVar21 + 17;
        sVar20 = (bVar6 << 8) | pbVar21[16];
    }

    piVar11[0x4a] = 0;
    *(uint16_t*)(piVar11 + 0xe) = 0;

    // Parse glyph entries if flag is set
    if ((int8_t)bVar5 < 0) {
        bVar5 = *pbVar25;
        pbVar25 += 1;
        for (uVar13 = bVar5; uVar13 != 0; uVar13--) {
            bVar5 = *pbVar25;
            pbVar21 = pbVar25 + 2;
            if (pbVar25[1] == 2) {
                // Allocate kerning table
                iVar14 = 0;
                bVar6 = *pbVar21;
                while (bVar6 != 0) {
                    iVar14++;
                    bVar6 = pbVar21[iVar14];
                }
                int iVar15 = allocMem();
                piVar11[0x3e] = iVar15;
                if (iVar15 != 0) {
                    FUN_00675f60(iVar14 + 1); // alloc size
                }
            } else if (pbVar25[1] == 3) {
                // Read vertical/horizontal glyph offset arrays
                bVar6 = *pbVar21;
                uVar17 = bVar6 >> 4;
                pbVar25 = pbVar25 + 3;
                piVar11[0x5f] = uVar17;
                piVar11[0x60] = bVar6 & 0xf;
                if (uVar17 != 0) {
                    int idx = 0;
                    do {
                        bVar6 = *pbVar25;
                        pbVar1 = pbVar25 + 1;
                        pbVar25 = pbVar25 + 2;
                        piVar11[idx + 0x6d] = (bVar6 << 8) | *pbVar1;
                        int temp = piVar11[0x3a];
                        int sign = (temp < 0) ? -1 : 1;
                        if (temp < 0) temp = -temp;
                        int fixed = mathFixedPoint(0, 0); // simplified
                        piVar11[idx + 0x6d] = (fixed + (temp >> 16) * sign + piVar11[0x3c]) >> 16;
                        idx++;
                    } while (idx < piVar11[0x5f]);
                }
                if (0 < piVar11[0x60]) {
                    int idx = 0;
                    pbVar25 = pbVar25 - 1;
                    do {
                        pbVar1 = pbVar25 + 1;
                        pbVar2 = pbVar25 + 2;
                        pbVar25 = pbVar25 + 2;
                        piVar11[idx + 0x61] = (*pbVar1 << 8) | *pbVar2;
                        int temp = piVar11[0x39];
                        int sign = (temp < 0) ? -1 : 1;
                        if (temp < 0) temp = -temp;
                        int fixed = mathFixedPoint(0, 0);
                        piVar11[idx + 0x61] = (fixed + (temp >> 16) * sign + piVar11[0x3d]) >> 16;
                        idx++;
                    } while (idx < piVar11[0x60]);
                }
            }
            local_3c = (uint16_t)bVar5;
            pbVar25 = pbVar21 + (int16_t)local_3c;
        }
    }

    // Read glyph pixel data
    uVar13 = (pbVar25[0] << 16) | (pbVar25[1] << 8) | pbVar25[2];
    piVar11[9] = uVar13;
    if (uVar13 == 0) {
        piVar11[8] = 0;
    } else {
        uint8_t* pixelData = allocMem();
        piVar11[8] = (int)pixelData;
        if (0 < uVar13) {
            int offset = 3 - (int)pixelData;
            do {
                *pixelData = pixelData[offset];
                pixelData++;
                uVar13--;
            } while (uVar13 != 0);
        }
    }

    // Read more arrays of offsets
    local_48 = (int16_t)(uint16_t)pbVar25[piVar11[9] + 3];
    pbVar21 = pbVar25 + piVar11[9] + 4;
    piVar11[0x59] = local_48;
    if (local_48 != 0) {
        uint32_t* puVar22 = (uint32_t*)(piVar11 + 0x4b);
        do {
            bVar5 = *pbVar21;
            pbVar25 = pbVar21 + 1;
            pbVar21 = pbVar21 + 2;
            uVar17 = (bVar5 << 8) | *pbVar25;
            *puVar22 = uVar17;
            uVar18 = uVar17 << 16;
            int tempA = piVar11[0x39];
            int signA = (tempA < 0) ? -1 : 1;
            if (tempA < 0) tempA = -tempA;
            int tempB = piVar11[0x3b];
            int signB = (tempB < 0) ? -1 : 1;
            if (tempB < 0) tempB = -tempB;
            // Fixed-point arithmetic
            *puVar22 = ((uVar18 >> 16) * (tempB & 0xffff) + (uVar18 >> 16) * (tempB >> 16) * 0x10000) * signB +
                        piVar11[0x3d] + (tempA >> 16) * signA;
            *puVar22 >>= 16;
            puVar22++;
            local_48--;
        } while (local_48 != 0);
    }

    // Additional fixed-point adjustments
    uVar17 = *pbVar21;
    int tempA = piVar11[0x39];
    piVar11[0x5a] = uVar17;
    uVar18 = uVar17 << 16;
    int signA = (tempA < 0) ? -1 : 1;
    if (tempA < 0) tempA = -tempA;
    int tempB = piVar11[0x3b];
    int signB = (tempB < 0) ? -1 : 1;
    if (tempB < 0) tempB = -tempB;
    piVar11[0x5a] = ((uVar18 >> 16) * (tempB & 0xffff) + (uVar18 >> 16) * (tempB >> 16) * 0x10000) * signB +
                     (tempA >> 16) * signA + piVar11[0x3d];
    piVar11[0x5a] >>= 16;

    uVar18 = pbVar21[1];
    tempA = piVar11[0x39];
    piVar11[0x5b] = uVar18;
    uVar13 = uVar18 << 16;
    signA = (tempA < 0) ? -1 : 1;
    if (tempA < 0) tempA = -tempA;
    tempB = piVar11[0x3b];
    signB = (tempB < 0) ? -1 : 1;
    if (tempB < 0) tempB = -tempB;
    piVar11[0x5c] = (*(uint16_t*)(piVar11 + 6) * 0x1cb + 0x8000) >> 16;
    piVar11[0x5b] = ((uVar13 >> 16) * (tempB >> 16) * 0x10000 + (uVar13 >> 16) * (tempB & 0xffff)) * signB +
                     (tempA >> 16) * signA + piVar11[0x3d];
    piVar11[0x5b] >>= 16;

    iVar14 = (pbVar21[2] << 8) | pbVar21[3];
    tempA = piVar11[0x38];
    piVar11[0x5d] = iVar14;
    uVar17 = iVar14 << 16;
    signA = (tempA < 0) ? -1 : 1;
    if (tempA < 0) tempA = -tempA;
    int tempC = piVar11[0x3a];
    int signC = (tempC < 0) ? -1 : 1;
    if (tempC < 0) tempC = -tempC;
    piVar11[0x5d] = ((uVar17 >> 16) * (tempA >> 16) * 0x10000 + (uVar17 >> 16) * (tempA & 0xffff)) * signA +
                     piVar11[0x3c] + (tempC >> 16) * signC;
    piVar11[0x5d] >>= 16;

    uVar17 = (pbVar21[4] << 8) | pbVar21[5];
    tempA = piVar11[0x39];
    piVar11[0x5e] = uVar17;
    uVar18 = uVar17 << 16;
    signA = (tempA < 0) ? -1 : 1;
    if (tempA < 0) tempA = -tempA;
    tempB = piVar11[0x3b];
    signB = (tempB < 0) ? -1 : 1;
    if (tempB < 0) tempB = -tempB;
    int iTemp = ((uVar18 >> 16) * (tempB >> 16) * 0x10000 + (uVar18 >> 16) * (tempB & 0xffff)) * signB;
    pbVar25 = pbVar21 + 8;
    piVar11[0x5e] = (iTemp + piVar11[0x3d] + (tempA >> 16) * signA) >> 16;
    *(uint16_t*)(piVar11 + 0x42) = (pbVar21[6] << 8) | pbVar21[7];

    processPalette(&pbVar25, local_38, sVar20);

    // Process glyph rectangles
    local_48 = 0;
    if ((int16_t)piVar11[0xe] != 0) {
        uint8_t* base = nullptr;
        do {
            local_44 = 0;
            if (0 < *(int*)(base + piVar11[0xf] + 4)) {
                iVar14 = 0;
                do {
                    uint8_t* pbVar21 = base + piVar11[0xf] + 8;
                    int* param_1 = nullptr;
                    uint32_t randomVal = FUN_0067bb50(&param_1); // get random
                    piVar11[0x7b] = randomVal & 0xff;
                    *(uint16_t*)(*(int*)pbVar21 + iVar14) = (uint16_t)param_1;
                    local_44++;
                    iVar14 += 0xc;
                } while (local_44 < *(int*)(base + piVar11[0xf] + 4));
            }
            base += 0xc;
            local_48++;
        } while (local_48 < (int)(uint16_t)*(uint16_t*)(piVar11 + 0xe));
    }

    finalizeFont();

    // Free temporary pixel data if allocated
    iVar14 = piVar11[8];
    iVar15 = *piVar11;
    if (iVar14 != 0) {
        *(int*)(*(int*)(iVar15 + 0xc) + *(int*)(iVar14 - 8) * 4) = 0;
        int* ctxPtr = (int*)(iVar15 + 4);
        *ctxPtr = *ctxPtr - 1;
        freeMem((int*)(iVar14 - 0x10));
    }

cleanup:
    *(uint8_t*)((int)piVar11 + 0xad) = 1;
    return piVar11;
}