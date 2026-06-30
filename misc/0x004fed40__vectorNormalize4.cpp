// FUNC_NAME: vectorNormalize4
// Function at 0x004fed40: Normalizes a 4-element float vector (likely quaternion or homogeneous coordinate). 
// Prevents division by zero by checking squared length against epsilon (DAT_00e2cbe0). 
// If length is too small, outputs zero vector. Otherwise scales by 1/sqrt(length^2).
// Input vector passed via EDX (in_EAX in decompiler), output via ECX (param_1).

void __fastcall vectorNormalize4(float* outVec, const float* inVec)
{
    float fVar1 = inVec[0];
    float sqLen = fVar1 * fVar1 + inVec[1] * inVec[1] + inVec[2] * inVec[2] + inVec[3] * inVec[3];
    
    float scale;
    if (sqLen <= DAT_00e2cbe0)   // epsilon threshold (e.g., 1e-6)
    {
        scale = 0.0f;
    }
    else
    {
        scale = DAT_00e2b1a4 / sqrtf(sqLen);   // DAT_00e2b1a4 is likely 1.0f
    }
    
    outVec[0] = fVar1 * scale;
    outVec[1] = inVec[1] * scale;
    outVec[2] = inVec[2] * scale;
    outVec[3] = inVec[3] * scale;
}