// FUNC_NAME: InterpolatePoseData
// Address: 0x005867d0
// Role: Blends two animation pose data sets (dual quaternion + translation) into an output, based on a type indicator and blend factor.

struct PoseDataRef {
    uint8_t* type;        // +0x00: pointer to type byte (0=empty, 2=has data)
    float* array1;        // +0x04: pointer to 8 floats (dual quaternion or two quaternions)
    float* array2;        // +0x08: pointer to 4 floats (translation/extra quaternion)
};

// Forward declaration of interpolation helper for array1 (likely quaternion slerp or dual quaternion blend)
void InterpolateArray1(float* outArray1, float blendFactor);

void __cdecl InterpolatePoseData(PoseDataRef* out, const PoseDataRef* srcA, const PoseDataRef* srcB, float blendFactor)
{
    uint8_t typeA = *srcA->type;
    uint8_t typeB = *srcB->type;

    if (typeA == 2) {
        // srcA has data
        *out->type = 2; // output is valid
        if (typeB == 2) {
            // Both sources have data: blend between them
            float* outArray1 = out->array1;
            // Interpolate array1 using helper (e.g. weighted average for dual quaternions)
            InterpolateArray1(outArray1, blendFactor);

            // Linear interpolation for array2 (translation)
            const float* aArray2 = srcA->array2;
            const float* bArray2 = srcB->array2;
            float* outArray2 = out->array2;
            for (int i = 0; i < 4; ++i) {
                outArray2[i] = (bArray2[i] - aArray2[i]) * blendFactor + aArray2[i];
            }
        } else {
            // Only srcA has data: copy all from srcA
            const float* aArray1 = srcA->array1;
            float* outArray1 = out->array1;
            for (int i = 0; i < 8; ++i) {
                outArray1[i] = aArray1[i];
            }
            const float* aArray2 = srcA->array2;
            float* outArray2 = out->array2;
            for (int i = 0; i < 4; ++i) {
                outArray2[i] = aArray2[i];
            }
        }
    } else {
        // srcA has no data (type != 2)
        if (typeB == 2) {
            // Only srcB has data: copy all from srcB
            *out->type = 2;
            const float* bArray1 = srcB->array1;
            float* outArray1 = out->array1;
            for (int i = 0; i < 8; ++i) {
                outArray1[i] = bArray1[i];
            }
            const float* bArray2 = srcB->array2;
            float* outArray2 = out->array2;
            for (int i = 0; i < 4; ++i) {
                outArray2[i] = bArray2[i];
            }
        } else {
            // Neither source has data: mark output as empty
            *out->type = 0;
        }
    }
}