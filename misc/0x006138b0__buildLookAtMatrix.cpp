// FUNC_NAME: buildLookAtMatrix
// Function address: 0x006138b0
// Builds a 4x4 look-at (view) matrix from eye, target, and up vectors.
// param_1: eye position (float[3])
// param_2: target position (float[3])
// param_3: up vector (float[3])
// param_4: output 4x4 column-major matrix (float[16])
void buildLookAtMatrix(const float* eye, const float* target, const float* up, float* outMatrix) {
    // Constants from the data section (likely floats)
    const float one = 1.0f;            // DAT_00e2b1a4
    const float epsilon = 1e-37f;      // DAT_00e2cbe0 (small threshold to avoid division by zero)
    const float zero = 0.0f;           // DAT_00e44564

    // Compute forward direction from eye to target
    float dx = target[0] - eye[0];
    float dy = target[1] - eye[1];
    float dz = target[2] - eye[2];

    // Normalize forward direction
    float lenSq = dx*dx + dy*dy + dz*dz;
    float len;
    if (lenSq <= epsilon) {
        len = 0.0f;
    } else {
        len = one / sqrtf(lenSq); // one/L = normalized factor
    }
    float forward[3] = { dx * len, dy * len, dz * len };

    // Compute right vector = cross(up, forward)
    float right[3];
    right[0] = up[1]*forward[2] - up[2]*forward[1];
    right[1] = up[2]*forward[0] - up[0]*forward[2];
    right[2] = up[0]*forward[1] - up[1]*forward[0];

    // Normalize right vector
    float lenRSq = right[0]*right[0] + right[1]*right[1] + right[2]*right[2];
    float rLen;
    if (lenRSq <= epsilon) {
        rLen = 0.0f;
    } else {
        rLen = one / sqrtf(lenRSq);
    }
    right[0] *= rLen;
    right[1] *= rLen;
    right[2] *= rLen;

    // Compute up vector = cross(forward, right) (re-orthogonalize)
    float upNew[3];
    upNew[0] = forward[1]*right[2] - forward[2]*right[1];
    upNew[1] = forward[2]*right[0] - forward[0]*right[2];
    upNew[2] = forward[0]*right[1] - forward[1]*right[0];

    // Build column-major 4x4 view matrix
    // First column: right vector
    outMatrix[0]  = right[0];
    outMatrix[4]  = right[1];
    outMatrix[8]  = right[2];
    outMatrix[12] = - (eye[0]*right[0] + eye[1]*right[1] + eye[2]*right[2]);

    // Second column: up vector (re-orthogonalized)
    outMatrix[1]  = upNew[0];
    outMatrix[5]  = upNew[1];
    outMatrix[9]  = upNew[2];
    outMatrix[13] = - (eye[0]*upNew[0] + eye[1]*upNew[1] + eye[2]*upNew[2]);

    // Third column: forward vector
    outMatrix[2]  = forward[0];
    outMatrix[6]  = forward[1];
    outMatrix[10] = forward[2];
    outMatrix[14] = - (eye[0]*forward[0] + eye[1]*forward[1] + eye[2]*forward[2]);

    // Fourth column: identity (0,0,0,1)
    outMatrix[3]  = zero;
    outMatrix[7]  = zero;
    outMatrix[11] = zero;
    outMatrix[15] = one;
}