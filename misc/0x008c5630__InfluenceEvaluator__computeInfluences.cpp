// FUNC_NAME: InfluenceEvaluator::computeInfluences

// Reconstructed C++ for function at 0x008c5630
// Purpose: Computes weighted influence values and stores sorted results into output structure.
// Output structure (param_2) layout:
//   [0] pointer to first influence array
//   [1] count of first influence array
//   [2] (unused/reset)
//   [3] pointer to second influence array
//   [4] count of second influence array
//   [5] (unused/reset)
//   [6] result value 1
//   [7] result value 2

// Known called functions (inferred names):
//   FUN_008c74d0 – possibly Context::prepareEvaluation or similar
//   FUN_008c3730 – computeBasicInfluence
//   FUN_008c51a0 – computeWeightedInfluence
//   FUN_008c52f0 – computeThresholdInfluence

// Comparison function at LAB_008bd9e0 assumed to be float descending compare

#include <stdlib.h>  // for qsort

// Forward declarations for internal functions
float __fastcall computeWeightedInfluence(int mode, float param, void* output);
float __fastcall computeThresholdInfluence(int mode, float param1, float param2, int unk, void* output);
float __fastcall computeBasicInfluence(float param1, float param2, void* output);
void __fastcall prepareEvaluationContext(void* context);

// Comparison callback for qsort (descending order of floats)
static int compareFloatDescending(const void* a, const void* b) {
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    if (fa < fb) return 1;
    if (fa > fb) return -1;
    return 0;
}

void* __thiscall InfluenceEvaluator::computeInfluences(
    int this_,                          // +0x00: this pointer
    void* resultStruct,                 // param_2: output structure
    float param3,                       // param_3: some input value
    float param4,                       // param_4: another input value
    int param5,                         // param_5: unk
    void* contextObj,                   // param_6: evaluation context
    int mode                            // param_7: 1=direct, 2=direct alternative, else normal
)
{
    // Initialize result structure
    *(int*)(resultStruct + 0x00) = 0;
    *(int*)(resultStruct + 0x04) = 0;
    *(int*)(resultStruct + 0x08) = 0;
    *(int*)(resultStruct + 0x0C) = 0;  // second array pointer
    *(int*)(resultStruct + 0x10) = 0;  // second array count
    *(int*)(resultStruct + 0x14) = 0;

    void* secondArrayPtr = (void*)((int)resultStruct + 0x0C);

    // Prepare context
    prepareEvaluationContext(*(void**)((int)contextObj + 0x40));

    if (mode == 1 || mode == 2) {
        // Direct evaluation modes
        float influenceResult1 = computeWeightedInfluence(mode, param3, resultStruct);
        *(float*)(resultStruct + 0x18) = influenceResult1;  // result value 1

        float influenceResult2 = computeThresholdInfluence(mode, param4, (float)param5, 0, secondArrayPtr);
        *(float*)(resultStruct + 0x1C) = influenceResult2;  // result value 2
    }
    else {
        // Normal evaluation
        float basicInfluence = 0.0f;
        if (*(int*)(this_ + 0x1D0) != 0) {  // m_bUseBasicInfluence
            basicInfluence = computeBasicInfluence(param4, (float)param5, secondArrayPtr);
        }

        float scaleFactor = *(float*)(this_ + 0x160);  // m_scaleFactor

        // Scale the second influence array if it exists and non-empty
        if (secondArrayPtr != 0 && *(int*)(resultStruct + 0x10) != 0) {
            for (unsigned int i = 0; i < *(unsigned int*)(resultStruct + 0x10); ++i) {
                float* array = *(float**)secondArrayPtr;
                array[i] = scaleFactor * array[i];
            }
        }

        // Store second result value scaled
        *(float*)(resultStruct + 0x1C) = scaleFactor * basicInfluence;  // result value 2

        if (*(int*)((int)contextObj + 0xFC) != 0) {  // some flag in context
            float influenceResult = computeWeightedInfluence(1, param3, resultStruct);
            *(float*)(resultStruct + 0x18) = influenceResult;  // result value 1
        }
    }

    // Sort first array if more than 1 element
    if (*(unsigned int*)(resultStruct + 0x04) > 1) {
        qsort(*(void**)resultStruct, *(unsigned int*)(resultStruct + 0x04), 4, compareFloatDescending);
    }

    // Sort second array if more than 1 element
    if (*(unsigned int*)(resultStruct + 0x10) > 1) {
        qsort(*(void**)(*(int*)(resultStruct + 0x0C)), *(unsigned int*)(resultStruct + 0x10), 4, compareFloatDescending);
    }

    return resultStruct;
}