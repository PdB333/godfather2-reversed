// FUNC_NAME: Vector4::setScaledFromVector
// Reconstructed for x86 thiscall (ECX = this, EDX = src, stack = scale)
// Multiplies src (x,y,z) by scale and stores into this (x,y,z), leaves this->w unchanged.
// Address: 0x0056dcd0

class Vector4 {
public:
    float x, y, z, w;

    void __thiscall setScaledFromVector(const float* src, float scale)
    {
        // Save original w component (to preserve it)
        float oldW = this->w;

        // Scale the x, y, z components from source vector
        this->x = src[0] * scale;
        this->y = src[1] * scale;
        this->z = src[2] * scale;

        // Restore original w (unaffected by scaling)
        this->w = oldW;
    }
};