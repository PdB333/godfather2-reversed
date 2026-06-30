// FUNC_NAME: LuaScriptEngine::stringFindReplace
undefined4 LuaScriptEngine::stringFindReplace(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  code *pcVar3;
  int iVar4;
  int *piVar5;
  undefined1 *puVar6;
  int iVar7;
  undefined4 uVar8;
  int *piVar9;
  float in_XMM0_Da;
  float fVar10;
  undefined1 *puStack_344;
  int iStack_340;
  int local_33c;
  undefined1 *local_334;
  char *pcStack_330;
  undefined1 *puStack_328;
  undefined4 uStack_324;
  int iStack_320;
  undefined1 auStack_31c [512];
  undefined1 auStack_11c [4];
  undefined1 *puStack_118;
  undefined1 *puStack_114;
  int iStack_110;
  undefined4 uStack_10c;
  
  piVar9 = *(int **)(param_1 + 0xc); // +0x0C: current instruction pointer
  if ((piVar9 < *(int **)(param_1 + 8)) && (piVar9 != (int *)0x0)) {
    if (*piVar9 == 4) { // OP_STRING
      puStack_344 = (undefined1 *)(piVar9[1] + 0x10); // string data offset
    }
    else {
      iVar7 = FUN_00633990(param_1); // getStringConstant
      if (iVar7 == 0) {
        puStack_344 = (undefined1 *)0x0;
      }
      else {
        puStack_344 = (undefined1 *)(piVar9[1] + 0x10);
      }
      if (*(uint *)(*(int *)(param_1 + 0x10) + 0x20) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x24))
      {
        FUN_00627360(); // growStack
      }
    }
    local_334 = puStack_344;
    if (puStack_344 == (undefined1 *)0x0) goto LAB_0062cbb2;
  }
  else {
LAB_0062cbb2:
    puStack_344 = (undefined1 *)0x1;
    FUN_00627ac0(PTR_s_string_00e2a8ac); // error: "string expected"
  }
  piVar9 = *(int **)(param_1 + 0xc);
  if ((piVar9 < *(int **)(param_1 + 8)) && (piVar9 != (int *)0x0)) {
    if (*piVar9 == 4) {
      local_33c = *(int *)(piVar9[1] + 0xc); // string length
    }
    else {
      iVar7 = FUN_00633990(param_1);
      if (iVar7 == 0) {
        local_33c = 0;
      }
      else {
        local_33c = *(int *)(piVar9[1] + 0xc);
      }
    }
  }
  else {
    local_33c = 0;
  }
  iVar7 = *(int *)(param_1 + 0xc);
  piVar9 = (int *)(iVar7 + 8);
  if ((piVar9 < *(int **)(param_1 + 8)) && (piVar9 != (int *)0x0)) {
    if (*piVar9 == 4) {
      pcStack_330 = (char *)(*(int *)(iVar7 + 0xc) + 0x10); // second string arg
    }
    else {
      iVar4 = FUN_00633990(param_1);
      if (iVar4 == 0) {
        pcStack_330 = (char *)0x0;
      }
      else {
        pcStack_330 = (char *)(*(int *)(iVar7 + 0xc) + 0x10);
      }
      if (*(uint *)(*(int *)(param_1 + 0x10) + 0x20) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x24))
      {
        FUN_00627360();
      }
    }
    if (pcStack_330 != (char *)0x0) goto LAB_0062cc69;
  }
  pcStack_330 = (char *)0x2;
  FUN_00627ac0(PTR_s_string_00e2a8ac);
LAB_0062cc69:
  fVar10 = (float)(local_33c + 1);
  if (local_33c + 1 < 0) {
    fVar10 = fVar10 + DAT_00e44578;
  }
  piVar9 = (int *)(*(int *)(param_1 + 0xc) + 0x18); // +0x18: optional third arg (max count)
  if (((piVar9 < *(int **)(param_1 + 8)) && (piVar9 != (int *)0x0)) && (0 < *piVar9)) {
    FUN_00628080(); // getNumberArg
    fVar10 = in_XMM0_Da;
  }
  cVar1 = *pcStack_330;
  if (cVar1 == '^') {
    pcStack_330 = pcStack_330 + 1; // skip leading caret for regex
  }
  piVar9 = *(int **)(param_1 + 8);
  iStack_340 = 0;
  if ((((int)((int)piVar9 - *(int *)(param_1 + 0xc) & 0xfffffff8U) < 0x18) ||
      (piVar5 = (int *)(*(int *)(param_1 + 0xc) + 0x10), piVar9 <= piVar5)) ||
     (((piVar5 == (int *)0x0 || ((*piVar5 != 4 && (*piVar5 != 3)))) &&
      ((piVar9 <= piVar5 || ((piVar5 == (int *)0x0 || (*piVar5 != 6)))))))) {
    FUN_00627a20(param_1,3,"string or function expected");
    pcVar3 = (code *)swi(3);
    uVar8 = (*pcVar3)();
    return uVar8;
  }
  puStack_328 = auStack_31c; // output buffer
  puStack_118 = local_334; // source string start
  puStack_114 = local_334 + local_33c; // source string end
  iStack_320 = param_1;
  uStack_324 = 0;
  iStack_110 = param_1;
  if ((int)fVar10 < 1) {
LAB_0062ce1e:
    FUN_00628b20(puStack_344,(int)puStack_114 - (int)puStack_344); // copy remaining
    FUN_00628940(); // pushStringResult
    FUN_00626460(); // advanceInstructionPointer
    puVar2 = *(undefined4 **)(param_1 + 8);
    *puVar2 = 3; // OP_NUMBER
    puVar2[1] = (float)iStack_340; // replacement count
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
    return 2;
  }
  do {
    uStack_10c = 0;
    puVar6 = (undefined1 *)FUN_0062bd60(&puStack_118,puStack_344,pcStack_330); // findSubstring
    if (puVar6 == (undefined1 *)0x0) {
LAB_0062cdba:
      if (puStack_114 <= puStack_344) goto LAB_0062ce1e;
      if (auStack_11c <= puStack_328) {
        iVar7 = FUN_00628940(); // growOutputBuffer
        if (iVar7 != 0) {
          FUN_006289a0(&puStack_328);
        }
      }
      *puStack_328 = *puStack_344;
      puStack_328 = puStack_328 + 1;
      puVar6 = puStack_344 + 1;
    }
    else {
      iStack_340 = iStack_340 + 1;
      FUN_0062c970(&puStack_118,&puStack_328,puStack_344,puVar6); // replaceMatch
      if (puVar6 <= puStack_344) goto LAB_0062cdba;
    }
    puStack_344 = puVar6;
    if ((cVar1 == '^') || ((int)fVar10 <= iStack_340)) goto LAB_0062ce1e;
  } while( true );
}