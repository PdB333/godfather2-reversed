// FUNC_NAME: Math::normalizeVector4

// Constants from the game binary (addresses noted)
extern float kNormalizeEpsilonSq; // 0x00e2cbe0 - squared length threshold
extern float kNormalizeScale;     // 0x00e2b1a4 - scaling factor (usually 1.0f)

// Normalizes a 4-component vector (e.g., quaternion) in-place or to another buffer.
// If squared length ≤ kNormalizeEpsilonSq, the result is the zero vector.
// inputVec: source vector
// outputVec: destination vector (can be same as inputVec)
void normalizeVector4(float* outputVec, const float* inputVec) {
    float w = inputVec[0];
    float x = inputVec[1];
    float y = inputVec[2];
    float z = inputVec[3];

    float sqLen = w * w + x * x + y * y + z * z;
    float invLen;

    if (sqLen <= kNormalizeEpsilonSq) {
        invLen = 0.0f;
    } else {
        invLen = kNormalizeScale / sqrtf(sqLen);
    }

    outputVec[0] = w * invLen;
    outputVec[1] = x * invLen;
    outputVec[2] = y * invLen;
    outputVec[3] = z * invLen;
}