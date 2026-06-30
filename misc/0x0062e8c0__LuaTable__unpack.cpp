// FUNC_NAME: LuaTable::unpack
int LuaTable::unpack(int param_1)
{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  piVar1 = *(int **)(param_1 + 0xc); // +0x0C: current element pointer
  if (((*(int **)(param_1 + 8) <= piVar1) || (piVar1 == (int *)0x0)) || (*piVar1 != 5)) {
    FUN_00627ac0(PTR_s_table_00e2a8b0); // error: "table" expected
  }
  iVar3 = FUN_00628820(1); // get table length (argument 1 = stack index)
  iVar4 = FUN_006254f0(); // check stack space
  if (iVar4 == 0) {
    FUN_00627bd0("stack overflow (%s)","table too big to unpack");
  }
  iVar4 = 1;
  if (0 < iVar3) {
    do {
      puVar5 = (undefined4 *)FUN_00637f10(); // get next table element
      puVar2 = *(undefined4 **)(param_1 + 8); // +0x08: destination stack pointer
      *puVar2 = *puVar5; // copy value
      puVar2[1] = puVar5[1]; // copy type tag
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8; // advance stack
      iVar4 = iVar4 + 1;
    } while (iVar4 <= iVar3);
  }
  return iVar3; // return number of elements unpacked
}