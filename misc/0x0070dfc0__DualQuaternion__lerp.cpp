// FUNC_NAME: DualQuaternion::lerp

void DualQuaternion::lerp(DualQuaternion& out, const DualQuaternion& other, float t) const {
    // Constants: likely 1.0f and a small epsilon. In the original, these were globals at 0xd5780c and 0xd5f168.
    const float kOne = 1.0f;          // _DAT_00d5780c
    const float kEpsilon = 1e-6f;     // DAT_00d5f168 (threshold)

    float oneMinusT = kOne - t;

    // Blend all 8 components of the dual quaternion (real quaternion and dual part)
    out.elems[0] = this->elems[0] * oneMinusT + other.elems[0] * t;
    out.elems[1] = this->elems[1] * oneMinusT + other.elems[1] * t;
    out.elems[2] = this->elems[2] * oneMinusT + other.elems[2] * t;
    out.elems[3] = this->elems[3] * oneMinusT + other.elems[3] * t;
    out.elems[4] = this->elems[4] * oneMinusT + other.elems[4] * t;
    out.elems[5] = this->elems[5] * oneMinusT + other.elems[5] * t;
    out.elems[6] = this->elems[6] * oneMinusT + other.elems[6] * t;
    out.elems[7] = this->elems[7] * oneMinusT + other.elems[7] * t;

    // Normalize the translation part (storage indices 4,5,6) to unit length.
    // This ensures the dual quaternion remains a unit dual quaternion after blending.
    float lenSq = out.elems[4] * out.elems[4] + out.elems[5] * out.elems[5] + out.elems[6] * out.elems[6];
    float len = sqrtf(lenSq);

    if (len < kEpsilon) {
        // If the blended translation is nearly zero, set it to a default unit vector (0,1,0).
        // This avoids division by zero and provides a safe fallback.
        out.elems[4] = 0.0f;
        out.elems[5] = kOne;
        out.elems[6] = 0.0f;
    } else {
        float invLen = kOne / len;
        out.elems[4] *= invLen;
        out.elems[5] *= invLen;
        out.elems[6] *= invLen;
    }
}