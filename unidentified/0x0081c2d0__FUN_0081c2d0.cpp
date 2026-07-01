// FUNC_NAME: SomeClass::updateComboCounter
void __thiscall updateComboCounter(int this, int other)
{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int *local_8;
  
  iVar4 = other;
  iVar7 = *(int *)(other + 0xf0);
  if (*(int *)(this + 0x14) != 0) {
    piVar2 = *(int **)(this + 0x10);
    piVar1 = piVar2 + *(int *)(this + 0x14) * 3;
    piVar8 = piVar2;
    local_8 = piVar1;
    if ((((*(int *)(other + 0x7c) != 0) && (*(int *)(other + 0x7c) != 0x48)) &&
        (*(int *)(other + 0x84) != 0)) && ((*(uint *)(other + 0x70) & 6) != 0)) {
      if (*(int *)(other + 0x7c) == 0) {
        other = 0;
      }
      else {
        other = *(int *)(other + 0x7c) + -0x48;
      }
      do {
        piVar3 = piVar8;
        piVar8 = piVar2;
        local_8 = piVar1;
        if (piVar3 == piVar1) break;
        if (*(int *)(*piVar3 + 8) == 0) {
          iVar6 = 0;
        }
        else {
          iVar6 = *(int *)(*piVar3 + 8) + -0x48;
        }
        piVar8 = piVar3 + 3;
        local_8 = piVar3;
      } while (iVar6 != other);
    }
    while (((piVar8 != piVar1 && (piVar8 != local_8)) &&
           (cVar5 = FUN_0081c240(*piVar8,iVar4,0x12), cVar5 == '\0'))) {
      piVar8 = piVar8 + 3;
    }
    if (((*(char *)(iVar7 + 0x7c) != '\0') && (*(int *)(iVar4 + 0x7c) != 0)) &&
       (*(int *)(iVar4 + 0x7c) != 0x48)) {
      *(int *)(iVar4 + 0xe8) = *(int *)(iVar4 + 0xe8) + 1;
      if (*(int *)(iVar4 + 0x7c) == 0) {
        iVar7 = 0;
      }
      else {
        iVar7 = *(int *)(iVar4 + 0x7c) + -0x48;
      }
      FUN_006d6930(iVar7);
      iVar7 = *(int *)(iVar4 + 0xe8);
      if (*(int *)(iVar4 + 0xe4) <= iVar7) {
        *(int *)(iVar4 + 0xe4) = iVar7;
      }
      if (iVar7 == 5) {
        *(undefined4 *)(iVar4 + 0xe8) = 0;
      }
    }
  }
  return;
}