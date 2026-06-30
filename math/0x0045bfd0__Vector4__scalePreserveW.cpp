// FUNC_NAME: Vector4::scalePreserveW
// Address: 0x0045bfd0
// Purpose: Scales the first three components of a 4D vector (x,y,z) by a factor, preserving the w component.
// This is typical for homogeneous vector scaling where w should remain unchanged (e.g., to avoid perspective distortion).

class Vector4 {
public:
    // Scale x, y, z by factor, keep w unchanged.
    // __thiscall: this (ECX) is the output, src (EDX) is source, factor (stack) is scale.
    void __thiscall scalePreserveW(const Vector4& src, float factor) {
        float originalW = this->w;           // Save original w
        this->x = src.x * factor;
        this->y = src.y * factor;
        this->z = src.z * factor;
        // w is NOT set from src; we restore the original w instead.
        // In assembly: in_EAX[3] = fVar1; (where fVar1 was saved from dest[3])
        this->w = originalW;
    }

    // Member offsets (assuming 4 floats at 0x00, 0x04, 0x08, 0x0C):
    // +0x00: x
    // +0x04: y
    // +0x08: z
    // +0x0C: w
    float x, y, z, w;
};