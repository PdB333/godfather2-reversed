// FUNC_NAME: AptStack::push
void AptStack::push(uint *param_1)
{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  int *unaff_EDI;
  int unaff_FS_OFFSET;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  if (*unaff_EDI < 6) goto LAB_005b1b07;
  local_14 = "nElements < _nSize";
  local_10 = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptStack.h";
  local_c = 0x1c;
  local_8 = 2;
  local_4 = &DAT_01129004;
  if (DAT_01129004 == '\0') goto LAB_005b1b07;
  piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar3 = 1;
  if (piVar1 == (int *)0x0) {
LAB_005b1ae4:
    if ((uVar3 & 2) != 0) {
      *local_4 = 0;
    }
  }
  else {
    uVar3 = (**(code **)(*piVar1 + 8))(&local_14,"nElements < _nSize");
    if (local_4 != (undefined1 *)0x0) goto LAB_005b1ae4;
  }
  if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
     (((uVar3 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
LAB_005b1b07:
  unaff_EDI[*unaff_EDI + 1] = (int)param_1;
  *unaff_EDI = *unaff_EDI + 1;
  if (param_1 != DAT_0119cbbc) {
    uVar3 = *param_1 & 0x7fff;
    if ((uVar3 != 0x19) &&
       (((~(byte)(*param_1 >> 0xf) & 1) != 0 ||
        (((uVar3 != 0xb && (uVar3 != 0x18)) && (uVar3 != 0x17)))))) {
      FUN_0059c230(param_1);
    }
  }
  return;
}