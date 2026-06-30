//FUNC_NAME: CommandBuffer::processEntry
undefined4 CommandBuffer::processEntry(int thisPtr)
{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  float local_14;
  int local_10;
  float local_c;
  
  piVar3 = *(int **)(thisPtr + 0xc); // read pointer
  if (*(int **)(thisPtr + 8) <= piVar3) goto LAB_0063192b; // if write pointer <= read pointer, buffer empty
  if (piVar3 == (int *)0x0) goto LAB_0063192b;
  if (*piVar3 != 3) {
    if (*piVar3 != 4) goto LAB_0063192b;
    iVar2 = FUN_00636850(&local_14); // some condition check, maybe "isValidNumber"
    if (iVar2 == 0) goto LAB_0063192b;
    local_10 = 3;
    local_c = local_14;
    piVar3 = &local_10; // redirect to local variable
  }
  local_14 = (float)piVar3[1]; // get value from entry (or local)
  if (local_14 == DAT_00e2b05c) { // compare to sentinel value (e.g., -1.0f)
    while (((piVar3 = *(int **)(thisPtr + 0xc), *(int **)(thisPtr + 8) <= piVar3 ||
            (piVar3 == (int *)0x0)) ||
           ((*piVar3 != 3 && ((*piVar3 != 4 || (iVar2 = FUN_00636850(&local_10), iVar2 == 0))))))) {
      FUN_00627ac0(PTR_s_number_00e2a8a8); // debug print "number"
LAB_0063192b:
      local_14 = 0.0;
    }
  }
  puVar1 = *(undefined4 **)(thisPtr + 8); // write pointer
  *puVar1 = 3; // output type = 3
  puVar1[1] = SQRT(local_14); // output value = sqrt(input)
  *(int *)(thisPtr + 8) = *(int *)(thisPtr + 8) + 8; // advance write pointer
  return 1;
}