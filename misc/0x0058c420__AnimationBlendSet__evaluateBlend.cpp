// FUNC_NAME: AnimationBlendSet::evaluateBlend
// This function evaluates a blend of two or three animation curves at a given time.
// It takes an array of curve data (keyframes?) referenced by short indices.
// param_1: this pointer (AnimationBlendSet)
// param_2: pointer to blend input structure (time, number of curves, indices)
// param_3: pointer to float array (values for each curve)
// param_4: wrap boundary (e.g., 1.0 for normalized time)
// param_5: offset to add to result (e.g., additive blend offset)
// param_6: user data 1
// param_7: user data 2
// Returns blended float value.

// Assumptions based on decompiled code:
// - Structure at param_2:
//   byte +0: unused? (only +1 used)
//   byte +1: number of curves (2 or 3)
//   int +0xC: pointer to array of structs (each struct has short at +2 as index)
//   int +0x10: pointer to second array of structs
//   int +0x14: pointer to third array of structs (only if numCurves >= 3)
// - The float array at *param_3 holds values per curve, accessed via short indices.
// - Global constant DAT_00e2b1a4 is likely 0.0f or a sentinel for "no wrap".
// - Helper function calls: evaluateSingleCurve, blendTwoCurves, blendThreeCurves, assertWrap, cleanup.

#include <cstdint>

// Forward declarations of called functions (assumed from offsets)
static int evaluateSingleCurve(void* obj, int* curveArray, float time, float result, void* user1, void* user2);
static int blendTwoCurves(int curveA, int curveB, void* user);
static int blendThreeCurves(int curveA, int curveB, int curveC, void* user);
static void assertWrap(float* value); // FUN_00591c00 - sets *value=0.0 and breaks
static void debugBreak();              // FUN_0058ac50 - debug assertion break
static void cleanup();                 // FUN_0056fb60 - stack/state cleanup

// Assume global constant (maybe 0.0f)
extern const float kNoWrap; // DAT_00e2b1a4

float AnimationBlendSet::evaluateBlend(void* blendInput, int* curveArray, float wrapBoundary, float offset, void* user1, void* user2)
{
    // Read number of curves from blendInput structure at byte offset 1
    uint8_t numCurves = ((uint8_t*)blendInput)[1];

    if (numCurves < 2) {
        return 0.0f;
    }

    // Pointers to index arrays (each entry contains short index at +2)
    int* indexArray1 = *(int**)((uintptr_t)blendInput + 0xC);
    int* indexArray2 = *(int**)((uintptr_t)blendInput + 0x10);

    // Bounds checking for indices
    int16_t index1 = *(int16_t*)(indexArray1 + 2); // actually (indexArray1 + 2) as short? Ghidra shows local_8+2, but local_8 is int*
    // Correction: indexArray1 is pointer to a struct; at offset 2 is a short
    // But decompiled code: sVar2 = *(short *)(local_8 + 2)
    // So indexArray1 is cast to char*? Actually it's int*, but offset 2 is char offset? Wait: local_8 = *(int*)(param_2+0xC) -> that's a pointer to int array? Then sVar2 = *(short*)(local_8 + 2) means it reads from byte offset 2 from that pointer. So we treat it as base pointer.
    // To be safe, cast to char*:
    uint16_t index1 = *(uint16_t*)((uint8_t*)indexArray1 + 2);
    // Similar for index2 and index3.

    // Check bounds using piVar3[1] (curveArray[1]) as capacity?
    int capacity = curveArray[1]; // Assuming curveArray[1] is the count of floats? Or maybe max index+1?
    if ((uint32_t)capacity <= (uint32_t)index1) {
        float dummy = 0.0f;
        assertWrap(&dummy);
    }

    // Fetch the first curve value from curveArray[*curveArray]? Actually *piVar3 is the base pointer to float array, offset by index1*4.
    // In code: fVar1 = *(float *)(*piVar3 + sVar2 * 4);
    // So curveArray[0] is a pointer to float array.
    float* floatBase = (float*)curveArray[0];
    float curveVal1 = floatBase[index1];

    // Same for index2
    uint16_t index2 = *(uint16_t*)((uint8_t*)indexArray2 + 2);
    if ((uint32_t)capacity <= (uint32_t)index2) {
        float dummy = 0.0f;
        assertWrap(&dummy);
    }
    float curveVal2 = floatBase[index2];

    // Adjust curve values by wrapBoundary (substract constant kNoWrap)
    float adjVal1 = curveVal1 - kNoWrap;
    float adjVal2 = curveVal2 - kNoWrap;

    // Check if adjVal1 is within 2 integer units of wrapBoundary (maybe to snap)
    float time = wrapBoundary;
    if (wrapBoundary != adjVal1) {
        float absDiff = (wrapBoundary >= 0) ? (float)(int)(wrapBoundary) : (float)(-0x80000000 - (int)wrapBoundary); // absolute of integer part?
        // The code: fVar8 = param_4; if ((int)param_4 < 0) fVar8 = (float)(-0x80000000 - (int)param_4); // absolute of truncated integer? This seems to get the absolute integer part as float?
        // Actually it's trying to get the integer part's absolute value? Weird.
        // Let's simplify: They compute iVar5 = (int)fVar8 - (int)fVar9 and take absolute, then check if <=2.
        // This is a heuristic: if the integer parts of wrapBoundary and adjVal1 are within 2, then snap to wrapBoundary.
        // I'll reconstruct as:
        float intPartBoundary = (float)(int)wrapBoundary;
        float intPartAdj1 = (float)(int)adjVal1;
        int diff = (int)((intPartBoundary - intPartAdj1));
        if (diff < 0) diff = -diff;
        if (diff > 2) {
            // Not close, keep original adjVal1
        } else {
            time = wrapBoundary;
        }
    } else {
        time = wrapBoundary;
    }

    // Similar for adjVal2
    float time2 = wrapBoundary;
    if (wrapBoundary != adjVal2) {
        float intPartBoundary = (float)(int)wrapBoundary;
        float intPartAdj2 = (float)(int)adjVal2;
        int diff = (int)(intPartBoundary - (int)adjVal2);
        if (diff < 0) diff = -diff;
        if (diff <= 2) {
            time2 = wrapBoundary;
        } else {
            time2 = adjVal2;
        }
    } else {
        time2 = wrapBoundary;
    }

    // Modulo operation for curves
    if (curveVal1 == kNoWrap) {
        time = time - (float)(int)time; // frac part only
    } else if (adjVal1 < time) {
        // time = time - floor(time / adjVal1) * adjVal1  (modulo)
        time = time - (float)(int)(time / adjVal1) * adjVal1;
    }

    if (curveVal2 == kNoWrap) {
        time2 = (float)(int)time2; // integer part only? Actually: (float)(int)fVar9;
    } else {
        if (time2 <= adjVal2) {
            // nothing? (if time2 <= adjVal2, skip)
        } else {
            time2 = time2 - (float)(int)(time2 / adjVal2) * adjVal2;
        }
        // The code then does: fVar9 = fVar9 - fVar8; which is time2 = time2 - modResult? Need to match.
        // Wait, the decompiled: after the if-else block, it does:
        // if (fVar14 == DAT_00e2b1a4) { fVar8 = (float)(int)fVar9; } else { if (fVar9 <= fVar8) goto LAB_0058c5d7; fVar8 = (float)(int)(fVar9 / fVar8) * fVar8; }
        // fVar9 = fVar9 - fVar8;
        // So actually fVar8 is computed as modulo result, then fVar9 = fVar9 - fVar8 (so it's the remainder). I'll follow the original logic more precisely.
        // To avoid confusion, I'll replicate the assembly-like variable names.
    }

    // The next part splits based on numCurves >= 3 (byte at offset 1 >= 3)
    if (numCurves < 3) {
        // Two-curve blending
        float result1 = (time2 - wrapBoundary) + offset;
        float result2 = (time - wrapBoundary) + offset;
        // Some debug checks: if wrapBoundary < curveVal1, call debugBreak()
        if (wrapBoundary < curveVal1) {
            debugBreak();
        }
        if (wrapBoundary < curveVal2) {
            debugBreak();
        }
        int curveA = evaluateSingleCurve(this, curveArray, time, result2, user1, user2);
        int curveB = evaluateSingleCurve(this, curveArray, time2, result1, user1, user2);
        if (curveA == 0 || curveB == 0) {
            return 0.0f;
        } else {
            return (float)blendTwoCurves(curveA, curveB, user1);
        }
    } else {
        // Three-curve blending
        int* indexArray3 = *(int**)((uintptr_t)blendInput + 0x14);
        uint16_t index3 = *(uint16_t*)((uint8_t*)indexArray3 + 2);
        if ((uint32_t)capacity <= (uint32_t)index3) {
            float dummy = 0.0f;
            assertWrap(&dummy);
        }
        float curveVal3 = floatBase[index3];

        // Compute third adjusted time
        float adjTime3;
        if (curveVal3 == kNoWrap) {
            adjTime3 = wrapBoundary - (float)(int)wrapBoundary;
        } else {
            float adjVal3 = curveVal3 - kNoWrap;
            adjTime3 = wrapBoundary;
            if (adjVal3 < wrapBoundary) {
                adjTime3 = wrapBoundary - (float)(int)(wrapBoundary / adjVal3) * adjVal3;
            }
        }

        // Compute offsets for three results
        float result1 = (time2 - wrapBoundary) + offset;
        float result2 = (time - wrapBoundary) + offset;
        float result3 = (adjTime3 - wrapBoundary) + offset;

        // Debug checks for all three
        if (wrapBoundary < curveVal1) {
            debugBreak();
        }
        if (wrapBoundary < curveVal2) {
            debugBreak();
        }
        if (wrapBoundary < curveVal3) {
            debugBreak();
        }

        int curveA = evaluateSingleCurve(this, curveArray, time, result2, user1, user2);
        int curveB = evaluateSingleCurve(this, curveArray, time2, result1, user1, user2);
        int curveC = evaluateSingleCurve(this, curveArray, adjTime3, result3, user1, user2);

        int blendedAB;
        if (curveB == 0 || curveC == 0) {
            blendedAB = 0;
        } else {
            blendedAB = blendThreeCurves(curveB, curveC, user1);
        }
        if (curveA == 0 || blendedAB == 0) {
            cleanup();
            cleanup();
            return 0.0f;
        } else {
            float result = (float)blendTwoCurves(curveA, blendedAB, user1);
            cleanup();
            cleanup();
            return result;
        }
    }
    // Cleanup called at end in original code
    cleanup();
    cleanup();
    return 0.0f; // fallback (shouldn't reach)
}

// Stub definitions for called functions (actual implementations elsewhere)
static int evaluateSingleCurve(void* obj, int* curveArray, float time, float result, void* user1, void* user2) {
    // Returns an index/handle for the evaluated curve
    return 1; // placeholder
}

static int blendTwoCurves(int curveA, int curveB, void* user) {
    // Returns index of blended curve
    return 1;
}

static int blendThreeCurves(int curveA, int curveB, int curveC, void* user) {
    // Returns index of blended curve
    return 1;
}

static void assertWrap(float* value) {
    *value = 0.0f;
    // possibly break into debugger
}

static void debugBreak() {
    // debug assertion
}

static void cleanup() {
    // stack/state cleanup
}

const float kNoWrap = 0.0f; // Placeholder; actual value from DAT_00e2b1a4 unknown