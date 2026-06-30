// FUNC_NAME: Transform::lerpRotation (likely)
// Address: 0x006dacd0
// Interpolates a 9-float rotation matrix (at offsets 0x40-0x60) from current orientation towards a target.
// Uses a blend factor param3, clamped in a way that appears buggy (uninitialized local variable for > threshold case).
// Threshold is a global float _DAT_00d5780c (sMaxBlendFactor).

extern float sMaxBlendFactor; // _DAT_00d5780c

void __thiscall Transform::lerpRotation(Transform* this, const Transform* target, float blendFactor)
{
    float unusedLocal; // local_8 - uninitialized in original code, likely intended to be 1.0f
    float zeroFactor = 0.0f; // local_4

    float* chosenFactor = &unusedLocal;

    // Buggy clamp logic from original: if blendFactor <= threshold && blendFactor >= 0, use blendFactor;
    // else if blendFactor <= threshold but < 0, use 0;
    // else use uninitialized local (probably meant 1.0).
    if ((blendFactor <= sMaxBlendFactor) && (chosenFactor = &zeroFactor, 0.0f <= blendFactor))
    {
        chosenFactor = &blendFactor;
    }

    float t = *chosenFactor;

    // Lerp each of the 9 floats (3x3 rotation matrix) at offset 0x40-0x60
    for (int i = 0; i < 9; i++)
    {
        float* current = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + 0x40 + i * 4);
        float* targetVal = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(target) + 0x40 + i * 4);
        *current = *current + (*targetVal - *current) * t;
    }
}