// FUNC_NAME: TransformBlendNode::update
// Address: 0x0057d140
// This function processes a bitmask to determine if a specific index is valid,
// then computes a blended transform (possibly quaternion or 4x3 matrix) from input data.
// It uses a squared distance threshold for interpolation.

#include <cmath>

struct TransformBlendNode {
    float* m_transformData;       // +0x00: pointer to 8-float blocks (output)
    int whatever_0x04;            // +0x04: unused? (not referenced)
    int whatever_0x08;            // +0x08: unused?
    int* m_bitmaskArray;          // +0x0C: pointer to bitmask (uint array)
    int m_extraValue;             // +0x10: additional parameter (local_34)
    uint m_targetIndex;           // +0x14: index into bitmask array (uVar2)
};

// Constants
extern float DAT_00e2b1a4;  // squared distance threshold
extern float DAT_00e44564;  // some base value

// Forward declarations
void FUN_0057c010();  // unknown: likely resets/clears a cache
void FUN_0057cd80(int, int, int*, float*);  // fills array with 4 floats (quaternion?)

__thiscall uint TransformBlendNode::update(void) {
    float threshold = DAT_00e2b1a4;
    int* bitmaskPtr = m_bitmaskArray;
    uint idx = m_targetIndex;

    // Check if the bit at index idx is set in the bitmask
    if ((*(uint*)((int)bitmaskPtr + ((int)idx >> 5) * 4) & (1 << (idx & 0x1F))) != 0) {
        int extraVal = m_extraValue;  // +0x10
        float* outBase = m_transformData;  // +0x00
        uint curIdx = 0;
        int bitmaskBase = (int)bitmaskPtr;

        // Loop over all indices from 0 to idx-1 and clear associated data if bit set
        if (idx != 0) {
            do {
                if ((*(uint*)(bitmaskBase + ((int)curIdx >> 5) * 4) & (1 << (curIdx & 0x1F))) != 0) {
                    // Clear something 7 times per set bit
                    FUN_0057c010();
                    FUN_0057c010();
                    FUN_0057c010();
                    FUN_0057c010();
                    FUN_0057c010();
                    FUN_0057c010();
                    FUN_0057c010();
                    bitmaskPtr = (int*)bitmaskBase;  // restore after potential change
                }
                curIdx++;
            } while (curIdx < idx);
        }

        int local_38 = 0;
        float local_30[11];  // likely larger than needed
        FUN_0057cd80(0, 0, &local_38, local_30);

        // Compute squared magnitude of first 3 components
        float magSq = local_30[0] * local_30[0] + local_30[1] * local_30[1] + local_30[2] * local_30[2];
        float result;
        if (threshold <= magSq) {
            result = 0.0f;
        } else {
            result = sqrtf(threshold - magSq);
        }

        // If fourth component is non-zero, adjust by subtracting from global value
        if (local_30[3] != 0.0f) {
            result = DAT_00e44564 - result;
        }

        // Store result in local_30[3] (overwrites previous)
        local_30[3] = result;

        // Copy data from local_30 to output, using a selection mask
        float* src = local_30;
        float* dst = outBase;
        float* dstEnd = outBase + 8;  // copy 8 floats (two 4-float groups)
        char* mask = nullptr;         // initially null, increments per block
        while (dst != dstEnd) {
            if (mask == nullptr || *mask == '\x02') {
                // Copy 8 floats (two groups of 4)
                float a0 = src[0];
                float a1 = src[1];
                float a2 = src[2];
                float a3 = src[3];
                dst[0] = a0;
                dst[1] = a1;
                dst[2] = a2;
                dst[3] = a3;

                float b0 = src[4];
                float b1 = src[5];
                float b2 = src[6];
                float b3 = src[7];
                dst[4] = b0;
                dst[5] = b1;
                dst[6] = b2;
                dst[7] = b3;

                src += 8;
            }
            dst += 8;
            if (mask != nullptr) mask++;
        }

        // Return pointer with low bit set (success indicator)
        return ((uint)dst & 0xFFFFFF00) | 0x01;
    } else {
        // Bit not set: clear output to default (identity?)
        float* out = m_transformData;
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = 0.0f;
        out[3] = threshold;     // fourth component set to threshold
        out[4] = 0.0f;
        out[5] = 0.0f;
        out[6] = 0.0f;
        out[7] = threshold;     // second group fourth component also threshold
        return ((uint)out & 0xFFFFFF00) | 0x01;
    }
}