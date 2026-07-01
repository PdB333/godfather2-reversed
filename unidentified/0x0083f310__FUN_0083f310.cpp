// FUNC_NAME: SomeClass::loadFromStream
void __thiscall SomeClass::loadFromStream(int this, undefined4 stream)
{
  char cVar1;
  int iVar2;
  
  FUN_0083c5c0(stream);
  FUN_0043aff0(stream,0x977d39dc);
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    FUN_0043b210();
    iVar2 = FUN_0043ab70();
    if (iVar2 == 0) {
      iVar2 = FUN_0043b210();
      *(float *)(this + 0x148) = *(float *)(iVar2 + 8) * DAT_00d5ef84;
    }
    else if (iVar2 == 1) {
      iVar2 = FUN_0043b210();
      *(undefined4 *)(this + 0x150) = *(undefined4 *)(iVar2 + 8);
    }
    else if (iVar2 == 2) {
      iVar2 = FUN_0043b210();
      *(undefined4 *)(this + 0x154) = *(undefined4 *)(iVar2 + 8);
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  }
  return;
}