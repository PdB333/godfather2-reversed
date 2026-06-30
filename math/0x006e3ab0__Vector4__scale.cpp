// FUNC_NAME: Vector4::scale
// Function address: 0x006e3ab0
// Role: Multiplies each component of a 4D vector (this) by a scalar and stores result in output.
// The class Vector4 is a simple struct with 4 floats (x, y, z, w).
// __thiscall: this pointer in ECX (in_EAX), output pointer in first stack parameter, scalar in second.

struct Vector4 {
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C

    void scale(Vector4* out, float s) const {
        out->x = s * x;
        out->y = s * y;
        out->z = s * z;
        out->w = s * w;
    }
};