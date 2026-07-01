// FUNC_NAME: SomeClass::setSomePointerOrHandle
void __thiscall SomeClass::setSomePointerOrHandle(int thisPtr, int *param_2)
{
  int *piVar1;
  char cVar2;
  uint uVar3;
  uint unaff_ESI;
  int iVar4;
  
  if (param_2 == (int *)0x0) {
    if (*(int *)(thisPtr + 0x70) != 0) {
      FUN_004daf90((undefined4 *)(thisPtr + 0x70)); // likely release/delete
      *(undefined4 *)(thisPtr + 0x70) = 0;
      return;
    }
  }
  else {
    iVar4 = *param_2;
    param_2 = (int *)0x0;
    cVar2 = (**(code **)(iVar4 + 0x10))(0x55859efa,&param_2); // virtual call with hash
    piVar1 = (int *)(thisPtr + 0x70);
    uVar3 = -(uint)(cVar2 != '\\0') & unaff_ESI;
    if (uVar3 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = uVar3 + 0x48;
    }
    if (*piVar1 != iVar4) {
      if (*piVar1 != 0) {
        FUN_004daf90(piVar1); // release old
      }
      *piVar1 = iVar4;
      if (iVar4 != 0) {
        *(undefined4 *)(thisPtr + 0x74) = *(undefined4 *)(iVar4 + 4);
        *(int **)(iVar4 + 4) = piVar1;
      }
    }
  }
  return;
}