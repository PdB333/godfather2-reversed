// FUNC_NAME: Entity::getWorldMatrix
// Function at 0x008cf3d0
// Copies the 16-float (4x4) world matrix from the entity's transform component into an output buffer.
void __thiscall Entity::getWorldMatrix(int this_, undefined4* outMatrix)
{
    // Offset +0x0c: pointer to transform component (e.g., TransformComponent*)
    int* transformComponent = *(int**)(this_ + 0x0c);
    // Virtual function at vtable offset +0x60 on the transform component returns a float* to the raw matrix data
    undefined4* matrixData = (*(undefined4*(__thiscall**)(int*))(*(int*)transformComponent + 0x60))(transformComponent);

    // Copy 4x4 matrix (16 floats) to output
    outMatrix[0] = matrixData[0];
    outMatrix[1] = matrixData[1];
    outMatrix[2] = matrixData[2];
    outMatrix[3] = matrixData[3];
    outMatrix[4] = matrixData[4];
    outMatrix[5] = matrixData[5];
    outMatrix[6] = matrixData[6];
    outMatrix[7] = matrixData[7];
    outMatrix[8] = matrixData[8];
    outMatrix[9] = matrixData[9];
    outMatrix[10] = matrixData[10];
    outMatrix[11] = matrixData[11];
    outMatrix[12] = matrixData[12];
    outMatrix[13] = matrixData[13];
    outMatrix[14] = matrixData[14];
    outMatrix[15] = matrixData[15];
}