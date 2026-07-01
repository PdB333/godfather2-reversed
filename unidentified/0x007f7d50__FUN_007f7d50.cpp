// FUNC_NAME: SomeClass::getFloatMatrixElement
float __thiscall SomeClass::getFloatMatrixElement(uint8 index1, uint8 index2) const
{
    // Offset 0x1c8c: float matrix[4][2] (4 rows, 2 columns, row-major)
    // index1 valid range: 0-3, index2 valid range: 0-1
    if (index1 < 4 && index2 < 2) {
        // Each element is 4 bytes, row stride = 2 * 4 = 8 bytes
        return *(float *)((uintptr_t)this + 0x1c8c + (index1 * 2 + index2) * 4);
    }
    return 0.0f;
}