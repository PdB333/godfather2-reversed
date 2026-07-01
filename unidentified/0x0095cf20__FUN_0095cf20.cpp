// FUNC_NAME: SomeClass::updateSomeField
void __fastcall SomeClass::updateSomeField(int thisPtr)
{
  char cVar1;
  int local_4;

  if (DAT_0112b9b4 != 0) {
    local_4 = thisPtr;
    cVar1 = FUN_0095c8c0(*(undefined4 *)(thisPtr + 0x10), &local_4);
    if (cVar1 != '\0') {
      *(int *)(thisPtr + 0x70) = local_4;
    }
  }
  return;
}