// FUNC_NAME: UnknownClass::computeSmoothedDelta
// Address: 0x0077eaa0
// This function takes a this pointer (param_1), a pointer to 4 float values (param_2), an unused param_3, and a scalar multiplier (param_4).
// It applies per-component smoothing (damping) to each of the 4 input values using stored coefficients at offsets +0x60, +0x64, +0x68, +0x6c,
// clamps the smoothed values between 0.0 and a global maximum (DAT_00d691d8), then computes the sum of the deltas (smoothed - original)
// and multiplies that sum by param_4.
// If the integer at +0x54 equals 0x25 (37), it instead returns FUN_0071e350(param_2) * param_4, presumably a special case.

float __thiscall UnknownClass::computeSmoothedDelta(
    void* thisPtr,
    float* inputValues,   // pointer to 4 floats, typically a color or vector component
    int unusedParam3,     // not used in this function
    float multiplier      // scaling factor for the final delta sum
)
{
    float fVar1;  // temporary for first component
    float fVar2;  // temporary for second component
    float fVar3;  // temporary for third component
    float fVar4;  // temporary for fourth component
    float fVar6;  // smoothed value for first component
    float fVar7;  // smoothed value for second component
    float fVar8;  // smoothed value for third component
    float fVar9;  // smoothed value for fourth component
    float10 fVar5; // extended precision result for special case

    // Check for special case: if field at +0x54 is 0x25
    if (*(int*)((char*)thisPtr + 0x54) == 0x25) {
        fVar5 = FUN_0071e350(inputValues); // calculates something from input (perhaps magnitude)
        return (float)fVar5 * multiplier;
    }

    // ----- First component (index 0) -----
    fVar1 = inputValues[0];
    fVar6 = fVar1;
    // Offset +0x60: first smoothing factor
    {
        float smoothFactor = *(float*)((char*)thisPtr + 0x60);
        if (smoothFactor != 0.0f) {
            // Smoothing formula: (globalMax - original) * globalCoeff * smoothFactor + original
            fVar6 = (DAT_00d691d8 - fVar1) * DAT_00d5ef84 * smoothFactor + fVar1;
            // Clamp to [0.0, globalMax]
            if (fVar6 > 0.0f) {
                if (fVar6 >= DAT_00d691d8) {
                    fVar6 = DAT_00d691d8;
                }
            } else {
                fVar6 = 0.0f;
            }
        }
    }

    // ----- Second component (index 1) -----
    fVar2 = inputValues[1];
    fVar7 = fVar2;
    // Offset +0x64: second smoothing factor (note: this is 100 decimal = 0x64)
    {
        float smoothFactor = *(float*)((char*)thisPtr + 0x64);
        if (smoothFactor != 0.0f) {
            fVar7 = (DAT_00d691d8 - fVar2) * DAT_00d5ef84 * smoothFactor + fVar2;
            if (fVar7 > 0.0f) {
                if (fVar7 >= DAT_00d691d8) {
                    fVar7 = DAT_00d691d8;
                }
            } else {
                fVar7 = 0.0f;
            }
        }
    }

    // ----- Third component (index 2) -----
    fVar3 = inputValues[2];
    fVar8 = fVar3;
    // Offset +0x68: third smoothing factor
    {
        float smoothFactor = *(float*)((char*)thisPtr + 0x68);
        if (smoothFactor != 0.0f) {
            fVar8 = (DAT_00d691d8 - fVar3) * DAT_00d5ef84 * smoothFactor + fVar3;
            if (fVar8 > 0.0f) {
                if (fVar8 >= DAT_00d691d8) {
                    fVar8 = DAT_00d691d8;
                }
            } else {
                fVar8 = 0.0f;
            }
        }
    }

    // ----- Fourth component (index 3) -----
    fVar4 = inputValues[3];
    fVar9 = fVar4;
    // Offset +0x6c: fourth smoothing factor
    {
        float smoothFactor = *(float*)((char*)thisPtr + 0x6c);
        if (smoothFactor != 0.0f) {
            fVar9 = (DAT_00d691d8 - fVar4) * DAT_00d5ef84 * smoothFactor + fVar4;
            if (fVar9 > 0.0f) {
                if (fVar9 >= DAT_00d691d8) {
                    fVar9 = DAT_00d691d8;
                }
            } else {
                fVar9 = 0.0f;
            }
        }
    }

    // Compute sum of deltas: (smoothed - original) for each component
    // Then multiply by multiplier and return (converted to float10)
    return (float10)((fVar9 - fVar4) + (fVar8 - fVar3) + (fVar7 - fVar2) + (fVar6 - fVar1)) * (float10)multiplier;
}