// FUNC_NAME: someClass::priorityComparison
uint __thiscall someClass::priorityComparison(int *this, int *other)
{
  int iVar1;
  uint uVar2;
  
  iVar1 = *this;
  if (iVar1 == *other) {
    if (iVar1 != 3) {
      if (iVar1 == 4) {
        iVar1 = FUN_006340e0(); // possibly a specific state check
        return (uint)(iVar1 < 1);
      }
      uVar2 = FUN_00634030(); // get some priority/type
      if (uVar2 == 0xffffffff) {
        iVar1 = FUN_00634030(); // retry
        if (iVar1 != -1) {
          return (uint)(iVar1 == 0);
        }
        uVar2 = FUN_006337e0(); // fallback priority/type
      }
      return uVar2;
    }
    if ((float)this[1] <= (float)other[1]) { // compare second field as float
      return 1;
    }
  }
  else {
    if ((&PTR_DAT_00e2a89c)[iVar1][2] == (&PTR_DAT_00e2a89c)[*other][2]) { // compare some table entry at offset 2
      FUN_00633920(); // log/mark something
      return 0;
    }
    FUN_00633920(); // log/mark something
  }
  return 0;
}