// FUNC_NAME: TransformNode::getWorldPosition
void __thiscall TransformNode::getWorldPosition(float *outPosition)
{
    // Offset +0x2e8: pointer to transform data (TransformData)
    int transformData = *(int *)(this + 0x2e8);
    
    // From transform data, +0x18 points to a 4x4 matrix (16 floats)
    float *matrix = *(float **)(transformData + 0x18);
    
    // Copy matrix into local stack (float[16])
    float localMatrix[16];
    localMatrix[0] = matrix[0];
    localMatrix[1] = matrix[1];
    localMatrix[2] = matrix[2];
    localMatrix[3] = matrix[3];
    localMatrix[4] = matrix[4];
    localMatrix[5] = matrix[5];
    localMatrix[6] = matrix[6];
    localMatrix[7] = matrix[7];
    localMatrix[8] = matrix[8];
    localMatrix[9] = matrix[9];
    localMatrix[10] = matrix[10];
    localMatrix[11] = matrix[11];
    localMatrix[12] = matrix[12];
    localMatrix[13] = matrix[13];
    localMatrix[14] = matrix[14];
    localMatrix[15] = matrix[15];
    
    // Translation components from matrix (row-major: indices 3,7,11? but here we use 7,13,14)
    // Actually the matrix orientation appears to be column-major? We'll keep the original indices.
    float tX = matrix[7];   // +0x1c from matrix start (element 7)
    float tY = matrix[13];  // element 13
    float tZ = matrix[14];  // element 14
    
    // Intermediate vector storage (output of the transform call)
    float result[3]; // stored as local_70 area: fStack_74, local_70[4] unused? Actually result[0]=fStack_6c, result[1]=fStack_68, result[2]=fStack_74
    
    // Call a virtual function on the transform data object to multiply matrix by a constant vector (DAT_00e3ac58)
    // The function is at vtable+0x1c (from transformData+0x10)
    void (**vtable)() = *(void (***)())(transformData + 0x10);
    void (*transformFunc)(float*, float*, float*) = (void (*)(float*, float*, float*))vtable[0x1c >> 2]; // offset 0x1c
    transformFunc(localMatrix, &DAT_00e3ac58, result); // DAT_00e3ac58 is a global 3D vector
    
    // Add the translation components and apply global scale factor (DAT_00e2cd54)
    float scale = DAT_00e2cd54; // float constant
    outPosition[0] = (result[0] + tY) * scale;  // note: uses fStack_6c (result[0]) + fVar1 (tY)
    outPosition[1] = (result[1] + tZ) * scale;  // fStack_68 (result[1]) + fVar3 (tZ)
    outPosition[2] = (result[2] + tX) * scale;  // fStack_74 (result[2]) + local_64 (tX)
}