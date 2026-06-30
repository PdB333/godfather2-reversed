// FUNC_NAME: SomeClass::maybeReleaseOrDestroy
void __fastcall SomeClass::maybeReleaseOrDestroy(int thisPtr)
{
  int iVar1;
  
  if (((*(int *)(thisPtr + 0x194) == 0) || (*(int *)(thisPtr + 0x194) == 0x48)) &&
     ((*(int *)(thisPtr + 0x184) != 0 ||
      (((*(int *)(thisPtr + 0x188) != 0 || (*(int *)(thisPtr + 0x18c) != 0)) ||
       (*(int *)(thisPtr + 400) != 0)))))) {
    // +0x184 is some pointer field, likely a resource or child object
    iVar1 = FUN_00446100(thisPtr + 0x184, 0);
    if (iVar1 != 0) {
      FUN_0044b210(iVar1);
    }
  }
  return;
}