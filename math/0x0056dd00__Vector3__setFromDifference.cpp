// FUNC_NAME: Vector3::setFromDifference
// Function address: 0x0056dd00
// Purpose: Sets this vector's x,y,z components to (vecA - vecB). w component is preserved.
// Note: Uses __thiscall; this pointer passed in ecx, vecA in edx, vecB on stack.
// Decompiled from __fastcall artifact: param_1 is unused, param_2 = vecA, param_3 = vecB, in_EAX = this.
void __fastcall Vector3::setFromDifference(float *thisVec, float *vecA, float *vecB)
{
    float ax = vecA[0];
    float ay = vecA[1];
    float az = vecA[2];
    float aw = vecA[3];          // unused in subtraction but loaded
    float bx = vecB[0];
    float by = vecB[1];
    float bz = vecB[2];
    float bw = vecB[3];          // unused in subtraction but loaded
    float thisW = thisVec[3];    // preserve original w

    // Only x,y,z are set; w remains unchanged
    thisVec[0] = ax - bx;
    thisVec[1] = ay - by;
    thisVec[2] = az - bz;
    thisVec[3] = thisW;          // restore w (overwrites the subtraction's result for w)
}