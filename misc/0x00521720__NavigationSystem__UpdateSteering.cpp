// FUNC_NAME: NavigationSystem::UpdateSteering
void NavigationSystem::UpdateSteering(float* thisptr, Vector3* inputPath) {
    char isEnabled;
    float dotProduct;
    float swapped;
    float tempFloat;
    float distResult;
    float fVar11;
    float fVar12;
    Vector3 normal;
    Vector3 pos;
    Vector3 box;
    Vector3 rayHit;
    Vector3 cross[2]; // actually 2 vectors stored in local_2b0[5], but use two Vec3

    isEnabled = FUN_00522150();
    if (!isEnabled) return;

    // Compute dot product of direction vector at +0xd0 with some stack vars (likely from input)
    dotProduct = thisptr[0xD0/4] * local_2e0 + thisptr[0xD4/4] * fStack_2dc + thisptr[0xD8/4] * fStack_2d8;
    if ((dotProduct < 0.0f) && (thisptr[0x203] != 0)) {
        dotProduct = DAT_00e44564 - dotProduct;
    }

    // Get bounding box info (FUN_00522100 likely fills local_2d0, local_2cc, local_2c8, local_2c0, etc.)
    FUN_00522100(&box);
    if ((thisptr[0x1F4/4] <= dotProduct) && // some threshold at +0x1F4? Wait offset 500 = 0x1F4
        (thisptr[0xE0/4] <= box.x) && // minX
        (box.x < thisptr[0xF0/4] || box.x == thisptr[0xF0/4]) && // maxX
        (thisptr[0xE4/4] <= box.y) &&
        (box.y < thisptr[0xF4/4] || box.y == thisptr[0xF4/4]) &&
        (thisptr[0xE8/4] <= box.z) &&
        (box.z <= thisptr[0xF8/4])) {

        // Initialize output struct? (FUN_0044c1a0 probably sets to identity/zero)
        FUN_0044c1a0(&normal);

        int ptr = thisptr[0x110/4];
        // Check various conditions on the data at +0x110
        if (FUN_00522540(ptr + 0x10) ||
            FUN_00522540(ptr + 0x20) ||
            FUN_00522540(ptr + 0x30) ||
            FUN_00522540(ptr) ||
            FUN_00522680(ptr, &pos) ||
            FUN_00522680(&normal, ptr + 0x20)) {
            // Condition succeeded

            if (thisptr[0x200] == 0) {
                // Static path input (no avoidance)
                short* index = (short*)(thisptr[0x1E4/4]);
                if (*index + 3 > 0x95) return;

                FUN_00522240(inputPath);      // copy first point
                box.x = fVar12;               // store back? fVar12 from earlier? Actually fVar12 was set at end of previous block? This is messy
                FUN_00522240(inputPath + 1);  // copy second point
                FUN_00522240(inputPath + 2);  // copy third point

                // Store into ring buffers
                short idx = *index;
                int floatArray = thisptr[0x1E8/4];
                *(float*)(floatArray + 8 + idx*4) = fVar12; // some float
                *(float*)(floatArray + idx*4) = box.x;
                *(float*)(floatArray + idx*4 + 4) = box.y;

                int vtxArray = thisptr[0x1E0/4] + idx * 0x20;
                *(Vector3*)vtxArray = *inputPath; // copy position
                *(Vector3*)(vtxArray + 0x10) = normal; // copy normal

                (*index)++;

                // Second vertex (next index)
                idx = *index;
                vtxArray = thisptr[0x1E0/4] + idx * 0x20;
                *(Vector3*)vtxArray = *(Vector3*)(inputPath + 4); // inputPath[4..6]
                *(Vector3*)(vtxArray + 0x10) = *(Vector3*)&local_300; // some other vec
                (*index)++;

                // Third vertex
                idx = *index;
                vtxArray = thisptr[0x1E0/4] + idx * 0x20;
                *(Vector3*)vtxArray = *(Vector3*)(inputPath + 8); // inputPath[8..10]
                *(Vector3*)(vtxArray + 0x10) = pos; // the pos from earlier
                (*index)++;

                // Store result direction (local_2e0, fStack_2dc, fStack_2d8) and distance
                int dirArray = thisptr[0x1EC/4];
                short dirIndex = *(short*)(thisptr[0x1F0/4]);
                *(Vector3*)(dirArray + dirIndex * 0x10) = *(Vector3*)(thisptr + 0x2E0/4? no, local_2e0 is stack variable)
                Actually the decompiled uses local_2e0, fStack_2dc, fStack_2d8 - these are local vars.
                // At end of function it writes: pfVar9 = (float *)(**(short **)(param_1 + 0x1f0) * 0x10 + *(int *)(param_1 + 0x1ec));
                // *pfVar9 = local_2e0; pfVar9[1] = fStack_2dc; pfVar9[2] = fStack_2d8; pfVar9[3] = fVar12;
                // So it stores direction and distance
                int dirBase = thisptr[0x1EC/4];
                short dirIdx = *(short*)(thisptr[0x1F0/4]);
                float* dirSlot = (float*)(dirBase + dirIdx * 0x10);
                dirSlot[0] = local_2e0;
                dirSlot[1] = fStack_2dc;
                dirSlot[2] = fStack_2d8;
                dirSlot[3] = fVar12;
                (*(short*)(thisptr[0x1F0/4]))++;
            }
            else {
                // Dynamic path input with obstacle avoidance
                float bitcheck = *((uint*)&dotProduct) & *((uint*)&DAT_00e44680);
                if (bitcheck <= DAT_00e2e210) return;

                dotProduct = 0.0f;
                // Compute cross products for avoidance
                FUN_00414c60(&local_300, &normal, (float*)cross); // cross1
                FUN_00414c60(&pos, &local_300, (float*)cross + 4); // cross2

                // Possibly swap if dot product negative
                swapped = cross[0].x * local_29c - cross[0].y * cross[1].x; // local_29c is from local_2b0[4]? Actually local_2b0[4] = local_29c
                if (swapped < DAT_00e2b05c) {
                    // Swap the two vectors
                    Vector3 temp = local_300;
                    local_300 = pos;
                    pos = temp;
                    swapped = pos.x; // fVar11 = fVar12 earlier? Actually fVar11 = local_300? This is messy
                }

                // Raycast or collision detection
                char hit = FUN_00521cb0(thisptr + 0x120/4, (float*)cross, &dotProduct);
                fVar12 = dotProduct;
                if (hit) {
                    FUN_0044c1a0((undefined4*)local_160); // zero out buffer
                }
                if (fVar12 == 0.0f) return;

                short* index = (short*)(thisptr[0x1E4/4]);
                if ((*index + (int)fVar12) > 0x95) return;

                // Copy multiple points from raycast result
                int count = (int)fVar12;
                int i = 0;
                do {
                    FUN_00522240((Vector3*)((int)local_160 + i)); // copy point
                    // Store into buffers
                    int floatArray = thisptr[0x1E8/4];
                    *(float*)(floatArray + (*index)*4) = swapped; // store distance?
                    int vtxArray = thisptr[0x1E0/4] + (*index)*0x20;
                    *(Vector3*)vtxArray = *(Vector3*)((int)local_160 + i);
                    *(Vector3*)(vtxArray + 0x10) = *(Vector3*)((int)cross + i);
                    (*index)++;
                    count--;
                    i += 0x10;
                } while (count > 0);

                fVar12 = (float)(int)fVar12; // convert back to float
            }

            // Store final direction and count
            int dirBase = thisptr[0x1EC/4];
            short dirIdx = *(short*)(thisptr[0x1F0/4]);
            float* dirSlot = (float*)(dirBase + dirIdx * 0x10);
            dirSlot[0] = local_2e0; // direction x
            dirSlot[1] = fStack_2dc; // direction y
            dirSlot[2] = fStack_2d8; // direction z
            dirSlot[3] = fVar12; // distance or count
            (*(short*)(thisptr[0x1F0/4]))++;
        }
    }
}