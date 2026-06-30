// FUNC_NAME: TextStyle::setDefaults
void __fastcall TextStyle::setDefaults(int thisPtr)
{
    // offset +0x10: font size (9)
    *(uint32_t *)(thisPtr + 0x10) = 9;
    // offset +0x14: font weight (2 = bold?)
    *(uint8_t *)(thisPtr + 0x14) = 2;
    // offset +0x18: font color as RGBA (0xffffff23 = white with alpha 0x23 ≈ 14% opacity)
    *(uint32_t *)(thisPtr + 0x18) = 0xffffff23;
}