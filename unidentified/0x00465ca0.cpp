// FUN_00465ca0: GameDataTable::getFloatValue
// Retrieves a float from internal data arrays. The class has two float arrays at offsets +0x5AE (base) and +0x5EE (modified).
// param_1 (this): pointer to GameDataTable instance
// param_2 (index): 0-17 (0x11), value 0x12 returns 0.0f
// param_3 (subIndex): additional offset within the entry (typically 0 or 1 due to *2 stride)
// param_4 (bUseModified): if non-zero, uses the modified array; otherwise uses base array

float GameDataTable::getFloatValue(byte index, int subIndex, char bUseModified)
{
    // Special case: index 0x12 (18) returns zero
    if (index == 0x12)
        return 0.0f;

    // Calculate offset into the float array
    // Each index entry occupies 2 floats (index * 2 gives base), subIndex is an additional offset
    int baseOffset = (bUseModified != 0) ? 0x5EE : 0x5AE;
    int floatIndex = subIndex + (index * 2);

    // Access the float at the computed offset
    float* array = (float*)((char*)this + baseOffset);
    return array[floatIndex];
}