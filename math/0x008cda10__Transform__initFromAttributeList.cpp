// FUNC_NAME: Transform::initFromAttributeList
undefined4 * __thiscall Transform::initFromAttributeList(Transform *this, int parent, int data)
{
    float globalScale = _DAT_00d5780c; // +0x0: scale factor (likely 1.0)
    float scaleFactor; // from global _DAT_00e445c8 (some multiplier)
    float *attrArray; // pointer to float array in data
    uint attrCount;
    float fVar1, fVar6;
    float *pfVar2;
    int iVar3;
    float squaredLength;

    // Call some function on parent (likely virtual method)
    (**(code **)(**(int **)(parent + 8) + 4))();

    // Initialize vtable and fields
    this->vtable = &PTR_FUN_00d7ca00; // +0x00
    this->scalar = 0.0f; // +0x04
    this->parent = parent; // +0x08
    this->unknownField = 0; // +0x0c

    FUN_0060ffd0(); // unknown initialization

    // Process attribute list from data
    // data structure: at +0x20: ushort count, at +0x1c: array of pointers to float arrays
    if (*(short *)(data + 0x20) != 0) {
        scaleFactor = DAT_00e445c8; // global multiplier
        for (attrCount = 0; attrCount < *(ushort *)(data + 0x20); attrCount++) {
            pfVar2 = *(float **)(*(int *)(data + 0x1c) + attrCount * 4);
            fVar6 = pfVar2[4]; // attribute type identifier

            // Check attribute type by comparing bit pattern as float
            if ((uint)fVar6 < 0xbfe9519a) {
                if (fVar6 == -1.8228027f) { // 0xBFE9519A? -> vector z
                    this->vectorZ = *pfVar2; // +0x18
                }
                else if (fVar6 == -1.8228024f) { // 0xBFE95199? -> vector x
                    this->vectorX = *pfVar2; // +0x10
                }
                else if (fVar6 == -1.8228025f) { // 0xBFE95198? -> vector y
                    this->vectorY = *pfVar2; // +0x14
                }
            }
            else if (fVar6 == -3.6446247e+24f) { // huge negative -> scalar
                this->scalar = *pfVar2 * scaleFactor; // +0x04
            }
        }
    }

    // Normalize the vector (x,y,z) and scale by globalScale
    squaredLength = this->vectorX * this->vectorX + this->vectorY * this->vectorY + this->vectorZ * this->vectorZ;
    if (DAT_00d5f2b4 < squaredLength) {
        float invLength = globalScale / sqrtf(squaredLength);
        this->vectorX *= invLength;
        this->vectorY *= invLength;
        this->vectorZ *= invLength;
    }

    // Build a scaling matrix on stack (identity-like with scale)
    float matrix[16]; // 4x4 row-major? This layout is approximate
    // Initialize with zeros and set diagonal to globalScale
    matrix[0] = globalScale;
    matrix[1] = 0.0f; matrix[2] = 0.0f; matrix[3] = 0.0f;
    matrix[4] = 0.0f; matrix[5] = globalScale; matrix[6] = 0.0f; matrix[7] = 0.0f;
    matrix[8] = 0.0f; matrix[9] = 0.0f; matrix[10] = globalScale; matrix[11] = 0.0f;
    matrix[12] = 0.0f; matrix[13] = 0.0f; matrix[14] = 0.0f; matrix[15] = globalScale;

    // Call function to apply matrix (likely updates internal transform)
    FUN_00610040(matrix);

    // Check if a sub-object should be initialized (at offset +0x20)
    iVar3 = (**(code **)(**(int **)(parent + 8) + 4))();
    if (iVar3 != 0) {
        FUN_00610160(this + 8); // Initialize sub-object at this+0x20 (matrix?)
    }

    return this;
}