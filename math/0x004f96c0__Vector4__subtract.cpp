// FUNC_NAME: Vector4::subtract
void __fastcall Vector4::subtract(float *thisVec, float *vecA, float *vecB)
{
    // Subtract vecB from vecA and store in thisVec
    // Note: The 4th component (w) is preserved from thisVec, not overwritten
    float aY = vecA[1];
    float aZ = vecA[2];
    float aW = vecA[3];
    float bY = vecB[1];
    float bZ = vecB[2];
    float bW = vecB[3];
    float thisW = thisVec[3]; // Preserve original w component

    thisVec[0] = vecA[0] - vecB[0]; // x = Ax - Bx
    thisVec[1] = aY - bY;           // y = Ay - By
    thisVec[2] = aZ - bZ;           // z = Az - Bz
    thisVec[3] = aW - bW;           // w = Aw - Bw (temporary)
    thisVec[3] = thisW;             // Restore original w (overwrites subtraction result)
}