// FUNC_NAME: ModelInstance::updateCachedWorldMatrix
void __fastcall ModelInstance::updateCachedWorldMatrix(ModelInstance* this)
{
    // Call skeleton pre-update (e.g. updateBoneHierarchy)
    FUN_00415300();

    // +0x80: pointer to a render-relevant data block that holds a cached 4x4 world matrix at offset 0x30
    if (this->renderDataPtr != 0)
    {
        // +0x0c: pointer to the skeleton/pivot object (has a vtable)
        // vtable+0x60: virtual function returning a 16-float matrix (likely GetCombinedWorldMatrix)
        GetMatrixFunc getMatrix = (GetMatrixFunc)
            (*(int*)(*(int*)(this->skeletonObjectPtr) + 0x60));
        float* srcMatrix = getMatrix();

        float* destMatrix = (float*)(this->renderDataPtr + 0x30); // +0x30 is the matrix offset

        // Copy the 4x4 matrix (16 floats) from skeleton source to cached destination
        destMatrix[0]  = srcMatrix[0];
        destMatrix[1]  = srcMatrix[1];
        destMatrix[2]  = srcMatrix[2];
        destMatrix[3]  = srcMatrix[3];
        destMatrix[4]  = srcMatrix[4];
        destMatrix[5]  = srcMatrix[5];
        destMatrix[6]  = srcMatrix[6];
        destMatrix[7]  = srcMatrix[7];
        destMatrix[8]  = srcMatrix[8];
        destMatrix[9]  = srcMatrix[9];
        destMatrix[10] = srcMatrix[10];
        destMatrix[11] = srcMatrix[11];
        destMatrix[12] = srcMatrix[12];
        destMatrix[13] = srcMatrix[13];
        destMatrix[14] = srcMatrix[14];
        destMatrix[15] = srcMatrix[15];
    }
}