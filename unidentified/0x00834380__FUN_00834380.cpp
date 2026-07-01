// FUNC_NAME: SomeClass::updateStateMachine
void __thiscall SomeClass::updateStateMachine(int thisPtr, undefined4 *param2)
{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  char cVar5;
  undefined4 uVar6;
  uint uVar7;
  code *pcVar8;
  int *piVar9;
  int **ppiVar10;
  int *local_20;
  undefined4 local_1c;
  undefined1 local_18 [24];
  
  puVar4 = param2;
  iVar1 = *(int *)(thisPtr + 0x18); // state machine current state
  if (iVar1 == 0) {
    // State 0: Initial state
    FUN_00827860(param2);
    FUN_008278d0(0);
    if ((undefined4 *)(thisPtr + 0x74) != param2) {
      *(undefined4 *)(thisPtr + 0x74) = *param2;
      *(undefined4 *)(thisPtr + 0x78) = param2[1];
      *(undefined4 *)(thisPtr + 0x7c) = param2[2];
      *(undefined4 *)(thisPtr + 0x80) = param2[3];
      *(undefined4 *)(thisPtr + 0x84) = param2[4];
      *(undefined4 *)(thisPtr + 0x88) = param2[5];
      return;
    }
  }
  else {
    if (iVar1 == 1) {
      // State 1: Transition state
      FUN_00833ee0(param2);
      uVar6 = FUN_00835c80(local_18,param2,*(undefined4 *)(thisPtr + 0xc));
      FUN_00833f50(uVar6);
      FUN_00833fc0(param2);
      *(float *)(thisPtr + 0x70) = _DAT_00d5780c; // some global float
      *(undefined4 *)(thisPtr + 0x18) = 2; // transition to state 2
    }
    else if (iVar1 == 2) {
      // State 2: Active state
      cVar5 = FUN_00835b00(thisPtr + 0x74,param2);
      if (cVar5 == '\0') {
        FUN_00833fc0(param2);
      }
      else {
        FUN_00834060(1);
      }
      cVar5 = FUN_00835a00(thisPtr + 0x4c,thisPtr + 0x1c);
      if ((cVar5 != '\0') || (cVar5 = FUN_00835a60(thisPtr + 0x4c,thisPtr + 0x34), cVar5 != '\0')) {
        *(undefined4 *)(thisPtr + 0x70) = 0;
        *(undefined4 *)(thisPtr + 0x18) = 0; // reset to state 0
        FUN_00827830();
        FUN_00827860(param2);
        FUN_008278d0(0);
        FUN_00834030(param2);
        return;
      }
      *(float *)(thisPtr + 0x70) =
           _DAT_00d5780c -
           (*(float *)(thisPtr + 0x6c) - *(float *)(thisPtr + 100)) /
           (*(float *)(thisPtr + 0x68) - *(float *)(thisPtr + 100));
    }
    FUN_00827860(param2);
    FUN_00827860(param2);
    param2 = (undefined4 *)0x0;
    if (*(int *)(*(int *)(thisPtr + 0x14) + 8) != 0) {
      do {
        piVar2 = *(int **)(*(int *)(*(int *)(thisPtr + 0x14) + 4) + (int)param2 * 8);
        uVar7 = 0;
        local_20 = (int *)0x0;
        local_1c = 0;
        if (*(int *)(*(int *)(thisPtr + 0x10) + 8) != 0) {
          piVar9 = *(int **)(*(int *)(thisPtr + 0x10) + 4);
          do {
            piVar3 = (int *)*piVar9;
            if ((piVar2[3] == piVar3[3]) && (piVar2 != piVar3)) {
              local_1c = *(undefined4 *)(thisPtr + 0x70);
              if ((char)piVar2[8] == '\0') goto LAB_008344a2;
              pcVar8 = *(code **)(*piVar2 + 8);
              ppiVar10 = &local_20;
              local_20 = piVar3;
              goto LAB_008344a0;
            }
            uVar7 = uVar7 + 1;
            piVar9 = piVar9 + 2;
          } while (uVar7 < *(uint *)(*(int *)(thisPtr + 0x10) + 8));
        }
        if ((char)piVar2[8] != '\0') {
          pcVar8 = *(code **)(*piVar2 + 8);
          ppiVar10 = (int **)0x0;
LAB_008344a0:
          (*pcVar8)(ppiVar10);
        }
LAB_008344a2:
        param2 = (undefined4 *)((int)param2 + 1);
      } while (param2 < *(uint *)(*(int *)(thisPtr + 0x14) + 8));
    }
    if ((undefined4 *)(thisPtr + 0x74) != puVar4) {
      *(undefined4 *)(thisPtr + 0x74) = *puVar4;
      *(undefined4 *)(thisPtr + 0x78) = puVar4[1];
      *(undefined4 *)(thisPtr + 0x7c) = puVar4[2];
      *(undefined4 *)(thisPtr + 0x80) = puVar4[3];
      *(undefined4 *)(thisPtr + 0x84) = puVar4[4];
      *(undefined4 *)(thisPtr + 0x88) = puVar4[5];
    }
  }
  return;
}