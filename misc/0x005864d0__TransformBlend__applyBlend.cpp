// FUNC_NAME: TransformBlend::applyBlend
// Address: 0x005864d0
// Role: Blends two transform descriptors into an output descriptor.
// The descriptors contain a type byte (0x00 or 0x02), an 8-float array (likely rotation+translation),
// and a 4-float array (likely scale + extra). When both inputs are type 0x02, a scaled blend is performed
// using a global scale factor (DAT_00e2b1a4, probably 1.0f). Otherwise, one input is copied directly.

#include <cstdint>

// Forward declaration of an external helper function (possibly clears or initializes something)
extern void FUN_00582b70();

// Global blend scale factor (likely 1.0f)
extern float DAT_00e2b1a4;

// Structure representing a transform blend descriptor
// Each field is a pointer to the actual data stored elsewhere.
struct TransformBlendDescriptor {
    uint8_t* typePtr;        // +0x00: pointer to type byte (0x00 or 0x02)
    float*   data8;          // +0x04: pointer to 8 floats (e.g., quaternion + translation)
    float*   data4;          // +0x08: pointer to 4 floats (e.g., scale + w component)
};

// __thiscall or __cdecl? The calling convention is unknown; likely __cdecl given no this pointer.
void applyBlend(TransformBlendDescriptor* out, TransformBlendDescriptor* inA, TransformBlendDescriptor* inB) {
    uint8_t typeA = *inA->typePtr;   // First byte of input A's type
    uint8_t typeB = *inB->typePtr;   // First byte of input B's type

    if (typeA != 0x02) {
        if (typeB == 0x02) {
            // Copy from input B to output
            *out->typePtr = 0x02;
            // Copy 8 floats (data8)
            float* src8 = inB->data8;
            float* dst8 = out->data8;
            for (int i = 0; i < 8; ++i) {
                dst8[i] = src8[i];
            }
            // Copy 4 floats (data4)
            float* src4 = inB->data4;
            float* dst4 = out->data4;
            for (int i = 0; i < 4; ++i) {
                dst4[i] = src4[i];
            }
        } else {
            // Both are non-0x02: set output type to 0
            *out->typePtr = 0x00;
        }
        return;
    }

    // Input A is type 0x02
    *out->typePtr = 0x02;

    if (typeB == 0x02) {
        // Both are 0x02: perform scaled blend
        FUN_00582b70();   // Possibly clears/initializes some state
        float globalScale = DAT_00e2b1a4;

        float* scaleB = inB->data4; // data4 of input B
        float* scaleA = inA->data4; // data4 of input A
        float* outScale = out->data4;

        // Compute relative scale factors
        float invX = globalScale / scaleB[0];  // fVar16? Actually fVar16 used second component
        float invY = globalScale / scaleB[1];  // fVar17
        float invZ = globalScale / scaleB[2];  // not used? Wait: code only computes fVar16 for [1] and fVar17 for [2]
        // Actually the original code computes:
        // fVar16 = globalScale / scaleB[1];
        // fVar17 = globalScale / scaleB[2];

        // Then uses those for scaling the Y and Z components of scaleA.
        // For X, it uses globalScale / scaleB[0].
        // The W component becomes globalScale.

        outScale[0] = scaleA[0] * (globalScale / scaleB[0]);
        outScale[1] = scaleA[1] * (globalScale / scaleB[1]);
        outScale[2] = scaleA[2] * (globalScale / scaleB[2]);
        outScale[3] = globalScale;                // Overwrites any previous compute
    } else {
        // Only input A is 0x02: copy from input A to output
        // Copy 8 floats
        float* src8 = inA->data8;
        float* dst8 = out->data8;
        for (int i = 0; i < 8; ++i) {
            dst8[i] = src8[i];
        }
        // Copy 4 floats
        float* src4 = inA->data4;
        float* dst4 = out->data4;
        for (int i = 0; i < 4; ++i) {
            dst4[i] = src4[i];
        }
    }
}