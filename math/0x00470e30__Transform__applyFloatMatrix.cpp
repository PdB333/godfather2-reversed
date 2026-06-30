// FUNC_NAME: Transform::applyFloatMatrix
void __thiscall Transform::applyFloatMatrix(int *thisTransform, float *srcMatrix)
{
    // Compute scale factors from first three rows (axes) of the matrix
    // scale.x = length of first column
    thisTransform[0x4d] = (int)SQRT(srcMatrix[0] * srcMatrix[0] + srcMatrix[1] * srcMatrix[1] + srcMatrix[2] * srcMatrix[2]);
    // scale.y = length of second column
    thisTransform[0x4e] = (int)SQRT(srcMatrix[4] * srcMatrix[4] + srcMatrix[5] * srcMatrix[5] + srcMatrix[6] * srcMatrix[6]);
    // scale.z = length of third column
    thisTransform[0x4f] = (int)SQRT(srcMatrix[8] * srcMatrix[8] + srcMatrix[9] * srcMatrix[9] + srcMatrix[10] * srcMatrix[10]);

    // Copy the 4x4 matrix as integers (truncation from floats)
    float fVar1, fVar2, fVar3;
    
    // Row 0
    fVar1 = srcMatrix[1];
    fVar2 = srcMatrix[2];
    fVar3 = srcMatrix[3];
    thisTransform[0x34] = (int)srcMatrix[0];
    thisTransform[0x35] = (int)fVar1;
    thisTransform[0x36] = (int)fVar2;
    thisTransform[0x37] = (int)fVar3;

    // Row 1
    fVar1 = srcMatrix[5];
    fVar2 = srcMatrix[6];
    fVar3 = srcMatrix[7];
    thisTransform[0x38] = (int)srcMatrix[4];
    thisTransform[0x39] = (int)fVar1;
    thisTransform[0x3a] = (int)fVar2;
    thisTransform[0x3b] = (int)fVar3;

    // Row 2
    fVar1 = srcMatrix[9];
    fVar2 = srcMatrix[10];
    fVar3 = srcMatrix[11];
    thisTransform[0x3c] = (int)srcMatrix[8];
    thisTransform[0x3d] = (int)fVar1;
    thisTransform[0x3e] = (int)fVar2;
    thisTransform[0x3f] = (int)fVar3;

    // Row 3
    fVar1 = srcMatrix[13];
    fVar2 = srcMatrix[14];
    fVar3 = srcMatrix[15];
    thisTransform[0x40] = (int)srcMatrix[12];
    thisTransform[0x41] = (int)fVar1;
    thisTransform[0x42] = (int)fVar2;
    thisTransform[0x43] = (int)fVar3;

    // Enforce affine transformation: last column = (0,0,0,1)
    thisTransform[0x37] = 0;  // row0,col3 = 0
    thisTransform[0x3b] = 0;  // row1,col3 = 0
    thisTransform[0x3f] = 0;  // row2,col3 = 0
    thisTransform[0x43] = DAT_00e2b1a4; // row3,col3 = 1.0f (as integer 0x3f800000)

    // Notify engine (e.g., node update)
    FUN_006101b0();                  // likely update bounding box or transform cache
    (*(void (**)(void))(*thisTransform + 0x68))(); // virtual call for additional processing
}