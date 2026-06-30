// FUNC_NAME: Matrix44::setFromData
void __thiscall Matrix44::setFromData(void *thisPtr, uint32_t *inputData)
{
    uint32_t *flags = (uint32_t *)((uint8_t *)thisPtr + 8);
    if (inputData != nullptr)
    {
        // Set bit 3 (0x8) as "valid" flag
        *flags |= 8;
        
        // Copy 16 DWORDs (presumably floats) into the matrix at offset 0x20
        // This stores a 4x4 matrix in row-major order
        uint32_t *matrix = (uint32_t *)((uint8_t *)thisPtr + 0x20);
        for (int i = 0; i < 16; i++)
        {
            matrix[i] = inputData[i];
        }
    }
    else
    {
        // Clear the "valid" flag when no data is provided
        *flags &= ~8;
    }
}