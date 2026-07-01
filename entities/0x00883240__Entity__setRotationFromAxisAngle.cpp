// FUNC_NAME: Entity::setRotationFromAxisAngle
// Function address: 0x00883240
// Sets a 4x3 affine transformation matrix from an axis-angle representation.
// The matrix is stored at offset 0x80 (12 floats, row-major with 4-byte padding per row).
// param_2 and param_3 are likely axis components (x, y) and param_4 is the angle (radians).
// The angle is clamped to [0, g_maxAngle] where g_maxAngle is a global constant.

void __thiscall Entity::setRotationFromAxisAngle(int thisPtr, float axisX, float axisY, float angle)
{
    float clampedAngle;
    float local_70[8]; // 32 bytes, likely a quaternion or intermediate representation
    float matrix[12];  // 12 floats for the 4x3 matrix (4 rows, 3 columns)

    // Clamp angle to valid range [0, g_maxAngle]
    clampedAngle = 0.0f;
    if ((angle <= 0.0f) || (clampedAngle = g_maxAngle, g_maxAngle <= angle)) {
        angle = clampedAngle;
    }

    // Convert axis-angle to quaternion (or other representation)
    // FUN_0056db60: likely quaternionFromAxisAngle(angle, axisX, axisY, output)
    quaternionFromAxisAngle(angle, axisX, axisY, local_70);

    // Convert quaternion to 4x3 matrix
    // FUN_0056dc20: likely matrixFromQuaternion(local_70, matrix)
    matrixFromQuaternion(local_70, matrix);

    // Copy matrix into object's transform at offset 0x80
    // Offsets: row0: +0x80, +0x84, +0x88; row1: +0x90, +0x94, +0x98;
    // row2: +0xa0, +0xa4, +0xa8; row3: +0xb0, +0xb4, +0xb8
    *(float*)(thisPtr + 0x80) = matrix[0];
    *(float*)(thisPtr + 0x84) = matrix[1];
    *(float*)(thisPtr + 0x88) = matrix[2];
    *(float*)(thisPtr + 0x90) = matrix[3];
    *(float*)(thisPtr + 0x94) = matrix[4];
    *(float*)(thisPtr + 0x98) = matrix[5];
    *(float*)(thisPtr + 0xa0) = matrix[6];
    *(float*)(thisPtr + 0xa4) = matrix[7];
    *(float*)(thisPtr + 0xa8) = matrix[8];
    *(float*)(thisPtr + 0xb0) = matrix[9];
    *(float*)(thisPtr + 0xb4) = matrix[10];
    *(float*)(thisPtr + 0xb8) = matrix[11];

    // Multiply the new matrix with itself (likely to combine with existing transform or normalize)
    // FUN_0043a2a0: matrixMultiplyOrNormalize(matrixPtr, matrixPtr)
    matrixMultiplyOrNormalize((float*)(thisPtr + 0x80), (float*)(thisPtr + 0x80));
}