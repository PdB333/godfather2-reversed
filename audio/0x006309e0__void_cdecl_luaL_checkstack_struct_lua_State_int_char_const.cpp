// Xbox PDB: void __cdecl luaL_checkstack(struct lua_State *,int,char const *)
// FUNC_NAME: StreamManager::writePacketData
undefined4 StreamManager::writePacketData(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  uint uVar3;
  int *extraout_ECX;
  int *piVar4;
  int extraout_EDX;
  int iVar5;
  
  piVar1 = *(int **)(param_1 + 0xc);
  if (((*(int **)(param_1 + 8) <= piVar1) || (piVar1 == (int *)0x0)) || (*piVar1 != 5)) {
    FUN_00627ac0(PTR_s_table_00e2a8b0);
  }
  uVar2 = FUN_00628820(1);
  if ((*(int *)(param_1 + 8) - *(int *)(param_1 + 0xc) >> 3) + 0x28 < 0x4001) {
    if (*(int *)(param_1 + 0x18) - *(int *)(param_1 + 8) < 0x141) {
      FUN_00635c70();
    }
    uVar3 = *(int *)(param_1 + 8) + 0x140;
    if (*(uint *)(*(int *)(param_1 + 0x14) + 4) < uVar3) {
      *(uint *)(*(int *)(param_1 + 0x14) + 4) = uVar3;
    }
    iVar5 = *(int *)(param_1 + 0xc);
    piVar4 = *(int **)(param_1 + 8);
    piVar1 = (int *)(iVar5 + 8);
    if ((((piVar4 <= piVar1) || (piVar1 == (int *)0x0)) || (*piVar1 < 1)) ||
       (((piVar1 < piVar4 && (piVar1 != (int *)0x0)) && (*piVar1 == 6)))) goto LAB_00630a9f;
    uVar2 = 2;
    FUN_00627ac0(PTR_s_function_00e2a8b4);
  }
  FUN_00627bd0("stack overflow (%s)",&DAT_00e2f044);
  piVar4 = extraout_ECX;
  iVar5 = extraout_EDX;
LAB_00630a9f:
  if (piVar4 < (int *)(iVar5 + 0x10)) {
    do {
      **(undefined4 **)(param_1 + 8) = 0;
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
    } while (*(uint *)(param_1 + 8) < *(int *)(param_1 + 0xc) + 0x10U);
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 0xc) + 0x10;
  FUN_006306c0(param_1,1,uVar2);
  return 0;
}