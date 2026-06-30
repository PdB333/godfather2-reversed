// FUNC_NAME: Matrix44TransformPoint
// Address: 0x0056b480
// Transforms a 3D point by a 4x4 matrix (column-major order).
// param_1: pointer to 16-float column-major matrix
// param_2: pointer to 3-float input vector (x, y, z)
// param_3: pointer to 4-float output vector (x', y', z', w')
// DAT_00e2b1a4 is a global scale factor (likely 1.0f unless overridden)

extern float g_transformScale; // DAT_00e2b1a4

void Matrix44TransformPoint(const float* matrix, const float* input, float* output)
{
    const float vx = input[0]; // +0x00
    const float vy = input[1]; // +0x04
    const float vz = input[2]; // +0x08

    // Column 0: rows 0,1,2,3 (offsets 0,1,2,3)
    const float m00 = matrix[0];
    const float m10 = matrix[1];
    const float m20 = matrix[2];
    const float m30 = matrix[3]; // translation? Actually column0 row3 is not translation normally; but used in final sum.

    // Column 1: offsets 4,5,6,7
    const float m01 = matrix[4];
    const float m11 = matrix[5];
    const float m21 = matrix[6];
    const float m31 = matrix[7];

    // Column 2: offsets 8,9,10,11
    const float m02 = matrix[8];
    const float m12 = matrix[9];
    const float m22 = matrix[10];
    const float m32 = matrix[11];

    // Column 3 (translation): offsets 12,13,14,15
    const float m03 = matrix[12];
    const float m13 = matrix[13];
    const float m23 = matrix[14];
    const float m33 = matrix[15]; // homogeneous coordinate (usually 1.0)

    // Result: output[0] = vx * m00 + vy * m01 + vz * m02 + (g_transformScale * m03)
    // Similarly for y and z; w component is vz*m20? Wait, careful: the code computes:
    // *param_3 = fVar2 * param_1[4] + fVar1 * *param_1 + fVar3 * param_1[8] + DAT * param_1[12];
    // That is: vy * m01 + vx * m00 + vz * m02 + (g_transformScale * m03)
    // Same ordering for other components.
    // So output[x] = vx*m00 + vy*m01 + vz*m02 + g_transformScale*m03
    // output[y] = vx*m10 + vy*m11 + vz*m12 + g_transformScale*m13
    // output[z] = vx*m20 + vy*m21 + vz*m22 + g_transformScale*m23
    // output[w] = vx*m30 + vy*m31 + vz*m32 + g_transformScale*m33

    output[0] = vx * m00 + vy * m01 + vz * m02 + g_transformScale * m03;
    output[1] = vx * m10 + vy * m11 + vz * m12 + g_transformScale * m13;
    output[2] = vx * m20 + vy * m21 + vz * m22 + g_transformScale * m23;
    output[3] = vx * m30 + vy * m31 + vz * m32 + g_transformScale * m33;
}