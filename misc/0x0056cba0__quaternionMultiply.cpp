// FUNC_NAME: quaternionMultiply
// Function at 0x0056cba0: Multiplies two quaternions (q1 * q2). Quaternion order: [x, y, z, w].
void quaternionMultiply(const float* q1, const float* q2, float* out)
{
    // Load quaternion components (x, y, z, w)
    float q1x = q1[0];
    float q1y = q1[1];
    float q1z = q1[2];
    float q1w = q1[3];

    float q2x = q2[0];
    float q2y = q2[1];
    float q2z = q2[2];
    float q2w = q2[3];

    // Compute product components
    out[0] = q1w * q2x + q2w * q1x + (q1y * q2z - q1z * q2y); // x component
    out[1] = q1w * q2y + q2w * q1y + (q1z * q2x - q1x * q2z); // y component
    out[2] = q1w * q2z + q2w * q1z + (q1x * q2y - q1y * q2x); // z component
    out[3] = q1w * q2w - (q1x * q2x + q1y * q2y + q1z * q2z); // w component
}