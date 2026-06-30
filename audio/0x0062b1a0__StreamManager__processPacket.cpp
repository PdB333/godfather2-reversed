// FUNC_NAME: StreamManager::processPacket
undefined4 StreamManager::processPacket(int this_ptr)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  float fStack_22c;
  int local_228;
  undefined4 local_224;
  int iStack_220;
  float fStack_21c;
  undefined1 *puStack_218;
  undefined4 uStack_214;
  int iStack_210;
  undefined1 auStack_20c [520];
  
  piVar1 = *(int **)(this_ptr + 0xc);  // +0x0C: current buffer pointer?
  if ((piVar1 < *(int **)(this_ptr + 8)) && (piVar1 != (int *)0x0)) {
    if (*piVar1 == 4) {
      iVar3 = piVar1[1] + 0x10;
    }
    else {
      iVar3 = FUN_00633990(this_ptr);
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = piVar1[1] + 0x10;
      }
      if (*(uint *)(*(int *)(this_ptr + 0x10) + 0x20) <= *(uint *)(*(int *)(this_ptr + 0x10) + 0x24))
      {
        FUN_00627360();
      }
    }
    local_228 = iVar3;
    if (iVar3 != 0) goto LAB_0062b215;
  }
  iVar3 = 1;
  FUN_00627ac0(PTR_s_string_00e2a8ac);
LAB_0062b215:
  piVar1 = *(int **)(this_ptr + 0xc);
  if ((piVar1 < *(int **)(this_ptr + 8)) && (piVar1 != (int *)0x0)) {
    if (*piVar1 == 4) {
      local_224 = *(undefined4 *)(piVar1[1] + 0xc);
    }
    else {
      iVar2 = FUN_00633990(this_ptr);
      if (iVar2 == 0) {
        local_224 = 0;
      }
      else {
        local_224 = *(undefined4 *)(piVar1[1] + 0xc);
      }
    }
  }
  else {
    local_224 = 0;
  }
  piVar1 = (int *)(*(int *)(this_ptr + 0xc) + 8);
  if (*(int **)(this_ptr + 8) <= piVar1) goto LAB_0062b309;
  if (piVar1 == (int *)0x0) goto LAB_0062b309;
  if (*piVar1 != 3) {
    if (*piVar1 != 4) goto LAB_0062b309;
    iVar2 = FUN_00636850(&fStack_22c);
    if (iVar2 == 0) goto LAB_0062b309;
    iStack_220 = 3;
    fStack_21c = fStack_22c;
    piVar1 = &iStack_220;
  }
  fStack_22c = (float)piVar1[1];
  if (fStack_22c == DAT_00e2b05c) {
    while (((piVar1 = (int *)(*(int *)(this_ptr + 0xc) + 8), *(int **)(this_ptr + 8) <= piVar1 ||
            (piVar1 == (int *)0x0)) ||
           ((*piVar1 != 3 && ((*piVar1 != 4 || (iVar2 = FUN_00636850(&iStack_220), iVar2 == 0)))))))
    {
      iVar3 = 2;
      FUN_00627ac0(PTR_s_number_00e2a8a8);
LAB_0062b309:
      fStack_22c = 0.0;
    }
  }
  puStack_218 = auStack_20c;
  uStack_214 = 0;
  iStack_210 = this_ptr;
  for (iVar2 = (int)fStack_22c; 0 < iVar2; iVar2 = iVar2 + -1) {
    FUN_00628b20(iVar3,local_224);
    iVar3 = local_228;
  }
  FUN_00628940();
  FUN_00626460();
  return 1;
}