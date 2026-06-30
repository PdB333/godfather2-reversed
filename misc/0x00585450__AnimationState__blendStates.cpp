// FUNC_NAME: AnimationState::blendStates
// Function at 0x00585450 merges two animation states (param_1 and param_2) into a new result state.
// Handles blending of multiple data arrays: bone mask (1 byte per bone), bone transforms (0x20 bytes per bone),
// optional additional transform data (0x10 bytes per bone), and per-bone override pairs (two ints per bone).
// Also copies a full transform block (8 floats) based on blend type flags at +0x30.

// Structure offsets (relative to the large state object):
// +0x30: uint8 blendType (0 = no blend, 2 = use source2 or override)
// +0x34: uint8* boneMask (size per bone: 1 byte, indicates presence)
// +0x38: ArrayHeader at +0x38 (offset +0xc is count, offset +0x10 is actual data of size 0x20 per bone)
// +0x3c: ArrayHeader (if non-null) at +0x3c (data size 0x10 per bone)
// +0x44: ArrayHeader (data size 8 per bone, pair of ints)
// +0x10 to +0x2c: 8 floats (position, rotation, scale? - 32 bytes)

int AnimationState::blendStates(int stateA, int stateB, byte flags)
{
    int result;
    int countA, countB, minCount;
    int iVar1, iVar2, iVar12;
    void *ptrMaskA, *ptrMaskB, *ptrMaskRes;
    int *ptrDataA, *ptrDataB, *ptrDataRes;
    int *ptrExtraA, *ptrExtraB, *ptrExtraRes;
    int *ptrPairA, *ptrPairB, *ptrPairRes;
    int iVar8;
    bool bVar14;

    // Validate inputs
    if ((stateA == 0) || (stateB == 0))
        return 0;
    result = FUN_0056fdd0();  // Get or create result state
    if (result == 0)
        return 0;

    // If no main blend data (bit 4 == 0) skip to secondary merge
    if ((flags & 4) != 0)
        goto LAB_0058595b;

    // Get bone counts from +0x38 header (offset +0xc)
    countA = *(int *)(*(int *)(stateA + 0x38) + 0xc);
    countB = *(int *)(*(int *)(stateB + 0x38) + 0xc);
    minCount = countA;
    if (countB <= countA)
        minCount = countB;

    // Reference count adjusts?
    FUN_0056f800(stateB);
    FUN_0056f800(stateA);
    iVar8 = stateB;
    if (countB <= countA)
        iVar8 = stateA;
    FUN_0056f800(iVar8);

    if (*(int *)(result + 0x3c) == 0)  // No extra transform channel
    {
        ptrMaskA = (void *)(*(int *)(stateA + 0x34) + 0x14);
        ptrDataA = (void *)(*(int *)(stateA + 0x38) + 0x10);
        ptrMaskB = (void *)(*(int *)(stateB + 0x34) + 0x14);
        ptrDataB = (int *)(*(int *)(stateB + 0x38) + 0x10);
        ptrMaskRes = (void *)(*(int *)(result + 0x34) + 0x14);
        ptrDataRes = (int *)(*(int *)(result + 0x38) + 0x10);
        iVar8 = minCount;

        if ((*(char *)(*(int *)(stateA + 0x34) + 0x10) == '\0') ||
            (*(char *)(*(int *)(stateB + 0x34) + 0x10) == '\0'))
        {
            // Per-bone copy (no bulk optimization)
            for (; 0 < iVar8; iVar8--)
            {
                FUN_00585400();  // Copy one bone mask and transform
                ptrDataA = (int *)((int)ptrDataA + 0x20);
                ptrMaskA = (void *)((int)ptrMaskA + 1);
                ptrMaskB = (void *)((int)ptrMaskB + 1);
                ptrMaskRes = (void *)((int)ptrMaskRes + 1);
                ptrDataB = ptrDataB + 8;   // 8 ints = 0x20 bytes
                ptrDataRes = ptrDataRes + 8;
            }
        }
        else
        {
            // Bulk copy for all bones in minCount
            FUN_0056f620();  // Setup for bulk copy
            if (0 < minCount)
            {
                ptrMaskA = (void *)((int)ptrMaskA + minCount);
                ptrMaskRes = (void *)((int)ptrMaskRes + minCount);
                ptrMaskB = (void *)((int)ptrMaskB + minCount);
                do {
                    // Copy 8 ints (0x20 bytes) from ptrDataB to ptrDataRes
                    *ptrDataRes = *ptrDataB;
                    ptrDataRes[1] = ptrDataB[1];
                    ptrDataRes[2] = ptrDataB[2];
                    ptrDataRes[3] = ptrDataB[3];
                    ptrDataRes[4] = ptrDataB[4];
                    ptrDataRes[5] = ptrDataB[5];
                    ptrDataRes[6] = ptrDataB[6];
                    ptrDataRes[7] = ptrDataB[7];
                    ptrDataRes += 8;
                    ptrDataB += 8;
                    iVar8--;
                } while (0 < iVar8);
            }
        }

        // Copy remaining bones from the state with more bones
        if (minCount < countA)
        {
            _memcpy(ptrMaskRes, ptrMaskA, countA - minCount);
            _memcpy(ptrDataRes, ptrDataA, (countA - minCount) * 0x20);
        }
        else if (minCount < countB)
        {
            _memcpy(ptrMaskRes, ptrMaskB, countB - minCount);
            _memcpy(ptrDataRes, ptrDataB, (countB - minCount) * 0x20);
        }
    }
    else  // Extra transform channel present (3 arrays)
    {
        int *ptrExtraDataA, *ptrExtraDataB, *ptrExtraDataRes;
        ptrExtraDataA = (int *)(*(int *)(stateA + 0x3c) + 0x10);
        ptrExtraDataB = (int *)(*(int *)(stateB + 0x3c) + 0x10);
        // ptrMaskA, ptrDataA reused
        ptrMaskA = (void *)(*(int *)(stateA + 0x34) + 0x14);
        ptrMaskB = (void *)(*(int *)(stateB + 0x34) + 0x14);
        ptrDataB = (int *)(*(int *)(stateB + 0x38) + 0x10);
        ptrMaskRes = (void *)(*(int *)(result + 0x34) + 0x14);
        ptrDataRes = (int *)(*(int *)(result + 0x38) + 0x10);
        ptrExtraDataRes = (int *)(*(int *)(result + 0x3c) + 0x10);
        iVar8 = minCount;

        if ((*(char *)(*(int *)(stateA + 0x34) + 0x10) == '\0') ||
            (*(char *)(*(int *)(stateB + 0x34) + 0x10) == '\0'))
        {
            // Per-bone copy for all three arrays
            for (; 0 < iVar8; iVar8--)
            {
                FUN_00586740(&ptrMaskA);  // Copy one set (mask + transforms)
                ptrExtraDataA += 4;       // 4 ints = 0x10 bytes
                ptrExtraDataB += 4;
                ptrExtraDataRes += 4;
                ptrDataA += 8;
                ptrDataB += 8;
                ptrDataRes += 8;
                ptrMaskA = (void *)((int)ptrMaskA + 1);
                ptrMaskB = (void *)((int)ptrMaskB + 1);
                ptrMaskRes = (void *)((int)ptrMaskRes + 1);
            }
        }
        else
        {
            // Bulk copy for the common count
            FUN_0056f620();
            if (0 < minCount)
            {
                ptrMaskA = (void *)((int)ptrMaskA + minCount);
                ptrMaskRes = (void *)((int)ptrMaskRes + minCount);
                ptrMaskB = (void *)((int)ptrMaskB + minCount);
                do {
                    // Copy 8 ints from ptrDataB to ptrDataRes
                    *ptrDataRes = *ptrDataB;
                    ptrDataRes[1] = ptrDataB[1];
                    ptrDataRes[2] = ptrDataB[2];
                    ptrDataRes[3] = ptrDataB[3];
                    ptrDataRes[4] = ptrDataB[4];
                    ptrDataRes[5] = ptrDataB[5];
                    ptrDataRes[6] = ptrDataB[6];
                    ptrDataRes[7] = ptrDataB[7];
                    // Copy 4 ints from ptrExtraDataB to ptrExtraDataRes
                    *ptrExtraDataRes = *ptrExtraDataB;
                    ptrExtraDataRes[1] = ptrExtraDataB[1];
                    ptrExtraDataRes[2] = ptrExtraDataB[2];
                    ptrExtraDataRes[3] = ptrExtraDataB[3];
                    ptrExtraDataRes += 4;
                    ptrExtraDataB += 4;
                    ptrDataRes += 8;
                    ptrDataB += 8;
                    iVar8--;
                } while (0 < iVar8);
            }
        }

        // Copy remaining bones (including extra channel)
        if (minCount < countA)
        {
            size_t size = countA - minCount;
            _memcpy(ptrMaskRes, ptrMaskA, size);
            _memcpy(ptrDataRes, ptrDataA, size * 0x20);
            _memcpy(ptrExtraDataRes, ptrExtraDataA, size * 0x10);
        }
        else if (minCount < countB)
        {
            size_t size = countB - minCount;
            _memcpy(ptrMaskRes, ptrMaskB, size);
            _memcpy(ptrDataRes, ptrDataB, size * 0x20);
            _memcpy(ptrExtraDataRes, ptrExtraDataB, size * 0x10);
        }
    }

LAB_0058581c:
    // Handle per-bone override pairs (+0x44 array, 2 ints per bone)
    if (*(int *)(result + 0x44) != 0)
    {
        int *pairA, *pairB, *pairRes;
        pairA = (int *)(*(int *)(stateA + 0x44) + 0x10);
        pairB = (int *)(*(int *)(stateB + 0x44) + 0x10);
        pairRes = (int *)(*(int *)(result + 0x44) + 0x10);
        iVar8 = minCount;

        // Unrolled loop for batches of 4 bones
        if (3 < minCount)
        {
            int batch = (minCount - 4) / 4 + 1;
            iVar8 = minCount - batch * 4;
            do {
                // For each pair, if pairB entry is -1, use pairA entry
                if (*pairB == -1)
                {
                    *pairRes = *pairA;
                    iVar1 = pairA[1];
                }
                else
                {
                    *pairRes = *pairB;
                    iVar1 = pairB[1];
                }
                pairRes[1] = iVar1;

                if (pairB[2] == -1)
                {
                    pairRes[2] = pairA[2];
                    iVar1 = pairA[3];
                }
                else
                {
                    pairRes[2] = pairB[2];
                    iVar1 = pairB[3];
                }
                pairRes[3] = iVar1;

                if (pairB[4] == -1)
                {
                    pairRes[4] = pairA[4];
                    iVar1 = pairA[5];
                }
                else
                {
                    pairRes[4] = pairB[4];
                    iVar1 = pairB[5];
                }
                pairRes[5] = iVar1;

                if (pairB[6] == -1)
                {
                    pairRes[6] = pairA[6];
                    iVar1 = pairA[7];
                }
                else
                {
                    pairRes[6] = pairB[6];
                    iVar1 = pairB[7];
                }
                pairRes[7] = iVar1;

                pairA += 8;
                pairB += 8;
                pairRes += 8;
                batch--;
            } while (batch != 0);
        }

        // Remaining bones
        for (; 0 < iVar8; iVar8--)
        {
            if (*pairB == -1)
            {
                *pairRes = *pairA;
                iVar12 = pairA[1];
            }
            else
            {
                *pairRes = *pairB;
                iVar12 = pairB[1];
            }
            pairRes[1] = iVar12;
            pairA += 2;
            pairB += 2;
            pairRes += 2;
        }

        // Copy remaining override pairs if one state has more bones
        if (minCount < countA)
        {
            int remain = countA - minCount;
            _memcpy(pairRes, pairA, remain * 8);
        }
        else if (minCount < countB)
        {
            int remain = countB - minCount;
            _memcpy(pairRes, pairB, remain * 8);
        }
    }

LAB_0058595b:
    if ((flags & 8) != 0)
        return result;

    // Handle full transform block (position/rotation/scale) based on blend type
    bVar14 = *(char *)(stateB + 0x30) != 2;
    if (*(char *)(stateA + 0x30) == 2)
    {
        *(char *)(result + 0x30) = 2;
        if (bVar14)   // stateB is not 2
        {
            // Copy transform from stateA
            *(undefined4 *)(result + 0x10) = *(undefined4 *)(stateA + 0x10);
            *(undefined4 *)(result + 0x14) = *(undefined4 *)(stateA + 0x14);
            *(undefined4 *)(result + 0x18) = *(undefined4 *)(stateA + 0x18);
            *(undefined4 *)(result + 0x1c) = *(undefined4 *)(stateA + 0x1c);
            *(undefined4 *)(result + 0x20) = *(undefined4 *)(stateA + 0x20);
            *(undefined4 *)(result + 0x24) = *(undefined4 *)(stateA + 0x24);
            *(undefined4 *)(result + 0x28) = *(undefined4 *)(stateA + 0x28);
            *(undefined4 *)(result + 0x2c) = *(undefined4 *)(stateA + 0x2c);
            return result;
        }
    }
    else
    {
        if (bVar14)   // stateB is also not 2
        {
            *(char *)(result + 0x30) = 0;
            return result;
        }
        // stateB is 2, stateA is not 2
        *(char *)(result + 0x30) = 2;
    }

    // Copy transform from stateB
    *(undefined4 *)(result + 0x10) = *(undefined4 *)(stateB + 0x10);
    *(undefined4 *)(result + 0x14) = *(undefined4 *)(stateB + 0x14);
    *(undefined4 *)(result + 0x18) = *(undefined4 *)(stateB + 0x18);
    *(undefined4 *)(result + 0x1c) = *(undefined4 *)(stateB + 0x1c);
    *(undefined4 *)(result + 0x20) = *(undefined4 *)(stateB + 0x20);
    *(undefined4 *)(result + 0x24) = *(undefined4 *)(stateB + 0x24);
    *(undefined4 *)(result + 0x28) = *(undefined4 *)(stateB + 0x28);
    *(undefined4 *)(result + 0x2c) = *(undefined4 *)(stateB + 0x2c);
    return result;
}