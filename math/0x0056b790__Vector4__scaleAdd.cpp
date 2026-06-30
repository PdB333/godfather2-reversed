// FUNC_NAME: Vector4::scaleAdd
void __thiscall Vector4::scaleAdd(const float* vecA, float scalar, float* result) const {
    // This function computes: result[i] = scalar * this[i] + vecA[i] for i=0..3
    // It performs a linear combination: result = vecA + scalar * (*this)
    // Used for vector scaling and addition operations (e.g., interpolations, blends)
    float vx = this[0];
    float vy = this[1];
    float vz = this[2];
    float vw = this[3];
    result[0] = scalar * vx + vecA[0];
    result[1] = scalar * vy + vecA[1];
    result[2] = scalar * vz + vecA[2];
    result[3] = scalar * vw + vecA[3];
}