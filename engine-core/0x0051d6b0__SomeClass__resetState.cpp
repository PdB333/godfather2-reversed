// FUNC_NAME: SomeClass::resetState
void SomeClass::resetState(void)
{
  int *piVar1;
  int unaff_ESI;
  
  piVar1 = (int *)(unaff_ESI + 0xc4);
  *(undefined4 *)(unaff_ESI + 0xb4) = 0; // +0xb4: some flag
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1); // likely a destructor or cleanup function
    *piVar1 = 0;
  }
  if (*(int *)(unaff_ESI + 0xb0) == 4) { // +0xb0: state enum, value 4 = some active state
    if (*(int *)(unaff_ESI + 0xc0) != 0) { // +0xc0: pointer to some object
      (**(code **)(*DAT_01194538 + 4))(*(int *)(unaff_ESI + 0xc0),0); // call vtable method at offset 4 (likely release/delete)
      *(undefined4 *)(unaff_ESI + 0xc0) = 0;
      *(undefined4 *)(unaff_ESI + 0xb0) = 0;
      *(undefined **)(unaff_ESI + 0x78) = PTR_LAB_00e38260; // +0x78: pointer to some static data
      return;
    }
    *(undefined4 *)(unaff_ESI + 0xb0) = 0;
    *(undefined **)(unaff_ESI + 0x78) = PTR_LAB_00e38260;
    return;
  }
  *(undefined4 *)(unaff_ESI + 0xb0) = 0;
  *(undefined **)(unaff_ESI + 0x78) = PTR_LAB_00e38260;
  return;
}