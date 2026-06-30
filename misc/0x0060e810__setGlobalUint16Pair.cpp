// FUNC_NAME: setGlobalUint16Pair
void __cdecl setGlobalUint16Pair(uint16_t param_1, uint16_t param_2)
{
    // Global data at 0x012058b8 and 0x012058bc (likely two consecutive uint16 values)
    *reinterpret_cast<uint16_t*>(0x012058b8) = param_1;
    *reinterpret_cast<uint16_t*>(0x012058bc) = param_2;
}