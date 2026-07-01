// FUNC_NAME: scaleTransformData
// Function at 0x0081fd70: Scales all transform components (4x4 matrix + extra vectors) from source to dest by a uniform factor.
// Called after FUN_0081fac0 (likely normalization or pre-processing of source).
// Param1 (int) = dest pointer (returned), Param2 (int) = source pointer, Param3 (float) = uniform scale factor.
// Offsets suggest a struct with: 4x4 matrix at +0x50, vec3 at +0x90, vec2 at +0xa0.

#include <cstdint>

// Forward declaration of the unknown pre-processing function
void preprocessTransform(TransformData* src); // FUN_0081fac0

struct TransformData {
    float matrix[16];   // +0x50 (4x4 row-major)
    float extraVec3[3]; // +0x90
    float extraVec2[2]; // +0xa0
};

TransformData* scaleTransformData(TransformData* dest, const TransformData* src, float scale) {
    preprocessTransform(const_cast<TransformData*>(src)); // modifies src? (might be harmless if const-casted)

    // Scale the entire 4x4 matrix (16 floats)
    for (int i = 0; i < 16; ++i) {
        dest->matrix[i] = src->matrix[i] * scale;
    }

    // Scale the extra 3-component vector at +0x90
    dest->extraVec3[0] = src->extraVec3[0] * scale;
    dest->extraVec3[1] = src->extraVec3[1] * scale;
    dest->extraVec3[2] = src->extraVec3[2] * scale;

    // Scale the extra 2-component vector at +0xa0
    dest->extraVec2[0] = src->extraVec2[0] * scale;
    dest->extraVec2[1] = src->extraVec2[1] * scale;

    return dest;
}