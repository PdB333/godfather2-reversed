// FUNC_NAME: SomeClass::clearSomeFlag

void __fastcall SomeClass::clearSomeFlag(int thisPtr)
{
  // Check bit 2 of the word at offset +0x68
  if ((*(byte *)(thisPtr + 0x68) >> 2 & 1) != 0) {
    // Clear bit 2 of the dword at DAT_011298d4 + 0x10 (likely a global flag)
    *(uint *)(DAT_011298d4 + 0x10) = *(uint *)(DAT_011298d4 + 0x10) & 0xfffffffb;
    // Call some function (likely to update state or notify)
    FUN_00912030();
    // Clear bit 2 of the word at +0x68
    *(ushort *)(thisPtr + 0x68) = *(ushort *)(thisPtr + 0x68) & 0xfffb;
  }
}