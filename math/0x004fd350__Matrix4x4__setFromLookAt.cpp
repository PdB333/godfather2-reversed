// FUNC_NAME: Matrix4x4::setFromLookAt
// Address: 0x004fd350
// Builds a 4x4 transformation matrix from a position and a target point.
// The matrix is stored as columns: right (col0), up (col1), look (col2), position (col3).
// Uses a world-up vector (1.0f, 0.0f, 0.0f) by default, with special handling for near-vertical look directions.

const float WORLD_UP = 1.0f;            // DAT_00e2b1a4 (component for world up, default y=1.0 but treated as component value)
const float EPSILON_NORMALIZE = 1e-10f; // DAT_00e2cbe0 (threshold to avoid division by zero in normalization)
const float EPSILON_LOCK = 1e-8f;       // DAT_00e2cd58 (threshold for gimbal lock detection)

void Matrix4x4::setFromLookAt(const float* position, const float* target)
{
    float diff[4];  // target - position

    // Store position in column 3 (indices 12-15)
    this[12] = position[0];
    this[13] = position[1];
    this[14] = position[2];
    this[15] = position[3];

    // Compute and store look direction (target - position) in column 2 (indices 8-11)
    diff[0] = target[0] - position[0];
    diff[1] = target[1] - position[1];
    diff[2] = target[2] - position[2];
    diff[3] = target[3] - position[3];

    this[8] = diff[0];
    this[9] = diff[1];
    this[10] = diff[2];
    this[11] = diff[3];

    // Normalize look direction
    float lenSq = diff[0]*diff[0] + diff[1]*diff[1] + diff[2]*diff[2] + diff[3]*diff[3];
    if (lenSq <= EPSILON_NORMALIZE)
        lenSq = 0.0f;
    else
        lenSq = WORLD_UP / sqrtf(lenSq);

    float lookX = diff[0] * lenSq;
    float lookY = diff[1] * lenSq;
    float lookZ = diff[2] * lenSq;
    float lookW = diff[3] * lenSq; // not used for cross

    // Store normalized look back into column 2
    this[8] = lookX;
    this[9] = lookY;
    this[10] = lookZ;
    this[11] = lookW;

    // Determine world up vector components (avoid gimbal lock)
    float upX, upY, upZ;
    upX = 0.0f;
    upY = WORLD_UP;   // default up along Y
    upZ = 0.0f;

    if (fabsf(lookY) >= EPSILON_LOCK)    // if look is not near vertical
    {
        upX = 0.0f;
        if (fabsf(lookX) < EPSILON_LOCK) // and look is near X? -> switch up to Z
        {
            upZ = WORLD_UP;
            upY = 0.0f;
            // goto result
        }
        // else up stays (0,1,0)
    }
    else // look is near vertical (Y component small) -> switch up to X
    {
        upX = WORLD_UP;
        upY = 0.0f;
    }

    // Compute right vector = cross(up, look) -> stored in column 0 (indices 0-3)
    float rightX = upY * lookZ - upZ * lookY;
    float rightY = upZ * lookX - upX * lookZ;
    float rightZ = upX * lookY - upY * lookX;
    float rightW = 0.0f; // fourth component is 0 for vector

    this[0] = rightX;
    this[1] = rightY;
    this[2] = rightZ;
    this[3] = rightW;

    // Normalize right vector
    float rLenSq = rightX*rightX + rightY*rightY + rightZ*rightZ + rightW*rightW;
    if (rLenSq <= EPSILON_NORMALIZE)
        rLenSq = 0.0f;
    else
        rLenSq = WORLD_UP / sqrtf(rLenSq);

    this[0] *= rLenSq;
    this[1] *= rLenSq;
    this[2] *= rLenSq;
    this[3] *= rLenSq;

    // Scale right to world-up magnitude? The original code multiplies by WORLD_UP again after normalization.
    this[0] *= WORLD_UP;
    this[1] *= WORLD_UP;
    this[2] *= WORLD_UP;
    this[3] *= WORLD_UP;

    // Compute up vector = cross(look, right) -> stored in column 1 (indices 4-7)
    float upFinalX = this[2] * lookY - this[1] * lookZ;  // rightZ*lookY - rightY*lookZ
    float upFinalY = this[0] * lookZ - this[2] * lookX;  // rightX*lookZ - rightZ*lookX
    float upFinalZ = this[1] * lookX - this[0] * lookY;  // rightY*lookX - rightX*lookY
    float upFinalW = this[3] * lookW - this[3] * lookW;  // 0

    this[4] = upFinalX;
    this[5] = upFinalY;
    this[6] = upFinalZ;
    this[7] = upFinalW;
}