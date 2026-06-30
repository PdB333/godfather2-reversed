// FUNC_NAME: applyOffsetUpdate
void __fastcall applyOffsetUpdate(int thisPtr)
{
    // DAT_01205228: global constant (likely a time delta or fixed offset)
    *(float*)(thisPtr + 0x2c) = *(float*)(thisPtr + 0x20) + DAT_01205228;
}