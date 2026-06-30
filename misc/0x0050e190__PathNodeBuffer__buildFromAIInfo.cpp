// FUNC_NAME: PathNodeBuffer::buildFromAIInfo
// Function at 0x0050e190 - Initializes a PathNodeBuffer (path node data for navigation) from an AI info object.
// Reads source data (AI info pointer in EAX) and populates the buffer with node positions, flags, and per-node random offsets.
// Handles alignment, flag checks, and optional per-node initialization for pathfinding.

struct PathNodeBuffer {
    // offsets relative to this
    // +0x00: unknown (size 0x24)
    // +0x24: pointer to AI info data block
    // +0x28: copy from AI+0x08
    // +0x2c: flags (uint)
    // +0x30: ?
    // +0x34: copy from AI+0xec (float)
    // +0x38: copy from AI+0xf0 (float)
    // +0x3c: ?
    // +0x40: ?
    // +0x44: ?
    // +0x48: global pointer DAT_00e2b1a4
    // +0x4c: 0
    // +0x50: 0
    // +0x54: 0
    // +0x58: short (number of valid nodes)
    // +0x5a: ?
    // +0x5b: char (type: 1,2,6 etc)
    // +0x5c: short (original count from AI+0x11a)
    // +0x5e: short 0
    // +0x60: 0
    // +0x68: 0
    // +0x6c: 0
    // +0x70: 0
    // +0x74: short (0 initially)
    // +0x76: short (0)
    // +0x80-0x8c: float[4] (quaternion or transform)
    // +0x90: copy from AI+0xdc
    // +0x94: copy from AI+0x17c
    // +0x98: 0
    // +0x9c: DAT_00e2cd54
    // +0xa0: 0
    // +0xa4: 0
    // +0xa8: ptr to extra node data (if flag 0x2000)
    // +0xac: ptr to node state array (type 1,2,6)
    // +0xb0: array of NodeEntry (8 bytes each)
};

struct NodeEntry {
    float x; // offset from path start
    float y; // random offset or flag
};

// Helper functions (stubs)
extern float* FUN_00533fb0(); // unknown, resets some state
extern void FUN_0050d5e0();  // unknown, resets something
extern void FUN_00513c70(float* outValue); // get random float
extern void FUN_00534350();  // compute some value
extern float FUN_004e41b0(); // compute scaling factor
extern int FUN_0050d660(short param1, float param2, void** param3); // iteration helper

// Global constants
extern void* DAT_00e2b1a4; // some global pointer
extern float DAT_00e2cd54; // some constant
extern int DAT_0112509c;   // flag for random generation
extern float DAT_00e2e210; // threshold
extern float DAT_00e44628; // filler value

// __fastcall: this in ecx (param_1), source AI info in eax (in_EAX)
int __fastcall PathNodeBuffer::buildFromAIInfo(int thisPointer) // param_1 = this
{
    char type;
    int countFromAI;
    int nodeCount;
    NodeEntry* nodePtr;
    int i;
    int j;
    float *pfVar1, *pfVar21;
    float fVar3, fVar4, fVar5, fVar6, fVar7, fVar8, fVar22, fVar23;
    uint *puVar17;
    int iVar14, iVar15, iVar16;
    NodeEntry* nodeEntryPtr;
    float local_1c;
    void* local_18;
    uint flags;

    // Clear fields
    *(int*)(thisPointer + 0x2c) = 0;
    *(int*)(thisPointer + 0x4c) = 0;

    // EAX holds pointer to AI info object
    int* aiInfoPtr = (int*)in_EAX;
    *(int*)(thisPointer + 0x24) = aiInfoPtr[1]; // +0x04 -> data block pointer
    *(int*)(thisPointer + 0x28) = *(int*)((int)aiInfoPtr + 8); // +0x08

    if ((*(uint*)(*(int*)(thisPointer + 0x24) + 0x108) & 0x8000) != 0) {
        puVar17 = (uint*)(*(int*)(thisPointer + 0x10) + *(int*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 8));
        *puVar17 |= 0x100;
    }

    *(void**)(thisPointer + 0x48) = DAT_00e2b1a4;
    type = *(char*)(aiInfoPtr[1] + 0x154); // data block +0x154
    *(char*)(thisPointer + 0x5b) = type;

    if (((*(uint*)(*(int*)(thisPointer + 0x24) + 0x104) & 0x4000) != 0) && (type == '\x06')) {
        puVar17 = (uint*)(*(int*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 8) + *(int*)(thisPointer + 0x10));
        *puVar17 |= 0x4000000;
    }

    *(int*)(thisPointer + 0xa0) = 0;
    *(int*)(thisPointer + 0xa4) = 0;
    *(int*)(thisPointer + 0x70) = 0;
    *(int*)(thisPointer + 100) = 0; // offset 0x64? Actually 0x64? Possibly 0x64, but earlier shows 100 decimal (0x64)
    *(int*)(thisPointer + 0x60) = 0;
    *(int*)(thisPointer + 0x68) = 0;
    *(int*)(thisPointer + 0x6c) = 0;

    int originalCount = *(short*)(*(int*)(thisPointer + 0x24) + 0x11a); // data block +0x11a
    if (originalCount == 0) {
        return 0;
    }

    // Calculate number of 8-byte nodes: round up originalCount to multiple of 8? Actually (originalCount+7)/8
    int numEntries = (originalCount + 7) >> 3; // rounded up division by 8
    int nodeArrayOffset = numEntries * 8 + 0xb0; // array starts at +0xb0
    *(int*)(thisPointer + 0xa8) = 0;

    if ((*(uint*)(*(int*)(thisPointer + 0x24) + 0x104) & 0x2000) != 0) {
        puVar17 = (uint*)(*(int*)(thisPointer + 4) + 0xc); // unknown offset
        *puVar17 |= 0x800000;
        int extraPtr = thisPointer + nodeArrayOffset;
        nodeArrayOffset += numEntries * 0x18; // each extra entry 0x18? Actually 0x18 = 24 bytes
        *(int*)(thisPointer + 0xa8) = extraPtr;
    }

    type = *(char*)(thisPointer + 0x5b);
    *(int*)(thisPointer + 0xac) = 0;
    if ((type == '\x01') || (type == '\x02') || (type == '\x06')) {
        int stateArrayPtr = thisPointer + nodeArrayOffset;
        nodeArrayOffset += numEntries * 8;
        *(int*)(thisPointer + 0xac) = stateArrayPtr;
    }

    iVar14 = *(int*)(thisPointer + 0x24); // data block pointer
    float fVar22 = (float*)(*(int**)(unaff_FS_OFFSET + 0x2c))[0]; // some global float
    *(float*)(thisPointer + 0x34) = *(float*)(iVar14 + 0xec);
    *(float*)(thisPointer + 0x38) = *(float*)(iVar14 + 0xf0);
    *(short*)(thisPointer + 0x5c) = *(short*)(iVar14 + 0x11a);
    *(float*)(thisPointer + 0x90) = *(float*)(iVar14 + 0xdc);
    *(float*)(thisPointer + 0x94) = *(float*)(iVar14 + 0x17c);

    if ((*(byte*)(*(int*)(thisPointer + 0x10) + *(int*)(fVar22 + 8)) & 0x10) != 0) {
        *(uint*)(thisPointer + 0x2c) |= 0x800;
    }

    // Check range conditions and set flags
    if ((0.0 < *(float*)(iVar14 + 0xac) || *(float*)(iVar14 + 0xac) == 0.0) ||
        (*(float*)(iVar14 + 0xcc) <= 0.0)) {
        if ((*(short*)(iVar14 + 0x118) < 1) && (*(float*)(iVar14 + 200) <= 0.0)) {
            puVar17 = (uint*)(*(int*)(fVar22 + 8) + *(int*)(thisPointer + 0x10));
            *puVar17 |= 2;
        }
    } else {
        *(uint*)(thisPointer + 0x2c) |= 4;
    }

    *(int*)(thisPointer + 0x44) = 0;
    void* local_20 = (void*)numEntries; // keep numEntries
    float local_1c = fVar22;

    if ((*(uint*)(*(int*)(thisPointer + 0x24) + 0x10c) & 0x80000000) != 0) {
        FUN_0050d5e0();
    }

    // Copy position offset from data block into buffer at +0x40? Actually reads from fVar22+8 center
    iVar14 = *(int*)(fVar22 + 8);
    iVar15 = *(int*)(thisPointer + 0x10);
    pfVar21 = (float*)(iVar14 + 0x40 + iVar15);
    fVar3 = pfVar21[1];
    fVar4 = pfVar21[2];
    fVar5 = pfVar21[3];
    fVar23 = *(float*)(iVar14 + 0x4c + iVar15);
    pfVar1 = (float*)(iVar14 + 0x40 + iVar15);
    iVar14 = *(int*)(thisPointer + 0x24);
    fVar6 = *(float*)(iVar14 + 0x94);
    fVar7 = *(float*)(iVar14 + 0x98);
    fVar8 = *(float*)(iVar14 + 0x9c);
    *pfVar1 = *(float*)(iVar14 + 0x90) + *pfVar21;
    pfVar1[1] = fVar6 + fVar3;
    pfVar1[2] = fVar7 + fVar4;
    pfVar1[3] = fVar8 + fVar5;
    pfVar1[3] = fVar23;

    FUN_00533fb0(); // reset some state

    // Copy transform from some buffer (quaternion?) into local fields
    float* quatSrc = (float*)(*(int*)(fVar22 + 8) + 0x80 + *(int*)(thisPointer + 0x10));
    *(float*)(thisPointer + 0x80) = quatSrc[0];
    *(float*)(thisPointer + 0x84) = quatSrc[1];
    *(float*)(thisPointer + 0x88) = quatSrc[2];
    *(float*)(thisPointer + 0x8c) = quatSrc[3];

    *(uint*)(thisPointer + 0x2c) |= 8;
    *(int*)(thisPointer + 0x30) = 0;
    *(int*)(thisPointer + 0x50) = 0;
    *(int*)(thisPointer + 0x54) = 0;
    *(int*)(thisPointer + 0x3c) = 0;
    *(int*)(thisPointer + 0x40) = 0;
    *(int*)(thisPointer + 0x98) = 0;
    *(float*)(thisPointer + 0x9c) = DAT_00e2cd54;
    *(short*)(thisPointer + 0x5e) = 0;
    *(short*)(thisPointer + 0x76) = 0;
    *(short*)(thisPointer + 0x74) = 0;

    // Initialize node array
    if ((*(uint*)(thisPointer + 0x2c) & 0x200) == 0) {
        // Standard random initialization for each node
        if (DAT_0112509c != 0) {
            nodeEntryPtr = (NodeEntry*)(thisPointer + 0xb0);
            for (int k = 0; k < numEntries; k++) {
                float randomValX, randomValY;
                if (DAT_0112509c == 0) {
                    randomValX = 0.0f;
                    randomValY = 0.0f;
                } else {
                    FUN_00513c70(&randomValX);
                }
                nodeEntryPtr->x = randomValX;
                nodeEntryPtr->y = randomValY;
                if (randomValX == 0.0f) break;
                nodeEntryPtr++;
            }
        }
    } else {
        // Alternative initialization using allocated buffer alignment
        int alignedOffset = ((nodeArrayOffset + 0xf) & 0xfffffff0) + thisPointer;
        int base = alignedOffset - *(int*)(fVar22 + 8);
        if (alignedOffset == 0) {
            base = 0;
        }
        if (numEntries > 0) {
            int iterOffset = 0;
            int* piVar18 = (int*)(thisPointer + 0xb0);
            int remaining = numEntries;
            do {
                int ptr = base + iterOffset;
                if (ptr == 0) {
                    *piVar18 = 0;
                } else {
                    *piVar18 = ptr - *(int*)(fVar22 + 8);
                }
                piVar18[1] = (ptr != 0) ? 1 : 0;
                piVar18 += 2;
                iterOffset += 0x2a0;
                remaining--;
            } while (remaining > 0);
        }
    }

    // Fill extra data if flag 0x1000 is set
    float filler = DAT_00e44628;
    flags = *(uint*)(*(int*)(thisPointer + 0x24) + 0x108);
    if ((flags & 0x1000) != 0 && numEntries > 0) {
        int* piVar18 = (int*)(thisPointer + 0xb0);
        int remaining = numEntries;
        do {
            float* target = (float*)(*(int*)(fVar22 + 8) + *piVar18 + 0x2c);
            for (int m = 0; m < 8; m++) {
                *target = filler;
                target += 0x14;
            }
            piVar18 += 2;
            remaining--;
        } while (remaining > 0);
    }

    if (numEntries == 0) {
        return 0;
    }

    *(short*)(thisPointer + 0x58) = (short)numEntries;
    *(short*)(thisPointer + 0x5c) = (short)(numEntries * 8); // originalCount? Actually numEntries*8

    if ((*(uint*)(*(int*)(thisPointer + 0x24) + 0x108) & 0x100000) == 0) {
        return 1;
    }

    type = *(char*)(thisPointer + 0x5b);
    if ((((type != '\0') && (type != '\x03')) && (type != '\x05')) && (type != '\x04')) {
        return 1;
    }

    if ((*(byte*)(*(int*)(fVar22 + 8) + *(int*)(thisPointer + 0x10)) & 0x10) != 0) {
        return 1;
    }

    // Final loop to adjust nodes based on range and flags
    float local_1c = 0.0f;
    bool bVar12 = true;
    FUN_00533fb0();

    iVar14 = *(int*)(thisPointer + 0x24);
    float range = *(float*)(iVar14 + 0xac);
    if (0.0 < range) {
        fVar23 = *(float*)(iVar14 + 0xcc);
        if (fVar23 <= 0.0f) {
            if (0 < *(short*)(iVar14 + 0x118)) {
                void* tempPtr = DAT_00e2b1a4;
                if ((*(uint*)(iVar14 + 0x10c) & 0x20000000) == 0) {
                    FUN_00534350();
                }
                int someVal = *(int*)(thisPointer + 0x24);
                tempPtr = DAT_00e2b1a4; // reassign
                float scale = FUN_004e41b0();
                fVar23 = (scale * (float)*(short*)(someVal + 0x126) + (float)*(short*)(someVal + 0x124)) * (float)tempPtr;
                int intVal = (int)fVar23;
                if (intVal == 0) {
                    intVal = *(short*)(someVal + 0x118);
                    goto LAB_loop;
                }
                intVal = (*(short*)(someVal + 0x118) - 1 + intVal) / intVal;
                goto LAB_loop;
            }
            goto LAB_end;
        }
        intVal = 1000;
        bVar12 = false;
        local_1c = fVar23;
    } else {
        intVal = 1;
    }

    // Loop
    do {
        if ((0.0 < *(float*)(*(int*)(thisPointer + 0x24) + 0xcc)) &&
            (fVar23 = local_1c, local_1c <= DAT_00e2e210)) break;
        FUN_0050d660(*(short*)(thisPointer + 0x74), local_1c, &local_20);
        *(int*)(thisPointer + 0x3c) = 0;
        if (fVar23 <= 0.0f) break;
        if (!bVar12) {
            local_1c -= fVar23;
        }
        intVal--;
    } while (0 < intVal);

LAB_loop:
    ;

LAB_end:
    *(int*)(thisPointer + 0x30) = 0;
    *(int*)(thisPointer + 0x3c) = 0;
    return 1;
}