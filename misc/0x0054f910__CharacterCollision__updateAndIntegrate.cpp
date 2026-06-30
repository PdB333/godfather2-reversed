// FUNC_NAME: CharacterCollision::updateAndIntegrate
void __thiscall CharacterCollision::updateAndIntegrate(float deltaTime) {
    // this->unknownFlag +0xe8: if non-zero, skip complex collision and just integrate position directly
    if (*(int*)(this + 0xe8) != 0) {
        // Simple path: just update movement state and integrate position
        int* movementState = *(int**)(this + 0x14);
        float vx = *(float*)(this + 0x64); // +0x64 velocity x
        float vy = *(float*)(this + 0x68); // +0x68 velocity y
        float vz = *(float*)(this + 0x6c); // +0x6c velocity z
        float vw = *(float*)(this + 0x70); // +0x70 velocity w (unused?)
        movementState[0x10/sizeof(float)] = vx; // +0x10 in movementState struct
        movementState[0x14/sizeof(float)] = vy;
        movementState[0x18/sizeof(float)] = vz;
        movementState[0x1c/sizeof(float)] = vw;

        int* physicsState = *(int**)(*(int*)(this + 0x14) + 0x30);
        if (physicsState) {
            physicsState = *(int**)(physicsState + 0x18);
            float newX = vx * deltaTime + *(float*)(physicsState + 0x30);
            float newY = vy * deltaTime + *(float*)(physicsState + 0x34);
            float newZ = vz * deltaTime + *(float*)(physicsState + 0x38);
            float newW = *(float*)(physicsState + 0x3c) + deltaTime;
            setPosition(&newX, 0); // FUN_009f1820
        }
        return;
    }

    // Profiling marker: LtCheater Character Collision (start)
    void* tlsData = TlsGetValue(*(int*)0x01139830);
    int* profileBuffer = *(int**)((int)tlsData + 4);
    if (profileBuffer < *(int**)((int)tlsData + 0xc)) {
        *profileBuffer = "LtCheater Character Collision";
        profileBuffer[3] = "StPre Cheap Cast";
        unsigned long long timer = rdtsc();
        *(int*)&timer = timer; // uStack_d4
        profileBuffer[1] = timer;
        *(int**)((int)tlsData + 4) = profileBuffer + 4;
    }

    // Copy velocities from this
    float velX = *(float*)(this + 100); // +0x64? Actually offset 0x64 is velocity, but decomp shows (this+100) which is 0x64? Wait 100 decimal = 0x64? Yes.
    float velY = *(float*)(this + 0x68); // 104 decimal = 0x68
    float velZ = *(float*)(this + 0x6c); // 108 decimal = 0x6c
    float velW = 0.0f; // default zero for w

    // Check bit 0 of flag at +0xe4
    if ((*(byte*)(this + 0xe4) & 1) == 0) {
        // Adjust velocities by some offset from movement state (likely external forces)
        adjustVelocities(deltaTime); // FUN_0054efb0
        velY += *(float*)(this + 0x74);
        velX += *(float*)(this + 0x70);
        velZ += *(float*)(this + 0x78);
        velW = *(float*)(this + 0x7c);
    }

    float displacementX, displacementY, displacementZ, displacementW;
    // Check bit 8 of flag at +0xe4
    if ((*(uint*)(this + 0xe4) >> 8 & 1) == 0) {
        displacementX = velX * deltaTime;
        displacementY = velY * deltaTime;
        displacementZ = velZ * deltaTime;
        displacementW = velW * deltaTime;
    } else {
        displacementX = 0.0f;
        displacementY = 0.0f;
        displacementZ = 0.0f;
        displacementW = 0.0f;
    }

    // Setup for collision cast
    int hitObjectIndex = -1; // uStack_5c
    int hitGeometryIndex = -1; // uStack_50
    int somethingId = *(int*)DAT_00e2b1a4; // uStack_60
    int contactCount = 0; // uStack_30
    int castResult = 0; // iStack_20
    float castDistance = 0.0f; // fStack_dc (used as distance or something)
    int hitMask = 0; // uStack_b4
    int hitFlags = 0; // uStack_d4

    // Perform collision cast: FUN_0054d3e0 with many parameters
    int* physicsManager = *(int**)(*(int*)(this + 0x14) + 0x30);
    castResult = segmentCast(physicsManager, &castStartPos, &castDistance, &contactNormal, &hitMask, &hitFlags); // FUN_0054d3e0
    // Actually FUN_0054d3e0 takes: (ptr to some object, output contact normal?, output castDistance?, output contactNormal array?,
    //   output hitMask?, output hitFlags?). The decomp shows many stack variables: &fStack_70, &fStack_dc, auStack_9f, &uStack_b4, &uStack_d4.

    // Profiling marker: StPost Cheap Cast
    void* tlsData2 = TlsGetValue(*(int*)0x01139830);
    int* profileBuffer2 = *(int**)((int)tlsData2 + 4);
    if (profileBuffer2 < *(int**)((int)tlsData2 + 0xc)) {
        *profileBuffer2 = "StPost Cheap Cast";
        unsigned long long timer2 = rdtsc();
        *(LPVOID*)&timer2 = (LPVOID)timer2;
        profileBuffer2[1] = timer2;
        *(int**)((int)tlsData2 + 4) = profileBuffer2 + 3;
    }

    float contactNormalX, contactNormalY, contactNormalZ, contactNormalW;
    byte contactFlags[2];
    if (castResult == 0) {
        // No collision: use stored previous position from this (offset 0x90)
        contactNormalX = *(float*)(this + 0x90);
        contactNormalY = *(float*)(this + 0x94);
        contactNormalZ = *(float*)(this + 0x98);
        contactNormalW = *(float*)(this + 0x9c);
        contactFlags[0] = 0;
        contactFlags[1] = 0;
        hitMask = 0; // iVar11? Actually hitMask remains 0
    } else {
        // Collision detected: use cast output (fStack_70, etc)
        contactNormalX = fStack_70;
        contactNormalY = fStack_6c;
        contactNormalZ = fStack_68;
        contactFlags[0] = 1;
        contactNormalW = uStack_64;
        hitMask = resolveCollisionContact(castResult); // FUN_004afca0
        if (hitMask == 0) {
            // Use object callback to get material/type
            int* materialInfo = getMaterialInfoFromHit(castResult); // FUN_0054c0e0
            somethingId = *materialInfo;
        } else {
            // Use environment callback
            int* envInfo = getEnvironmentInfo(); // FUN_00421430
            somethingId = *envInfo;
        }
    }

    // Set tangent vectors to default values (DAT_01139820 etc)
    float tangentX = *(float*)0x01139820;
    float tangentY = *(float*)0x01139824;
    float tangentZ = *(float*)0x01139828;
    float tangentW = *(float*)0x0113982c;

    // If position control flag is set (bit 8 again), apply the result directly to this
    if ((*(uint*)(this + 0xe4) >> 8 & 1) != 0) {
        // Apply collision contact info to this
        *(byte*)(this + 0x30) = contactFlags[0];
        *(byte*)(this + 0x31) = contactFlags[1];
        *(float*)(this + 0x40) = contactNormalX;
        *(float*)(this + 0x44) = contactNormalY;
        *(float*)(this + 0x48) = contactNormalZ;
        *(float*)(this + 0x4c) = contactNormalW;
        *(float*)(this + 0x50) = tangentX;
        *(float*)(this + 0x54) = tangentY;
        *(float*)(this + 0x58) = tangentZ;
        *(float*)(this + 0x5c) = tangentW;
        *(int*)(this + 0xd0) = hitFlags;
        *(int*)(this + 0xcc) = hitMask;
        *(float*)(this + 0x60) = somethingId; // Or uVar13?
        onContactResolved(hitMask); // FUN_0044b210
    }

    // Compute dot product of contact normal with previous stored contact normal
    float dotProduct = *(float*)(this + 0x90) * contactNormalX +
                       *(float*)(this + 0x94) * contactNormalY +
                       *(float*)(this + 0x98) * contactNormalZ;

    if (dotProduct > *(float*)DAT_00e2cd54) {
        // Object is moving away from surface: do not snap or set grounded
        if (*(int*)(this + 0xa4) == 0) {
            *(int*)(this + 0xa4) = *(int*)DAT_01205224; // Probably true flag
        }
    } else {
        // Object is moving towards surface: apply ground snap and integrate position
        int* movementState = *(int**)(this + 0x14);
        // Store final velocities into movement state
        *(float*)(movementState + 0x10/sizeof(float)) = velX;
        *(float*)(movementState + 0x14/sizeof(float)) = velY;
        *(float*)(movementState + 0x18/sizeof(float)) = velZ;
        *(float*)(movementState + 0x1c/sizeof(float)) = velW;

        // Get physics state from movement state
        int* physicsState = *(int**)(*(int*)(this + 0x14) + 0x30);
        if (physicsState != 0) {
            physicsState = *(int**)(physicsState + 0x18);
            // Compute new position with velocities and current position
            float newX = velX * deltaTime + *(float*)(physicsState + 0x30);
            float newY = velY * deltaTime + *(float*)(physicsState + 0x34);
            float newZ = velZ * deltaTime + *(float*)(physicsState + 0x38);
            float newW = velW * deltaTime + *(float*)(physicsState + 0x3c);

            if ((castResult != 0) && ((*(byte*)(this + 0xe4) & 1) == 0)) {
                // Override Y displacement with cast distance (snap to ground)
                newY = castDistance; // fStack_dc (the cast distance/height)
            }

            // Profiling marker: StSet position
            void* tlsData3 = TlsGetValue(*(int*)0x01139830);
            int* profileBuffer3 = *(int**)((int)tlsData3 + 4);
            if (profileBuffer3 < *(int**)((int)tlsData3 + 0xc)) {
                *profileBuffer3 = "StSet position";
                unsigned long long timer3 = rdtsc();
                *(float*)&timer3 = (float)timer3;
                profileBuffer3[1] = timer3;
                *(int**)((int)tlsData3 + 4) = profileBuffer3 + 3;
            }

            // Apply the new position
            setPosition(&newX, 0); // FUN_009f1820

            // Store contact info back to this
            *(byte*)(this + 0x30) = contactFlags[0];
            *(byte*)(this + 0x31) = contactFlags[1];
            *(float*)(this + 0x40) = contactNormalX;
            *(float*)(this + 0x44) = contactNormalY;
            *(float*)(this + 0x48) = contactNormalZ;
            *(float*)(this + 0x4c) = contactNormalW;
            *(float*)(this + 0x50) = tangentX;
            *(float*)(this + 0x54) = tangentY;
            *(float*)(this + 0x58) = tangentZ;
            *(float*)(this + 0x5c) = tangentW;
            *(int*)(this + 0xcc) = hitMask;
            *(int*)(this + 0xd0) = hitFlags;
            *(float*)(this + 0x60) = somethingId;
            onContactResolved(hitMask); // FUN_0044b210

            // Clear grounded flag
            *(int*)(this + 0xa4) = 0;
        }
    }

    // Update grounded flag based on contact flag at +0x30
    if (*(char*)(this + 0x30) == 0) {
        // Not grounded
        if (*(int*)(this + 0xb0) == 0) {
            *(int*)(this + 0xb0) = *(int*)DAT_01205224; // Set something
        }
    } else {
        // Grounded
        *(int*)(this + 0xb0) = 0;
    }

    // If bit 9 of flag at +0xe4 is set, do additional finalization
    if ((*(uint*)(this + 0xe4) >> 9 & 1) != 0) {
        finalizeCollisionStep(); // FUN_0054f520
    }

    // Clear bit 8
    *(uint*)(this + 0xe4) = *(uint*)(this + 0xe4) & 0xfffffeff;

    // Profiling marker: End
    void* tlsDataEnd = TlsGetValue(*(int*)0x01139830);
    int* profileBufferEnd = *(int**)((int)tlsDataEnd + 4);
    if (profileBufferEnd < *(int**)((int)tlsDataEnd + 0xc)) {
        *profileBufferEnd = "End Character Collision";
        unsigned long long timerEnd = rdtsc();
        profileBufferEnd[1] = timerEnd;
        *(int**)((int)tlsDataEnd + 4) = profileBufferEnd + 3;
    }
}