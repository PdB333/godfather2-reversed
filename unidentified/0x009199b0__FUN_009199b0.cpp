// FUNC_NAME: SomeManager::clearLists
void __thiscall SomeManager::clearLists(int this, char param_2)
{
  int iVar1;
  int *piVar2;
  char cVar3;
  uint uVar4;
  
  iVar1 = *(int *)(DAT_01130044 + 0xb8);
  if (((iVar1 == 10) || (iVar1 == 0xb)) || (iVar1 == 0xc)) {
    *(undefined4 *)(DAT_01130044 + 0xec) = *(undefined4 *)(this + 0x50);
    FUN_005a04a0("ClearList",0,&DAT_00d8510c,0);
    if (param_2 != '\0') {
      uVar4 = 0;
      if (*(int *)(this + 0x50) != 0) {
        do {
          piVar2 = *(int **)(*(int *)(this + 0x4c) + uVar4 * 4);
          if (piVar2 != (int *)0x0) {
            if (*piVar2 != 0) {
              (*(code *)piVar2[3])(*piVar2);
            }
            FUN_009c8eb0(piVar2);
          }
          uVar4 = uVar4 + 1;
        } while (uVar4 < *(uint *)(this + 0x50));
      }
      *(undefined4 *)(this + 0x50) = 0;
      FUN_009c8f10(*(undefined4 *)(this + 0x4c));
      *(undefined4 *)(this + 0x4c) = 0;
      *(undefined4 *)(this + 0x54) = 0;
      return;
    }
  }
  else if (iVar1 == 0x19) {
    *(undefined4 *)(DAT_01130044 + 0xec) = *(undefined4 *)(this + 0x5c);
    FUN_005a04a0("ClearList",0,&DAT_00d8510c,0);
    if (param_2 != '\0') {
      uVar4 = 0;
      if (*(int *)(this + 0x5c) != 0) {
        do {
          piVar2 = *(int **)(*(int *)(this + 0x58) + uVar4 * 4);
          if (piVar2 != (int *)0x0) {
            if (*piVar2 != 0) {
              (*(code *)piVar2[3])(*piVar2);
            }
            FUN_009c8eb0(piVar2);
          }
          uVar4 = uVar4 + 1;
        } while (uVar4 < *(uint *)(this + 0x5c));
      }
      *(undefined4 *)(this + 0x5c) = 0;
      FUN_009c8f10(*(undefined4 *)(this + 0x58));
      *(undefined4 *)(this + 0x58) = 0;
      *(undefined4 *)(this + 0x60) = 0;
      return;
    }
  }
  else if (((iVar1 == 0xd) || (iVar1 == 0xe)) ||
          ((iVar1 == 0xf || ((iVar1 == 0x10 || (iVar1 == 0x11)))))) {
    *(undefined4 *)(DAT_01130044 + 0xec) = *(undefined4 *)(this + 0x68);
    FUN_005a04a0("ClearList",0,&DAT_00d8510c,0);
    if (param_2 != '\0') {
      uVar4 = 0;
      if (*(int *)(this + 0x68) != 0) {
        do {
          piVar2 = *(int **)(*(int *)(this + 100) + uVar4 * 4);
          if (piVar2 != (int *)0x0) {
            if (*piVar2 != 0) {
              (*(code *)piVar2[3])(*piVar2);
            }
            FUN_009c8eb0(piVar2);
          }
          uVar4 = uVar4 + 1;
        } while (uVar4 < *(uint *)(this + 0x68));
      }
      *(undefined4 *)(this + 0x68) = 0;
      FUN_009c8f10(*(undefined4 *)(this + 100));
      *(undefined4 *)(this + 100) = 0;
      *(undefined4 *)(this + 0x6c) = 0;
      return;
    }
  }
  else {
    cVar3 = FUN_00917060();
    if ((cVar3 != '\0') && (FUN_00916f80(*(undefined4 *)(this + 0x74)), param_2 != '\0')) {
      uVar4 = 0;
      if (*(int *)(this + 0x74) != 0) {
        do {
          piVar2 = *(int **)(*(int *)(this + 0x70) + uVar4 * 4);
          if (piVar2 != (int *)0x0) {
            if (*piVar2 != 0) {
              (*(code *)piVar2[3])(*piVar2);
            }
            FUN_009c8eb0(piVar2);
          }
          uVar4 = uVar4 + 1;
        } while (uVar4 < *(uint *)(this + 0x74));
      }
      FUN_009177a0();
    }
  }
  return;
}