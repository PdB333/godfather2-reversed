// FUNC_NAME: Transform::applyToPoint
void __thiscall Transform::applyToPoint(float *thisVec, float *quat, float *translation)
{
    // Quaternion rotation (likely conjugate) + translation
    float negX = DAT_00e44564 - quat[0]; // typically 0.0f - quat[0] (negate X)
    float negY = DAT_00e44564 - quat[1]; // negate Y
    float negZ = DAT_00e44564 - quat[2]; // negate Z
    float w = quat[3];                    // w component of quaternion

    // Temporary storage for helper function (likely quaternion multiplication or matrix construction)
    float temp[7]; // 28 bytes

    // First call: possibly initializing temp to identity?
    FUN_0056cba0();

    // Second call: process conjugate quaternion and store result
    FUN_0056cba0(temp, &negX);

    // Accumulate translation into output vector
    thisVec[0] += translation[0];
    thisVec[1] += translation[1];
    thisVec[2] += translation[2];
    thisVec[3] = 0.0f; // Ensure homogeneous coordinate is 0 (vector)
}