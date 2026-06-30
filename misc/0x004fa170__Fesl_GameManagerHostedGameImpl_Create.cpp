// FUNC_NAME: EffectManager::updateEffects

void __thiscall EffectManager::updateEffects(EffectManager* this, float deltaTime)
{
    // Thread-local data access (likely per-thread game state index)
    int threadIndex = *(int*)(__readfsdword(0x2C));  // +0x2C from FS base

    // Check if the effect system is paused/disabled (bit 0 of flags)
    // +0x10 points to some global flags array, offset by threadIndex*8 (or 4?)
    if ((*(byte*)(*(int*)(this + 0x10) + *(int*)(threadIndex + 8)) & 1) != 0)
        return;

    // Handle life timer: decrement and expire if non-positive
    if (*(float*)(this + 0x38) > 0.0f)
    {
        float timer = *(float*)(this + 0x38) - deltaTime;
        *(float*)(this + 0x38) = timer;
        if (timer <= 0.0f)
        {
            *(uint32*)(this + 0x38) = 0;
            uint* flags = (uint*)(*(int*)(this + 0x10) + *(int*)(threadIndex + 8));
            *flags |= 1;  // Set idle flag
        }
    }

    // Get active particle count from the effect array
    int activeCount = *(int*)(*(int*)(this + 0x40) + 0x58 + *(int*)(threadIndex + 8));
    float* particlePos = (float*)(*(int*)(this + 0x10) + 0x80 + *(int*)(threadIndex + 8));
    float localPos[4];
    localPos[0] = particlePos[0];
    localPos[1] = particlePos[1];
    localPos[2] = particlePos[2];
    localPos[3] = particlePos[3]; // w component

    // Iterate over active particles (backwards for safe removal)
    for (int idx = activeCount - 1; idx >= 0; idx--)
    {
        int basePtr = *(int*)(this + 0x40) + *(int*)(threadIndex + 8);
        int particle = *(int*)(basePtr + 8 + idx * 8);
        int particleData = *(int*)(basePtr + 12 + idx * 8);
        if (particle == 0)
        {
            int containerCount = *(int*)(basePtr + 0x58);
            if (idx < containerCount)
            {
                if (idx < containerCount - 1)
                {
                    // Remove element by swapping with last
                    *(int*)(basePtr + 8 + idx * 8) = *(int*)(basePtr + containerCount * 8);
                    *(int*)(basePtr + 12 + idx * 8) = *(int*)(basePtr + 4 + containerCount * 8);
                }
                *(int*)(basePtr + 0x58) = *(int*)(basePtr + 0x58) - 1;
                int* lastSlot = (int*)(basePtr + 8 + *(int*)(basePtr + 0x58) * 8);
                if (lastSlot)
                {
                    lastSlot[1] = 0;
                    *lastSlot = 0;
                }
            }
            continue;
        }

        // Get the particle's state pointer (per-thread)
        int statePtr = *(int*)(particle + 0x24 + *(int*)(threadIndex + 8));
        if (statePtr == 0)
        {
            // Particle is dead/inactive, remove it
            removeParticle(particle, particleData);
            int arrayBase = *(int*)(threadIndex + 8) + 8 + *(int*)(this + 0x40);
            int count = *(int*)(arrayBase + 0x50);
            if (idx < count)
            {
                if (idx < count - 1)
                {
                    *(int*)(arrayBase + idx * 8) = *(int*)(arrayBase - 8 + count * 8);
                    *(int*)(arrayBase + 4 + idx * 8) = *(int*)(arrayBase - 4 + count * 8);
                }
                *(int*)(arrayBase + 0x50) = count - 1;
                int* lastSlot = (int*)(arrayBase + *(int*)(arrayBase + 0x50) * 8);
                if (lastSlot)
                {
                    lastSlot[1] = 0;
                    *lastSlot = 0;
                }
            }
        }
        else
        {
            // Check distance from source to particle
            float dx = localPos[0] - *(float*)(statePtr + 0x70);
            float dy = localPos[1] - *(float*)(statePtr + 0x74);
            float dz = localPos[2] - *(float*)(statePtr + 0x78);
            float maxDist = *(float*)(*(int*)(*(int*)(this + 4) + 0x10) + 0x20) + *(float*)(statePtr + 0x28);
            float distSq = dx*dx + dy*dy + dz*dz;
            if (maxDist * maxDist <= distSq)
            {
                // Particle out of range, destroy it and trigger an effect
                removeParticle(particle, particleData);
                spawnEffect();
            }
        }
    }

    // Second pass: look for newly added particles that need processing
    int baseCount = *(int*)(*(int*)(this + 0x40) + 0x58 + *(int*)(threadIndex + 8));
    char flag = checkAddEffectStatus(g_AddEffectBuffer, *(int*)(this + 0x40) + *(int*)(threadIndex + 8));
    float constZero = *(float*)0x00e2b1a4; // likely 0.0f
    if (flag == 1)
    {
        int newCount = *(int*)(*(int*)(this + 0x40) + 0x58 + *(int*)(threadIndex + 8));
        while (baseCount < newCount)
        {
            int newParticle = *(int*)(*(int*)(this + 0x40) + 8 + baseCount * 8 + *(int*)(threadIndex + 8));
            if (newParticle != 0)
            {
                int particleState = newParticle + *(int*)(threadIndex + 8);
                int timer = *(int*)(particleState + 0x10);
                if (timer < 1)
                {
                    timer = *(int*)(*(int*)(this + 0x3C) + 0x8C);
                }
                else if (*(float*)(*(int*)(particleState + 0x24) + 0x3C) == constZero)
                    goto skipParticle;  // Skip if special condition

                if (timer > 0)
                {
                    scheduleParticleUpdate(timer);
                    constZero = *(float*)0x00e2b1a4;
                }
            }
skipParticle:
            baseCount++;
        }
    }

    // Update fire mode (0: simple float, 1: pointer to object, 2: script method)
    int fireMode = *(int*)(this + 0x150);
    float fireValueX = 0.0f;
    if (fireMode == 0)
        fireValueX = *(float*)(this + 0x154);
    else if (fireMode == 1)
    {
        if (*(int*)(this + 0x154) != 0)
            fireValueX = *(float*)(*(int*)(this + 0x154) + 0x10);
    }
    else if (fireMode == 2)
    {
        int scriptOffset = *(int*)(this + 4) + (*(int*)(this + 0x154) + 12) * 0x14;
        float temp = 0.0f;
        scrReturnFloat = 0.0f;  // local_9c
        if (*(int*)(scriptOffset + 4) != 0)
        {
            (**(code**)(**(int**)(scriptOffset + 4) + 0x2C))(0, &temp);
            fireValueX = temp;
        }
    }
    *(float*)(*(int*)(threadIndex + 8) + 0x5C + *(int*)(this + 0x40)) = fireValueX;

    // Second fire axis (Y or similar)
    int fireModeY = *(int*)(this + 0x158);
    float fireValueY = 0.0f;
    if (fireModeY == 0)
        fireValueY = *(float*)(this + 0x15C);
    else if (fireModeY == 1)
    {
        if (*(int*)(this + 0x15C) != 0)
            fireValueY = *(float*)(*(int*)(this + 0x15C) + 0x10);
    }
    else if (fireModeY == 2)
    {
        int scriptOffset = *(int*)(this + 4) + (*(int*)(this + 0x15C) + 12) * 0x14;
        float temp = 0.0f;
        if (*(int*)(scriptOffset + 4) != 0)
        {
            (**(code**)(**(int**)(scriptOffset + 4) + 0x2C))(0, &temp);
            fireValueY = temp;
        }
    }
    *(float*)(*(int*)(threadIndex + 8) + 0x84 + *(int*)(this + 0x40)) = fireValueY;

    // Update axis-specific values if enabled (flags at +0x50 bit 0= X, bit 1= Y)
    if ((*(byte*)(*(int*)(this + 0x3C) + 0x50) & 3) != 0)
    {
        for (int i = 1; ; i++)
        {
            float factor = (float)i * g_SomeConstant;  // _DAT_00e44944
            float valX = 0.0f;
            if ((*(byte*)(*(int*)(this + 0x3C) + 0x50) & 1) != 0)
            {
                int fireMode = *(int*)(this + 0x150);
                if (fireMode == 0)
                    valX = *(float*)(this + 0x154);
                else if (fireMode == 1)
                {
                    if (*(int*)(this + 0x154) != 0)
                        valX = *(float*)(*(int*)(this + 0x154) + 0x10);
                }
                else if (fireMode == 2)
                {
                    int scriptOffset = *(int*)(this + 4) + (*(int*)(this + 0x154) + 12) * 0x14;
                    float temp = 0.0f;
                    if (*(int*)(scriptOffset + 4) != 0)
                    {
                        (**(code**)(**(int**)(scriptOffset + 4) + 0x2C))(&factor, &temp);
                        valX = temp;
                    }
                }
                *(float*)(*(int*)(threadIndex + 8) + (i*4 + 0x60) + *(int*)(this + 0x40)) = valX;  // offset = 0x60, 0x64, ...
            }
            int valY = 0;
            if ((*(byte*)(*(int*)(this + 0x3C) + 0x50) & 2) != 0)
            {
                int fireModeY = *(int*)(this + 0x158);
                if (fireModeY == 0)
                    valY = *(int*)(this + 0x15C);
                else if (fireModeY == 1)
                {
                    if (*(int*)(this + 0x15C) != 0)
                        valY = *(int*)(*(int*)(this + 0x15C) + 0x10);
                }
                else if (fireModeY == 2)
                {
                    int scriptOffset = *(int*)(this + 4) + (*(int*)(this + 0x15C) + 12) * 0x14;
                    int temp = 0;
                    if (*(int*)(scriptOffset + 4) != 0)
                    {
                        (**(code**)(**(int**)(scriptOffset + 4) + 0x2C))(&factor, &temp);
                        valY = temp;
                    }
                }
                *(int*)(*(int*)(threadIndex + 8) + (i*4 + 0x88) + *(int*)(this + 0x40)) = valY;  // offset = 0x88, 0x8C, ...
            }
            if (i*4 + 0x88 >= 0xA9) break;
        }
    }

    // Time accumulation and decay
    *(float*)(this + 0x160) += deltaTime;
    float decayRate = *(float*)(*(int*)(this + 0x3C) + 0x44);
    if (decayRate != 0.0f)
    {
        float newDecay = *(float*)(this + 0x168) + decayRate * deltaTime;
        *(float*)(this + 0x168) = newDecay;
        if (newDecay > constZero)
            *(uint32*)(this + 0x168) = 0;
        else if (newDecay < 0.0f)
            *(float*)(this + 0x168) = constZero;
    }
    float decayRate2 = *(float*)(*(int*)(this + 0x3C) + 0x48);
    if (decayRate2 != 0.0f)
    {
        float newDecay = *(float*)(this + 0x164) + decayRate2 * deltaTime;
        *(float*)(this + 0x164) = newDecay;
        if (newDecay > constZero)
            *(uint32*)(this + 0x164) = 0;
        else if (newDecay < 0.0f)
            *(float*)(this + 0x164) = constZero;
    }

    // Process orientation/transform updates if a render object exists
    int renderObj = *(int*)(this + 0x16C);
    if (renderObj != 0)
    {
        if (*(int*)(renderObj + 0x10) == 0)
        {
            if (*(void**)(renderObj + 8) != 0)
            {
                **(int**)(renderObj + 8) = 0;
                *(int*)(renderObj + 8) = 0;
            }
            uint* flags = (uint*)(*(int*)(this + 0x10) + *(int*)(threadIndex + 8));
            *flags |= 1;
            return;
        }
        int particleCount = *(int*)(*(int*)(this + 0x40) + 0x58 + *(int*)(threadIndex + 8));
        for (int idx = 0; idx < particleCount; idx++)
        {
            float* particle = (float*)(*(int*)(*(int*)(this + 0x40) + 8 + idx * 8 + *(int*)(threadIndex + 8)));
            if (particle != 0)
            {
                int perThreadOffset = *(int*)(threadIndex + 8);
                float posX = *(float*)((int)particle + 0x28 + perThreadOffset);
                float posY = *(float*)((int)particle + 0x2C + perThreadOffset);
                float diff = posY - posX;
                float modifiedPosX = posX;
                if (diff < 0.0f)
                {
                    diff = 0.0f;
                    modifiedPosX = posY;
                }
                // Simple noise generator (linear feedback shift register)
                int noiseIdx = g_NoiseIndex;
                int newNoise = (g_NoiseHistory[noiseIdx - 1] + g_NoiseHistory[noiseIdx + 2]);  // wrap handled by mod
                noiseIdx = (noiseIdx - 1) & 0x1F; // wrap to 0..31
                if (noiseIdx < 0) noiseIdx = 0x13; // not sure; original uses magic
                g_NoiseHistory[noiseIdx] = newNoise;
                float noiseFloat = (float)(newNoise & 0x7FFFFF | 0x3F800000);  // generate float in [1,2)
                g_NoiseIndex = noiseIdx;
                float contribution = (noiseFloat - constZero) * modifiedPosX + diff;

                // Check for active flag (two slots)
                if ((*(int*)((int)particle + 0x14 + perThreadOffset) != 0) ||
                    (*(int*)((int)particle + 0x24 + perThreadOffset) != 0))
                {
                    int* ptr1 = (int*)((int)particle + 0x14 + perThreadOffset);
                    int* ptr2 = (int*)((int)particle + 0x24 + perThreadOffset);
                    bool transformFlag;
                    if (*(int*)((int)particle + 0x1C + perThreadOffset) == 0)
                    {
                        int dataPtr = 0;
                        if (*ptr1 != 0)
                            dataPtr = *ptr1 + perThreadOffset;
                        if (dataPtr != 0)
                        {
                            // Use precomputed transform
                            transformFlag = checkTransformFlag(*(int*)((int)particle + 0x24 + perThreadOffset) + 0x30);
                        }
                        else
                        {
                            char ret = (**(code**)(**(int**)((int)particle + 0x24 + perThreadOffset) + 0x18))(localStack44, contribution);
                            constZero = *(float*)0x00e2b1a4;
                            transformFlag = (ret != 0);
                        }
                    }
                    else
                    {
                        transformFlag = checkTransformFlag(*(int*)((int)particle + 0x24 + perThreadOffset) + 0x30);
                    }
                    if (transformFlag)
                    {
                        // Perform matrix transformation
                        setupTransform();
                        int statePtr = *(int*)((int)particle + 0x24 + *(int*)(threadIndex + 8));
                        // Assuming matrix is 4x4 with rows: 0x40..0x7C
                        float mat[4][4];
                        mat[0][0] = *(float*)(statePtr + 0x40);
                        mat[0][1] = *(float*)(statePtr + 0x44);
                        mat[0][2] = *(float*)(statePtr + 0x48);
                        mat[0][3] = *(float*)(statePtr + 0x4C);
                        mat[1][0] = *(float*)(statePtr + 0x50);
                        mat[1][1] = *(float*)(statePtr + 0x54);
                        mat[1][2] = *(float*)(statePtr + 0x58);
                        mat[1][3] = *(float*)(statePtr + 0x5C);
                        mat[2][0] = *(float*)(statePtr + 0x60);
                        mat[2][1] = *(float*)(statePtr + 0x64);
                        mat[2][2] = *(float*)(statePtr + 0x68);
                        mat[2][3] = *(float*)(statePtr + 0x6C);
                        mat[3][0] = *(float*)(statePtr + 0x70);
                        mat[3][1] = *(float*)(statePtr + 0x74);
                        mat[3][2] = *(float*)(statePtr + 0x78);
                        mat[3][3] = *(float*)(statePtr + 0x7C);
                        // Transform localPos
                        float transformed[4];
                        transformed[0] = localPos[0] * mat[0][0] + localPos[1] * mat[1][0] + localPos[2] * mat[2][0] + constZero * mat[3][0];
                        transformed[1] = localPos[0] * mat[0][1] + localPos[1] * mat[1][1] + localPos[2] * mat[2][1] + constZero * mat[3][1];
                        transformed[2] = localPos[0] * mat[0][2] + localPos[1] * mat[1][2] + localPos[2] * mat[2][2] + constZero * mat[3][2];
                        transformed[3] = localPos[0] * mat[0][3] + localPos[1] * mat[1][3] + localPos[2] * mat[2][3] + constZero * mat[3][3];

                        // Compute difference from current particle position
                        float* currentPos = (float*)(*(int*)(this + 0x10) + 0x80 + *(int*)(threadIndex + 8));
                        float dx = transformed[0] - currentPos[0];
                        float dy = transformed[1] - currentPos[1];
                        float dz = transformed[2] - currentPos[2];
                        float distSq = dx*dx + dy*dy + dz*dz;
                        float scale = constZero;
                        if (g_MaxDistSq < distSq)
                            scale = constZero / sqrtf(distSq);
                        // Normalize
                        dx *= scale;
                        dy *= scale;
                        dz *= scale;
                        // Prepare for applyTransform (maybe a quaternion or matrix)
                        struct TransformArgs
                        {
                            float t[4][4];
                            float dt;
                            uint32 flag1;
                            float norm[3];
                            float flag2;
                            float const1;
                        } args;
                        args.t[0][0] = transformed[0];
                        args.t[0][1] = transformed[1];
                        args.t[0][2] = transformed[2];
                        args.t[0][3] = transformed[3];
                        args.dt = deltaTime;
                        args.flag1 = 1;
                        args.norm[0] = dx;
                        args.norm[1] = dy;
                        args.norm[2] = dz;
                        args.flag2 = 1;
                        args.const1 = constZero;
                        applyTransform(*(int*)(this + 0x16C), &args);
                        constZero = *(float*)0x00e2b1a4;
                    }
                }
            }
        }
    }
}