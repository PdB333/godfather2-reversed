// FUNC_NAME: ParticleEmitter::emitParticles

// Address: 0x004fd540
// Role: Updates particle positions and emits new particles each frame. Uses LFSR-based pseudo-random number generation.
// Parameters:
//   pOwner  - pointer to owner object (provides random modulus via [pOwner+0x28]+0x6c)
//   scale   - scaling factor (multiplied by velocity magnitude)
void ParticleEmitter::emitParticles(void* pOwner, float scale)
{
    int i;
    float dt;
    float halfDt;
    float scaledDt;
    float cumulativeX, cumulativeY, cumulativeZ;
    float temp1, temp2, temp3;  // reused temporaries
    float val1, val2, val3;
    int index;  // loop index
    int particleIdx;  // particle index
    int maxParticles;

    // Constants (likely from config)
    float const1 = 0.0f;  // placeholder, real values from DAT_
    float const2 = 0.0f;
    // ... more consts

    // Read global constants (interpreted from decompiled globals)
    float g_someConst1 = *(float*)(0x00e2b1a4);
    float g_someConst2 = *(float*)(0x00e2b04c);
    float g_someConst3 = *(float*)(0x00e2cd54);
    float g_someConst4 = *(float*)(0x00e2b198);
    float g_someConst5 = *(float*)(0x00e2eff4);
    float g_someConst6 = *(float*)(0x00e44564);

    // LFSR globals
    int* lfsrIndex = (int*)0x0119478c;
    uint* lfsrTable = (uint*)0x01194790;

    // Particle count (max particles) from this+0x64
    maxParticles = *(int*)((int)this + 0x64);
    // Particle buffer pointer from this+0x60
    float* particleBuffer = *(float**)((int)this + 0x60);
    // Number of emitted particles this frame? (counter at +0x68)
    int* emittedCount = (int*)((int)this + 0x68);

    // Precomputed scale factors
    float invCount = (float)(maxParticles - 1);  // avoid division by zero? assume >0
    float step = g_someConst1 / invCount;  // fVar7
    float spread1 = step * g_someConst2;  // fVar4
    float spread2 = step * g_someConst3;  // fVar8

    // Read velocity from this+0x20,24,28 and compute magnitude
    float velX = *(float*)((int)this + 0x20);
    float velY = *(float*)((int)this + 0x24);
    float velZ = *(float*)((int)this + 0x28);
    float velMag = sqrtf(velX*velX + velY*velY + velZ*velZ);
    scale *= velMag;  // param_2 is scaled

    cumulativeX = 0.0f;
    cumulativeY = 0.0f;
    cumulativeZ = 0.0f;
    temp1 = 0.0f;  // local_28
    *emittedCount = 0;  // reset count

    index = 0;
    if (0 < maxParticles) {
        i = 0;
        do {
            // Store current cumulative positions into particle buffer (offset i*16)
            particleBuffer[i*4 + 0] = cumulativeX;   // x
            particleBuffer[i*4 + 1] = cumulativeY;   // y
            particleBuffer[i*4 + 2] = cumulativeZ;   // z
            // particleBuffer[i*4 + 3] will be set later (random value from LFSR)

            // LFSR update: advance index and combine values
            int idxA = *lfsrIndex - 1;
            int idxB = *lfsrIndex + 2;
            if (idxA < 0) idxA = 0x13;
            else if (0x13 < idxB) idxB = *lfsrIndex - 0x12;
            lfsrTable[idxA] = lfsrTable[idxA] + lfsrTable[idxB];

            float randomFloat;
            float newCumulative;
            *lfsrIndex = idxA;

            // Modulo from pOwner->someRange (pOwner+0x28 then +0x6c)
            uint modVal = *(uint*)(*(int*)((int)pOwner + 0x28) + 0x6c);
            particleBuffer[i*4 + 3] = (float)(lfsrTable[idxA] % modVal);  // store as float conversion?

            // Check if cumulativeZ (or cumulativeX?) exceeds threshold
            if (g_someConst1 <= cumulativeZ) {
                // Early exit: store final particle and return
                *emittedCount = (*emittedCount) * 0x10;
                particleBuffer[8 + *emittedCount] = g_someConst1;
                particleBuffer[0 + *emittedCount] = 0.0f;
                particleBuffer[4 + *emittedCount] = 0.0f;
                (*emittedCount)++;
                return;
            }

            // Continue LFSR update for second random
            *lfsrIndex = idxA - 1;
            idxB = idxA + 2;
            if (*lfsrIndex < 0) *lfsrIndex = 0x13;
            else if (0x13 < idxB) idxB = idxA - 0x12;
            lfsrTable[*lfsrIndex] = lfsrTable[*lfsrIndex] + lfsrTable[idxB];

            // Generate random float in [fVar8, fVar4] (interpolated using LFSR mantissa)
            randomFloat = (spread1 - spread2) * ((float)(lfsrTable[*lfsrIndex] & 0x7fffff | 0x3f800000) - g_someConst1) + spread2;

            if (0.0f < temp1) {
                randomFloat += temp1;
            }

            temp1 = step - randomFloat;
            if (temp1 < 0.0f) temp1 = 0.0f;

            cumulativeX = randomFloat + cumulativeX;  // new cumulativeX

            // Boundary checks and adjustments (complicated)
            if (cumulativeX <= g_someConst4) {
                if (cumulativeY <= g_someConst1) {
                    if (g_someConst5 <= cumulativeY) {
                        newCumulative = g_someConst5;
                        SomeMathFunc();  // 0x004e41b0
                        float diff = g_someConst1 - newCumulative * g_someConst2;
                    } else {
                        newCumulative = g_someConst5;
                        SomeMathFunc();
                        diff = g_someConst5;
                    }
                    temp2 = diff * scale;
                } else {
                    newCumulative = cumulativeX;
                    SomeMathFunc();
                    temp2 = g_someConst6 - newCumulative * scale;
                }
                if (g_someConst1 < cumulativeZ) goto label_done;
                if (cumulativeZ < g_someConst5) goto label_low;
                newCumulative = cumulativeZ;
                SomeMathFunc();
                temp3 = g_someConst1 - newCumulative * g_someConst2;
label_combine:
                temp3 *= scale;
            } else {
                if (cumulativeY <= 0.0f) {
                    temp2 = cumulativeX;
                    SomeMathFunc();
                    temp2 *= scale;
                } else {
                    newCumulative = cumulativeX;
                    SomeMathFunc();
                    temp2 = g_someConst6 - newCumulative * scale;
                }
                if (cumulativeZ <= g_someConst4) {
label_low:
                    newCumulative = cumulativeZ;
                    SomeMathFunc();
                    goto label_combine;
                }
label_done:
                newCumulative = cumulativeZ;
                SomeMathFunc();
                temp3 = g_someConst6 - newCumulative * scale;
            }

            cumulativeY = temp2 + cumulativeY;
            cumulativeZ = temp3 + cumulativeZ;

            (*emittedCount)++;
            index++;
            i += 4;  // stride 0x10 = 4 floats
        } while (index < maxParticles);
    }

    // After loop: set the last particle's final position
    int lastIdx = *emittedCount * 4 - 8;  // offset for z
    particleBuffer[lastIdx] = g_someConst1;  // z
    particleBuffer[lastIdx - 4] = 0.0f;      // x?
    particleBuffer[lastIdx - 3] = 0.0f;      // y
}