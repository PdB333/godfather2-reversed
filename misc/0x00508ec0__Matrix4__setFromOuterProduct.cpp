// FUNC_NAME: Matrix4::setFromOuterProduct
void __fastcall Matrix4::setFromOuterProduct(float *outMatrix, float *vecA, float *vecB)
{
    float ax = vecA[0]; // +0x00
    float ay = vecA[1]; // +0x04
    float az = vecA[2]; // +0x08
    float aw = vecA[3]; // +0x0C
    float bx = vecB[0]; // +0x00
    float by = vecB[1]; // +0x04
    float bz = vecB[2]; // +0x08
    
    // Compute dot product of vecA and vecB (only xyz components)
    float dot = ax * bx + ay * by + az * bz;
    
    // Set the matrix to the outer product of vecA and vecB scaled by the dot product
    outMatrix[0] = dot * ax; // +0x00
    outMatrix[1] = dot * ay; // +0x04
    outMatrix[2] = dot * az; // +0x08
    outMatrix[3] = dot * aw; // +0x0C
    
    // Restore the original w component (likely identity or previous value)
    outMatrix[3] = aw;
}