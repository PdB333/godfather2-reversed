// FUNC_NAME: SomeClass::clearReferences
void __fastcall SomeClass::clearReferences(int this)
{
  int iVar1;
  
  iVar1 = *(int *)(this + 4);
  if ((iVar1 != 0) && ((*(byte *)(iVar1 + 0x10) & 1) != 0)) {
    *(ushort *)(iVar1 + 0x10) = *(ushort *)(iVar1 + 0x10) & 0xfffe;
  }
  iVar1 = *(int *)(this + 8);
  if ((iVar1 != 0) && ((*(byte *)(iVar1 + 0x10) & 1) != 0)) {
    *(ushort *)(iVar1 + 0x10) = *(ushort *)(iVar1 + 0x10) & 0xfffe;
  }
  if (*(int *)(this + 0x10) != 0) {
    FUN_009c8eb0(*(int *)(this + 0x10));
  }
  return;
}