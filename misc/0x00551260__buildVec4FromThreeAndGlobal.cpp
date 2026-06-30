// FUNC_NAME: buildVec4FromThreeAndGlobal
void buildVec4FromThreeAndGlobal(uint32_t* inputStruct)
{
    // Copy the first three fields from the input struct (offsets +0x00, +0x04, +0x08)
    uint32_t vecX = inputStruct[0];
    uint32_t vecY = inputStruct[1];
    uint32_t vecZ = inputStruct[2];

    // Fourth component is taken from a global constant (likely a D3DXVECTOR4 w component or similar)
    uint32_t globalW = DAT_00e2b1a4;

    // Build a local 4-element vector on the stack
    uint32_t localVec[4];
    localVec[0] = vecX;
    localVec[1] = vecY;
    localVec[2] = vecZ;
    localVec[3] = globalW;

    // Pass the local vector and a flag (0) to the underlying processing function
    FUN_009f1820(localVec, 0);
}