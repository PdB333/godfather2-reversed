// FUNC_NAME: Math::quaternionMultiply
void Math::quaternionMultiply(const float* q1, const float* q2, float* result)
{
    float q1w = q1[3]; // +0x0C
    float q1x = q1[0]; // +0x00
    float q1y = q1[1]; // +0x04
    float q1z = q1[2]; // +0x08
    float q2w = q2[3]; // +0x0C
    float q2x = q2[0]; // +0x00
    float q2y = q2[1]; // +0x04
    float q2z = q2[2]; // +0x08

    // Quaternion multiplication: q1 * q2
    // Result = (w1*w2 - x1*x2 - y1*y2 - z1*z2,
    //           w1*x2 + x1*w2 + y1*z2 - z1*y2,
    //           w1*y2 - x1*z2 + y1*w2 + z1*x2,
    //           w1*z2 + x1*y2 - y1*x2 + z1*w2)
    result[0] = q1w * q2x + q2w * q1x + (q1y * q2z - q1z * q2y); // x component
    result[1] = q1w * q2y + q2w * q1y + (q1z * q2x - q1x * q2z); // y component
    result[3] = q1w * q2w - (q1z * q2z + q1y * q2y + q1x * q2x); // w component
    result[2] = q1w * q2z + q2w * q1z + (q1x * q2y - q1y * q2x); // z component
}