// FUNC_NAME: AnimBlender::blendAnimations
// Function address: 0x0058bba0
// Role: Blends animation data using interpolation and weighting, with threshold handling and optional clamping.
// The function takes input positions (param_3, param_4), a blend factor (param_6), a weight (param_7),
// flags (param_5), and a blend type (param_8). It uses arrays stored in the object (float array at +0x0,
// size at +0x4) and a descriptor at param_2 (with byte at +1, short at +2, pointer at +0xC, int at +0x10).
// It performs blending and returns a combined result via FUN_005848f0.

#include <cstdint>

// Forward declarations for called functions (assumed to be member functions or global)
// These are placeholders; actual names should be replaced based on context.
class AnimBlender {
public:
    // Unknown internal functions
    void clampBound(float* out);                // FUN_00591c00 - clamps a value to 0
    void storeBlendState(float a1, float a2, float a3, float a4, uint32_t flags, float b1, float b2); // FUN_00581e90 - saves current blend data
    float getInterpolant();                     // FUN_00591160 - returns some interpolant
    int startBlend();                           // FUN_00583a30 - begins a blend and returns handle
    int combineBlends(int h1, int h2, float t, uint32_t flags); // FUN_005848f0 - combines two blend handles
    void endBlend();                            // FUN_0056fb60 - ends a blend stage
    int getResult();                            // FUN_00590360 - returns a result from the blend

    // Data members (offset from this)
    float* mFloatArray;                         // +0x00: pointer to array of floats (blend weights? indices?)
    uint32_t mArraySize;                        // +0x04: number of elements in mFloatArray
    // Possibly more members...
};

// Global constants
static const float THRESHOLD = 0.0f; // Actually DAT_00e2b1a4 - unknown value, likely a small threshold

// Note: param_1 is implicitly 'this'. The decompiler used 'in_EAX' for this.
// The function signature is adjusted accordingly.

int32_t AnimBlender::blendAnimations(void* descriptor, float inputX, float inputY, uint32_t flags, float blendFactor, float weight, int32_t blendType) {
    char descriptorByte = *(char*)((uint8_t*)descriptor + 1);
    if (descriptorByte < 2) {
        return 0;
    }

    uint32_t indexA = (uint32_t)*(int16_t*)(*(int*)((uint8_t*)descriptor + 0xC) + 2);
    int32_t offsetB = *(int*)((uint8_t*)descriptor + 0x10);
    uint32_t indexB = (uint32_t)*(int16_t*)(offsetB + 2);

    // Bounds check for indexA
    if (mArraySize <= indexA) {
        float zero = 0.0f;
        clampBound(&zero);
    }
    float valA = mFloatArray[indexA * 4]; // Note: The decompiler had *4, but maybe it's an array of floats? Actually it's *(float*)(*in_EAX + uVar3 * 4) - that suggests each element is 4 bytes, so mFloatArray is float*. So it's mFloatArray[indexA] (since indexA * 4 offsets incorrectly? Wait: uVar3*4 would be byte offset if mFloatArray is char*? But the decompiler treats in_EAX as int*, and *in_EAX is an int* to a float array. Then it adds uVar3*4 (bytes) and dereferences float. So mFloatArray is float*, and indexA is an index that should be multiplied by sizeof(float) (4 bytes) to get the correct element. But the decompiler adds uVar3 * 4 directly, so it's likely that mFloatArray is an array of floats, and uVar3 is the index. So the line should be valA = mFloatArray[indexA]; but the decompiler explicitly multiplies by 4. Let's check: *in_EAX is a pointer to float, but the decompiler uses *(float *)(*in_EAX + uVar3 * 4). This is correct because pointer arithmetic on int* would increment by 4 bytes per unit. However, if *in_EAX is float*, then *(float *)(*in_EAX + indexA) would be wrong because pointer + int gives float* offset by indexA*4. But the decompiler's expression is exactly that: it casts to float* and adds indexA*4 bytes. So it's actually doing float* + indexA, which is indexA*4 bytes. So the typecast is necessary. So I'll keep: valA = *(float*)((uint8_t*)mFloatArray + indexA * 4); But to simplify, assume mFloatArray is an array of floats and indexA is direct index. The decompiler's multiplication by 4 is redundant if it's a float*. I'll assume it's a float array, so valA = mFloatArray[indexA]; but I'll keep the multiplication to match decompiled logic. Actually the decompiler uses uVar3 * 4, then casts to float*. So if uVar3 is an index, then uVar3*4 is byte offset. So mFloatArray is of type char* or void*, not float*. I'll assume mFloatArray is a byte pointer to an array of floats. So:
    float valA = *(float*)(mFloatArray + indexA * 4);

    // Continue with other indices...
    float temp1 = (float)*(int16_t*)((uint8_t*)descriptor + 2);
    if (mArraySize <= (uint32_t)temp1) {
        float zero = 0.0f;
        clampBound(&zero);
    }
    float valB = *(float*)(mFloatArray + (int32_t)temp1 * 4); // local_28 initially

    // Actually the decompiler assigns local_28 from the array, then later uses it.
    // There is also local_24 which comes from indexB.
    float valC = *(float*)(mFloatArray + indexB * 4); // local_24

    // The code later uses valA (fVar5), valB (local_28), valC (local_24).

    if (blendFactor <= 0.0f) {
        int32_t somePtr = *(int32_t*)((uint8_t*)this + 0x7C);
        float storeX = inputX;
        float storeY = inputY;
        // Check flag bit 7 (assuming param_5 is flags)
        if ( ((~(flags >> 7) & 1) != 0) && (THRESHOLD < valB) ) { // Note: THRESHOLD is DAT_00e2b1a4
            storeY = valA - THRESHOLD;
            weight = THRESHOLD / weight; // weight is param_7
            float factor = THRESHOLD / (valB - THRESHOLD);
            *(float*)(somePtr + 0x28) = (valA - valB) * weight + *(float*)(somePtr + 0x28);
            storeX = factor * inputX * storeY;
            storeY = factor * inputY * storeY;
            *(float*)(somePtr + 0x1C) = (storeX - inputX) * weight + *(float*)(somePtr + 0x1C);
        }
        return getResult();
    }

    // If blendFactor is >0, check threshold
    if (THRESHOLD <= blendFactor) {
        // Store params for later blend
        storeBlendState(inputX, inputY, valB, weight, flags, valC, 0.0f?); // actually local_14 = valC? The decompiler has local_14 = local_24, local_18 = local_28, local_10 = param_7, local_c = param_5, etc.
        // But need to match actual arguments. The decompiler sets:
        // local_20 = param_3
        // local_1c = param_4
        // local_14 = local_24 (valC)
        // local_1c = param_4 (overwrites?)
        // Actually it's: local_20=param3, local_1c=param4, local_14=local_24, local_10=param7, local_c=param5, local_18=local_28
        // Then call FUN_00581e90 (storeBlendState)
        storeBlendState(inputX, inputY, valB, weight, flags, valC, 0.0f);
        return getResult();
    }

    // Blending between 0 and threshold
    float interpolantA = blendFactor;
    getInterpolant(); // returns something? But the decompiler just calls and discards?
    float interpolantB = interpolantA; // Actually FUN_00591160 is called twice with different args? The decompiler calls FUN_00591160() with no args? It says FUN_00591160() twice. Possibly it's a member function that returns a float based on some internal state? But it doesn't use the result? Hmm.
    // In the decompiler:
    // fVar5 = param_6; 
    // FUN_00591160();
    // fVar4 = fVar5;
    // FUN_00591160();
    // So it calls twice, but the return values are not stored. Possibly it modifies some global or internal? Might be a side effect.
    // We'll just call them as discard.

    // Then compute blend factors:
    #if 0
    // The code:
    // if (param_8 == 0) {
    //     fVar6 = fVar5;
    //     if (fVar5 <= fVar4) {
    //         fVar6 = fVar4;
    //     }
    // } else {
    //     fVar6 = (fVar4 - fVar5) * param_6 + fVar5;
    // }
    // So fVar6 is a blended value depending on blendType (param_8).
    #endif
    float fVar4 = interpolantA; // Actually fVar4 is assigned from fVar5 after first call? I think fVar5 is the original param_6, fVar4 becomes the result of first call? No, the decompiler doesn't assign return. I'm confused.

    // Better to look at the actual decompiled lines:
    /*
    fVar5 = param_6;
    FUN_00591160();
    fVar4 = fVar5;
    FUN_00591160();
    if (param_8 == 0) {
      fVar6 = fVar5;
      if (fVar5 <= fVar4) {
        fVar6 = fVar4;
      }
    }
    else {
      fVar6 = (fVar4 - fVar5) * param_6 + fVar5;
    }
    */
    // So fVar5 is the original param_6. After first FUN_00591160(), it doesn't change fVar5. Then fVar4 = fVar5 (so they are equal). Then second FUN_00591160() doesn't affect them. Then based on param_8, fVar6 is either max of fVar5 and fVar4 (they are equal so it's just fVar5) or an interpolated value (since fVar4 - fVar5 = 0, it becomes fVar5). So essentially fVar6 = fVar5. This seems trivial. Maybe FUN_00591160 has side effects that modify something else, like internal state. Or the decompiler is missing return values. Possibly it's a function that returns a float that is stored in some register that is later used? Very odd. I'll assume FUN_00591160 modifies some global or internal that affects later calculations. But for reconstruction, I'll call them and ignore return.

    float fVar6 = blendFactor; // simplified

    // Then store blend state with the computed values
    storeBlendState(inputX, inputY, valB, weight, flags, fVar4, fVar6);

    // Then conditionally call startBlend (FUN_00583a30) and combine
    if (fVar5 == local_24) {
        // Note: local_24 is valC? Actually local_24 is from earlier: local_24 = *(float*)(*in_EAX + (int)local_28 * 4)?? No, local_24 is from indexB. So compare fVar5 (param_6) with valC.
        if (fVar5 == valC) {
            int h1 = getResult(); // but getResult returns something? Actually FUN_00590360 is called, returns undefined4 (int). The decompiler assigns local_30 = FUN_00590360(param_1) and iVar2 = FUN_00590360(param_1). So two calls.
            int h1 = getResult();
            int h2 = getResult();
        }
    } else {
        float factor = THRESHOLD;
        if (THRESHOLD < valC) {
            factor = (fVar6 - THRESHOLD) / (valC - THRESHOLD);
        }
        int h1 = startBlend(); // FUN_00583a30
        int h2 = startBlend();
    }

    // Then combine if both handles nonzero
    int h1 = ...; // from above
    int h2 = ...;
    int result = 0;
    if (h1 != 0 && h2 != 0) {
        result = combineBlends(h1, h2, blendFactor, flags); // FUN_005848f0
    }

    // Cleanup
    endBlend(); // FUN_0056fb60
    endBlend();

    return result;
}

// End of reconstructed function. Note: Some details are approximate due to decompiler ambiguity.