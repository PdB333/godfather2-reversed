// FUNC_NAME: Entity::computeAnimationTransform

#include <math.h>

// Forward declaration for random function
extern float RandomFloat();

void Entity::computeAnimationTransform(float* outMatrix, float param2, float param3)
{
    // Global state for procedural noise generation (circular buffer of 20 floats)
    static int s_noiseIndex = 0; // DAT_0119478c
    static float s_noiseBuffer[20]; // DAT_01194790

    float* matrixRow0 = outMatrix;       // first row (orientation X)
    float* matrixRow4 = outMatrix + 4;   // second row (orientation Z? actually Y?)

    // --- Procedural noise update (likely Perlin-like) ---
    int prevIndex = s_noiseIndex - 1;
    int nextIndex = s_noiseIndex + 2;
    if (prevIndex < 0) prevIndex = 19;
    else if (nextIndex > 19) nextIndex = s_noiseIndex - 18;

    s_noiseBuffer[prevIndex] += s_noiseBuffer[nextIndex];

    float noiseValue = s_noiseBuffer[prevIndex];

    // --- Get flags from an internal state (likely animation flags) ---
    uint flags = *(uint*)(*(int*)(this + 0x24) + 0x108); // animationState->flags
    float* stateBase = (float*)*(int*)(this + 0x24);     // pointer to animation state

    // --- Compute fVar10 (first axis scale) ---
    float fVar10;
    if ((flags & 8) == 0) {
        fVar10 = *(stateBase + 0xd4/4); // default base
    } else {
        // Use noise to perturb
        float noisePart = (float)((uint)noiseValue & 0x7fffff | 0x3f800000) - 1.0f;
        fVar10 = noisePart * *(stateBase + 0xd8/4) + *(stateBase + 0xd4/4);
    }

    // --- Compute local_58 (second axis scale, e.g., Y scale) ---
    float scaleY;
    if ((flags & 0x20) == 0) {
        if ((flags & 0x20000) == 0) {
            scaleY = *(float*)(this + 0x90); // default Y component
        } else {
            scaleY = *(stateBase + 0xe0/4) * param2 + *(float*)(this + 0x90);
        }
    } else {
        float noiseVal2 = (float)(((uint)noiseValue & 0x7f) << 16 | (uint)noiseValue >> 16 | 0x3f800000) - 1.0f;
        if ((flags & 0x10) != 0) {
            noiseVal2 = sqrtf(noiseVal2);
        }
        scaleY = *(stateBase + 0xe0/4) * noiseVal2 + *(float*)(this + 0x90);
    }

    // --- Update noise index (circular) ---
    s_noiseIndex = prevIndex - 1;
    int nextIndex2 = prevIndex + 2;
    if (s_noiseIndex < 0) s_noiseIndex = 19;
    else if (nextIndex2 > 19) nextIndex2 = prevIndex - 18;
    s_noiseBuffer[s_noiseIndex] += s_noiseBuffer[nextIndex2];

    uint noise2 = (uint)s_noiseBuffer[s_noiseIndex];

    // --- Compute local_60 and local_64 (likely speed/amplitude) ---
    float speed = 0.0f;     // local_60
    float amplitude = 0.0f; // local_64

    // First component: speed based on second noise
    uint flags2 = *(uint*)(stateBase + 0x10c/4);
    float* stateBase2 = (float*)*(int*)(this + 0x24);  // same pointer but used again

    if ((flags2 & 0x2000) == 0) {
        speed = ((float)(noise2 & 0x7fffff | 0x3f800000) - 1.0f) * *(stateBase2 + 0x148/4);
    } else {
        speed = *(stateBase2 + 0x148/4) * param2;
    }

    // Amplitude
    byte flagsByte = *(byte*)(stateBase + 0x108/4); // lower byte of flags
    if ((flagsByte & 0x40) == 0) {
        if ((flags2 & 0x4000) == 0) {
            amplitude = *(stateBase2 + 0xe4/4);
        } else {
            amplitude = *(stateBase2 + 0xe8/4) * param2 + *(stateBase2 + 0xe4/4);
        }
    } else {
        amplitude = ((float)((noise2 & 0x7f) << 16 | noise2 >> 16 | 0x3f800000) - 1.0f) *
                    *(stateBase2 + 0xe8/4) + *(stateBase2 + 0xe4/4);
    }

    // --- Special handling when flags2 0x8000 set (randomize speed/amplitude) ---
    if ((flags2 & 0x8000) != 0) {
        speed = *(stateBase2 + 0x148/4);
        double ampLow = (double)*(stateBase2 + 0xe4/4);
        RandomFloat();  // FUN_00b99fcb? unknown
        double ampHigh = (double)(*(stateBase2 + 0xe8/4) + *(stateBase2 + 0xe4/4));
        RandomFloat();  // FUN_00b99fcb? unknown
        float fVar11 = (float)ampHigh - (float)ampLow;
        // Some modulo operation with DAT_00e44680
        float modVal = (float)((uint)(fVar11 * speed * param3) & 0x00e44680); // probably a mask
        // DAT_00e44848 likely threshold
        if (modVal <= 0.0f) { // DAT_00e44848 is zero
            amplitude = 0.0f;
            speed = 0.0f;
        } else {
            float invSqrt = 1.0f / sqrtf(modVal + 0.0f); // PTR_FUN_00e4462c is zero?
            float term1 = invSqrt * fVar11 * param2;
            float term2 = invSqrt * speed * param2;
            speed = (term1 - (float)(int)term1) * speed;
            fVar11 = (term2 - (float)(int)term2) * fVar11 + (float)ampLow;
            float clampLow = 0.0f; // DAT_00e2eff4
            float clampHigh = 1.0f; // DAT_00e2b1a4
            if (clampLow < fVar11 && fVar11 <= clampHigh) {
                clampLow = fVar11;
            }
            double clamped = (double)clampLow;
            RandomFloat(); // FUN_00b9c766
            amplitude = (float)clamped;
        }
    }

    // --- Compute trig components from speed and amplitude ---
    double dSpeed = (double)speed;
    RandomFloat(); // FUN_00b99fcb
    double dSpeed2 = (double)speed;
    RandomFloat(); // FUN_00b99e20
    double dAmplitude = (double)amplitude;
    RandomFloat(); // FUN_00b99fcb
    double dAmplitude2 = (double)amplitude;
    RandomFloat(); // FUN_00b99e20

    // Build orientation matrix rows
    float sinAmp = (float)dAmplitude2 * scaleY;
    matrixRow0[0] = sinAmp * (float)dSpeed2; // X component
    matrixRow0[1] = (float)dAmplitude * scaleY;
    matrixRow0[2] = sinAmp * (float)dSpeed;
    matrixRow0[3] = 1.0f; // W component (homogeneous)

    float sinAmp2 = (float)dAmplitude2 * fVar10;
    matrixRow4[0] = sinAmp2 * (float)dSpeed2;
    matrixRow4[1] = (float)dAmplitude * fVar10;
    matrixRow4[2] = sinAmp2 * (float)dSpeed;
    matrixRow4[3] = 0.0f; // No translation component here

    // --- Secondary noise-based perturbation (when flags 0x200 set) ---
    flags = *(uint*)(*(int*)(this + 0x24) + 0x108);
    if ((flags & 0x200) != 0) {
        if ((flags & 0x400) == 0) {
            uint randVal = RandomFloat() * 0x7fffff + 0x3f800000; // simplified
            // Actually uses FUN_004e9200 which returns a random uint
            uint randVal = RandomUint32(); // assume returns 32-bit
            uint highByte = (randVal & 0xff000000) >> 24;
            uint midPart = (randVal & 0x00ff0000) >> 16;
            uint lowPart = randVal & 0x0000ffff;

            float fVar21 = (float)((randVal & 0x7fffff) | 0x3f800000) - 1.0f;
            float local_58 = (float)(((randVal << 8) & 0x7fffff) | 0x3f800000) - 1.0f;
            float fVar11 = (float)(((randVal & 0x7fff) | (randVal >> 18)) << 8 | highByte | 0x3f800000) - 1.0f;

            // Condition checking (complex)
            float* stateBase3 = (float*)*(int*)(this + 0x24);
            uint flags3 = *(uint*)(stateBase3 + 0x10c/4);
            float fVar10 = *(stateBase3 + 0x84/4);
            if (((flags3 & 0x10000) != 0) && fVar10 != 0.0f &&
                (*(stateBase3 + 0xe0/4) < fVar10) &&
                ((*(stateBase3 + 0xe0/4) / fVar10) > fVar21 && (fVar11 < fVar10))) {
                float factor = 1.0f - (*(stateBase3 + 0xe0/4) / fVar10);
                if ((highByte & 1) == 0) {
                    if ((highByte & 2) == 0) {
                        fVar11 = factor * fVar11 + (*(stateBase3 + 0xe0/4) / fVar10);
                    } else {
                        fVar21 = factor * fVar21 + (*(stateBase3 + 0xe0/4) / fVar10);
                    }
                } else {
                    local_58 = factor * local_58 + (*(stateBase3 + 0xe0/4) / fVar10);
                }
            }

            uint randVal2 = RandomUint32();
            fVar21 *= (float)(int)((randVal2 & 2) - 1);
            local_58 *= (float)(int)(((randVal2 >> 24) & 2) - 1);
            fVar11 *= (float)(int)((((randVal2 << 8) >> 24) & 2) - 1);

            if ((*(uint*)(*(int*)(this + 0x24) + 0x108) & 0x20000) != 0) {
                local_58 = param2 * 0.0f - 1.0f; // DAT_00e2b04c likely zero?
            }
        } else {
            uint randVal = RandomUint32();
            float fVar12 = 1.0f - ((float)((randVal & 0x7fffff) | 0x3f800000) - 1.0f) * 0.0f; // DAT_00e2b04c
            float fVar20 = sqrtf(1.0f - fVar12 * fVar12);
            float fVar12_ = ((float)(((randVal & 0x7f) << 16) | (randVal >> 16) | 0x3f800000) - 1.0f) * 0.0f; // DAT_00e2a848
            double dTemp = (double)fVar12_;
            RandomFloat(); // FUN_00b99fcb
            float fVar11 = (float)dTemp;
            double dTemp2 = (double)fVar12_;
            RandomFloat(); // FUN_00b99e20
            float fVar21 = (float)dTemp2;

            float* stateBase4 = (float*)*(int*)(this + 0x24);
            if (*(stateBase4 + 0x84/4) == 0.0f) {
                local_58 = 0.0f;
            } else {
                fVar21 = fVar21 * fVar20;
                fVar11 = fVar11 * fVar20;
            }

            if ((*(uint*)(stateBase4 + 0x108/4) & 0x800) != 0) {
                float fVar20_ = local_58;
                float fVar14 = fVar21;
                float fVar22 = fVar11;
                uint randVal3 = RandomUint32();
                stateBase4 = (float*)*(int*)(this + 0x24);
                float fVar12_val = *(stateBase4 + 0x84/4);
                float fVar13 = (float)((randVal3 & 0x7fffff) | 0x3f800000) - 1.0f;
                if (fVar12_val == 0.0f) {
                    fVar13 = sqrtf(fVar13);
                } else {
                    double dTemp3 = (double)fVar13;
                    RandomFloat(); // FUN_00b9af10
                    fVar13 = (float)dTemp3;
                    fVar20_ = local_58;
                    fVar14 = fVar21;
                    fVar22 = fVar11;
                }
                if (((*(uint*)(stateBase4 + 0x10c/4) & 0x10000) != 0) && fVar12_val != 0.0f &&
                    (*(stateBase4 + 0xe0/4) < fVar12_val) &&
                    ((*(stateBase4 + 0xe0/4) / fVar12_val) > fVar13)) {
                    fVar13 = (1.0f - (*(stateBase4 + 0xe0/4) / fVar12_val)) * fVar13 + (*(stateBase4 + 0xe0/4) / fVar12_val);
                }
                fVar21 = fVar13 * fVar14;
                local_58 = fVar13 * fVar20_;
                fVar11 = fVar13 * fVar22;
            }

            if ((*(byte*)(stateBase4 + 0x108/4) & 0x40) == 0) {
                matrixRow4[0] = fVar21 * fVar10;
                matrixRow4[1] = local_58 * fVar10;
                matrixRow4[2] = fVar11 * fVar10;
                matrixRow4[3] = 0.0f;
            }
        }

        // Add positional offset from animation state (x,y,z) to orientation matrix rows
        float* posPtr = (float*)*(int*)(this + 0x24);
        matrixRow0[0] += posPtr[0x80/4] * fVar21;
        matrixRow0[1] += posPtr[0x84/4] * local_58;
        matrixRow0[2] += posPtr[0x88/4] * fVar11;
    }

    // --- Ground clamping / collision detection (based on pointer +0xa0) ---
    uint* flagsPtr = (uint*)(*(int*)(this + 0x24) + 0x108);
    if (((*flagsPtr & 0x2000) == 0) || (*(int*)(*(int*)(this + 4) + 0xb0) != 4)) {
        int index = *(int*)(this + 0xa0); // some offset for collision height
        if (index != 0) {
            int* fsBase = *(int**)(__readfsdword(0x2c)); // FS segment offset
            int objBase = *(int*)(fsBase + 8);
            float height1 = *(float*)(objBase + 0x2c + index);
            float height0 = *(float*)(objBase + 0x28 + index);
            float diff = height1 - height0;
            if (diff < 0.0f) {
                diff = 0.0f;
                height0 = height1;
            }
            if ((*flagsPtr & 0x20000) == 0) {
                RandomFloat(); // FUN_004e41b0
                param2 = height1;
            }
            // Check if this height difference is valid
            // FUN_00519540 is probably a clamping function
            if (!clampToGround(param2 * height0 + diff)) {
                goto skipClamp;
            }
        }
    } else {
        // Play sound? (function at 0x00537020 with short from this+0x5e)
        playCollisionSound(*(short*)(this + 0x5e));
    }

    // Apply some final offsets from local variables (likely stack-based for previous frame)
    // These are local_30, fStack_2c, fStack_28, fStack_24
    float fVar12_save = matrixRow0[3];
    matrixRow0[0] += local_30;
    matrixRow0[1] += fStack_2c;
    matrixRow0[2] += fStack_28;
    matrixRow0[3] += fStack_24;
    matrixRow0[3] = fVar12_save;

skipClamp:
    // --- Apply additional transform from environment (e.g., vehicle) ---
    int* fsBase2 = **(int**)(__readfsdword(0x2c));
    byte* extraFlags = (byte*)(*(int*)(fsBase2 + 8) + *(int*)(this + 0x10));
    if ((*extraFlags & 4) == 0) {
        // FUN_0056b420 - likely matrix multiply or transform
        applyMatrixTransformation(extraFlags + 0x50, outMatrix, outMatrix);
        // FUN_0044c4c0 - another transform for second row
        applySecondRowTransform(*(int*)(this + 0x10) + 0x50 + *(int*)(fsBase2 + 8), matrixRow4, matrixRow4);
    }

    // --- Blending with previous state or external influence (e.g., camera) ---
    if (*(float*)(this + 0x30) < 0.0f) { // DAT_00e2fc44 likely zero threshold
        uint flagsA = *(uint*)(*(int*)(this + 0x24) + 0x108);
        if ((flagsA & 0x40000000) != 0) {
            float* prevRow = (float*)(*(int*)(this + 0x10) + 0x80 + *(int*)(fsBase2 + 8));
            float prevX = prevRow[1];
            float prevY = prevRow[2];
            float curX = *(float*)(this + 0x84);
            float curY = *(float*)(this + 0x88);
            float diffX = *prevRow - *(float*)(this + 0x80);
            float blend = 1.0f - diffX; // DAT_00e44564 - diffX
            RandomFloat(); // FUN_004e41b0
            float saveW = matrixRow0[3];
            matrixRow0[0] = blend * diffX + matrixRow0[0];
            matrixRow0[1] = blend * (prevX - curX) + matrixRow0[1];
            matrixRow0[2] = blend * (prevY - curY) + matrixRow0[2];
            matrixRow0[3] = blend * fStack_24 + matrixRow0[3];
            matrixRow0[3] = saveW;
        }
        if ((*(uint*)(*(int*)(this + 0x24) + 0x10c) & 0x40000000) != 0) {
            float* prevRow = (float*)(*(int*)(this + 0x10) + 0x80 + *(int*)(fsBase2 + 8));
            float prevX = prevRow[1];
            float prevY = prevRow[2];
            float curX = *(float*)(this + 0x84);
            float curY = *(float*)(this + 0x88);
            float blend = *(float*)(*(int*)(this + 0x24) + 0x150) / *(float*)(this + 0x30);
            float saveW2 = matrixRow4[3];
            matrixRow4[0] = blend * (*prevRow - *(float*)(this + 0x80)) + matrixRow4[0];
            matrixRow4[1] = blend * (prevX - curX) + matrixRow4[1];
            matrixRow4[2] = blend * (prevY - curY) + matrixRow4[2];
            matrixRow4[3] = blend * fStack_24 + matrixRow4[3];
            matrixRow4[3] = saveW2;
        }
    }
}