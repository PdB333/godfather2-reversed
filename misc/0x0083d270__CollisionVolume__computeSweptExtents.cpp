// FUNC_NAME: CollisionVolume::computeSweptExtents

float __thiscall CollisionVolume::computeSweptExtents(
    void* thisPtr,           // pointer to collision volume object
    float* outSqExtent0,     // output: squared extent 0
    float* outSqExtent1,     // output: squared extent 1
    float* outSqExtent2,     // output: squared extent 2
    float* outSqExtent3,     // output: squared extent 3
    const float* inPoint,    // point (likely position or velocity delta)
    float* outTransformedPoint // optional output transformed point
) {
    // Local extents (half dimensions) read from object at known offsets
    // +0x58: halfExtentX
    // +0x5c: halfExtentY
    // +0x60: halfExtentZ
    // +0x64: halfExtentW (likely height or special dimension)
    float halfExt0 = *(float*)((char*)thisPtr + 0x58);
    float halfExt1 = *(float*)((char*)thisPtr + 0x64);
    float halfExt2 = *(float*)((char*)thisPtr + 0x60);
    float halfExt3 = *(float*)((char*)thisPtr + 0x5c);

    // Global constants (likely collision tuning values)
    extern const float g_thresholdA;   // _DAT_00d577a0
    extern const float g_thresholdB;   // _DAT_00d5779c
    extern const float g_scaleFactor;  // _DAT_00d5c458 (multiplier for enhanced collisions)
    extern const float g_additionalOffset; // _DAT_00d742d4
    extern int g_flagGlobal;           // DAT_0122339c (0 or 1)
    extern void* g_mgrGlobal;          // DAT_012233a0 (pointer to manager or singleton)

    // Read integer flags at +0xa8
    uint32_t flags = *(uint32_t*)((char*)thisPtr + 0xa8);

    // Condition 1: if halfExt3 <= g_thresholdA and bit 5 of flags is set, replace with halfExt1
    // This likely adjusts the "height" extent for a lower posture (crouching)
    if ((halfExt3 <= g_thresholdA) && ((flags >> 5) & 1)) {
        halfExt3 = halfExt1;
    }

    // Condition 2: if bit 9 of flags is set, and a global manager exists and its function returns true,
    // then scale all extents by a global factor (e.g., for underwater or special zones)
    if (((flags >> 9) & 1) && (*(int**)(*(int*)((char*)g_mgrGlobal + 4) + 0x0) != 0)) {
        int* mgrPtr = *(int**)(*(int*)((char*)g_mgrGlobal + 4) + 0x0);
        // offset -0x1f30 from that pointer yields some object
        int* objPtr = (int*)((char*)mgrPtr - 0x1f30);
        if (objPtr != 0) {
            // call virtual function at vtable+0x28c, returns bool
            typedef bool (*VFunc)(void*);
            VFunc vf = *(VFunc*)(*(int*)objPtr + 0x28c);
            if (vf(objPtr)) {
                halfExt0 *= g_scaleFactor;
                halfExt1 *= g_scaleFactor;
                halfExt2 *= g_scaleFactor;
                halfExt3 *= g_scaleFactor;
            }
        }
    }

    // Clamp halfExt2 so that halfExt1 - g_thresholdB is not less than it
    if (halfExt1 - g_thresholdB < halfExt2) {
        halfExt2 = halfExt1 - g_thresholdB;
    }

    // Compute some value from the input point (likely its length along a direction)
    float inPointVal = FUN_0083ba90(inPoint); // returns float

    // Adjusted extents based on the input point value
    float adjustedExt1 = halfExt1 + inPointVal; // upper bound after sweep
    float adjustedExt2 = halfExt2 + inPointVal; // another adjusted bound
    float adjustedExt3 = halfExt3 - inPointVal; // lower bound after sweep (inverted)

    // Clamp adjustedExt3 with lower bound from halfExt0 and threshold
    if (adjustedExt3 < halfExt0 + g_thresholdB) {
        adjustedExt3 = halfExt0 + g_thresholdB;
    }

    // Optionally compute a transformed output point outTransformedPoint
    if (outTransformedPoint != 0) {
        if (g_flagGlobal == 0) {
            // Simple copy of input point
            *(uint64_t*)outTransformedPoint = *(uint64_t*)inPoint;
            outTransformedPoint[2] = inPoint[2];
        } else {
            // More complex transform using random? data
            float stackVar[1]; // uninitialized? Actually auStack_18 is used
            char auStack_18[4]; // stack alignment
            float fStack_14;    // used as random seed? Or from FUN_00425060
            float fStack_c;     // from FUN_00b99fcb? Actually two calls
            // First call: FUN_00425060(auStack_18,0) - likely initializes random
            FUN_00425060(auStack_18, 0);
            double doubleVal1 = (double)fStack_14;
            FUN_00b99fcb(); // likely noise or random
            float noiseX = (float)doubleVal1; // actually fStack_c? Wait, reassignment
            // Re-reading fStack_14, note fStack_14 is still from stack?
            // This part is messy; simplified: compute output point using fVar8
            float noiseY = fStack_c; // after FUN_00b99fcb? Actually code sets fStack_c = (float)dVar6 after second call
            // Original p-code:
            // dVar6 = (double)fStack_14;
            // FUN_00b99fcb();
            // fStack_c = (float)dVar6;
            // dVar6 = (double)fStack_14;
            // FUN_00b99e20();
            // fVar3 = fvar8;
            // fVar8 = fVar8 + DAT_00d742d4;
            // *param_7 = fStack_c * fVar8 + *param_6;
            // param_7[1] = fVar8 * _DAT_00d577a0 + param_6[1];
            // param_7[2] = (float)dVar6 * fVar8 + param_6[2];
            // So fStack_c is used for x, fVar8 for y (with g_additionalOffset), and dVar6 for z
            // Second call FUN_00b99e20 yields something in dVar6 (global or another random)
            // We simplify as using the same noise pattern
            float fVar8 = inPointVal; // the value from FUN_0083ba90
            fVar8 = fVar8 + g_additionalOffset;
            outTransformedPoint[0] = fStack_c * fVar8 + inPoint[0];
            outTransformedPoint[1] = fVar8 * g_thresholdA + inPoint[1];
            // note: _DAT_00d577a0 is reused as multiplier
            outTransformedPoint[2] = (float)dVar6 * fVar8 + inPoint[2];
        }
    }

    // Write squared extents to output pointers
    *outSqExtent0 = halfExt0 * halfExt0;
    *outSqExtent1 = adjustedExt1 * adjustedExt1;
    *outSqExtent2 = adjustedExt2 * adjustedExt2;
    *outSqExtent3 = adjustedExt3 * adjustedExt3;

    return inPointVal; // return the computed value from input point
}