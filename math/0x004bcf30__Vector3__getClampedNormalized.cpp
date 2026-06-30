// FUNC_NAME: Vector3::getClampedNormalized
// Address: 0x004bcf30
// Role: Computes a normalized version of the vector, clamped to zero if its squared length is below a threshold,
// and scaled to a fixed desired length. Writes result to output pointer.

class Vector3 {
public:
    float x, y, z; // Offset 0x00, 0x04, 0x08

    // Constants from global data addresses:
    // DAT_00e2cbe0: minimum squared length (threshold)
    // DAT_00e2b1a4: desired length after normalization
    static constexpr float kMinSqLength = 0.0f; // replaced with actual value if known
    static constexpr float kDesiredLength = 1.0f; // replaced with actual value if known

    void getClampedNormalized(float *out) const __thiscall {
        // this pointer assumed in ECX; out in EDX (first parameter)
        float lenSq = this->x * this->x + this->y * this->y + this->z * this->z;

        float scale;
        if (lenSq <= kMinSqLength) {
            scale = 0.0f; // Vector too short, output zero
        } else {
            scale = kDesiredLength / sqrtf(lenSq);
        }

        out[0] = this->x * scale;
        out[1] = this->y * scale;
        out[2] = this->z * scale;
    }
};