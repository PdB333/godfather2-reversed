// FUNC_NAME: MathUtils::normalizeMatrixWithScaleCheck
void __fastcall normalizeMatrixWithScaleCheck(float* inMatrix, void* outMatrix)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float local_20;
    float local_1c;
    float local_18;
    float local_14;
    
    // Global constants for scale checking
    local_14 = DAT_00e2b1a4;  // target scale value (e.g., 1.0f)
    
    // Compute squared magnitude of first column (position/scale vector)
    local_20 = SQRT(inMatrix[0] * inMatrix[0] + inMatrix[1] * inMatrix[1] + inMatrix[2] * inMatrix[2]);
    
    // Check if magnitude is within acceptable range
    if ((DAT_00e44854 <= local_20) && (local_20 <= _DAT_00e4488c)) {
        // Within range: copy matrix as-is
        fVar1 = inMatrix[1];
        fVar2 = inMatrix[2];
        fVar3 = inMatrix[3];
        *(float*)((int)outMatrix + 0x40) = inMatrix[0];
        *(float*)((int)outMatrix + 0x44) = fVar1;
        *(float*)((int)outMatrix + 0x48) = fVar2;
        *(float*)((int)outMatrix + 0x4c) = fVar3;
        
        fVar1 = inMatrix[5];
        fVar2 = inMatrix[6];
        fVar3 = inMatrix[7];
        *(float*)((int)outMatrix + 0x50) = inMatrix[4];
        *(float*)((int)outMatrix + 0x54) = fVar1;
        *(float*)((int)outMatrix + 0x58) = fVar2;
        *(float*)((int)outMatrix + 0x5c) = fVar3;
        
        fVar1 = inMatrix[9];
        fVar2 = inMatrix[10];
        fVar3 = inMatrix[0xb];
        *(float*)((int)outMatrix + 0x60) = inMatrix[8];
        *(float*)((int)outMatrix + 100) = fVar1;
        *(float*)((int)outMatrix + 0x68) = fVar2;
        *(float*)((int)outMatrix + 0x6c) = fVar3;
        
        fVar1 = inMatrix[0xd];
        fVar2 = inMatrix[0xe];
        fVar3 = inMatrix[0xf];
        *(float*)((int)outMatrix + 0x70) = inMatrix[0xc];
        *(float*)((int)outMatrix + 0x74) = fVar1;
        *(float*)((int)outMatrix + 0x78) = fVar2;
        *(float*)((int)outMatrix + 0x7c) = fVar3;
        
        FUN_00424470();  // identity matrix set or similar
        return;
    }
    
    // Out of range: normalize the matrix
    local_20 = DAT_00e2b1a4 / local_20;  // compute normalization factor
    
    fVar1 = inMatrix[1];
    fVar2 = inMatrix[2];
    fVar3 = inMatrix[3];
    *(float*)((int)outMatrix + 0x40) = inMatrix[0];
    *(float*)((int)outMatrix + 0x44) = fVar1;
    *(float*)((int)outMatrix + 0x48) = fVar2;
    *(float*)((int)outMatrix + 0x4c) = fVar3;
    
    fVar1 = inMatrix[5];
    fVar2 = inMatrix[6];
    fVar3 = inMatrix[7];
    *(float*)((int)outMatrix + 0x50) = inMatrix[4];
    *(float*)((int)outMatrix + 0x54) = fVar1;
    *(float*)((int)outMatrix + 0x58) = fVar2;
    *(float*)((int)outMatrix + 0x5c) = fVar3;
    
    fVar1 = inMatrix[9];
    fVar2 = inMatrix[10];
    fVar3 = inMatrix[0xb];
    *(float*)((int)outMatrix + 0x60) = inMatrix[8];
    *(float*)((int)outMatrix + 100) = fVar1;
    *(float*)((int)outMatrix + 0x68) = fVar2;
    *(float*)((int)outMatrix + 0x6c) = fVar3;
    
    fVar1 = inMatrix[0xd];
    fVar2 = inMatrix[0xe];
    fVar3 = inMatrix[0xf];
    *(float*)((int)outMatrix + 0x70) = inMatrix[0xc];
    *(float*)((int)outMatrix + 0x74) = fVar1;
    *(float*)((int)outMatrix + 0x78) = fVar2;
    *(float*)((int)outMatrix + 0x7c) = fVar3;
    
    local_1c = local_20;
    local_18 = local_20;
    FUN_0056b0e0((float*)((int)outMatrix + 0x40), (int)outMatrix + 0x80, &local_20);  // apply normalization to matrix
    return;
}