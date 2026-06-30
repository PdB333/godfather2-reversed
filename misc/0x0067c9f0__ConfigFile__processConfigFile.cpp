// FUNC_NAME: ConfigFile::processConfigFile
undefined4 ConfigFile::processConfigFile(char *param_1, undefined4 param_2)

{
  char cVar1;
  int *piVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined1 *local_164;
  undefined1 *local_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  code *local_154;
  undefined1 *local_150;
  undefined4 local_14c;
  undefined4 local_148;
  code *local_144;
  int local_140 [3];
  code *local_134;
  undefined1 *puStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  code *pcStack_124;
  int local_120 [3];
  code *pcStack_114;
  undefined1 *puStack_110;
  code *pcStack_104;
  undefined1 auStack_100 [256];
  
  local_164 = (undefined1 *)0x0;
  iVar4 = 0;
  local_140[0] = 0;
  local_140[1] = 0;
  local_140[2] = 0;
  local_134 = (code *)0x0;
  if (*param_1 == '#') {
    // Comment line - skip
    FUN_004d3bc0(param_1);
    FUN_004d53a0(0x23);
    local_150 = (undefined1 *)0x0;
    local_14c = 0;
    local_148 = 0;
    local_144 = (code *)0x0;
    iVar4 = FUN_004d46f0(&DAT_00e2f04c,0);
    if (iVar4 == 0) {
      piVar2 = local_120;
    }
    else {
      piVar2 = (int *)FUN_004d5170(&local_160,&DAT_00e2f04c);
    }
    FUN_004d3e20(piVar2);
    if ((iVar4 != 0) && (local_160 != (undefined1 *)0x0)) {
      (*local_154)(local_160);
    }
    FUN_004d5570();
    FUN_004d53a0(0x5c);
    puVar3 = local_150;
    if (local_150 == (undefined1 *)0x0) {
      puVar3 = &DAT_0120546e;
    }
    iVar4 = FUN_00412740(puVar3);
    FUN_004d3e20(local_120);
    if (local_150 != (undefined1 *)0x0) {
      (*local_144)(local_150);
    }
    if (local_120[0] != 0) {
      (*pcStack_114)(local_120[0]);
    }
  }
  else {
    FUN_004d4300(param_1);
  }
  FUN_004d4300(&DAT_00e2f048);
  puStack_130 = (undefined1 *)0x0;
  uStack_12c = 0;
  uStack_128 = 0;
  pcStack_124 = (code *)0x0;
  FUN_004d3bc0(param_2);
  local_164 = puStack_110;
  if (puStack_110 == (undefined1 *)0x0) {
    local_164 = &DAT_0120546e;
  }
  cVar1 = FUN_004d6260(auStack_100,&local_164,&DAT_00d57620,0x100,0);
  if (cVar1 != '\\0') {
    do {
      FUN_004d3e20(local_140);
      FUN_004d4300(auStack_100);
      local_160 = (undefined1 *)0x0;
      uStack_15c = 0;
      uStack_158 = 0;
      local_154 = (code *)0x0;
      puVar3 = puStack_130;
      if (puStack_130 == (undefined1 *)0x0) {
        puVar3 = &DAT_0120546e;
      }
      FUN_00402e90(&local_160,puVar3,iVar4 != 0);
      puVar3 = local_160;
      if (local_160 == (undefined1 *)0x0) {
        puVar3 = &DAT_0120546e;
      }
      FUN_00411c70(puVar3,iVar4);
      if (local_160 != (undefined1 *)0x0) {
        (*local_154)(local_160);
      }
      cVar1 = FUN_004d6260(auStack_100,&local_164,&DAT_00d57620,0x100,0);
    } while (cVar1 != '\\0');
  }
  if (puStack_110 != (undefined1 *)0x0) {
    (*pcStack_104)(puStack_110);
  }
  if (puStack_130 != (undefined1 *)0x0) {
    (*pcStack_124)(puStack_130);
  }
  if (local_140[0] != 0) {
    (*local_134)(local_140[0]);
  }
  return 1;
}