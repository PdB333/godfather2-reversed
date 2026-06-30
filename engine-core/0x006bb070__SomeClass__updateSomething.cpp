// FUNC_NAME: SomeClass::updateSomething
void __fastcall SomeClass::updateSomething(int thisPtr)
{
  int iVar1;
  int uVar2;
  
  if (*(int *)(thisPtr + 0x54) != 0) {
    iVar1 = FUN_006b0ee0(*(int *)(thisPtr + 0x54)); // likely getSomeObject or resolve pointer
    *(int *)(thisPtr + 0x9c) = iVar1;               // +0x9c: some object pointer
    if (iVar1 != 0) {
      FUN_006b4ca0();                                // likely a static initialization or reset
      *(int *)(thisPtr + 0x90) = 0;                  // +0x90: some flag or counter
      uVar2 = FUN_006babc0(*(int *)(thisPtr + 0x9c) + 0xa8); // +0xa8: offset in sub-object
      *(int *)(thisPtr + 0x94) = uVar2;              // +0x94: another pointer or handle
      if ((*(int *)(thisPtr + 0x9c) != 0) && ((*(byte *)(thisPtr + 0x84) & 1) != 0)) {
        *(int *)(thisPtr + 0x98) = *(int *)(*(int *)(thisPtr + 0x9c) + 0xac); // +0x98: copy from sub-object +0xac
        return;
      }
      *(int *)(thisPtr + 0x98) = 0;                  // +0x98: default to null
    }
  }
  return;
}