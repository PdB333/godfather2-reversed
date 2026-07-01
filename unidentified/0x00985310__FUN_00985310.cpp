// FUNC_NAME: SomeClass::enableSomeFeature
void __fastcall SomeClass::enableSomeFeature(int thisPtr)
{
  if ((*(byte *)(thisPtr + 0x68) >> 2 & 1) == 0) {
    FUN_00911fd0(); // likely a static or global function to enable/initialize something
    *(ushort *)(thisPtr + 0x68) = *(ushort *)(thisPtr + 0x68) | 4; // set bit 2 at +0x68
    *(uint *)(DAT_011298d4 + 0x10) = *(uint *)(DAT_011298d4 + 0x10) | 4; // set bit 2 in global state at +0x10
  }
}