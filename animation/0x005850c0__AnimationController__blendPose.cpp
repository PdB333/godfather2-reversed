// FUNC_NAME: AnimationController::blendPose
// Function address: 0x005850c0
// Reconstructed from Ghidra decompilation
// Purpose: Interpolates animation pose data (blends between two animation frames or blends a frame with identity)
// Parameters: (this, blendFactor, flags) - __thiscall
// flags: bit 2 (0x4) controls whether pose blending is skipped (bit set = skip), 
//        bit 3 (0x8) controls whether final transformation blend is done (bit set = skip)

int __thiscall AnimationController::blendPose(void* this, float blendFactor, unsigned char flags)
{
    int context;
    float* dstArray;
    float* srcArray;
    int count;
    int i;
    unsigned int elementCount;
    float* srcPtr;
    float* dstPtr;
    char* weightPtr;
    int blendCount;
    float* sourcePtr1;
    float result;
    float tempVars[4]; // local_20, fStack_1c, pfStack_18, fStack_14
    int tempInt;
    float fVar1, fVar2, fVar3;
    unsigned int uVar8;

    if ((this != 0) && (context = getAnimationContext(), context != 0)) {
        // Check if pose blending is enabled (bit 2 clear)
        if ((flags & 4) == 0) {
            pushTransformStack();
            applyTransform(this);
            // Get the number of elements to blend (stored at +0x0C inside the array at this+0x38)
            blendCount = *(int*)(*(int*)(this + 0x38) + 0xc);
            // Pointer to weight data? (at this+0x34, offset +0x14)
            weightPtr = (char*)(*(int*)(this + 0x34) + 0x14);
            // If context->m_blendCount == 0, then no per-element scaling, just uniform scale
            if (*(int*)(context + 0x3c) == 0) {
                // Uniform blending: either skip per-bone weights or apply uniform blend
                if (*(char*)(*(int*)(this + 0x34) + 0x10) == '\0') {
                    // Per-bone but uniform? Actually uses per-bone weight bytes but only calls FUN_00582bf0 (scaleQuaternion?)
                    for (; 0 < blendCount; blendCount--) {
                        if (*weightPtr == '\x02') {
                            scaleQuaternion(blendFactor); // ??? likely scales something with blendFactor
                        }
                        weightPtr++;
                    }
                } else {
                    // No per-bone weights, apply uniform blend to all
                    for (; 0 < blendCount; blendCount--) {
                        scaleQuaternion(blendFactor);
                    }
                }
            } else {
                // Dual source blending: interpolate between source1 and source2 with per-bone weights
                // Source1 pointer at context+0x34, source2 at context+0x38, destination at context+0x3c? Actually destinations are stored elsewhere
                sourcePtr1 = (float*)(*(int*)(context + 0x34) + 0x10); // source1 array starting at offset 0x10
                // Destination pointer at this+0x3c
                dstPtr = (float*)(*(int*)(this + 0x3c) + 0x10);
                // Setup counters and store locals
                tempVars[0] = (float)(*(int*)(context + 0x34) + 0x14); // source1 count? Not exactly, see below
                tempVars[1] = (float)(*(int*)(context + 0x38) + 0x10); // source2 array
                srcPtr = (float*)(*(int*)(context + 0x3c) + 0x10); // destination array
                // Stored in stack variables: local_20, fStack_1c, pfStack_18 etc.
                // Reconstruct as local array for readability
                float local_20 = (float)(*(int*)(context + 0x34) + 0x14); // not used? Actually above
                float fStack_1c = (float)(*(int*)(context + 0x38) + 0x10);
                float* pfStack_18 = (float*)(*(int*)(context + 0x3c) + 0x10);
                // Actually the code uses local_20, fStack_1c, pfStack_18, fStack_14
                // I'll keep names but this is messy; likely the compiler optimized parameters 
                // The function FUN_005866e0 takes pointers to these locals.

                if (*(char*)(*(int*)(this + 0x34) + 0x10) == '\0') {
                    // Per-bone weights active: iterate with interpolation
                    for (; 0 < blendCount; blendCount--) {
                        interpolateQuaternion(&tempVars[0], weightPtr, blendFactor);
                        weightPtr++;
                        // Advance pointers: local_20 = (int)local_20 + 1; But it's float cast
                        tempVars[0] = (float)((int)tempVars[0] + 1);
                        tempVars[1] = (float)((int)tempVars[1] + 0x20); // 0x20 = 32 bytes per element?
                        // Advance source and destination arrays by 4 floats (16 bytes) each
                        // But they are float* so +4 increments by 16 bytes? Actually +4 adds 16 bytes (4 floats) if sizeof(float)==4
                        // Wait: local_24 and pfStack_18 are used as pointers to floats, but code does local_24 = local_24 + 4; that increments pointer by 4*4=16 bytes.
                        // However the casts above are weird. Possibly the compiler used the same registers for different types.
                        // I'll simplify: The actual pointers are advanced by one element (4 floats) each loop.
                    }
                } else {
                    // No per-bone weights: uniform blend, multiply source by blendFactor
                    if (0 < blendCount) {
                        // Initialize locals with blendFactor
                        tempVars[0] = blendFactor;
                        tempVars[1] = blendFactor;
                        tempVars[2] = *(float*)&blendFactor; // treat blendFactor as float*
                        tempVars[3] = blendFactor;
                        // Actually the code sets local_20, fStack_1c, pfStack_18, fStack_14 all to blendFactor (or param_2), but pfStack_18 is a pointer cast.
                        // This is likely a compiler optimization for vector multiplication. We'll treat as vector multiply.
                        do {
                            scaleQuaternion(blendFactor); // Not sure why scaleQuaternion called each time?
                            fVar1 = dstPtr[1];
                            fVar2 = dstPtr[2];
                            fVar3 = dstPtr[3];
                            *srcPtr = *dstPtr * local_20;
                            srcPtr[1] = fVar1 * fStack_1c;
                            srcPtr[2] = fVar2 * (float)pfStack_18;
                            srcPtr[3] = fVar3 * fStack_14; // Actually fStack_14 stored locally
                            blendCount--;
                            srcPtr[3] = DAT_00e2b1a4; // constant (likely 1.0 or 0.0)
                            dstPtr += 4;
                            srcPtr += 4;
                        } while (0 < blendCount);
                    }
                }
            }

            // Second part: blend another array (perhaps positions) if present
            if (*(int*)(context + 0x40) != 0) {
                uVar8 = *(uint*)(*(int*)(context + 0x40) + 0xc); // element count
                dstPtr = (float*)(*(int*)(context + 0x40) + 0x10); // destination
                srcPtr = (float*)(*(int*)(this + 0x40) + 0x10); // source
                // Loop dividing by 4 (because each element is 4 floats)
                count = uVar8 >> 2;
                while (0 < count) {
                    fVar1 = srcPtr[1];
                    fVar2 = srcPtr[2];
                    fVar3 = srcPtr[3];
                    *dstPtr = *srcPtr * blendFactor;
                    dstPtr[1] = fVar1 * blendFactor;
                    dstPtr[2] = fVar2 * blendFactor;
                    dstPtr[3] = fVar3 * blendFactor;
                    srcPtr += 4;
                    dstPtr += 4;
                    count--;
                }
                uVar8 = uVar8 & 3; // remaining elements (less than 4)
                // Handle remaining floats individually
                if (3 < uVar8) {
                    // Actually this branch is for if uVar8 > 3, but after mask it can't be >3? Possibly a bug or compiler artifact.
                    count = (uVar8 - 4 >> 2) + 1; // always 0 if uVar8 <=3? This is weird.
                    uVar8 = uVar8 + count * -4;
                    do {
                        *dstPtr = *srcPtr * blendFactor;
                        dstPtr[1] = srcPtr[1] * blendFactor;
                        dstPtr[2] = srcPtr[2] * blendFactor;
                        dstPtr[3] = srcPtr[3] * blendFactor;
                        srcPtr += 4;
                        dstPtr += 4;
                        count--;
                    } while (count != 0);
                }
                // Handle any remaining singles
                while (0 < (int)uVar8) {
                    *dstPtr = *srcPtr * blendFactor;
                    srcPtr++;
                    dstPtr++;
                    uVar8--;
                }
            }
        }

        // If flag bit 3 is clear, blend the final transformation
        if ((flags & 8) == 0) {
            int baseTransform = this + 0x10; // transformation matrix at this+0x10? 
            if (*(char*)(this + 0x30) == '\x02') {
                // Blend type '2' (maybe additive or override)
                float blendResult[4]; // local_20, fStack_1c, pfStack_18, fStack_14
                blendResult[0] = 0.0f;
                blendResult[1] = 0.0f;
                blendResult[2] = 0.0f;
                blendResult[3] = DAT_00e2b1a4; // constant (perhaps 1.0 for w)
                // lerpTransform(ctx, blendResult, thisTransform, contextTransform, constant)
                lerpTransform(blendFactor, blendResult, baseTransform, context + 0x10, DAT_00e2e780);
                // Then multiply the result by blendFactor and store into context
                fVar1 = *(float*)(baseTransform + 0x14);
                fVar2 = *(float*)(baseTransform + 0x18);
                fVar3 = *(float*)(baseTransform + 0x1c);
                *(float*)(context + 0x20) = blendFactor * *(float*)(baseTransform + 0x10);
                *(float*)(context + 0x24) = blendFactor * fVar1;
                *(float*)(context + 0x28) = blendFactor * fVar2;
                *(float*)(context + 0x2c) = blendFactor * fVar3;
                *(float*)(context + 0x2c) = DAT_00e2b1a4; // overwrite last element with constant
                *(char*)(context + 0x30) = 2; // set blend type to 2
            }
        }
        return context;
    }
    return 0;
}