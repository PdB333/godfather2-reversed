// FUNC_NAME: SomeClass::maybeDequeueOrProcess
int __fastcall SomeClass::maybeDequeueOrProcess(int *param_1)
{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_1;
  iVar2 = param_1[iVar1 + 3];
  param_1[iVar1 + 3] = 0;
  if (iVar2 != 0) {
    *(undefined1 **)(iVar2 + 0x158) = &LAB_00707620;
    FUN_007075e0(0);
    *(uint *)(iVar2 + 0x1d0) = *(uint *)(iVar2 + 0x1d0) & 0xfffffffd;
  }
  param_1[2] = param_1[2] + -1;
  *param_1 = (*param_1 + 1) % 0xf;
  return iVar1;
}