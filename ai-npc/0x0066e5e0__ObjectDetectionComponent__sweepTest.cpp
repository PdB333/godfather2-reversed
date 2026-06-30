// FUNC_NAME: ObjectDetectionComponent::sweepTest
bool ObjectDetectionComponent::sweepTest(int entityList, float travelDistance, float& outClosestDistance, int& outClosestEntityIndex, uint& outClosestSubIndex)
{
    if (*(short*)(this + 0x49d0c) == 0x1000) {
        return false;
    }

    int bestEntityIndex = -1;
    uint bestSubIndex = 0xFFFFFFFF;
    byte bVar2 = *(byte*)(entityList + 0x2d); // some selector byte
    float closestDistance = travelDistance;
    uint entityIter = 0;

    if (*(int*)(entityList + 0x34) != 0) {
        int offsetEntity = 0; // offset into entity data array (stride 0x20)
        int offsetEntity2 = 0; // offset into second entity array (stride 0xb0)
        do {
            int entityPtr = *(int*)(entityList + 0x50) + offsetEntity2; // pointer to entity structure (0xb0 size)
            float fVar14 = 0.0f;
            if ((*(char*)(entityPtr + 4) == 0x01) && ((*(uint*)(entityPtr + 8) & 0x4000) == 0)) {
                if (*(char*)(entityPtr + 6) == 0) {
                    FUN_00417560(); // likely push matrix / push context
                }
                char cVar8 = FUN_004166b0(); // some condition, possibly "can collide" or "is active"
                if ((*(int*)(this + 0x18) == 0) || (cVar8 != 0)) {
                    // Transform current position and orientation
                    FUN_0056c640(this + 0x60, &local_d0); // get transformation matrix at +0x60
                    FUN_00417560(); // pop matrix?
                    FUN_00417560(); // ?
                    // Store 4x4 matrix at this+0x160 (rotation part)
                    *(undefined4*)(this + 0x160) = local_90;
                    *(undefined4*)(this + 0x164) = uStack_8c;
                    // ... (similar for columns)
                    *(undefined4*)(this + 0x19c) = uStack_54;
                    // Convert transformation to orientation and compute velocity
                    FUN_0056b480(&local_d0, this + 0xa0, this + 0xc0); // computes local axes and velocity?
                    float f11 = *(float*)(this + 0xb0);
                    float f12 = *(float*)(this + 0xb4);
                    float f13 = *(float*)(this + 0xb8);
                    uint uVar3 = *(uint*)(this + 0xdc);
                    float* pfVar9 = (float*)(this + 0xd0);
                    // Transform velocity by orientation
                    *pfVar9 = f12 * local_c0 + f11 * local_d0 + f13 * local_b0;
                    *(float*)(this + 0xd4) = f12 * fStack_bc + f11 * fStack_cc + f13 * fStack_ac;
                    *(float*)(this + 0xd8) = f12 * fStack_b8 + f11 * fStack_c8 + f13 * fStack_a8;
                    *(float*)(this + 0xdc) = f12 * fStack_b4 + f11 * fStack_c4 + f13 * fStack_a4;
                    *(uint*)(this + 0xdc) = uVar3;
                    // Normalize velocity to length with safe division
                    float velLen = *pfVar9 * *pfVar9 + *(float*)(this + 0xd4) * *(float*)(this + 0xd4) + *(float*)(this + 0xd8) * *(float*)(this + 0xd8);
                    float scale = fVar14; // 0
                    if (DAT_00e2cbe0 < velLen) {
                        scale = DAT_00e2b1a4 / SQRT(velLen);
                    }
                    *pfVar9 *= scale;
                    *(float*)(this + 0xd4) *= scale;
                    *(float*)(this + 0xd8) *= scale;
                    *(float*)(this + 0xdc) = fVar14; // set w to 0
                    // Store current entity pointer
                    *(int*)(this + 0x18) = entityPtr;
                    // Update history
                    *(short*)(this + 0x49d08) = *(short*)(this + 0x49d0a);
                    *(short*)(this + 0x49d0a) = *(short*)(this + 0x49d0a) + 1;
                    *(int*)(this + 0x49d00) = entityPtr;
                    *(int*)(this + 0x49d10 + (uint)*(ushort*)(this + 0x49d08) * 4) = entityPtr;
                    // Recompute final transformed position (maybe for swept AABB)
                    FUN_0066dd90(this + 0xc0, pfVar9); // some compute that uses velocity
                } else {
                    FUN_0066e580(); // skip or early out
                }
                // Swept AABB test: compute min/max of original and swept positions
                __m128 originalAABB = *(__m128*)(this + 0xc0); // AABB min/max? Actually it's four floats (x,y,z,w)?
                __m128 sweptPos = _mm_set_ps(travelDistance * *(float*)(this + 0xdc) + ((float*)&originalAABB)[3],
                                              travelDistance * *(float*)(this + 0xd8) + ((float*)&originalAABB)[2],
                                              travelDistance * *(float*)(this + 0xd4) + ((float*)&originalAABB)[1],
                                              travelDistance * *(float*)(this + 0xd0) + ((float*)&originalAABB)[0]);
                __m128 maxBox = _mm_max_ps(originalAABB, sweptPos);
                __m128 minBox = _mm_min_ps(originalAABB, sweptPos);
                // Check against entity's AABB (stored at offset in a different format?)
                float* entityAABB = (float*)(*(int*)(entityList + 0x58 + (uint)bVar2 * 4) + offsetEntity);
                if ((maxBox.m128_f32[0] >= entityAABB[0]) &&
                    (maxBox.m128_f32[1] >= entityAABB[1]) &&
                    (maxBox.m128_f32[2] >= entityAABB[2]) &&
                    (minBox.m128_f32[0] <= entityAABB[4] || minBox.m128_f32[0] == entityAABB[4]) &&
                    (minBox.m128_f32[1] <= entityAABB[5] || minBox.m128_f32[1] == entityAABB[5]) &&
                    (minBox.m128_f32[2] <= entityAABB[6] || minBox.m128_f32[2] == entityAABB[6])) {
                    // Perform precise ray intersection
                    uint collisionOffset = (entityPtr + 100 + local_f4 * 4); // entity collision data
                    uint collisionPtr = *(uint*)collisionOffset;
                    uint hitData;
                    if (*(char*)(collisionPtr + 7) == 0) {
                        hitData = *(uint*)(collisionPtr + 4); // direct data
                        *(char*)(collisionPtr + 0x1d) = 1; // mark as testing
                    } else {
                        uint local_108 = 0;
                        (**(code**)(*(int*)*collisionPtr + 0x2c))((int*)*collisionPtr, 0, 0, &local_108, 0x10); // vtable call to get collision data
                        hitData = local_108;
                    }
                    int hitSubIndex = -1;
                    float hitDistance = closestDistance;
                    bool hit = FUN_0066fae0(hitData, *(short*)(entityPtr + 0x3e), this + 0xc0, this + 0xd0, &hitSubIndex, &hitDistance, this + 0x49d00);
                    if (hit && (hitDistance < closestDistance)) {
                        closestDistance = hitDistance;
                        bestEntityIndex = hitSubIndex;
                        bestSubIndex = local_11c;
                    }
                    // Restore collision testing state
                    uint collisionPtr2 = *(uint*)collisionOffset;
                    if (*(char*)(collisionPtr2 + 7) == 0) {
                        *(char*)(collisionPtr2 + 0x1d) = 0;
                    } else {
                        (**(code**)(*(int*)*collisionPtr2 + 0x30))((int*)*collisionPtr2); // vtable call to end test
                    }
                    if (*(short*)(this + 0x49d0c) == 0x1000) break;
                }
            }
            offsetEntity2 += 0xb0; // next entity
            offsetEntity += 0x20; // next AABB block
            entityIter++;
        } while (entityIter < *(uint*)(entityList + 0x34));
    }

    outClosestDistance = closestDistance;
    outClosestEntityIndex = bestEntityIndex;
    outClosestSubIndex = bestSubIndex;
    return bestEntityIndex != -1;
}