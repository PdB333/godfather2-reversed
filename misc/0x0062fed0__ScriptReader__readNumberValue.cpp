// FUNC_NAME: ScriptReader::readNumberValue
undefined4 ScriptReader::readNumberValue(int param_1)

{
  int *piVar1;
  int iVar2;
  int *extraout_ECX;
  int *piVar3;
  float local_14;
  int iStack_10;
  float fStack_c;
  
  piVar1 = *(int **)(param_1 + 0xc);  // +0x0C: current read position pointer
  piVar3 = *(int **)(param_1 + 8);    // +0x08: end of data pointer
  if (((piVar3 <= piVar1) || (piVar1 == (int *)0x0)) || (*piVar1 != 5)) {
    piVar1 = (int *)FUN_00627ac0(PTR_s_table_00e2a8b0);  // "table" string lookup
    piVar3 = extraout_ECX;
  }
  piVar1 = piVar1 + 2;  // Skip token type (5) and advance to next token
  if (piVar3 <= piVar1) goto LAB_0062ffb2;
  if (piVar1 == (int *)0x0) goto LAB_0062ffb2;
  if (*piVar1 != 3) {
    if (*piVar1 != 4) goto LAB_0062ffb2;
    iVar2 = FUN_00636850(&local_14);  // Parse float value
    if (iVar2 == 0) goto LAB_0062ffb2;
    iStack_10 = 3;
    fStack_c = local_14;
    piVar1 = &iStack_10;
  }
  local_14 = (float)piVar1[1];  // Get the numeric value from token
  if (local_14 == DAT_00e2b05c) {  // Check for special value (likely NaN or sentinel)
    while (((piVar1 = (int *)(*(int *)(param_1 + 0xc) + 8), *(int **)(param_1 + 8) <= piVar1 ||
            (piVar1 == (int *)0x0)) ||
           ((*piVar1 != 3 && ((*piVar1 != 4 || (iVar2 = FUN_00636850(&iStack_10), iVar2 == 0)))))))
    {
      FUN_00627ac0(PTR_s_number_00e2a8a8);  // "number" string lookup
LAB_0062ffb2:
      local_14 = 0.0;
    }
  }
  FUN_006286b0((int)local_14);  // Push value onto stack
  return 0;
}