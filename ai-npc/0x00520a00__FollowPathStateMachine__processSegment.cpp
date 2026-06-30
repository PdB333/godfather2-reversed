// FUNC_NAME: FollowPathStateMachine::processSegment
void __thiscall FollowPathStateMachine::processSegment(PathSegment* path, const uint8_t* pathKey) {
    // +0x28 is a disabled flag in PathSegment
    if (path->disabled != 0) {
        return;
    }

    // +0x214 stores current path key pointer
    if (pathKey == m_currentPathKey) {
        goto LAB_00520b4a;
    }

    // +0x90 is a 64-byte path key buffer (16 dwords)
    uint8_t* keyBuf = reinterpret_cast<uint8_t*>(this) + 0x90;
    FUN_0056c640(pathKey, keyBuf); // copy path key into buffer

    // +0x240 is some matrix/transform, +0x110 is direction vector
    FUN_0044c4c0(keyBuf, *(void**)(this + 0x240), reinterpret_cast<float*>(this + 0x110));

    // Compute magnitude of direction vector and store at +0x218
    float dx = *(float*)(this + 0x110);
    float dy = *(float*)(this + 0x114);
    float dz = *(float*)(this + 0x118);
    *(float*)(this + 0x218) = sqrtf(dx * dx + dy * dy + dz * dz);

    m_currentPathKey = pathKey;
    *(uint8_t*)(this + 0x211) = 1; // flag: transform needs update

    if (*(uint8_t*)(this + 0x251) != 0) {
        goto LAB_00520b4a;
    }

    // Compare the new path key with the old one at +0x90 (byte by byte, 16 dwords)
    uint32_t remaining = 0x40; // 64 bytes in dword steps
    uint8_t* buf1 = keyBuf;
    const uint8_t* buf2 = pathKey;
    do {
        if (*(int32_t*)buf2 != *(int32_t*)buf1) {
            goto LAB_00520ac8;
        }
        remaining -= 4;
        buf1 += 4;
        buf2 += 4;
    } while (remaining > 3);

    if (remaining == 0) {
        // keys are equal
        bool equal = false; // bVar4
        goto LAB_00520b33;
    }

LAB_00520ac8:
    int32_t diff = (int32_t)*buf2 - (int32_t)*buf1;
    bool bLess;
    if (diff == 0) {
        if (remaining == 1) goto LAB_00520b33;
        diff = (int32_t)buf2[1] - (int32_t)buf1[1];
        if (diff == 0) {
            if (remaining == 2) goto LAB_00520b33;
            diff = (int32_t)buf2[2] - (int32_t)buf1[2];
            if (diff == 0) {
                if (remaining == 3) goto LAB_00520b33;
                diff = (int32_t)buf2[3] - (int32_t)buf1[3];
                if (diff == 0) goto LAB_00520b33;
            }
        }
    }
    bLess = (diff < 1) ? true : false; // actually diff < 1 means less? Usually memcmp returns negative/positive
    // Set flag at +0x212 based on comparison
    if (diff < 0) {
        *(uint8_t*)(this + 0x212) = 0;
        goto LAB_00520b4a;
    }
    *(uint8_t*)(this + 0x212) = 1;
    goto LAB_00520b4a;

LAB_00520b33:
    *(bool*)(this + 0x212) = false; // equal case

LAB_00520b4a:
    if (*(uint8_t*)(this + 0x251) == 0) {
        // +0x1c is speed scalar in PathSegment
        float speedScalar = *(float*)(path + 0x1c);
        float length = *(float*)(this + 0x218);
        float threshold = speedScalar * length;

        if (*(uint8_t*)(this + 0x212) == 0) {
            // path key is going forward? Use FUN_0056b480 to transform target point
            threshold = length * threshold;
            // +0x10 is target position in path segment
            float targetLocal[3];
            FUN_0056b480(pathKey, reinterpret_cast<float*>(path + 0x10), targetLocal);
            // +0x244 is pointer to current position (Vector3*)
            float* curPos = *(float**)(this + 0x244);
            targetLocal[0] -= curPos[0];
            targetLocal[1] -= curPos[1];
            targetLocal[2] -= curPos[2];
        } else {
            // path key is reversed, direct difference
            float* curPos = *(float**)(this + 0x244);
            float distX = *(float*)(path + 0x10) - curPos[0];
            float distY = *(float*)(path + 0x14) - curPos[1];
            float distZ = *(float*)(path + 0x18) - curPos[2];
            // actually stored as local_a0, local_9c, local_98
        }

        // +0x248 is an offset to add
        float offset = *(float*)(this + 0x248);
        float squaredDist = offset + threshold;
        squaredDist *= squaredDist; // compare with squared distance

        // Compute squared distance from above differences
        float diffSq = local_98 * local_98 + local_9c * local_9c + local_a0 * local_a0;
        if (squaredDist < diffSq) {
            return; // not close enough
        }

        // Check path segment type and validity
        if (*(uint8_t*)(path + 4) != 2) {
            return;
        }
        if (*(int32_t*)(path + 0x8c) == 0) {
            return;
        }
    }

    if (*(uint8_t*)(this + 0x211) != 0) {
        *(uint8_t*)(this + 0x211) = 0;
        // Play sound effects or something
        FUN_00417560(); // sound?
        FUN_00417560(); // sound?

        // Copy current transform from +0x10 to +0x50
        FUN_0056c640(this + 0x10, this + 0x50);

        // Get identity matrix? at local_90
        float identity[4]; // actually a 3x4? but used as 4 floats
        FUN_0044c1a0(&identity);

        // Store at +0xd0
        *(Vector4*)(this + 0xd0) = identity;

        // Compute direction vector length again
        float dirX = *(float*)(this + 0x110);
        float dirY = *(float*)(this + 0x114);
        float dirZ = *(float*)(this + 0x118);
        float magSq = dirX*dirX + dirY*dirY + dirZ*dirZ;
        float invMag;
        if (magSq <= DAT_00e2cbe0) {
            invMag = 0.0f;
        } else {
            invMag = DAT_00e2b1a4 / sqrtf(magSq); // speed constant
        }

        // Store normalized direction * speed at +0xe0 (velocity)
        float* velocity = reinterpret_cast<float*>(this + 0xe0);
        velocity[0] = dirX * invMag;
        velocity[1] = dirY * invMag;
        velocity[2] = dirZ * invMag;

        float speedFactor = *(float*)(this + 0x24c) * (DAT_00e2b1a4 / *(float*)(this + 0x218));
        float otherFactor = DAT_00e44564 - speedFactor;

        *(int32_t*)(this + 0xec) = 0;
        *(float*)(this + 0x208) = speedFactor; // store at +0x208

        // Calculate 4 corner points of a bounding box (or orientation vectors)
        Vector4 corners[8]; // not sure about size, but loop runs 4 times with +10 and +0 offsets
        Vector4* writePtr = &corners[4]; // +10 offset
        Vector4* writePtr2 = &corners[0]; // direct offset

        int iter = 4;
        do {
            FUN_00427140(&identity, velocity, otherFactor, writePtr);
            FUN_00427140(&identity, velocity, speedFactor, writePtr2);
            // set w component to constant
            writePtr2[3] = DAT_00e2b1a4;
            writePtr[3] = DAT_00e2b1a4;
            writePtr += 4;
            writePtr2 += 4;
            iter--;
        } while (iter != 0);

        // Store first set of 4 vectors at +0xf0 and +0x100 as min/max? Actually uses SSE min/max
        *(Vector4*)(this + 0xf0) = corners[0];
        *(Vector4*)(this + 0xf4) = corners[1];
        *(Vector4*)(this + 0xf8) = corners[2];
        *(float*)(this + 0xfc) = corners[3].w;
        *(Vector4*)(this + 0x100) = corners[4];
        *(Vector4*)(this + 0x104) = corners[5];
        *(Vector4*)(this + 0x108) = corners[6];
        *(float*)(this + 0x10c) = corners[7].w;

        // Now compute min/max across all 8 points (0..7) using SSE
        Vector4 minVec = *(Vector4*)(this + 0xf0);
        Vector4 maxVec = *(Vector4*)(this + 0x100);
        float* points = reinterpret_cast<float*>(local_80); // 60 bytes? Actually 15 floats? Possibly 8*4=32 bytes?
        // The code reads 8 vectors from local_80? But local_80 is 60 bytes, that's 15 floats. Inconsistent.
        // We'll just replicate the SSE min/max logic.
        for (int i = 0; i < 7; ++i) {
            Vector4 cur = *(Vector4*)(points + i*16);
            // SSE minps and maxps on each component
            minVec = _mm_min_ps(minVec, cur);
            maxVec = _mm_max_ps(maxVec, cur);
        }
        *(Vector4*)(this + 0xf0) = minVec;
        *(Vector4*)(this + 0x100) = maxVec;

        FUN_005214e0(); // update something
    }

    // Get current count of waypoints from +500 (pointer to short)
    int oldCount = **(short**)(this + 500);
    // Call another method to possibly add waypoint
    FUN_00520ee0(this + 0x10, path);

    // If count changed, store new entry
    if (**(short**)(this + 500) != oldCount) {
        int newCount = **(short**)(this + 500);
        int index = **(int**)(this + 0x220); // current index
        **(int**)(this + 0x220) = index + 1;

        if (oldCount < newCount) {
            int stride = oldCount * 0x20;
            for (int i = oldCount; i < newCount; ++i) {
                // +0x1f8 is array of floats, scale by length
                *(float*)(*(int*)(this + 0x1f8) + i * 4) *= *(float*)(this + 0x218);
                // +0x1f0 is array of 0x20-byte struct
                // at +0x0c: path pointer
                *(int*)(*(int*)(this + 0x1f0) + 0x0c + stride) = (int)path;
                // at +0x18: pathKey
                *(const uint8_t**)(*(int*)(this + 0x1f0) + 0x18 + stride) = pathKey;
                // at +0x1c: index
                *(int*)(*(int*)(this + 0x1f0) + 0x1c + stride) = index;
                stride += 0x20;
            }
        }
        // +0x21c is array of path pointers indexed by index
        *(int*)(*(int*)(this + 0x21c) + index * 4) = (int)path;
    }
}