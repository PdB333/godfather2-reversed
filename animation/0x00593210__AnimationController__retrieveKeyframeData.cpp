// FUNC_NAME: AnimationController::retrieveKeyframeData
// Function at 0x00593210: Retrieves or stores a keyframe data (8 floats) indexed by a float key.
// Uses a two-buffer system for efficient lookup and replacement (LRU-like).
// Each slot is 12 floats (48 bytes): slot[0] = timestamp, slot[1] = key, slot[4..7] = vectorA, slot[8..11] = vectorB.
// The class has two active buffer groups (A and B) and a pending buffer for swapping.

void __thiscall AnimationController::retrieveKeyframeData(float *outData, float key)
{
    int *thisPtr = this; // unaff_EDI assumed to be this
    int iVar6;
    int iVar2;
    float fVar1;
    float fVar3;
    float fVar8;
    float fVar10;
    float *pfVar7;
    float *pfVar9;
    float *local_2c;
    bool bVar4;
    int *puVar5;

    // Determine which buffer group to use based on a magic field at this[1]
    iVar6 = thisPtr[1]; // some kind of state or index
    // Access a field at offset 4 from iVar6: first 4 bytes? Actually (*(uint *)(iVar6 + 4) & 0xff) < 10
    // This suggests iVar6 points to a structure with a byte at +4 that determines path.
    if ((*(uint *)(iVar6 + 4) & 0xff) < 10) {
        iVar6 = *(int *)(iVar6 + 0x10); // follow pointer at +0x10
    } else {
        iVar6 = *(int *)(iVar6 + 0x24); // follow pointer at +0x24
    }
    if (iVar6 < 0) {
        return; // invalid state
    }

    // Increment a counter at this->0x2d0
    *(int *)(thisPtr[0] + 0x2d0) = *(int *)(thisPtr[0] + 0x2d0) + 1;
    iVar6 = thisPtr[0]; // reload base pointer
    iVar2 = thisPtr[1];
    bVar4 = false;
    local_2c = (float *)0x0;

    if (iVar2 == *(int *)(iVar6 + 0x2c0)) {
        // Active buffer A
        local_2c = (float *)(iVar6 + 0x1d0); // end of buffer A
        bVar4 = true;
    } else {
        if (iVar2 == *(int *)(iVar6 + 0x2c4)) {
            // Active buffer B
            local_2c = (float *)(iVar6 + 0x290); // end of buffer B
            bVar4 = true;
            pfVar7 = (float *)(iVar6 + 0x200); // start of buffer B
            goto LAB_00593310;
        }
        if (*(int *)(iVar6 + 0x2c8) == *(int *)(iVar6 + 0x2c0)) {
            // Swap: set buffer B to this key and clear buffer B slots
            *(int *)(iVar6 + 0x2c4) = iVar2;
            puVar5 = (undefined4 *)(iVar6 + 0x230);
            if (puVar5 <= (undefined4 *)(iVar6 + 0x290)) {
                do {
                    puVar5[1] = 0xffffffff; // clear key
                    *puVar5 = 0; // clear timestamp
                    puVar5 = puVar5 + 0xc; // advance 48 bytes (12 floats)
                } while (puVar5 <= (undefined4 *)(iVar6 + 0x290));
            }
            iVar6 = thisPtr[0];
            pfVar7 = (float *)(iVar6 + 0x200);
            goto LAB_00593310;
        }
        // Otherwise, set buffer A to this key and clear buffer A slots
        *(int *)(iVar6 + 0x2c0) = iVar2;
        puVar5 = (undefined4 *)(iVar6 + 0x170);
        if (puVar5 <= (undefined4 *)(iVar6 + 0x1d0)) {
            do {
                puVar5[1] = 0xffffffff;
                *puVar5 = 0;
                puVar5 = puVar5 + 0xc;
            } while (puVar5 <= (undefined4 *)(iVar6 + 0x1d0));
        }
        iVar6 = thisPtr[0];
        bVar4 = false;
    }
    pfVar7 = (float *)(iVar6 + 0x140); // start of buffer A

LAB_00593310:
    // Record the last used key index
    *(int *)(iVar6 + 0x2c8) = thisPtr[1];

    if (bVar4) {
        // Search the active buffer for a matching key
        float bestTimestamp = (float)DAT_00e2e50c; // a sentinel high timestamp
        float bestKey = 0.0f;
        // Actually the logic uses pfVar7 as current best slot pointer
        // and fVar8/fVar10 as current best key/timestamp
        // Rewriting the loop more clearly:
        pfVar9 = pfVar7;
        fVar8 = 0.0f;
        fVar10 = bestTimestamp;
        while (pfVar9 <= local_2c) {
            fVar3 = pfVar9[1];
            if (fVar3 == key) {
                // Key found, copy stored vectors and return
                *(int *)(thisPtr[0] + 0x2cc) = *(int *)(thisPtr[0] + 0x2cc) + 1;
                *pfVar9 = *(float *)(thisPtr[0] + 0x78); // update timestamp
                fVar8 = pfVar9[5];
                fVar10 = pfVar9[6];
                fVar3 = pfVar9[7];
                outData[0] = pfVar9[4];
                outData[1] = fVar8;
                outData[2] = fVar10;
                outData[3] = fVar3;
                fVar8 = pfVar9[9];
                fVar10 = pfVar9[10];
                fVar3 = pfVar9[0xb];
                outData[4] = pfVar9[8];
                outData[5] = fVar8;
                outData[6] = fVar10;
                outData[7] = fVar3;
                return;
            }
            if (fVar3 == 0.0f) {
                // Empty slot, skip
                pfVar9 = pfVar9 + 0xc;
                continue;
            }
            fVar1 = *pfVar9; // timestamp
            if (fVar10 <= fVar1) {
                if ((fVar1 == fVar10) && ((int)fVar3 < (int)fVar8)) {
                    // tie-breaker: prefer lower key
                    pfVar7 = pfVar9;
                    fVar8 = fVar3;
                }
                pfVar9 = pfVar9 + 0xc;
            } else {
                // New best slot found (older timestamp)
                pfVar7 = pfVar9;
                fVar8 = fVar3;
                pfVar9 = pfVar9 + 0xc;
                fVar10 = fVar1;
            }
        }
    }

    // No matching key found; call an external function (likely to update some state)
    FUN_0056ec90();

    // Replace the best slot (oldest timestamp) with new data
    *pfVar7 = *(float *)(thisPtr[0] + 0x78); // current timestamp
    pfVar7[1] = key;
    fVar8 = outData[1];
    fVar10 = outData[2];
    fVar3 = outData[3];
    pfVar7[4] = outData[0];
    pfVar7[5] = fVar8;
    pfVar7[6] = fVar10;
    pfVar7[7] = fVar3;
    fVar8 = outData[5];
    fVar10 = outData[6];
    fVar3 = outData[7];
    pfVar7[8] = outData[4];
    pfVar7[9] = fVar8;
    pfVar7[10] = fVar10;
    pfVar7[0xb] = fVar3;
    return;
}