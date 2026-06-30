// FUNC_NAME: AnimationBlend::blendTransformations
// Function at 0x0058bba0: Handles blending between target values using keyframe data and easing.
// Parameters:
//   this (EAX): pointer to AnimationData with float array at [0] and count at [4]
//   param_1 (ECX?): context object, likely a StateMachine or Controller (uses offset 0x7c)
//   param_2: keyframe data structure (byte at +1, shorts at +2, pointer at +0x0C, pointer at +0x10)
//   param_3, param_4: target values (e.g., velocity components)
//   param_5: flags (bit 7 controls interpolation type)
//   param_6: blend factor (0.0 to threshold or beyond)
//   param_7: additional blend parameter (e.g., max magnitude)
//   param_8: interpolation mode (0 = max, 1 = weighted average)

extern float DAT_00e2b1a4; // global threshold constant (approx 0.000038? based on usage)

__thiscall int AnimationBlend::blendTransformations(int param_1, int param_2, float param_3, float param_4, uint param_5, float param_6, float param_7, int param_8)
{
    // Early exit if keyframe version < 2
    if (*(char *)(param_2 + 1) < 2)
        return 0;

    // Read keyframe indices from param_2 structure
    // param_2 layout:
    // +0x00: ?? (unused)
    // +0x01: byte version (checked)
    // +0x02: short index0 (used for third keyframe)
    // +0x0C: pointer to another struct with short at +2 (first keyframe index)
    // +0x10: pointer to another struct with short at +2 (second keyframe index)
    uint index1 = (uint)*(short *)(*(int *)(param_2 + 0x0C) + 2);
    int *secondStruct = *(int **)(param_2 + 0x10);
    float index2 = (float)*(short *)(secondStruct + 2); // actually short cast to float
    float index3 = (float)*(short *)(param_2 + 2);

    // Bounds checking against AnimationData count (thisPtr[1])
    // thisPtr layout:
    // +0x00: float* data
    // +0x04: uint count
    if (thisPtr[1] <= index1)
    {
        float dummy = 0.0f;
        FUN_00591c00(&dummy); // out-of-bounds handler (likely sets to 0)
    }
    float val1 = thisPtr[0][index1]; // first keyframe value

    if (thisPtr[1] <= (uint)index2)
    {
        float dummy = 0.0f;
        FUN_00591c00(&dummy);
    }
    float val2 = thisPtr[0][(int)index2]; // second keyframe value

    if (thisPtr[1] <= (uint)index3)
    {
        float dummy = 0.0f;
        FUN_00591c00(&dummy);
    }
    float val3 = thisPtr[0][(int)index3]; // third keyframe value

    // Branch based on blend factor param_6
    if (param_6 <= 0.0f)
    {
        // No blending: direct assignment
        int contextObj = *(int *)(param_1 + 0x7C); // object at +0x7C (e.g., PlayerCCTVariables)
        float outVal1 = param_3;
        float outVal2 = param_4;

        // Check flag (bit 7 of param_5) and threshold condition
        if ((~(param_5 >> 7) & 1) != 0 && DAT_00e2b1a4 < val3)
        {
            // Apply correction using keyframe values
            outVal2 = val1 - DAT_00e2b1a4;
            float invThreshold = DAT_00e2b1a4 / param_7;
            float scale = DAT_00e2b1a4 / (val3 - DAT_00e2b1a4);
            *(float *)(contextObj + 0x28) = (val1 - val3) * invThreshold + *(float *)(contextObj + 0x28);
            outVal1 = scale * param_3 * outVal2;
            outVal2 = scale * param_4 * outVal2;
            *(float *)(contextObj + 0x1C) = (outVal1 - param_3) * invThreshold + *(float *)(contextObj + 0x1C);
        }

        return FUN_00590360(param_1); // finalize/update state
    }

    if (DAT_00e2b1a4 <= param_6)
    {
        // Blend factor at or beyond threshold → use default interpolation
        float out1 = param_3;
        float out2 = param_4;
        float key3 = val3;
        float param7 = param_7;
        uint flags = param_5;
        float key2 = val2;

        FUN_00581e90(out1, out2, key3, param7, flags, key2, out1, out2); // template interpolation function
        return FUN_00590360(param_1);
    }

    // 0 < param_6 < DAT_00e2b1a4: smooth/weighted interpolation
    float fVar5 = param_6;
    FUN_00591160(); // first easing (likely returns something in fReg or modifies global)
    float fVar4 = fVar5;
    FUN_00591160(); // second easing

    // Compute fVar6 based on param_8
    float fVar6;
    if (param_8 == 0)
    {
        fVar6 = fVar5;
        if (fVar5 <= fVar4)
            fVar6 = fVar4;
    }
    else
    {
        fVar6 = (fVar4 - fVar5) * param_6 + fVar5; // lerp between the two eased values
    }

    // Prepare arguments for template interpolation
    float arg1 = param_3;
    float arg2 = param_4;
    float arg3 = val3;
    float arg4 = param_7;
    uint arg5 = param_5;
    float arg6 = val2; // actually fVar4? Wait, local_24 was set to fVar4 and local_14 to fVar6
    float arg7 = fVar6;
    float arg8 = fVar4; // local_24
    // Fun_00581e90 uses these locals; not all are passed as arguments in the raw asm, but here we simulate
    FUN_00581e90();

    // Handle two possible result paths
    int result1;
    int result2;
    if (fVar5 == fVar4)
    {
        result1 = FUN_00590360(param_1);
        result2 = FUN_00590360(param_1);
    }
    else
    {
        float blendWeight = DAT_00e2b1a4;
        if (DAT_00e2b1a4 < fVar4)
            blendWeight = (fVar6 - DAT_00e2b1a4) / (fVar4 - DAT_00e2b1a4);
        result1 = FUN_00583a30(param_1); // create handle 1
        result2 = FUN_00583a30(param_1); // create handle 2
    }

    int finalResult = 0;
    if (result1 != 0 && result2 != 0)
        finalResult = FUN_005848f0(result1, result2, param_6, param_5); // combine results

    FUN_0056fb60(); // cleanup/pop stack
    FUN_0056fb60();

    return finalResult;
}