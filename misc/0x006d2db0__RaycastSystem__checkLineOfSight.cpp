// FUNC_NAME: RaycastSystem::checkLineOfSight

uint32 checkLineOfSight(float* fromPos, float* toPos, float* outHitDistance)
{
    float fVar1, fVar2, fVar3, fVar4, fVar5, fVar6, fVar7, fVar8;
    int iVar9;
    char extraout_AL;
    uint32 uVar10;
    uint32 uVar11;
    undefined1* puVar12;
    int iVar14;
    int iVar15;
    bool bVar16, bVar17;
    float hitDistA, hitDistB;
    // Ray query structure (size approx 0x1e0)
    struct {
        int field_00; // +0x00
        float rayStart[4]; // +0x04
        float rayEnd[4]; // +0x14
        // +0x24: hit point?
        // +0x28: hit normal?
        // +0x30: hit distance?
        // +0x34: ...
        // ... many fields
    } rayQuery; // stack variable local_380 area, size ~0x1e0
    float fromPosCopy[4]; // local_2a0..294
    float toPosCopy[4]; // local_330..324
    undefined** pCallback; // local_310 = &PTR_LAB_00dc471c
    float someFloatA; // local_2e4
    int someIntFlag; // local_2e0
    // Other local variables

    if (outHitDistance != nullptr) {
        *outHitDistance = _DAT_00d5780c; // FLT_MAX likely
    }
    fVar1 = fromPos[0];
    fVar2 = fromPos[1];
    fVar3 = fromPos[2];
    fVar4 = fromPos[3];
    fVar5 = toPos[0];
    fVar6 = toPos[1];
    fVar7 = toPos[2];
    fVar8 = toPos[3];

    // Initialize collision system
    resetCollisionWorld(_DAT_00e51108);
    // Setup default ray query data
    local_2d0[1] = 0.0f;
    local_2d0[2] = 0.0f;
    local_2d0[3] = 0.0f;
    local_2d0[4] = 0.0f;
    local_2b8 = 0;
    local_2b4 = 0;
    local_2b0 = 0;
    local_2ac = 0;
    local_2a4 = 0;
    local_2d0[0] = _DAT_00d5780c;
    local_2d0[5] = _DAT_00d5780c;
    local_2a8 = _DAT_00d5780c;

    // Prepare ray query structure
    local_378 = local_2d0; // pointer to some buffer
    local_380 = local_220; // another buffer for collision results?
    local_374 = 0;
    local_37c = 0xffffffff; // maybe entity ID or filter
    local_370 = 0;
    local_36c = 0;
    local_368 = 0;
    local_364 = 0;
    local_366 = 0;
    local_367 = 0x7f; // max hits?

    // Set ray start position
    local_2a0 = fVar1;
    local_29c = fVar2;
    local_298 = fVar3;
    local_294 = fVar4;

    beginCollisionQuery(); // FUN_00a64fd0
    local_338 = DAT_00d5ccf8; // some constant
    local_320 = DAT_00e44598; // epsilon?
    local_31c = DAT_00e44598;
    // Compute size of query structure?? (char)&local_380 - (char)&local_36c
    local_367 = (char)&local_380 - (char)&local_36c;
    local_36f = 0;
    local_36e = 0;
    local_310 = &PTR_LAB_00dc471c; // default callback vtable
    local_2e0 = 0;
    local_2e4 = DAT_00e445dc; // some default distance?
    local_30c = DAT_00e445dc;

    // Set ray end position
    local_330 = fVar5;
    local_32c = fVar6;
    local_328 = fVar7;
    local_324 = fVar8;

    // Allocation/filter setup - first call
    local_364 = memoryAlloc(0xc, 1, 0); // FUN_00540c60
    local_2e0 = 0;
    local_2e4 = DAT_00e445dc;
    local_30c = DAT_00e445dc;
    // First ray sweep (returns hit distance or flag)
    uVar10 = sweepRay(&local_380, &local_330, &local_310, &local_310); // FUN_009e7fd0
    bVar16 = local_2e0 != 0; // true if hit found
    hitDistA = 0.0f;
    if (bVar16) {
        hitDistA = local_2e4; // distance from first sweep
    }

    // Second call - different filter (0x17)
    local_364 = memoryAlloc(0xc, 0x17, 0);
    local_2e0 = 0;
    local_2e4 = DAT_00e445dc;
    local_30c = DAT_00e445dc;
    uVar10 = sweepRay(&local_380, &local_330, &local_310, &local_310);
    bVar17 = local_2e0 == 0; // true if no hit
    hitDistB = 0.0f;
    if (!bVar17) {
        hitDistB = local_2e4; // distance from second sweep
    }

    // Decision: if both sweeps hit, and the second hit is closer (within epsilon) than the first, try alternative method
    if (bVar16 && !bVar17 && (hitDistB + DAT_00e44598 < hitDistA)) {
        // Else branch from original: try sphere sweep
        uVar10 = sweepSphere(local_60, fromPos, 5); // FUN_006d11c0
        sweepCapsule(local_60, uVar10, toPos); // FUN_006d12b0
        if (extraout_AL != 0) {
            goto LAB_006d3318; // no clear line
        }
        hitDistB = hitDistA; // fallback
    }

    // Check if hit distance is valid: if (hitDistB >= 0) or (distance between points * hitDistB <= threshold)
    if ((hitDistB >= 0.0f) ||
        (computeDistance(fromPos, toPos) * hitDistB <= DAT_00e44564 - _DAT_00e51108)) {
        // If first sweep hit, do iterative query for better hit
        if (bVar16) {
            local_1f0 = local_1e0; // result buffer
            local_200 = &PTR_LAB_00e397fc; // different callback
            local_1e8 = 0x80000008; // flags
            local_1ec = 0;
            local_1fc = DAT_00e445dc;
            // Perform another sweep with new callback
            sweepRay(&local_380, &local_330, &local_200, &local_200);
            if ((0 < local_1ec) && (resetCollisionWorld(), iVar9 = local_1ec, 0 < local_1ec)) {
                iVar14 = 0;
                iVar15 = 0;
                puVar12 = local_1f0;
                do {
                    // Each hit entry size 0x30 bytes
                    float hitDist = *(float*)(puVar12 + iVar14 + 0x1c);
                    if ((hitDistB < hitDist) &&
                        (uVar11 = checkHitFlags(*(uint32*)(*(int*)(puVar12 + iVar14 + 0x28) + 0x1c)), // FUN_005413f0
                         puVar12 = local_1f0, (uVar11 & 2) == 0)) {
                        if (outHitDistance != nullptr) {
                            *outHitDistance = hitDist;
                        }
                        uVar11 = getHitEntityId(); // FUN_00543d10
                        return uVar11 & 0xffffff00;
                    }
                    iVar15++;
                    iVar14 += 0x30;
                } while (iVar15 < iVar9);
            }
            // Cleanup allocated buffer
            if ((int)local_1e8 >= 0) {
                uVar11 = local_1e8 & 0x3fffffff;
                TlsGetValue(DAT_01139810);
                deallocateBuffer(local_1f0, uVar11 * 0x30, 0x17); // FUN_00aa26e0
            }
        }
        if (outHitDistance != nullptr) {
            *outHitDistance = hitDistB;
        }
        return (uint32)outHitDistance & 0xffffff00; // success, clear line
    }

LAB_006d3318:
    // Return failure (blocked)
    return CONCAT31(uVar13, 1); // low byte set to 1
}