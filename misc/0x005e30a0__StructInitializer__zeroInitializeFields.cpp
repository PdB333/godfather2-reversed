// FUNC_NAME: StructInitializer::zeroInitializeFields
void __fastcall StructInitializer::zeroInitializeFields(uint32_t *this)
{
    // Zero out 8 consecutive 32-bit fields (32 bytes total)
    this[0] = 0;
    this[1] = 0;
    this[2] = 0;
    this[3] = 0;
    this[4] = 0;
    this[5] = 0;
    this[7] = 0;   // Note field 7 zeroed before field 6 in original binary
    this[6] = 0;
}