// FUNC_NAME: SomeClass::updateSomething
void __fastcall SomeClass::updateSomething(int this)
{
  int iVar1;
  uint uVar2;

  if (*(int *)(this + 0x1c) != 0) {
    uVar2 = 0;
    do {
      FUN_008d5e60(); // likely processItem or similar
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(this + 0x1c)); // loop count from field at +0x1c
  }
  iVar1 = 4;
  do {
    FUN_008d5ef0(); // likely processSomethingElse
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  FUN_008d5ef0(); // one more call
  return;
}