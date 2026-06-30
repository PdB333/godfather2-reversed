// FUNC_NAME: Vector3::crossProduct
// Function address: 0x0058a7f0
// Reconstructed C++: Computes cross product of two 3D vectors (stored as float[4]) and writes result
// The function takes 'this' as first vector (passed in ECX), second vector in EAX, result in param_2 (stack)
// This is likely a fastcall-like member function, but we'll model as __thiscall with explicit parameter for other
// Note: The fourth component (w) of both vectors is ignored; result w is set to zero.

class Vector3 {
public:
    float x, y, z, w; // +0x00 to +0x0C

    // Cross product: this x other -> result
    // __thiscall: this in ECX, other in EAX, result in param_2 (stack)
    void __thiscall crossProduct(const Vector3& other, Vector3& result) {
        // Extract components of this (first vector)
        float a1 = this->x;
        float a2 = this->y;
        float a3 = this->z;
        float a4 = this->w; // not used in cross product

        // Extract components of other (second vector)
        float b1 = other.x;
        float b2 = other.y;
        float b3 = other.z;
        float b4 = other.w; // not used in cross product

        // Compute cross product components
        result.x = a2 * b3 - a3 * b2;
        result.y = a3 * b1 - a1 * b3;
        result.z = a1 * b2 - a2 * b1;
        result.w = a4 * b4 - a4 * b4; // always 0.0f
    }
};
// Note: The original decompiled code uses in_EAX for the second vector and param_2 for output.
// This reconstruction aligns with the observed register usage and produces the same computation.