// FUNC_NAME: Raycast::performRaycast
// Function address: 0x006d3330 (thunk to 0x006d2db0)
// Performs a raycast (or sphere sweep) from param_1 position to param_2 direction, returns closest hit distance via param_3.
uint Raycast_performRaycast(float* startPos, float* endPos, float* outClosestDistance)
{
    float t1, t2, t3, t4;
    float q1, q2, q3, q4;
    bool hitFound1, hitFound2;
    float hitDist1, hitDist2;
    int numResults;
    int resultIndex;
    float resultDist;
    uint resultFlags;
    void* resultObj;
    uint allocResult;
    uint retVal;

    // Set default output
    if (outClosestDistance != nullptr) {
        *outClosestDistance = _DAT_00d5780c; // some default large distance?
    }

    t1 = startPos[0];
    t2 = startPos[1];
    t3 = startPos[2];
    t4 = startPos[3];
    q1 = endPos[0];
    q2 = endPos[1];
    q3 = endPos[2];
    q4 = endPos[3];

    FUN_00a64b00(_DAT_00e51108); // Likely set some global time/state

    // Initialize local structures
    float afStack_2d0[6]; // maybe bounds or query parameters?
    afStack_2d0[0] = _DAT_00d5780c;
    afStack_2d0[1] = 0.0f;
    afStack_2d0[2] = 0.0f;
    afStack_2d0[3] = 0.0f;
    afStack_2d0[4] = 0.0f;
    afStack_2d0[5] = _DAT_00d5780c;
    // other stack variables...

    // Setup query structure
    pfStack_378 = afStack_2d0; // pointer to float array
    puStack_380 = auStack_220; // some buffer
    uStack_374 = 0;
    uStack_37c = 0xffffffff;
    uStack_370 = 0;
    uStack_36c = 0;
    uStack_368 = 0;
    uStack_364 = 0;
    uStack_366 = 0;
    cStack_367 = 0x7f; // max hits? flags?

    // Set start position in query
    fStack_2a0 = t1;
    fStack_29c = t2;
    fStack_298 = t3;
    fStack_294 = t4;

    FUN_00a64fd0(); // Maybe reset query accumulator

    // More initialization
    uStack_338 = DAT_00d5ccf8;
    fStack_320 = DAT_00e44598; // some epsilon?
    fStack_31c = DAT_00e44598;
    cStack_367 = (char)(&puStack_380 - &uStack_36c); // compute offset?
    uStack_36f = 0;
    uStack_36e = 0;
    ppuStack_310 = &PTR_LAB_00dc471c; // vtable or function table
    iStack_2e0 = 0;
    fStack_2e4 = DAT_00e445dc; // default distance?
    fStack_30c = DAT_00e445dc;

    // Set end position in query
    fStack_330 = q1;
    fStack_32c = q2;
    fStack_328 = q3;
    fStack_324 = q4;

    // Allocate query result buffer (size 0xc * 1, flags 0)
    uStack_364 = FUN_00540c60(0xc, 1, 0); // allocation call

    // First query call
    iStack_2e0 = 0;
    fStack_2e4 = DAT_00e445dc;
    fStack_30c = DAT_00e445dc;
    FUN_009e7fd0(&puStack_380, &fStack_330, &ppuStack_310, &ppuStack_310); // physics query
    hitFound1 = (iStack_2e0 != 0);
    hitDist1 = 0.0f;
    if (hitFound1) {
        hitDist1 = fStack_2e4; // distance from first query
    }

    // Second query call
    uStack_364 = FUN_00540c60(0xc, 0x17, 0);
    iStack_2e0 = 0;
    fStack_2e4 = DAT_00e445dc;
    fStack_30c = DAT_00e445dc;
    uint uVar10 = FUN_009e7fd0(&puStack_380, &fStack_330, &ppuStack_310, &ppuStack_310);
    hitFound2 = (iStack_2e0 == 0); // note: inverted logic
    hitDist2 = 0.0f;
    if (!hitFound2) {
        hitDist2 = fStack_2e4;
    }

    // Determine best hit
    if ((hitFound1) && ((!hitFound2 && (hitDist2 + DAT_00e44598 < hitDist1)))) {
        // Second hit is better
        // Do nothing special? Actually fall through to later code
    }
    else {
        if (hitFound2) {
            goto LAB_006d3318; // miss
        }
        // First hit is better or only first hit
        uVar10 = FUN_006d11c0(auStack_60, startPos, 5); // possibly interpolate
        FUN_006d12b0(auStack_60, uVar10, endPos);
        if (extraout_AL != 0) {
            goto LAB_006d3318;
        }
        hitDist2 = hitDist1; // use first hit distance
    }

    // Check if hitDist2 is valid (>= 0) and distance to endPos is small enough
    if ((hitDist2 >= 0.0f) ||
        (sqrtf((startPos[1]-endPos[1])*(startPos[1]-endPos[1]) +
               (startPos[2]-endPos[2])*(startPos[2]-endPos[2]) +
               (startPos[0]-endPos[0])*(startPos[0]-endPos[0])) * hitDist2 <=
         (DAT_00e44564 - _DAT_00e51108)))
    {
        // No hit in this branch? Actually if condition true, we iterate results
        if (hitFound1) {
            puStack_1f0 = auStack_1e0; // result array
            ppuStack_200 = &PTR_LAB_00e397fc; // possibly result info
            uStack_1e8 = 0x80000008; // flags
            iStack_1ec = 0;
            fStack_1fc = DAT_00e445dc;
            FUN_009e7fd0(&puStack_380, &fStack_330, &ppuStack_200, &ppuStack_200);

            if ((0 < iStack_1ec) && (FUN_00a65200(), numResults = iStack_1ec, 0 < iStack_1ec)) {
                resultIndex = 0;
                do {
                    resultDist = *(float*)(puStack_1f0 + resultIndex + 0x1c); // distance at offset 0x1c
                    if ((hitDist2 < resultDist) &&
                        (resultObj = *(void**)(*(int*)(puStack_1f0 + resultIndex + 0x28) + 0x1c),
                         resultFlags = FUN_005413f0(resultObj), (resultFlags & 2) == 0))
                    {
                        if (outClosestDistance != nullptr) {
                            *outClosestDistance = resultDist;
                        }
                        uint result = FUN_00543d10();
                        return result & 0xffffff00;
                    }
                    resultIndex += 0x30; // stride = 48 bytes per result
                } while (resultIndex/0x30 < numResults);
            }
            // Cleanup allocated memory
            ppuStack_200 = &PTR_LAB_00e397fc;
            if ((int)uStack_1e8 >= 0) {
                uint size = uStack_1e8 & 0x3fffffff;
                TlsGetValue(DAT_01139810);
                FUN_00aa26e0(puStack_1f0, size * 0x30, 0x17);
            }
        }
        if (outClosestDistance != nullptr) {
            *outClosestDistance = hitDist2;
        }
        return (uint)outClosestDistance & 0xffffff00; // success indicator
    }

LAB_006d3318:
    return 1; // miss/failure
}