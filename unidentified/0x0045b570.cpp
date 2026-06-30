// FUN_0045b570: Entity::duplicate
// Reconstructed C++ function for duplicating an entity with optional override parameters and memory alignment.
// Address: 0x0045b570

#define ALIGN128(x) (((x) + 0x7F) & ~0x7F)

Entity* __thiscall Entity::duplicate(Entity* this, int* overrideParam, uint overrideCount, undefined4 param4)
{
    // Compute sizing from source entity
    uint countA = *(ushort*)(this + 0x3C); // +0x3C: count of type A entries
    int totalSizeA = 0;
    if (countA != 0) {
        int* p = (int*)(this->arrayA + 4); // +0x68: arrayA base, each entry 0x10 bytes
        for (uint i = 0; i < countA; i++) {
            if (p[7] & 1) {                 // +0x1C? Actually p[7] is offset 0x1C? Wait: p is int* from arrayA+4, each entry offset 4 bytes
                totalSizeA += ALIGN128(p[0] * 0x14) * 2; // align(p[0]*20) * 2
            }
            p += 4; // next entry (0x10 bytes)
        }
    }

    uint countB = *(ushort*)(this + 0x3E); // +0x3E: count of type B entries
    int totalSizeB = 0;
    if (countB != 0) {
        int* p = (int*)this->arrayB; // +0x6C: arrayB base
        for (uint i = 0; i < countB; i++) {
            if (*(char*)(p + 0xB) == 1) { // +0x2C? Actually p is int* so p+0xB = offset 0x2C? Use byte offset
                totalSizeB += ALIGN128(p[0]) * 2; // align(p[0]) * 2
            }
            p += 4;
        }
    }

    int mainCount = this->mainCount; // +0x34: number of main entries
    int overrideCountLocal = 0;
    int countOverrides = 0;
    if (mainCount != 0) {
        char* entry = (char*)(this->mainArray + 6); // +0x50: mainArray base, each 0xB0 bytes, offset 6 for some flag
        for (int i = 0; i < mainCount; i++) {
            if (entry[-2] == 1) {          // +0x4? Actually entry points to +6, so -2 = +4
                overrideCountLocal++;
                if (*entry == 0) {          // +6 flag
                    countOverrides++;
                }
            }
            entry += 0xB0; // next entry
        }
    }

    ushort countC = *(ushort*)(this + 0x44); // +0x44: count of type C
    size_t mainArrayBytes = mainCount * 0xB0;
    int mainArrayBytesAligned = mainCount * 0x80; // 0x80? = 128, but used for alignment? Actually 0x80 is 128, maybe for something else

    // Compute size for override block
    int overrideBlockSize = 0;
    if (overrideCountLocal != 0) {
        overrideBlockSize = mainCount << 5; // mainCount * 32
    }

    // Compute total allocation size with 128-byte alignment for each block
    int totalSize = ALIGN128(mainArrayBytes)
                    + (ALIGN128(overrideBlockSize) + ALIGN128(countOverrides * 0x40)) * 2
                    + totalSizeB
                    + totalSizeA
                    + mainArrayBytesAligned
                    + ALIGN128((uint)countC * 0x50)
                    + ALIGN128(*(ushort*)(this + 0x46) * 0x68); // +0x46: another count

    // Allocate memory via EARS allocator
    undefined4* newObj = (undefined4*) ((code**)(*DAT_01205870))(totalSize, &DAT_0110b8f0);

    // Copy first 0xC0 bytes from source to new object
    undefined4* dst = newObj;
    undefined4* src = this;
    for (int i = 0; i < 0x30; i++) {
        *dst++ = *src++;
    }

    // Set flags and clear counters
    newObj[9] |= 1;              // +0x24: some flag
    newObj[0x1D] = 0;           // +0x74
    *(char*)(newObj + 0x2D) = 0; // +0xB4? Actually char offset 0xB4
    newObj[0xC] = 0;            // +0x30
    *(char*)(newObj + 0x2E) = 0; // +0xB8
    *(ushort*)(newObj + 0xF) = 0; // +0x3C
    *(ushort*)((char*)newObj + 0x3E) = 0;
    *(ushort*)(newObj + 0x10) = 0; // +0x40
    *(ushort*)((char*)newObj + 0x42) = 0;
    newObj[0x1A] = 0;           // +0x68
    newObj[0x1B] = 0;           // +0x6C
    newObj[0x16] = 0;           // +0x58
    newObj[0x17] = 0;           // +0x5C
    newObj[0x19] = param4;     // +0x64
    newObj[0x14] = newObj + 0x30; // +0x50: point to main array after header
    memcpy(newObj + 0x30, (void*)this->mainArray, overrideBlockSize); // Actually copy only overrideBlockSize? Should be mainArrayBytes? Need to check

    // Compute aligned pointers for sub-arrays
    void* alignedPtr = (void*)((int)newObj + overrideBlockSize + 0x13F & ~0x7F); // +0x13F? Actually sizing: header 0xC0 + overrideBlockSize, then align to 128
    newObj[0x15] = alignedPtr; // +0x54: pointer to type C array
    memcpy(alignedPtr, (void*)this->typeCArray, (uint)countC * 0x50);

    // Compute more pointers with 128-byte alignment
    int offsetC = mainArrayBytesAligned; // 0x80 per main? Actually 0x80 * mainCount
    int* ptrC = (int*)((int)alignedPtr + offsetC);
    uint sizeAfterC = unaff_EBX + 0x7F & 0xFFFFFF80; // unaff_EBX is unknown register
    newObj[0x16] = (unaff_EBX != 0) ? ptrC : 0; // +0x58

    uint ptrD = (int)ptrC + sizeAfterC;
    newObj[0x17] = (unaff_EBX != 0) ? (int)ptrC + sizeAfterC : 0; // +0x5C

    // More alignment for unknown blocks from stack variables
    uint local_30 = (iStack_24 != 0) ? ptrD + sizeAfterC : 0;
    uint local_2c = (iStack_24 != 0) ? ptrD + 2 * sizeAfterC : 0;

    // Align for main array block
    void* mainArrayDst = (void*)((mainArrayBytes != 0) ? local_2c + sizeAfterC : 0);
    uint nextPtr = (uint)mainArrayDst + mainArrayBytesAligned;

    // Align for type A block
    void* typeADst = (void*)((totalSizeA + 0x7F != 0) ? nextPtr : 0);

    // Align for type B block
    void* typeBDst = (void*)((*(short*)((char*)this + 0x46) != 0) ? totalSizeB + countOverrides * 0x40 + nextPtr : 0);

    // Copy main array zeroed if countC > 0
    if (*(short*)(this + 0x44) != 0) {
        memset(mainArrayDst, 0, mainArrayBytes);
        newObj[0x20] = mainArrayDst; // +0x80
        newObj[0x21] = (void*)((int)mainArrayDst + (uint)countC * 0x28); // +0x84
    }

    // Copy type A array zeroed if another count > 0
    if (*(short*)((char*)this + 0x46) != 0) {
        memset(typeADst, 0, totalSizeA + 0x7F);
        newObj[0x22] = typeADst; // +0x88
        newObj[0x23] = (void*)((int)typeADst + *(ushort*)((char*)this + 0x46) * 0x34); // +0x8C
    }

    // Process type A entries: copy aligned data
    if (*(short*)(this + 0x3C) != 0) {
        int idxA = 0;
        int* overridePtr = (int*)0; // unused
        for (uint i = 0; i < countA; i++) {
            // Check if entry flagged
            if (*(char*)(this->arrayA + idxA + 0x0B) & 1) { // arrayA + offset0
                int entrySize = *(int*)(this->arrayA + idxA + 4) * 0x14;
                int alignedSize = ALIGN128(entrySize);
                void* srcA = (void*)this->arrayA + idxA + ???;
                // Copy to both buffers (probably double buffer for networking)
                for (int buf = 0; buf < 2; buf++) {
                    FUN_0060b620(alignedSize, 0, ((int*)newObj[0x20])[buf] + idxA, 2);
                }
                idxA += 0x28; // 0x28 bytes per entry in the output array? actually 0x14*2=0x28
            }
            idxA += 0x10; // each input entry size 0x10
        }
    }

    // Process type B entries
    if (*(short*)((char*)this + 0x3E) != 0) {
        int idxB = 0;
        int outIdx = 0;
        for (uint i = 0; i < countB; i++) {
            int* entryB = (int*)(this->arrayB + idxB);
            if (*(char*)((int)entryB + 0x0B) == 1) {
                // Find first main entry with non-negative id
                void* srcOverride = 0;
                if (mainCount != 0) {
                    for (int j = 0; j < mainCount; j++) {
                        if (*(int*)(this->mainArray + j * 0xB0 + 0x70) != -1) {
                            srcOverride = (void*)*(int*)(this->mainArray + j * 0xB0 + 0x88);
                            break;
                        }
                    }
                }
                size_t dataSize = *entryB;
                void* dstArray[2];
                dstArray[0] = (void*)newObj[0x22];
                dstArray[1] = (void*)newObj[0x23];
                for (int buf = 0; buf < 2; buf++) {
                    memcpy(typeBDst, srcOverride, dataSize);
                    FUN_0060c080(entryB[1], typeBDst, dstArray[buf] + outIdx, 0x12);
                    dataSize = *entryB; // reset? Actually memcpy uses dataSize, but the call uses different sizes
                }
                outIdx += 0x34;
            }
            idxB += 0x10;
        }
    }

    // Initialize main entries
    int overrideCountUsed = 0;
    if (newObj[0xD] != 0) {
        int* overridePtr = (int*)overrideParam;
        int offset = 0;
        for (uint i = 0; i < (uint)newObj[0xD]; i++) {
            int* mainEntry = (int*)(newObj[0x14] + offset); // each main entry 0xB0 bytes
            // Set flags
            uint* flags = (uint*)(mainEntry + 2); // +8 from start
            *flags |= 0x402;
            // Clear some fields
            mainEntry[0x17] = 0; // +0x5C
            mainEntry[0x16] = 0; // +0x58
            mainEntry[0x14] = (int)newObj; // +0x50
            // Copy four values from a global DAT_00e2b1a4
            mainEntry[0x29] = DAT_00e2b1a4; // +0xA4
            mainEntry[0x2A] = DAT_00e2b1a4; // +0xA8
            mainEntry[0x2B] = DAT_00e2b1a4; // +0xAC
            mainEntry[0x28] = DAT_00e2b1a4; // +0xA0
            // Set pointer to type C array
            mainEntry[8] = (int)newObj[0x15] + (int)overridePtr; // +0x20? Actually overridePtr used as index
            // Check override flag from source
            char* srcEntry = (char*)(this->mainArray + offset);
            if (srcEntry[6] == 0) {
                // Allocate two 0x40-byte aligned blocks from local_30 and local_2c
                mainEntry[0x1E] = local_30; // +0x78
                local_0 += 0x40;
                // Initialize that block with DAT_00e2b1a4 pattern
                int* block = (int*)mainEntry[0x1E];
                block[0] = DAT_00e2b1a4;
                block[1] = 0; block[2] = 0; block[3] = 0; block[4] = 0;
                block[5] = DAT_00e2b1a4;
                block[6] = 0; block[7] = 0; block[8] = 0; block[9] = 0;
                block[10] = DAT_00e2b1a4;
                block[11] = 0; block[12] = 0; block[13] = 0; block[14] = 0;
                block[15] = DAT_00e2b1a4;

                mainEntry[0x1F] = local_2c; // +0x7C
                local_2c += 0x40;
                block = (int*)mainEntry[0x1F];
                block[0] = DAT_00e2b1a4;
                block[1] = 0; block[2] = 0; block[3] = 0; block[4] = 0;
                block[5] = DAT_00e2b1a4;
                block[6] = 0; block[7] = 0; block[8] = 0; block[9] = 0;
                block[10] = DAT_00e2b1a4;
                block[11] = 0; block[12] = 0; block[13] = 0; block[14] = 0;
                block[15] = DAT_00e2b1a4;
            }
            // Reference count for some ID (likely texture/object)
            int* refList = *(int**)(DAT_012054ac + (mainEntry[3] & 0x1FFF) * 4); // +0xC
            for (; refList != 0; refList = (int*)refList[4]) {
                if (refList[3] == mainEntry[3]) {
                    if (refList) {
                        LOCK();
                        *refList += 1;
                        UNLOCK();
                    }
                    break;
                }
            }
            // Handle override parameters
            if (overrideParam != 0 && *overridePtr == (int)srcEntry) {
                FUN_0045a100((int)mainEntry, overridePtr[1]);
                overrideCountUsed++;
                if (overrideCountUsed < overrideCount) {
                    overridePtr += 3; // advance to next triplet
                } else {
                    overrideParam = 0;
                }
            }
            // Set pointers for secondary arrays
            int id58 = *(int*)(srcEntry + 0x70); // +0x70
            int id68 = *(int*)(srcEntry + 0x68); // +0x68
            if (id68 == -1) {
                mainEntry[0x1A] = 0; // +0x68
            } else {
                int idx68 = id68 * 0x28;
                mainEntry[0x19] = (int)newObj[0x20] + idx68; // +0x64? Actually offset 100? *0x64? Wait 100 in decimal? Use 0x64
                mainEntry[0x1A] = (int)newObj[0x21] + idx68; // +0x68
            }
            if (id58 == -1) {
                mainEntry[0x1C] = 0; // +0x70
                mainEntry[0x1D] = 0; // +0x74
            } else {
                int idx58 = id58 * 0x34;
                mainEntry[0x1C] = (int)newObj[0x22] + idx58; // +0x70
                mainEntry[0x1D] = (int)newObj[0x23] + idx58; // +0x74
            }
            offset += 0xB0;
        }
    }

    // Finalize
    if (*(short*)(newObj + 0x44) != 0) {
        FUN_00459800();
    }

    return (Entity*)newObj;
}