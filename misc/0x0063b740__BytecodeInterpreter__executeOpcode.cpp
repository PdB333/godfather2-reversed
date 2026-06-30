// FUNC_NAME: BytecodeInterpreter::executeOpcode
undefined4 BytecodeInterpreter::executeOpcode(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined1 local_c [8];
  
  piVar5 = *(int **)(param_1 + 0xc);
  piVar1 = *(int **)(param_1 + 8);
  if ((piVar5 < piVar1) && (piVar5 != (int *)0x0)) {
    if (*piVar5 == 7) {
      if ((((piVar5 < piVar1) && (piVar5 != (int *)0x0)) &&
          (iVar4 = *(int *)(piVar5[1] + 8), iVar4 != 0)) &&
         (iVar4 != *(int *)(*(int *)(param_1 + 0x10) + 0x38))) {
        *piVar1 = 5;
        piVar1[1] = iVar4;
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
      }
      iVar4 = FUN_00625740();
      do {
        if (iVar4 != 5) {
          FUN_006255e0();
          FUN_0063abc0(param_1);
          return 0;
        }
        piVar5 = (int *)(*(int *)(param_1 + 0xc) + 8);
        if (((piVar5 < *(int **)(param_1 + 8)) && (piVar5 != (int *)0x0)) &&
           ((*piVar5 == 3 || ((*piVar5 == 4 && (iVar4 = FUN_00636850(local_c), iVar4 != 0)))))) {
          FUN_00625ca0(param_1,".seti");
          iVar4 = *(int *)(param_1 + 8);
          iVar2 = *(int *)(iVar4 + -8);
          if (iVar2 == 3) {
            if ((float)(int)*(float *)(iVar4 + -4) != *(float *)(iVar4 + -4)) goto LAB_0063b84a;
            piVar5 = (int *)FUN_00637f10();
          }
          else if (iVar2 == 4) {
            piVar5 = (int *)FUN_00637f90();
          }
          else {
LAB_0063b84a:
            piVar5 = (int *)FUN_00637ea0();
          }
          *(int *)(iVar4 + -8) = *piVar5;
          *(int *)(iVar4 + -4) = piVar5[1];
          iVar4 = FUN_00625740();
          if (iVar4 == 6) {
            puVar6 = *(undefined4 **)(param_1 + 0xc);
            puVar3 = *(undefined4 **)(param_1 + 8);
            *puVar3 = *puVar6;
            puVar3[1] = puVar6[1];
            iVar4 = *(int *)(param_1 + 0xc);
            *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
            puVar6 = *(undefined4 **)(param_1 + 8);
            *puVar6 = *(undefined4 *)(iVar4 + 8);
            puVar6[1] = *(undefined4 *)(iVar4 + 0xc);
            *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
            iVar4 = *(int *)(param_1 + 0xc);
            puVar6 = *(undefined4 **)(param_1 + 8);
            *puVar6 = *(undefined4 *)(iVar4 + 0x10);
            puVar6[1] = *(undefined4 *)(iVar4 + 0x14);
            *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
            FUN_006362d0(param_1,*(int *)(param_1 + 8) + -0x20,0);
            return 0;
          }
        }
        else {
          FUN_00625ca0(param_1,&DAT_00e416f4);
          iVar4 = *(int *)(param_1 + 8);
          iVar2 = *(int *)(iVar4 + -8);
          if (iVar2 == 3) {
            if ((float)(int)*(float *)(iVar4 + -4) != *(float *)(iVar4 + -4)) goto LAB_0063b91c;
            piVar5 = (int *)FUN_00637f10();
          }
          else if (iVar2 == 4) {
            piVar5 = (int *)FUN_00637f90();
          }
          else {
LAB_0063b91c:
            piVar5 = (int *)FUN_00637ea0();
          }
          *(int *)(iVar4 + -8) = *piVar5;
          *(int *)(iVar4 + -4) = piVar5[1];
          iVar4 = FUN_00625740();
          if (iVar4 == 5) {
            iVar4 = *(int *)(param_1 + 0xc);
            puVar6 = *(undefined4 **)(param_1 + 8);
            *puVar6 = *(undefined4 *)(iVar4 + 8);
            puVar6[1] = *(undefined4 *)(iVar4 + 0xc);
            *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
            iVar4 = *(int *)(param_1 + 8);
            iVar2 = *(int *)(iVar4 + -8);
            if (iVar2 == 3) {
              if ((float)(int)*(float *)(iVar4 + -4) != *(float *)(iVar4 + -4)) goto LAB_0063b998;
              piVar5 = (int *)FUN_00637f10();
            }
            else if (iVar2 == 4) {
              piVar5 = (int *)FUN_00637f90();
            }
            else {
LAB_0063b998:
              piVar5 = (int *)FUN_00637ea0();
            }
            *(int *)(iVar4 + -8) = *piVar5;
            *(int *)(iVar4 + -4) = piVar5[1];
            iVar4 = FUN_00625790();
            if (iVar4 != 0) {
              puVar6 = *(undefined4 **)(param_1 + 0xc);
              puVar3 = *(undefined4 **)(param_1 + 8);
              *puVar3 = *puVar6;
              puVar3[1] = puVar6[1];
              iVar4 = *(int *)(param_1 + 0xc);
              *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
              puVar6 = *(undefined4 **)(param_1 + 8);
              *puVar6 = *(undefined4 *)(iVar4 + 0x10);
              puVar6[1] = *(undefined4 *)(iVar4 + 0x14);
              *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
              FUN_006362d0(param_1,*(int *)(param_1 + 8) + -0x18,0);
              return 0;
            }
            *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -8;
          }
          *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -8;
          puVar6 = *(undefined4 **)(param_1 + 8);
          if (puVar6 + -2 == (int *)0x0) {
LAB_0063ba08:
            *puVar6 = 0;
          }
          else {
            iVar4 = puVar6[-2];
            if (iVar4 == 5) {
              iVar4 = *(int *)(puVar6[-1] + 8);
            }
            else {
              if (iVar4 != 7) goto LAB_0063ba08;
              iVar4 = *(int *)(puVar6[-1] + 8);
            }
            if ((iVar4 == 0) || (iVar4 == *(int *)(*(int *)(param_1 + 0x10) + 0x38)))
            goto LAB_0063ba08;
            *puVar6 = 5;
            puVar6[1] = iVar4;
          }
          *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
          puVar6 = *(undefined4 **)(param_1 + 8) + -2;
          if (puVar6 < *(undefined4 **)(param_1 + 8)) {
            do {
              puVar6[-2] = *puVar6;
              puVar6[-1] = puVar6[1];
              puVar6 = puVar6 + 2;
            } while (puVar6 < *(undefined4 **)(param_1 + 8));
          }
          *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -8;
        }
        iVar4 = FUN_00625740();
      } while( true );
    }
    if (*piVar5 == 5) {
      FUN_0063af50(param_1);
    }
  }
  return 0;
}