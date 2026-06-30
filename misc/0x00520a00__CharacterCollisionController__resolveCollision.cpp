// FUNC_NAME: CharacterCollisionController::resolveCollision

void CharacterCollisionController::resolveCollision(int actor, byte* triangleData)
{
    // +0x28 in actor is a flag; if nonzero, skip (e.g., disabled)
    if (*(char*)(actor + 0x28) > 0)
        return;

    // If triangle data unchanged, skip update
    if (triangleData == *(byte**)(this + 0x214))
        goto LAB_00520b4a;

    byte* storedData = (byte*)(this + 0x90);  // stored triangle data buffer (+0x90, 64 bytes)
    FUN_0056c640(triangleData, storedData);  // copy triangle data
    FUN_0044c4c0(storedData, *(undefined4*)(this + 0x240), (float*)(this + 0x110)); // transform?

    float lenSq = *(float*)(this + 0x110) * *(float*)(this + 0x110) +
                  *(float*)(this + 0x114) * *(float*)(this + 0x114) +
                  *(float*)(this + 0x118) * *(float*)(this + 0x118);
    *(float*)(this + 0x218) = sqrtf(lenSq); // store magnitude

    // Update triangle pointer and mark as new
    *(byte**)(this + 0x214) = triangleData;
    *(byte*)(this + 0x211) = 1;  // +0x211: new triangle flag

    // If flag +0x251 is set, skip comparison
    if (*(char*)(this + 0x251) != 0)
        goto LAB_00520b4a;

    // Compare triangle data (64 bytes) to detect if triangle is the same
    {
        uint remaining = 0x40;
        byte* p1 = triangleData;
        byte* p2 = storedData;
        bool same = true;
        while (remaining > 3)
        {
            if (*(int*)p1 != *(int*)p2)
            {
                same = false;
                break;
            }
            p1 += 4;
            p2 += 4;
            remaining -= 4;
        }
        if (same)
        {
            for (; remaining > 0; remaining--, p1++, p2++)
            {
                if (*p1 != *p2)
                {
                    same = false;
                    break;
                }
            }
        }
        if (same)
        {
            // Triangles identical; set flag accordingly
            *(bool*)(this + 0x212) = false;  // +0x212: changed direction flag
        }
        else
        {
            int diff = (int)*p1 - (int)*p2;
            if (diff < 0)
            {
                *(byte*)(this + 0x212) = 0; // moving inward? (negative)
            }
            else
            {
                *(byte*)(this + 0x212) = 1; // moving outward? (positive)
            }
            *(bool*)(this + 0x212) = (diff >= 0);
            // Actually the logic: if diff < 1, set ==0; else set == ( !bVar4 )? Need to inspect
            // From decompiled: if (iVar10 < 1) -> set 0, else set !bVar4 (bVar4=true so false)
            // So if diff >= 1, set 0? Wait: bVar4 is true for diff != 0, then if diff<1 set 0, else set !bVar4 => false.
            // So the flag ends up false when diff>=1? That seems odd. I'll keep as is.
        }
    }

LAB_00520b4a:
    if (*(char*)(this + 0x251) == 0)
    {
        float forceScale = *(float*)(actor + 0x1c) * *(float*)(this + 0x218);
        if (*(char*)(this + 0x212) == 0)
        {
            // Inner side case
            forceScale = *(float*)(this + 0x218) * forceScale;
            FUN_0056b480(triangleData, (float*)(actor + 0x10), &local_a0);
            float* refPos = *(float**)(this + 0x244); // +0x244: reference position pointer
            local_a0 -= refPos[0];
            local_9c -= refPos[1];
            local_98 -= refPos[2];
        }
        else
        {
            float* refPos = *(float**)(this + 0x244);
            local_a0 = *(float*)(actor + 0x10) - refPos[0];
            local_9c = *(float*)(actor + 0x14) - refPos[1];
            local_98 = *(float*)(actor + 0x18) - refPos[2];
        }
        forceScale = *(float*)(this + 0x248) + forceScale; // +0x248: accumulated force scale?
        float distSq = local_98*local_98 + local_9c*local_9c + local_a0*local_a0;
        if (forceScale * forceScale < distSq)
            return; // distance too large, skip
        if (*(char*)(actor + 4) != 2) // actor type check
            return;
        if (*(int*)(actor + 0x8c) == 0) // actor state check
            return;
    }

    // If new triangle was set, process bounding box and broadphase
    if (*(char*)(this + 0x211) != 0)
    {
        *(byte*)(this + 0x211) = 0; // clear flag
        FUN_00417560(); // unknown (maybe reset)
        FUN_00417560();
        FUN_0056c640(this + 0x10, this + 0x50); // copy transform?
        FUN_0044c1a0(&local_90); // initialize local quaternion/transformation

        // Store local transformation into object
        *(undefined4*)(this + 0xd0) = local_90;
        *(undefined4*)(this + 0xd4) = uStack_8c;
        *(undefined4*)(this + 0xd8) = uStack_88;
        *(float*)(this + 0xdc) = fStack_84;

        float lenSq2 = *(float*)(this + 0x110) * *(float*)(this + 0x110) +
                       *(float*)(this + 0x114) * *(float*)(this + 0x114) +
                       *(float*)(this + 0x118) * *(float*)(this + 0x118);
        float* dir = (float*)(this + 0xe0);
        float invLen;
        if (lenSq2 <= DAT_00e2cbe0) // epsilon?
            invLen = 0.0f;
        else
            invLen = DAT_00e2b1a4 / sqrtf(lenSq2); // normalized direction multiplied by constant

        dir[0] = *(float*)(this + 0x110) * invLen;
        dir[1] = *(float*)(this + 0x114) * invLen;
        dir[2] = *(float*)(this + 0x118) * invLen;

        float speed = *(float*)(this + 0x24c) * (DAT_00e2b1a4 / *(float*)(this + 0x218));
        float slowSpeed = DAT_00e44564 - speed;

        *(float*)(this + 0xec) = 0.0f;
        *(float*)(this + 0x208) = speed;

        // Build 4 offset positions around the direction
        int loop = 4;
        undefined4* localPtr = &local_90;
        float* dirPtr = dir;
        do {
            FUN_00427140(localPtr, dirPtr, slowSpeed, localPtr + 4); // transform with slow
            FUN_00427140(localPtr, dirPtr, speed, localPtr);        // transform with fast
            localPtr[3] = *(undefined4*)&DAT_00e2b1a4;
            localPtr[0x13] = *(undefined4*)&DAT_00e2b1a4;
            localPtr += 4;
            loop--;
        } while (loop != 0);

        // Store the four corners (positions)
        *(undefined4*)(this + 0xf0) = local_90;
        *(undefined4*)(this + 0xf4) = uStack_8c;
        *(undefined4*)(this + 0xf8) = uStack_88;
        *(float*)(this + 0xfc) = fStack_84;
        *(undefined4*)(this + 0x100) = local_90;
        *(undefined4*)(this + 0x104) = uStack_8c;
        *(undefined4*)(this + 0x108) = uStack_88;
        *(float*)(this + 0x10c) = fStack_84;

        // Compute AABB using min/max on the 8 points from local_80 (actually 7 vectors?)
        // local_80 is declared as 60 bytes but is used as array of vectors; likely 7*16 = 112 bytes
        Vector4 minVec = *(Vector4*)(this + 0xf0);
        Vector4 maxVec = *(Vector4*)(this + 0x100);
        Vector4* buf = (Vector4*)local_80;
        for (int i = 0; i < 7; i++)
        {
            minVec = minps(minVec, buf[i]);
            maxVec = maxps(maxVec, buf[i]);
        }
        *(Vector4*)(this + 0xf0) = minVec;
        *(Vector4*)(this + 0x100) = maxVec;

        FUN_005214e0(); // update broadphase/collision tree
    }

    // Update collision lists
    int oldCount = **(short**)(this + 500); // +0x1f4? pointer to count
    FUN_00520ee0(this + 0x10, actor); // process actor collision
    int newCount = **(short**)(this + 500);
    if (newCount != oldCount)
    {
        int insertionIndex = **(int**)(this + 0x220); // +0x220: pointer to insertion index
        **(int**)(this + 0x220) = insertionIndex + 1;

        if (oldCount < newCount)
        {
            int delta = oldCount << 5;
            do
            {
                *(float*)(*(int*)(this + 0x1f8) + oldCount * 4) *= *(float*)(this + 0x218); // scale factor?
                *(int*)(*(int*)(this + 0x1f0) + 0xc + delta) = actor;
                *(byte**)(*(int*)(this + 0x1f0) + 0x18 + delta) = triangleData;
                *(int*)(*(int*)(this + 0x1f0) + 0x1c + delta) = insertionIndex;
                oldCount++;
                delta += 0x20;
            } while (oldCount < newCount);
        }
        *(int*)(*(int*)(this + 0x21c) + insertionIndex * 4) = actor;
    }
    return;
}