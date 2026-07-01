// FUNC_NAME: Matrix4x4::transformVectors
void __thiscall Matrix4x4::transformVectors(float *thisMatrix, float *outVectors, float *inVectors)
{
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
    int count;
    float *pIn, *pOut;
    
    // Load transformation matrix components (16 floats at this +0x00)
    m00 = thisMatrix[0];  // +0x00
    m01 = thisMatrix[1];  // +0x04
    m02 = thisMatrix[2];  // +0x08
    m03 = thisMatrix[3];  // +0x0C
    
    m10 = thisMatrix[4];  // +0x10
    m11 = thisMatrix[5];  // +0x14
    m12 = thisMatrix[6];  // +0x18
    m13 = thisMatrix[7];  // +0x1C
    
    m20 = thisMatrix[8];  // +0x20
    m21 = thisMatrix[9];  // +0x24
    m22 = thisMatrix[10]; // +0x28
    m23 = thisMatrix[11]; // +0x2C
    
    m30 = thisMatrix[12]; // +0x30
    m31 = thisMatrix[13]; // +0x34
    m32 = thisMatrix[14]; // +0x38
    m33 = thisMatrix[15]; // +0x3C
    
    // Transform each 4-component vector (homogeneous coordinates)
    count = in_EAX;
    if (count > 0) {
        do {
            float x = inVectors[0];
            float y = inVectors[1];
            float z = inVectors[2];
            float w = inVectors[3];
            
            outVectors[0] = x * m00 + y * m10 + z * m20 + w * m30;
            outVectors[1] = x * m01 + y * m11 + z * m21 + w * m31;
            outVectors[2] = x * m02 + y * m12 + z * m22 + w * m32;
            outVectors[3] = x * m03 + y * m13 + z * m23 + w * m33;
            
            inVectors += 4;
            outVectors += 4;
            count--;
        } while (count > 0);
    }
}