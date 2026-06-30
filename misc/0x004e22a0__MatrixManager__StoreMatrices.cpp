// FUNC_NAME: MatrixManager::StoreMatrices
void __thiscall MatrixManager::StoreMatrices(float* matrixB, float* matrixA)
{
    // Copy 16 floats (4x4 matrix) from matrixB to global storage at 0x01218d40
    for (int i = 0; i < 16; i++)
    {
        gMatrixB[i] = matrixB[i];
    }

    // Copy 16 floats from matrixA to global storage at 0x01218d80
    for (int i = 0; i < 16; i++)
    {
        gMatrixA[i] = matrixA[i];
    }

    // Copy 16 floats from this (implicit parameter) to global storage at 0x01218dc0
    for (int i = 0; i < 16; i++)
    {
        gMatrixThis[i] = this->matrixData[i];
    }

    // Process the stored matrices (likely multiply or combine)
    ProcessMatrices();
}