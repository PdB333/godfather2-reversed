// FUNC_NAME: SomeClass::resetOrCleanup
void __fastcall SomeClass::resetOrCleanup(int param_1)
{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 4);
  if (((*(int *)(param_1 + 4) != 0) && (*(int *)(param_1 + 4) != 0x48)) &&
     (FUN_007ee880(param_1), *piVar1 != 0)) {
    FUN_004daf90(piVar1);
    *piVar1 = 0;
  }
  *(undefined1 *)(param_1 + 0x12) = 0xff;
  *(ushort *)(param_1 + 0x10) = *(ushort *)(param_1 + 0x10) & 0xfffe;
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1);
  }
  return;
}