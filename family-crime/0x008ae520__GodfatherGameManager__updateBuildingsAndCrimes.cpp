// FUNC_NAME: GodfatherGameManager::updateBuildingsAndCrimes
void __thiscall GodfatherGameManager::updateBuildingsAndCrimes(int *this, int *param_2)
{
  undefined4 *puVar1;
  int *piVar2;
  char cVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  uint uVar10;
  int iStack_14;
  undefined **local_10;
  int local_c;
  int iStack_8;
  int iStack_4;
  
  iVar7 = DAT_01223484;
  if ((((DAT_01223484 != 0) && ((*(uint *)(DAT_01223484 + 0x37c) >> 4 & 1) != 0)) &&
      (*(int *)(DAT_01223484 + 8) != 0)) &&
     ((param_2 != (int *)0x0 &&
      (iVar6 = *(int *)(DAT_01223484 + 0x3b0), iVar4 = (**(code **)(*param_2 + 0xc))(),
      iVar6 == iVar4)))) {
    puVar5 = *(undefined1 **)(iVar7 + 900);
    if (puVar5 == (undefined1 *)0x0) {
      puVar5 = &DAT_0120546e;
    }
    iVar6 = FUN_008acaf0(puVar5);
    if (iVar6 != -1) {
      *(uint *)(iVar7 + 0x3b4) = (uint)(iVar6 == 0);
      FUN_008a5440();
      (**(code **)(*param_1 + 0xb4))();
    }
  }
  iVar7 = param_1[0x18]; // +0x60: building list pointer
  if (iVar7 == 0) {
    return;
  }
  local_c = 0;
  iStack_8 = iVar7;
  if (*(int *)(iVar7 + 8) == 0) {
    iStack_8 = 0;
  }
  local_10 = &PTR_FUN_00d79c8c;
  iStack_4 = 0;
  if (iStack_8 != 0) {
    iStack_4 = iVar7;
  }
  do {
    if ((local_c == 0) && (iStack_8 == 0)) goto LAB_008ae68a;
    iVar7 = (*(code *)*local_10)();
    if ((*(byte *)(iVar7 + 0x30) & 1) != 0) {
      uVar8 = (*(code *)*local_10)();
      uVar9 = (**(code **)(*param_2 + 4))();
      uVar8 = FUN_004bb600(uVar8);
      cVar3 = FUN_00411fd0(uVar8,uVar9);
      if (cVar3 != '\\0') break;
    }
    (*(code *)local_10[1])();
  } while( true );
  iVar7 = (*(code *)*local_10)();
  *(uint *)(iVar7 + 0x30) = *(uint *)(iVar7 + 0x30) & 0xfffffffe;
  if (iVar7 != 0) {
    puVar1 = (undefined4 *)(iVar7 + 8);
    (**(code **)(*param_1 + 0xcc))(*puVar1);
    FUN_008ab770(&iStack_14,puVar1);
    if (iStack_14 != 0) {
      FUN_008acf50(puVar1);
    }
  }
LAB_008ae68a:
  uVar10 = 0;
  if (param_1[0x3f] != 0) { // +0xFC: crime count
    do {
      iVar7 = *(int *)(param_1[0x3e] + uVar10 * 8); // +0xF8: crime array base
      if ((iVar7 != 0) && (piVar2 = (int *)(iVar7 + -0x48), piVar2 != (int *)0x0)) {
        uVar8 = (**(code **)(*param_2 + 4))();
        uVar8 = (**(code **)(*piVar2 + 0x1d4))(uVar8);
        cVar3 = FUN_00411fd0(uVar8);
        if (cVar3 != '\\0') {
          FUN_008ab630(uVar10);
          break;
        }
      }
      uVar10 = uVar10 + 1;
    } while (uVar10 < (uint)param_1[0x3f]);
  }
  FUN_009847c0(0xffffffff);
  return;
}