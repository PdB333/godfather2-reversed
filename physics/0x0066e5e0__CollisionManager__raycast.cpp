//FUNC_NAME: CollisionManager::raycast
bool CollisionManager::raycast(int param_1, undefined4 param_2, float param_3, float *outDistance, int *outHitIndex, uint *outHitType)
{
    // +0x49d0c: short, if == 0x1000, raycast is disabled
    if (*(short *)(this + 0x49d0c) == 0x1000) {
        return false;
    }

    int bestHitIndex = -1;
    uint bestHitType = 0xffffffff;
    byte collisionType = *(byte *)(param_1 + 0x2d); // collision type filter
    float bestDistance = param_3; // max distance
    uint objectIndex = 0;

    int objectCount = *(int *)(param_1 + 0x34);
    if (objectCount != 0) {
        int objectOffset = 0;
        int arrayOffset = 0;
        do {
            int objectPtr = *(int *)(param_1 + 0x50) + objectOffset; // base of object array, stride 0xB0
            float fVar14 = 0.0f;

            // Check if object is active and not flagged (0x4000 = ignore?)
            if ((*(char *)(objectPtr + 4) == '\x01') && ((*(uint *)(objectPtr + 8) & 0x4000) == 0)) {
                if (*(char *)(objectPtr + 6) == '\0') {
                    FUN_00417560(); // likely push/pop matrix stack
                }
                char cVar8 = FUN_004166b0(); // check something (maybe visibility?)
                if ((*(int *)(this + 0x18) == 0) || (cVar8 != '\0')) {
                    // Get world transform from this+0x60
                    FUN_0056c640(this + 0x60, &local_d0); // local_d0 is a matrix
                    FUN_00417560();
                    FUN_00417560();
                    // Copy matrix to this+0x160 (16 floats)
                    *(undefined4 *)(this + 0x160) = local_90;
                    *(undefined4 *)(this + 0x164) = uStack_8c;
                    *(undefined4 *)(this + 0x168) = uStack_88;
                    *(undefined4 *)(this + 0x16c) = uStack_84;
                    *(undefined4 *)(this + 0x170) = local_80;
                    *(undefined4 *)(this + 0x174) = uStack_7c;
                    *(undefined4 *)(this + 0x178) = uStack_78;
                    *(undefined4 *)(this + 0x17c) = uStack_74;
                    *(undefined4 *)(this + 0x180) = local_70;
                    *(undefined4 *)(this + 0x184) = uStack_6c;
                    *(undefined4 *)(this + 0x188) = uStack_68;
                    *(undefined4 *)(this + 0x18c) = uStack_64;
                    *(undefined4 *)(this + 400) = local_60;
                    *(undefined4 *)(this + 0x194) = uStack_5c;
                    *(undefined4 *)(this + 0x198) = uStack_58;
                    *(undefined4 *)(this + 0x19c) = uStack_54;
                    // Transform ray origin/direction
                    FUN_0056b480(&local_d0, this + 0xa0, this + 0xc0);
                    float fVar11 = *(float *)(this + 0xb0);
                    float fVar12 = *(float *)(this + 0xb4);
                    float fVar13 = *(float *)(this + 0xb8);
                    undefined4 uVar3 = *(undefined4 *)(this + 0xdc);
                    float *pfVar9 = (float *)(this + 0xd0);
                    *pfVar9 = fVar12 * local_c0 + fVar11 * local_d0 + fVar13 * local_b0;
                    *(float *)(this + 0xd4) = fVar12 * fStack_bc + fVar11 * fStack_cc + fVar13 * fStack_ac;
                    *(float *)(this + 0xd8) = fVar12 * fStack_b8 + fVar11 * fStack_c8 + fVar13 * fStack_a8;
                    *(float *)(this + 0xdc) = fVar12 * fStack_b4 + fVar11 * fStack_c4 + fVar13 * fStack_a4;
                    *(undefined4 *)(this + 0xdc) = uVar3;
                    // Normalize direction
                    fVar11 = *pfVar9;
                    fVar13 = fVar11 * fVar11 + *(float *)(this + 0xd4) * *(float *)(this + 0xd4) + *(float *)(this + 0xd8) * *(float *)(this + 0xd8);
                    fVar12 = fVar14;
                    if (DAT_00e2cbe0 < fVar13) {
                        fVar12 = DAT_00e2b1a4 / SQRT(fVar13);
                    }
                    *pfVar9 = fVar11 * fVar12;
                    *(float *)(this + 0xd4) = *(float *)(this + 0xd4) * fVar12;
                    *(float *)(this + 0xd8) = *(float *)(this + 0xd8) * fVar12;
                    *(float *)(this + 0xdc) = fVar14;
                    // Store hit object index
                    *(int *)(this + 0x18) = objectPtr;
                    // Update trace history
                    *(short *)(this + 0x49d08) = *(short *)(this + 0x49d0a);
                    *(short *)(this + 0x49d0a) = *(short *)(this + 0x49d0a) + 1;
                    *(int *)(this + 0x49d00) = objectPtr;
                    *(int *)(this + 0x49d10 + (uint)*(ushort *)(this + 0x49d08) * 4) = objectPtr;
                    // Call raycast against object
                    FUN_0066dd90(this + 0xc0, pfVar9);
                } else {
                    FUN_0066e580(); // skip or alternative
                }

                // Compute AABB test
                __m128 rayOrigin = *(__m128 *)(this + 0xc0);
                __m128 rayEnd = _mm_set_ps(
                    param_3 * *(float *)(this + 0xdc) + rayOrigin.m128_f32[3],
                    param_3 * *(float *)(this + 0xd8) + rayOrigin.m128_f32[2],
                    param_3 * *(float *)(this + 0xd4) + rayOrigin.m128_f32[1],
                    param_3 * *(float *)(this + 0xd0) + rayOrigin.m128_f32[0]
                );
                __m128 maxVec = _mm_max_ps(rayOrigin, rayEnd);
                __m128 minVec = _mm_min_ps(rayOrigin, rayEnd);

                // Get bounding box from object (type-specific)
                float *bbox = (float *)(*(int *)(param_1 + 0x58 + collisionType * 4) + arrayOffset);
                bool bVar7 = true;
                if ((maxVec.m128_f32[0] < bbox[0]) || (maxVec.m128_f32[1] < bbox[1]) || (maxVec.m128_f32[2] < bbox[2])) {
                    bVar7 = false;
                }
                if (((minVec.m128_f32[0] < bbox[4] || minVec.m128_f32[0] == bbox[4]) &&
                     (minVec.m128_f32[1] < bbox[5] || minVec.m128_f32[1] == bbox[5])) &&
                    ((minVec.m128_f32[2] < bbox[6] || minVec.m128_f32[2] == bbox[6]) && bVar7)) {
                    // Object intersects ray segment
                    uint local_f4 = -(uint)(*(char *)(objectPtr + 6) != '\0') & (uint)collisionType;
                    undefined4 *puVar4 = *(undefined4 **)(objectPtr + 100 + local_f4 * 4);
                    undefined4 local_104;
                    if (*(char *)(puVar4 + 7) == '\0') {
                        local_104 = puVar4[4];
                        *(undefined1 *)((int)puVar4 + 0x1d) = 1;
                    } else {
                        undefined4 local_108 = 0;
                        (**(code **)(*(int *)*puVar4 + 0x2c))((int *)*puVar4, 0, 0, &local_108, 0x10);
                        local_104 = local_108;
                    }
                    int local_10c = -1;
                    float local_fc = bestDistance;
                    char cVar8 = FUN_0066fae0(local_104, *(short *)(objectPtr + 0x3e), this + 0xc0,
                                              this + 0xd0, &local_10c, &local_fc, this + 0x49d00);
                    if ((cVar8 != '\0') && (local_fc < bestDistance)) {
                        bestDistance = local_fc;
                        bestHitIndex = local_10c;
                        bestHitType = objectIndex;
                    }
                    // Restore state
                    puVar4 = *(undefined4 **)(objectPtr + 100 + local_f4 * 4);
                    if (*(char *)(puVar4 + 7) == '\0') {
                        *(undefined1 *)((int)puVar4 + 0x1d) = 0;
                    } else {
                        (**(code **)(*(int *)*puVar4 + 0x30))((int *)*puVar4);
                    }
                    if (*(short *)(this + 0x49d0c) == 0x1000) break;
                }
            }
            objectOffset += 0xB0;
            arrayOffset += 0x20;
            objectIndex++;
        } while (objectIndex < (uint)objectCount);
    }
    *outDistance = bestDistance;
    *outHitIndex = bestHitIndex;
    *outHitType = bestHitType;
    return bestHitIndex != -1;
}