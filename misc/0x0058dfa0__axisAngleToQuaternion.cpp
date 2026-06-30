// FUNC_NAME: axisAngleToQuaternion
// Function at 0x0058dfa0: Converts an axis-angle representation to a quaternion.
// Input: in_EAX - pointer to 3 floats (axis * angle)
// Output: unaff_ESI - pointer to 4 floats (quaternion x,y,z,w)
// Uses two external math functions: sinf and cosf (likely wrappers at 0x00b99fcb and 0x00b99e20)
// Constants: epsilon (0x00e4462c), 1.0f (0x00e2b1a4), 0.5f (0x00e2cd54)

void axisAngleToQuaternion(float* inVec, float* outQuat)
{
    float x = inVec[0];
    float y = inVec[1];
    float z = inVec[2];
    float len = sqrtf(x * x + y * y + z * z);
    
    // Epsilon threshold (likely 0.0001f or similar)
    float epsilon = *(float*)0x00e4462c; // PTR_FUN_00e4462c is actually a float pointer
    if (len < epsilon)
    {
        outQuat[0] = 0.0f;
        outQuat[1] = 0.0f;
        outQuat[2] = 0.0f;
        outQuat[3] = 1.0f; // DAT_00e2b1a4 = 1.0f
        return;
    }
    
    float halfAngle = len * 0.5f; // DAT_00e2cd54 = 0.5f
    float sinHalf = sinf(halfAngle);
    float cosHalf = cosf(halfAngle);
    
    float invLen = 1.0f / len;
    outQuat[0] = sinHalf * invLen * x;
    outQuat[1] = sinHalf * invLen * y;
    outQuat[2] = sinHalf * invLen * z;
    outQuat[3] = cosHalf;
}