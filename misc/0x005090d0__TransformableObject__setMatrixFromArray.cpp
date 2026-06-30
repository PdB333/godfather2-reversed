// FUNC_NAME: TransformableObject::setMatrixFromArray
void __thiscall TransformableObject::setMatrixFromArray(TransformableObject* this, unsigned int* srcData)
{
    if (srcData != nullptr) {
        // Set flag bit 0x10 (indicates matrix is valid)
        this->flags |= 0x10;

        // Copy 16 integers/floats starting at source into matrix field at +0x60
        // This is a 4x4 matrix (row-major or column-major) used for world/object transform
        this->matrix[0]  = srcData[0];
        this->matrix[1]  = srcData[1];
        this->matrix[2]  = srcData[2];
        this->matrix[3]  = srcData[3];
        this->matrix[4]  = srcData[4];
        this->matrix[5]  = srcData[5];
        this->matrix[6]  = srcData[6];
        this->matrix[7]  = srcData[7];
        this->matrix[8]  = srcData[8];
        this->matrix[9]  = srcData[9];
        this->matrix[10] = srcData[10];
        this->matrix[11] = srcData[11];
        this->matrix[12] = srcData[12];
        this->matrix[13] = srcData[13];
        this->matrix[14] = srcData[14];
        this->matrix[15] = srcData[15];
    } else {
        // Clear the valid flag when data is removed
        this->flags &= ~0x10;
    }
}