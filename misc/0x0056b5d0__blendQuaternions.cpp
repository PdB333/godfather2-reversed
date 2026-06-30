// FUNC_NAME: blendQuaternions
// Address: 0x0056b5d0
// Role: Performs a weighted sum of two quaternions (4-component vectors).
// Computes: result = weight2 * quat2 + weight1 * quat1 (component-wise)
void blendQuaternions(float weight1, float* quat1, float weight2, float* quat2, float* result)
{
    float q1_1 = quat1[1];
    float q1_2 = quat1[2];
    float q1_3 = quat1[3];
    float q2_1 = quat2[1];
    float q2_2 = quat2[2];
    float q2_3 = quat2[3];

    result[0] = weight2 * quat2[0] + weight1 * quat1[0];
    result[1] = weight2 * q2_1 + weight1 * q1_1;
    result[2] = weight2 * q2_2 + weight1 * q1_2;
    result[3] = weight2 * q2_3 + weight1 * q1_3;
}