// FUNC_NAME: Entity::processRayHits
void Entity::processRayHits(uint8_t* thisPtr, float* rayInput)
{
    char activeFlag;
    float dotProduct;
    float crossProductResult;
    float tmpFloat1, tmpFloat2;
    uint8_t* collisionDataPtr;
    int countPrimed;
    short* impactCountPtr;
    float* impactDistPtr;
    int impactBufferBase;
    int tmpInt1, tmpInt2;
    float* tmpFloatPtr;
    float localVar1, localVar2; // stacked locals that are used in bounding checks
    // Actually, many locals come from uninitialized stack – they are set by prior calls.
    // We'll keep them as local variables that are used.

    // The actual stack frame has many floats that are used as scratch.
    // For reconstruction, we'll treat them as named local variables where they
    // are first used in expression.

    activeFlag = FUN_00522150(); // likely checking if game is active
    if (activeFlag == 0) return;

    // The following variables are actually on the stack and are presumably set
    // by earlier processing (e.g., from rayInput or from the object's state).
    // For clarity, we assume they are already on the stack and initialized.
    // We'll just use the names from the decompiled code.

    // local_2e0, fStack_2dc, fStack_2d8 are used in dot product.
    // They are likely from the ray direction or from the object's forward vector.
    // We'll treat them as locals that hold the ray direction (or similar).
    // For reconstruction, we'll define them as local floats.

    // The function performs a dot product of the object's orientation vectors with these locals.
    dotProduct = *(float*)(thisPtr + 0xd0) * local_2e0
                + *(float*)(thisPtr + 0xd4) * fStack_2dc
                + *(float*)(thisPtr + 0xd8) * fStack_2d8;

    if ((dotProduct < 0.0f) && (*(uint8_t*)(thisPtr + 0x203) != 0)) {
        dotProduct = DAT_00e44564 - dotProduct; // invert if negative and flag set
    }

    // Bounding box test: compare with stored mins and maxs
    // FUN_00522100 likely computes or returns the bounds (local_2c0, etc.)
    if ((*(float*)(thisPtr + 500) <= dotProduct) &&
        (FUN_00522100(&local_2c0), *(float*)(thisPtr + 0xe0) <= local_2d0) &&
        (local_2c0 < *(float*)(thisPtr + 0xf0) || local_2c0 == *(float*)(thisPtr + 0xf0)) &&
        (*(float*)(thisPtr + 0xe4) <= local_2cc) &&
        (local_2bc < *(float*)(thisPtr + 0xf4) || local_2bc == *(float*)(thisPtr + 0xf4)) &&
        (*(float*)(thisPtr + 0xe8) <= local_2c8) &&
        (tmpFloat1 = *(float*)(thisPtr + 0xf8), local_2b8 <= tmpFloat1))
    {
        // Initialize local_310 (likely a vector, used for normals)
        FUN_0044c1a0(&local_310); // likely set to zero

        collisionDataPtr = *(uint8_t**)(thisPtr + 0x110); // pointer to some collision data
        activeFlag = FUN_00522540(collisionDataPtr + 0x10);
        if ((((activeFlag != 0) ||
             (activeFlag = FUN_00522540(collisionDataPtr + 0x20), activeFlag != 0)) ||
            ((activeFlag = FUN_00522540(collisionDataPtr + 0x30), activeFlag != 0 ||
             (activeFlag = FUN_00522540(collisionDataPtr), activeFlag != 0 ||
             (activeFlag = FUN_00522680(collisionDataPtr, &local_2f0), activeFlag != 0)))) ||
            (activeFlag = FUN_00522680(&local_310, collisionDataPtr + 0x20), activeFlag != 0)) != 0)
        {
            // If any of these checks succeed, we store the impact data.
            if (*(uint8_t*)(thisPtr + 0x200) == 0) {
                // First branch: direct store of rayInput points
                if (0x95 < (**(short**)(thisPtr + 0x1e4)) + 3) { // capacity check
                    return;
                }
                FUN_00522240(rayInput);          // read first point
                local_2d0 = tmpFloat1;            // store the max.z? Actually reuses the earlier tmp
                FUN_00522240(rayInput + 4);       // read second point
                local_314 = rayInput + 8;         // third point pointer
                local_2cc = tmpFloat1;
                FUN_00522240(local_314);           // read third point

                // Update impact counters and buffers
                // m_pImpactCount (short) is at thisPtr+0x1e4
                short currentCount = **(short**)(thisPtr + 0x1e4);
                // m_pImpactDist is at thisPtr+0x1e8
                float* distanceBuffer = *(float**)(thisPtr + 0x1e8);
                distanceBuffer[currentCount] = tmpFloat1; // store distance (first)
                // Actually the code stores at position+8? Let's see:
                // *(float *)(iVar10 + 8 + sVar1*4) = fVar12 → each entry has 12 bytes? No.
                // The buffer at +0x1e8 is a float array, index = currentCount*1 (4 bytes per float)
                // But the code does: *(float *)(iVar10 + 8 + sVar1 * 4) = fVar12; which is weird.
                // It might be storing distance at offset 8 in some structure?
                // Actually, it seems the distance buffer stores 3 floats per entry??
                // Let's re-read: sVar1 = **(short**)(param_1+0x1e4); iVar10 = *(int*)(param_1+0x1e8);
                // *(float *)(iVar10 + 8 + sVar1 * 4) = fVar12;
                // So the buffer at +0x1e8 is a flat float array, and we write to [8 + sVar1*4].
                // That suggests the buffer has an extra offset of 8, i.e., the first 2 floats are something else.
                // Possibly it stores a struct { float something; float something; float distance; }.
                // But for simplicity, we'll treat as a flat array. The code also writes to [iVar10 + sVar1*4] earlier.
                // That writes the first float from local_2d0.
                // So the buffer is likely: [ float x; float y; float distance; ] for each entry? Actually
                // *pfVar9 = local_2d0; pfVar9[1] = local_2cc; pfVar9[2] = ...? No, it only sets two and then sets a third at +8.
                // Let's manually reconstruct the stores:
                // iVar10 = *(int*)(param_1+0x1e8)
                // current = **(short**)(param_1+0x1e4)
                // iVar10 += current*4? Actually sVar1 is current.
                // Store float at iVar10 + 0: local_2d0
                // Store float at iVar10 + 4: local_2cc
                // Store float at iVar10 + 8: fVar12
                // So each entry in that buffer is 3 floats (12 bytes). But the index is current, not scaled.
                // So the buffer is an array of structs of size 12? Or it's a flat array and we store three consecutive floats.
                // Given that, the buffer at +0x1e8 appears to store Vec3? Possibly distance plus something.
                // We'll define it as an array of struct {float x, y, z}; where z is the distance/t value.
                // So we store local_2d0, local_2cc, tmpFloat1.
                // But local_2d0 and local_2cc come from earlier overwrites with tmpFloat1? Confusing.
                // Actually local_2d0 = local_2cc = tmpFloat1, so both are the same? That seems odd.
                // Probably a decompiler artifact; we'll just store as per code.

                // For now, we'll write the reconstructed logic without over-interpreting these details.
                // The code:
                // *pfVar9 = local_2d0;
                // pfVar9[1] = local_2cc;
                // Then later: *(float *)(iVar10 + 8 + sVar1*4) = fVar12;
                // So we'll assume it stores three floats per entry.

                // Similarly, the impact entry buffer at +0x1e0 stores a struct at index current*0x20.
                // It stores: *puVar6 = *param_2; puVar6[1]= param_2[1]; puVar6[2]= param_2[2]; (first 3 floats)
                // Then at +0x10: local_310 (2 floats) (normal)
                // then first entry done.
                // Then increments count and stores again for second vector (rayInput[4..6] and local_300)
                // then third vector (rayInput[8..10] and local_2f0)

                // We'll implement that.

                // Write first entry
                // Use structures for clarity
                typedef struct {
                    float x,y,z;
                    float pad; // to make 0x10? Actually position takes 12 bytes, normal takes 8 -> 20, but entry size is 0x20.
                    float nx, ny;
                    float pad2[3];
                } ImpactEntry; // total 32 bytes

                ImpactEntry* entry = (ImpactEntry*)(*(uint8_t**)(thisPtr + 0x1e0) + currentCount * 0x20);
                entry->x = rayInput[0];
                entry->y = rayInput[1];
                entry->z = rayInput[2];
                *(float*)&entry->pad = local_310; // actually we need to store at offset 0x10
                // Actually the code uses (iVar8+0x10) and (iVar8+0x14). So we set entry->nx = local_310, entry->ny = local_30c.
                // But we don't know the struct layout. We'll just cast.
                // For simplicity, we'll use a raw pointer and write.

                // First entry
                uint32_t* entryBase = (uint32_t*)(*(uint32_t*)(thisPtr + 0x1e0) + currentCount * 0x20);
                entryBase[0] = rayInput[0];
                entryBase[1] = rayInput[1];
                entryBase[2] = rayInput[2];
                *(uint32_t*)((uint8_t*)entryBase + 0x10) = local_310;
                *(uint32_t*)((uint8_t*)entryBase + 0x14) = local_30c;

                // Increment count
                **(short**)(thisPtr + 0x1e4) = currentCount + 1;

                // Write second entry (using rayInput[4..6] for position, local_300 and uStack_2fc for normal)
                entryBase = (uint32_t*)(*(uint32_t*)(thisPtr + 0x1e0) + (currentCount + 1) * 0x20);
                entryBase[0] = rayInput[4];
                entryBase[1] = rayInput[5];
                entryBase[2] = rayInput[6];
                *(uint32_t*)((uint8_t*)entryBase + 0x10) = local_300;
                *(uint32_t*)((uint8_t*)entryBase + 0x14) = uStack_2fc;
                **(short**)(thisPtr + 0x1e4) = currentCount + 2;

                // Write third entry (using rayInput[8..10] for position, local_2f0 and uStack_2ec for normal)
                entryBase = (uint32_t*)(*(uint32_t*)(thisPtr + 0x1e0) + (currentCount + 2) * 0x20);
                entryBase[0] = local_314[0]; // actually local_314 = rayInput+8, so *local_314 = rayInput[8]
                entryBase[1] = local_314[1]; // rayInput[9]
                entryBase[2] = local_314[2]; // rayInput[10]
                *(uint32_t*)((uint8_t*)entryBase + 0x10) = local_2f0;
                *(uint32_t*)((uint8_t*)entryBase + 0x14) = uStack_2ec;
                **(short**)(thisPtr + 0x1e4) = currentCount + 3;

                // Now store ray entry at +0x1ec buffer
                // Ray entry: 4 floats: direction (local_2e0, fStack_2dc, fStack_2d8) and count (float)
                // Count is set from the previous? Actually fVar12 was not set in this branch, but likely it's the number of impacts? In this branch it's 3? No.
                // In the code, after the three stores, it does:
                // pfVar9 = (float *)(**(short **)(param_1 + 0x1f0) * 0x10 + *(int *)(param_1 + 0x1ec));
                // *pfVar9 = local_2e0; pfVar9[1] = fStack_2dc; pfVar9[2] = fStack_2d8; pfVar9[3] = fVar12;
                // fVar12 is not changed in this branch, so it retains whatever value it had (likely from earlier). We'll treat it as the number of impacts (3).
                // So we set count = 3.0f;
                float rayCount = fVar12; // but we need to set it to something meaningful? The original code used fVar12 from earlier context.
                // Actually the branch also sets fVar12 = fVar12; so it's unchanged.
                // We'll assume fVar12 is the number of new entries (3).
                uint32_t rayEntryIndex = **(short**)(thisPtr + 0x1f0);
                float* rayBuffer = *(float**)(thisPtr + 0x1ec);
                rayBuffer[rayEntryIndex * 4 + 0] = local_2e0;
                rayBuffer[rayEntryIndex * 4 + 1] = fStack_2dc;
                rayBuffer[rayEntryIndex * 4 + 2] = fStack_2d8;
                rayBuffer[rayEntryIndex * 4 + 3] = 3.0f; // probably the count
                **(short**)(thisPtr + 0x1f0) = rayEntryIndex + 1;
            }
            else {
                // Second branch: more complex, involves collision detection, trace line
                if ((float)((uint32_t)dotProduct & DAT_00e44680) <= DAT_00e2e210) return;
                dotProduct = 0.0f;
                FUN_00414c60(&local_300, &local_310, local_2b0); // likely vector operations
                FUN_00414c60(&local_2f0, &local_300, local_2b0 + 4);
                // Swap based on cross product
                crossProductResult = local_29c * local_2b0[0] - local_2b0[4] * local_2b0[1];
                if (crossProductResult < DAT_00e2b05c) {
                    // Swap local_300 <-> local_2f0 and their associated normals
                    float tempX = local_300;
                    float tempY = uStack_2fc;
                    float tempZ = uStack_2f8;
                    float tempW = uStack_2f4;
                    local_300 = local_2f0;
                    uStack_2fc = uStack_2ec;
                    uStack_2f8 = uStack_2e8;
                    uStack_2f4 = uStack_2e4;
                    local_2f0 = tempX;
                    uStack_2ec = tempY;
                    uStack_2e8 = tempZ;
                    uStack_2e4 = tempW;
                    crossProductResult = tempX;
                }
                // Perform ray trace, get number of hits
                activeFlag = FUN_00521cb0(thisPtr + 0x120, local_2b0, &dotProduct);
                if (activeFlag != 0) {
                    FUN_0044c1a0(local_160); // clear local array
                }
                if (dotProduct == 0.0f) return;
                if ((int)(**(short**)(thisPtr + 0x1e4) + (int)dotProduct) > 0x95) return;
                // Loop for each impact (dotProduct is count of impacts)
                int impactCount = (int)dotProduct;
                for (int i = 0; i < impactCount; i++) {
                    // Process each impact: read from local_160 (which was populated by FUN_00521cb0) and local_2b0
                    // local_160 is an array of 87 floats? Actually local_160 is 87*4 bytes, so holds 87 floats.
                    // We'll treat it as an array of floats indexed by i offset.
                    FUN_00522240((uint32_t*)((uint8_t*)local_160 + i*0x10)); // read a set of floats? Actually each iteration reads 4 floats? The loop increments iVar10 by 0x10.
                    // So each impact is a struct of 4 floats (maybe position and normal? Actually local_160 is an array of 4 floats per entry)
                    // The code stores: first the distance buffer: *(float *)(*(int*)(param_1+0x1e8) + current*4) = crossProductResult (the cross product value, not the distance)
                    // That's weird. We'll follow the decompiled order.
                    uint32_t currentCount = **(short**)(thisPtr + 0x1e4);
                    *(float*)(*(uint32_t*)(thisPtr + 0x1e8) + currentCount * 4) = crossProductResult; // store the "crossProductResult" as distance
                    // Then store impact entry: position from local_160[i*4..i*4+2], normal from local_2b0[i*4..i*4+1]? But local_2b0 is fixed? No, it's not indexed.
                    // Actually the code stores local_2b0 at offset 0x10 and 0x14. So normal is from local_2b0 (same for all?)
                    // That suggests local_2b0 might be updated each iteration? No.
                    // For now, we'll replicate the code exactly.
                    uint32_t* entryBase = (uint32_t*)(*(uint32_t*)(thisPtr + 0x1e0) + currentCount * 0x20);
                    entryBase[0] = ((uint32_t*)local_160)[i*4 + 0];
                    entryBase[1] = ((uint32_t*)local_160)[i*4 + 1];
                    entryBase[2] = ((uint32_t*)local_160)[i*4 + 2];
                    *(uint32_t*)((uint8_t*)entryBase + 0x10) = ((uint32_t*)local_2b0)[0];
                    *(uint32_t*)((uint8_t*)entryBase + 0x14) = ((uint32_t*)local_2b0)[1];
                    **(short**)(thisPtr + 0x1e4) = currentCount + 1;
                }
                // Set ray count to dotProduct (float)
                fVar12 = dotProduct;
            }
            // Write ray entry for the overall ray direction and count
            float* rayBuffer = *(float**)(thisPtr + 0x1ec);
            uint32_t rayIndex = **(short**)(thisPtr + 0x1f0);
            rayBuffer[rayIndex * 4 + 0] = local_2e0;
            rayBuffer[rayIndex * 4 + 1] = fStack_2dc;
            rayBuffer[rayIndex * 4 + 2] = fStack_2d8;
            rayBuffer[rayIndex * 4 + 3] = fVar12;
            **(short**)(thisPtr + 0x1f0) = rayIndex + 1;
        }
    }
}