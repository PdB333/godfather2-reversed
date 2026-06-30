// FUNC_NAME: LuaVM::evaluateExpression
int LuaVM::evaluateExpression(int param_1)
{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int extraout_ECX;
  undefined4 *puVar4;
  int *extraout_EDX;
  int *piVar5;
  int aiStack_10 [3];
  
  iVar3 = *(int *)(param_1 + 0xc);  // +0xC: stack top pointer
  piVar5 = *(int **)(param_1 + 8);  // +0x8: current stack pointer
  piVar1 = (int *)(iVar3 + 8);      // stack base + 8 (skip header)
  if (((piVar5 <= piVar1) || (piVar1 == (int *)0x0)) || (*piVar1 == -1)) {
    FUN_00627a20(param_1,2,"value expected");  // error handler
    iVar3 = extraout_ECX;
    piVar5 = extraout_EDX;
  }
  if (piVar5 < (int *)(iVar3 + 0x10)) {  // stack has room for at least 2 entries
    do {
      **(undefined4 **)(param_1 + 8) = 0;
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
    } while (*(uint *)(param_1 + 8) < *(int *)(param_1 + 0xc) + 0x10U);
  }
  puVar2 = *(undefined4 **)(param_1 + 0xc);
  puVar4 = puVar2 + 4;
  *(undefined4 **)(param_1 + 8) = puVar4;
  for (; puVar2 < puVar4; puVar4 = puVar4 + -2) {
    *puVar4 = puVar4[-2];
    puVar4[1] = puVar4[-1];
  }
  puVar4 = *(undefined4 **)(param_1 + 8);
  *puVar2 = *puVar4;
  puVar2[1] = puVar4[1];
  aiStack_10[0] = *(int *)(param_1 + 8) + -8;
  aiStack_10[1] = 0xffffffff;
  iVar3 = FUN_00636570(&LAB_006261e0,aiStack_10,aiStack_10[0] - *(int *)(param_1 + 0x1c));  // evaluate expression
  puVar4 = *(undefined4 **)(param_1 + 8);
  *puVar4 = 1;  // push true
  puVar4[1] = (uint)(iVar3 == 0);  // push success flag
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
  iVar3 = *(int *)(param_1 + 8);
  puVar4 = *(undefined4 **)(param_1 + 0xc);
  *puVar4 = *(undefined4 *)(iVar3 + -8);
  puVar4[1] = *(undefined4 *)(iVar3 + -4);
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -8;
  return *(int *)(param_1 + 8) - *(int *)(param_1 + 0xc) >> 3;  // return number of stack entries
}