// FUNC_NAME: SomeClass::setActionData
void __thiscall SomeClass::setActionData(int this, undefined4 param2, undefined4 param3, undefined4 param4, char param5)
{
  bool bVar1;
  
  bVar1 = false;
  if ((param5 != '\0') && (*(char *)(DAT_01129814 + 0x15) != '\0')) {
    FUN_0068c590(0);
    bVar1 = true;
  }
  if (bVar1) {
    *(uint *)(this + 0x10) = *(uint *)(this + 0x10) | 4;
  }
  else {
    *(uint *)(this + 0x10) = *(uint *)(this + 0x10) & 0xfffffffb;
  }
  *(undefined4 *)(this + 0xc) = param2;
  *(undefined4 *)(this + 0x30) = param3;
  *(undefined4 *)(this + 0x34) = param4;
  return;
}