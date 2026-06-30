// FUNC_NAME: EARSObject::setThreePointers
void __thiscall EARSObject::setThreePointers(uint64 param_2, uint64 param_3, uint64 param_4)
{
    // Stores three 8-byte values at offsets 0x78, 0x80, 0x88
    // Likely pointers or 64-bit data (e.g., timestamps, IDs, or double values)
    this->field_0x78 = param_2;
    this->field_0x80 = param_3;
    this->field_0x88 = param_4;
}