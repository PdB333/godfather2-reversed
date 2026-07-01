// FUNC_NAME: Unknown::constructor
void __fastcall Unknown::constructor(Unknown* thisPtr) // 0x007ac460: Initialize object with default values
{
    // Zero-initialize most fields (sizeof ~0x68 bytes, but writes are sparse)
    thisPtr->field_0 = 0;
    thisPtr->field_4 = 0;
    thisPtr->field_8 = 0;
    thisPtr->field_C = 0;
    thisPtr->field_10 = 0;
    thisPtr->field_14 = gDefaultConstant; // +0x14: Set from global constant (likely magic number or version)
    thisPtr->field_18 = 0; // byte write at offset 0x18
    thisPtr->field_1C = 0;
    thisPtr->field_20 = 0;
    thisPtr->field_24 = 0;
    thisPtr->field_28 = 0;
    thisPtr->field_2C = 0;
    thisPtr->field_48 = 0; // indices 0x12 (offset 0x48)
    thisPtr->field_4C = 0;
    thisPtr->field_50 = 0;
    thisPtr->field_54 = 0;
    thisPtr->field_58 = 0; // byte write at offset 0x58
    thisPtr->field_5C = 0;
    thisPtr->field_60 = 0;
    thisPtr->field_64 = 0; // byte write at offset 0x64
    // Additional zeroing of fields not in sequential order (offsets 0x38, 0x34, 0x30, 0x44, 0x40, 0x3C)
    thisPtr->field_38 = 0;
    thisPtr->field_34 = 0;
    thisPtr->field_30 = 0;
    thisPtr->field_44 = 0;
    thisPtr->field_40 = 0;
    thisPtr->field_3C = 0;
}