// FUNC_NAME: Vector4::subtract
void __fastcall Vector4::subtract(float *thisVec, float *vecA, float *vecB)
{
    // Subtract vecB from vecA component-wise and store in thisVec
    // Note: The last component (w) is preserved from thisVec's original value
    float aX = vecA[0];
    float aY = vecA[1];
    float aZ = vecA[2];
    float aW = vecA[3];
    float bX = vecB[0];
    float bY = vecB[1];
    float bZ = vecB[2];
    float bW = vecB[3];
    float originalW = thisVec[3]; // +0x0C: preserve original w component

    thisVec[0] = aX - bX; // +0x00: x
    thisVec[1] = aY - bY; // +0x04: y
    thisVec[2] = aZ - bZ; // +0x08: z
    thisVec[3] = aW - bW; // +0x0C: w (temporarily set to subtraction result)
    thisVec[3] = originalW; // restore original w component
}