// FUNC_NAME: SomeClass::xorValidateInputs
byte __thiscall xorValidateInputs(int this, undefined4 param_2)
{
  char cVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  
  bVar3 = 0;
  iVar4 = 0;
  // +0x01: count of entries
  if ('\0' < *(char *)(this + 1)) {
    do {
      // +0x08: pointer to array of pointers to strings
      cVar1 = **(char **)(*(int *)(this + 8) + iVar4 * 4);
      if (cVar1 < '\n') {
        // Dispatch based on first character (0-9) via function table
        bVar2 = (*(code *)(&PTR_FUN_0103af90)[cVar1])(param_2);
      }
      else {
        bVar2 = 0;
      }
      bVar3 = bVar3 ^ bVar2;
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(char *)(this + 1));
  }
  return bVar3;
}