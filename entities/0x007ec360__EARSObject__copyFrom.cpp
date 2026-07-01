// FUNC_NAME: EARSObject::copyFrom
void __thiscall EARSObject::copyFrom(int this, int other)
{
  short sVar1;
  
  if (other != this) {
    sVar1 = *(short *)(this + 0x12);
    while (sVar1 != 0) {
      FUN_00408090(); // likely releaseRef or decrementRefCount
      sVar1 = *(short *)(this + 0x12);
    }
    *(undefined4 *)(this + 8) = *(undefined4 *)(other + 8); // +0x08: some pointer/ID
    FUN_004080d0(other + 0xc); // likely addRef or copyRef at +0x0C
    *(undefined4 *)(this + 0x14) = *(undefined4 *)(other + 0x14); // +0x14: some data
    *(undefined4 *)(this + 4) = *(undefined4 *)(other + 4); // +0x04: some data
  }
  return;
}