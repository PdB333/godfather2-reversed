// FUNC_NAME: initDefaultBlock
void __thiscall initDefaultBlock(undefined4 *this) // this->size at least 0x60 (96 bytes)
{
    undefined4 *src = (undefined4 *)getDefaultTemplate(); // FUN_008a2d90 -> returns pointer to static template of 0x14 DWORDs (80 bytes)

    // Copy 0x14 DWORDs from template (offset 0x00 to 0x4F)
    for (int i = 0x14; i != 0; i--) {
        *this = *src;
        this++;
        src++;
    }

    // Zero remaining fields
    this[0x14] = 0;           // offset 0x50
    this[0x15] = 0;           // offset 0x54
    *(byte *)(this + 0x16) = 0;   // offset 0x58 (byte)
    *(byte *)((int)this + 0x59) = 0; // offset 0x59 (byte)
    this[0x17] = 0;           // offset 0x5C
}