// FUNC_NAME: TransformData::TransformData
void __thiscall TransformData::TransformData(TransformData *this, uint param1, uint param2, uint param3)
{
    // vtable pointer at offset 0x00
    this->vtable = &PTR_FUN_00e373a4;
    // Store three parameters at offsets 0x04, 0x08, 0x0C (likely floats or ints)
    this->field_0x04 = param1;
    this->field_0x08 = param2;
    this->field_0x0C = param3;
    // Store this pointer at offset 0x30? (unusual, but decompiler shows in_EAX)
    this->field_0x30 = this;
    // Call some global function (e.g., memory manager) with a global handle
    int result = FUN_00426af0(DAT_012233e4);
    this->field_0x34 = result;
    // If the result is non-zero, copy 32 bytes (4 quadwords) from source to offset 0x10
    if (result != 0) {
        // Copy 4x8 bytes = 32 bytes (likely a 4x4 matrix or transform data)
        this->matrix[0] = *sourceMatrix;      // offset 0x10
        this->matrix[1] = sourceMatrix[1];    // offset 0x18
        this->matrix[2] = sourceMatrix[2];    // offset 0x20
        this->matrix[3] = sourceMatrix[3];    // offset 0x28
    }
    // Note: sourceMatrix is passed via unaff_EDI (likely a register parameter)
    // field_0x38 (offset 0x38) is set to 0 earlier (this->field_0x38 = 0)
}